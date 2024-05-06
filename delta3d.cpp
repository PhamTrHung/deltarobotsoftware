#include "delta3d.h"

/****************************************************************************
  void Rotate120 : quay vector 120 do theo chieu nguoc chieu kim dong ho
*****************************************************************************/
Vector3 Delta3D::Rotate120(Vector3 vector)
{
    Vector3 t = vector;
    t.x = vector.x * cos120 - vector.y * sin120;
    t.y = vector.x * sin120 + vector.y * cos120;
    t.z = vector.z;
    return t;
}
/****************************************************************************
  void Rotate240 : quay vector 240 do theo chieu nguoc chieu kim dong ho
*****************************************************************************/
Vector3 Delta3D::Rotate240(Vector3 vector)
{
    Vector3 t = vector;
    t.x = vector.x * cos120 + vector.y * sin120;
    t.y = -vector.x * sin120 + vector.y * cos120;
    t.z = vector.z;
    return t;
}

float Delta3D::r2(float in)
{
    return in * in;
}
/****************************************************************************
  void SetEEParam : dat lai vi tri cua End Effector va cap nhat luon gia
                       tri cua cac ankleVertex
*****************************************************************************/
void Delta3D::SetEEParam(DeltaParameter* data, Vector3 dstPos)
{
    data->eePos = dstPos;
    data->ankleVertex[0].Set(dstPos.x, dstPos.y - data->rEE, dstPos.z);
    // ankleVertex[1] = ( eePos.x + s120 * rEE, eePos.y - c120 * rEE, eePos.z)
    data->ankleVertex[1].Set(dstPos.x + sin120 * data->rEE, dstPos.y - cos120 * data->rEE, dstPos.z);
    // ankleVertex[2] = ( eePos.x + s240 * rEE, eePos.y - c240 * rEE, eePos.z) & C120 = c240, s120 = -s240
    data->ankleVertex[2].Set(dstPos.x - sin120 * data->rEE, dstPos.y - cos120 * data->rEE, dstPos.z);
}
/****************************************************************************
  function IK_Find_Angles : tinh cac goc theta tuong ung voi toa do x, y, z
    return 0 neu tao do nam trong vung hoat dong
    return 1 neu tao do nam ngoai vung hoat dong
    result_array la
*****************************************************************************/
/****************************************************************************
  function  IK_Find_Angles : implement inverse kinematics, calculate angle from
                            x, y, z
            return 0 if EE position is in working zone
            return 1 otherwise
/****************************************************************************/
uint8_t Delta3D::IK_Find_Angles(float x, float y, float z, DeltaParameter* src_dbot, DeltaParameter* d_bot)
{
    // init result data
    *d_bot = *src_dbot;
    SetEEParam(d_bot, Vector3(x, y, z));

    Vector3 dstOriginPos = d_bot->eePos;

    for (uint8_t i = 0; i < 3; i++) {
        if (i == 1)
            // Xoay goc toa do 120 xac dinh toa do EE theo he truc moi
            dstOriginPos = Rotate240(d_bot->eePos);
        else if (i == 2)
            // Xoay goc toa do 240 xac dinh toa do EE theo he truc moi
            dstOriginPos = Rotate120(d_bot->eePos);

        // Xac dinh toa do diem ankles C1( xEE, yEE - rEE, zEE) => C1'( 0, yEE - rEE, zEE)
        dstOriginPos.y -= d_bot->rEE;
        // Tinh do dai doan re' = re^2 - xEE
        float re1_sqr = r2(d_bot->re) - r2(dstOriginPos.x);
        float re1 = sqrt(re1_sqr);
        // Tinh khoang cach tu hip D1 toi C1'
        float length_sqr = r2(d_bot->hipVertex[0].y - dstOriginPos.y) + r2(dstOriginPos.z);
        float length = sqrt(length_sqr);
        // Kiem tra EE position co nam trong vung lam viec hay ko
        if ((length > (re1 + d_bot->rf)) || (length < abs(re1 - d_bot->rf))) {
            qDebug() << "Out of bound";
            return 1;
        }
        // Tim alpha va h
        float alpha = -(length_sqr + r2(d_bot->rf) - re1_sqr) / (2 * length);
        float h = -sqrt(r2(d_bot->rf) - r2(alpha));

        // Xac dinh goc quay cua he toa do gan voi duong thang noi tu hip D1 toi C1'
        float cgamma = -dstOriginPos.z / length;
        float sgamma = (dstOriginPos.y + d_bot->rBase) / length;

        float tempY = cgamma * h - sgamma * alpha;
        float tempZ = sgamma * h + cgamma * alpha;

        d_bot->theta[i] = atan2(tempZ, tempY);        // rad

        d_bot->kneeVertex[i].Set(0, tempY + d_bot->hipVertex[0].y, tempZ);
        if (i == 1)
            d_bot->kneeVertex[i] = Rotate120(d_bot->kneeVertex[i]);
        else if (i == 2)
            d_bot->kneeVertex[i] = Rotate240(d_bot->kneeVertex[i]);
    }

    return 0;
}
/****************************************************************************
  function FK_Find_Position : tinh toa do end effector tuong ung voi goc theta
    return 0 neu tao do nam trong vung hoat dong
    return 1 neu tao do nam ngoai vung hoat dong
    return d_bot : thong tin ve vi tri cac co cau
*****************************************************************************/
/****************************************************************************
  function FK_Find_Position : implement inverse kinematics
    return 0 if EE position is in working zone
    return 1 otherwise
    return d_bot : copy of new delta model
*****************************************************************************/
uint8_t Delta3D::FK_Find_Position(float theta1, float theta2, float theta3, DeltaParameter* src_dbot, DeltaParameter* d_bot)
{
    // init d_bot
    *d_bot = *(src_dbot);
    d_bot->theta[0] = theta1;
    d_bot->theta[1] = theta2;
    d_bot->theta[2] = theta3;

    // calculate knee 1
    d_bot->kneeVertex[0].x = 0;
    d_bot->kneeVertex[0].y = d_bot->rf * cos(theta1) - d_bot->rBase;
    d_bot->kneeVertex[0].z = d_bot->rf * sin(theta1);

    // calculate knee 2
    float k = -d_bot->rf * cos(theta2) + d_bot->rBase;
    d_bot->kneeVertex[1].x = k * cos30;
    d_bot->kneeVertex[1].y = k * sin30;
    d_bot->kneeVertex[1].z = d_bot->rf * sin(theta2);

    // calculate knee 2
    k = -d_bot->rf * cos(theta3) + d_bot->rBase;
    d_bot->kneeVertex[2].x = -k * cos30;
    d_bot->kneeVertex[2].y = k * sin30;
    d_bot->kneeVertex[2].z = d_bot->rf * sin(theta3);

    // calc x', y', z'
    float y1 = d_bot->rEE + d_bot->kneeVertex[0].y;
    float z1 = d_bot->kneeVertex[0].z;

    float x2 = -sin120 * d_bot->rEE + d_bot->kneeVertex[1].x;
    float y2 = cos120 * d_bot->rEE + d_bot->kneeVertex[1].y;
    float z2 = d_bot->kneeVertex[1].z;
    float x3 = sin120 * d_bot->rEE + d_bot->kneeVertex[2].x;
    float y3 = cos120 * d_bot->rEE + d_bot->kneeVertex[2].y;
    float z3 = d_bot->kneeVertex[2].z;

    float dnm = (y2 - y1) * x3 - (y3 - y1) * x2;

    float w1 = y1 * y1 + z1 * z1;
    float w2 = x2 * x2 + y2 * y2 + z2 * z2;
    float w3 = x3 * x3 + y3 * y3 + z3 * z3;

    // x = (a1*z + b1)/dnm
    float a1 = (z2 - z1) * (y3 - y1) - (z3 - z1) * (y2 - y1);
    float b1 = -((w2 - w1) * (y3 - y1) - (w3 - w1) * (y2 - y1)) / 2.0;

    // y = (a2*z + b2)/dnm;
    float a2 = -(z2 - z1) * x3 + (z3 - z1) * x2;
    float b2 = ((w2 - w1) * x3 - (w3 - w1) * x2) / 2.0;

    // a*z^2 + b*z + c = 0
    float a = a1 * a1 + a2 * a2 + dnm * dnm;
    float b = 2 * (a1 * b1 + a2 * (b2 - y1 * dnm) - z1 * dnm * dnm);
    float c = (b2 - y1 * dnm) * (b2 - y1 * dnm) + b1 * b1 + dnm * dnm * (z1 * z1 - r2(d_bot->re));

    // discriminant
    float d = b * b - (float)4.0 * a * c;

    if (d < 0)
        return 1; // non-existing point

    float z0 = -(float)0.5 * (b + sqrt(d)) / a;
    float x0 = (a1 * z0 + b1) / dnm;
    float y0 = (a2 * z0 + b2) / dnm;

    // set EE position & re-calc ankles position
    SetEEParam(d_bot, Vector3(x0, y0, z0));


    return 0;
}

Delta3D::Delta3D(QOpenGLWidget* parent) :
    QOpenGLWidget(parent)
{
    myDelta = new DeltaParameter();
    testDelta = new DeltaParameter();
}
/****************************************************************************
  Du lieu vao la rBase va rEE, suy ra f/2 = rBase/tan30, tinh ra dc 2 dinh cua Base
  (song song voi Ox) va 1 nam tren 0y. Va tinh dc toa do cua 3 hip.

  rBase and rEE are inputs which are radius of Base and radius of End plate,
  f/2 = rBase/tan30, initilize the model with 3 vertices of the base ( 2 of them
  parallel with axis Ox, the last one on axis Oy), and coordinates of 3 hips.
*****************************************************************************/
Delta3D::Delta3D(float f, float e, float rBase, float rEE, float rf, float re)
{
    // init delta data
    myDelta = new DeltaParameter();
    testDelta = new DeltaParameter();

    myDelta->rf = rf;
    myDelta->re = re;

    if (f == 0) {
        myDelta->rBase = rBase;
        myDelta->rEE = rEE;
        myDelta->f = 2 * rBase / tan30;
        myDelta->e = 2 * rEE / tan30;
    }
    else {
        myDelta->f = f;
        myDelta->e = e;
        myDelta->rBase = f * 0.5 * tan30;
        myDelta->rEE = e * 0.5 * tan30;
    }

    // 3 coordinates of base
    rBase = myDelta->rBase;
    myDelta->baseVertex[0].Set(-rBase / tan30, -rBase, 0);
    myDelta->baseVertex[1].Set(rBase / tan30, -rBase, 0);
    myDelta->baseVertex[2].Set(0, rBase / sin30, 0);

    // 3 coordinates of hip
    myDelta->hipVertex[0].Set(0, -rBase, 0);
    myDelta->hipVertex[1] = Rotate120(myDelta->hipVertex[0]);
    myDelta->hipVertex[2] = Rotate240(myDelta->hipVertex[0]);


}
/****************************************************************************
  void Draw : draw Delta model
*****************************************************************************/
void Delta3D::Draw()
{
    uint8_t i;

    glBegin(GL_TRIANGLES);
    // draw base
    glColor3f(0.2, 0.1, 0.8);

    for (i = 0; i < 3; i++) {
        glVertex3f(this->myDelta->baseVertex[i].x,
            this->myDelta->baseVertex[i].y,
            this->myDelta->baseVertex[i].z);
    }

    // draw end effector
    glColor3f(0.2, 0.1, 0.8);
    for (i = 0; i < 3; i++) {
        glVertex3f(this->myDelta->ankleVertex[i].x,
            this->myDelta->ankleVertex[i].y,
            this->myDelta->ankleVertex[i].z);
    }
    glEnd();

    // draw 3 legs
    for (i = 0; i < 3; i++) {
        glBegin(GL_LINES);
        glColor3f(0.4, 0.8, 0.1);
        glVertex3f(this->myDelta->hipVertex[i].x,
            this->myDelta->hipVertex[i].y,
            this->myDelta->hipVertex[i].z);
        glVertex3f(this->myDelta->kneeVertex[i].x,
            this->myDelta->kneeVertex[i].y,
            this->myDelta->kneeVertex[i].z);


        glVertex3f(this->myDelta->kneeVertex[i].x + 10,
            this->myDelta->kneeVertex[i].y,
            this->myDelta->kneeVertex[i].z);
        glVertex3f(this->myDelta->kneeVertex[i].x - 10,
            this->myDelta->kneeVertex[i].y,
            this->myDelta->kneeVertex[i].z);


        glVertex3f(this->myDelta->kneeVertex[i].x + 10,
            this->myDelta->kneeVertex[i].y,
            this->myDelta->kneeVertex[i].z);
        glVertex3f(this->myDelta->ankleVertex[i].x + 10,
            this->myDelta->ankleVertex[i].y,
            this->myDelta->ankleVertex[i].z);


        glVertex3f(this->myDelta->kneeVertex[i].x - 10,
            this->myDelta->kneeVertex[i].y,
            this->myDelta->kneeVertex[i].z);
        glVertex3f(this->myDelta->ankleVertex[i].x - 10,
            this->myDelta->ankleVertex[i].y,
            this->myDelta->ankleVertex[i].z);


        glVertex3f(this->myDelta->ankleVertex[i].x + 10,
            this->myDelta->ankleVertex[i].y,
            this->myDelta->ankleVertex[i].z);
        glVertex3f(this->myDelta->ankleVertex[i].x - 10,
            this->myDelta->ankleVertex[i].y,
            this->myDelta->ankleVertex[i].z);

        glEnd();

    }

    for (i = 0; i < 3; ++i) {

        centerSphere[0] = this->myDelta->kneeVertex[i].x + 10;
        centerSphere[1] = this->myDelta->kneeVertex[i].y;
        centerSphere[2] = this->myDelta->kneeVertex[i].z;
        drawSphere(centerSphere, 5.0f, 50, 50);

        centerSphere[0] = this->myDelta->kneeVertex[i].x - 10;
        centerSphere[1] = this->myDelta->kneeVertex[i].y;
        centerSphere[2] = this->myDelta->kneeVertex[i].z;
        drawSphere(centerSphere, 5.0f, 50, 50);

        centerSphere[0] = this->myDelta->ankleVertex[i].x + 10;
        centerSphere[1] = this->myDelta->ankleVertex[i].y;
        centerSphere[2] = this->myDelta->ankleVertex[i].z;
        drawSphere(centerSphere, 5.0f, 50, 50);

        centerSphere[0] = this->myDelta->ankleVertex[i].x - 10;
        centerSphere[1] = this->myDelta->ankleVertex[i].y;
        centerSphere[2] = this->myDelta->ankleVertex[i].z;
        drawSphere(centerSphere, 5.0f, 50, 50);

        /*centerSphere[0] = this->myDelta->hipVertex[i].x;
        centerSphere[1] = this->myDelta->hipVertex[i].y;
        centerSphere[2] = 0;
        drawSphere(centerSphere, 5.0f, 50, 50);*/
    }
}

void Delta3D::drawSphere(const GLfloat center[3], GLfloat radius, GLint slices, GLint stacks) {

    for (int i = 0; i < slices; ++i) {
        float theta1 = i * 2.0 * M_PI / slices;
        float theta2 = (i + 1) * 2.0 * M_PI / slices;

        glBegin(GL_TRIANGLE_STRIP);
        glColor3ub(0, 154, 255);
        for (int j = 0; j <= stacks; ++j) {
            float phi = j * M_PI / stacks;
            float phi2 = (j + 1) * M_PI / stacks;

            float x1 = center[0] + radius * sin(phi) * cos(theta1);
            float y1 = center[1] + radius * sin(phi) * sin(theta1);
            float z1 = center[2] + radius * cos(phi);

            float x2 = center[0] + radius * sin(phi2) * cos(theta1);
            float y2 = center[1] + radius * sin(phi2) * sin(theta1);
            float z2 = center[2] + radius * cos(phi2);

            float x3 = center[0] + radius * sin(phi) * cos(theta2);
            float y3 = center[1] + radius * sin(phi) * sin(theta2);
            float z3 = center[2] + radius * cos(phi);

            float x4 = center[0] + radius * sin(phi2) * cos(theta2);
            float y4 = center[1] + radius * sin(phi2) * sin(theta2);
            float z4 = center[2] + radius * cos(phi2);

            glNormal3f(x1 - center[0], y1 - center[1], z1 - center[2]);
            glVertex3f(x1, y1, z1);
            glNormal3f(x2 - center[0], y2 - center[1], z2 - center[2]);
            glVertex3f(x2, y2, z2);
            glNormal3f(x3 - center[0], y3 - center[1], z3 - center[2]);
            glVertex3f(x3, y3, z3);
            glNormal3f(x4 - center[0], y4 - center[1], z4 - center[2]);
            glVertex3f(x4, y4, z4);
        }
        glEnd();
    }
}

void Delta3D::drawCylinder(const GLfloat start[3], const GLfloat end[3], GLfloat radius) {
    const int numSegments = 50; // Number of segments for the circumference

    // Calculate the direction vector from start to end
    GLfloat direction[3] = { end[0] - start[0], end[1] - start[1], end[2] - start[2] };
    GLfloat length = sqrt(direction[0] * direction[0] + direction[1] * direction[1] + direction[2] * direction[2]);

    // Calculate the rotation angles to align the cylinder with the direction vector
    GLfloat angleX = -atan2(direction[0], direction[1]);
    //GLfloat angleY = atan2(direction[0], direction[2]);

    // Draw the cylinder
    glPushMatrix();
    glTranslatef((start[0] + end[0]) * 0.5f, (start[1] + end[1]) * 0.5f, (start[2] + end[2]) * 0.5f);
    glRotatef(angleX * 180 / M_PI, 0.0, 0.0, 1.0);
    //glRotatef(angleY * 180 / M_PI, 0.0, 1.0, 0.0);

    GLfloat segmentAngle = 2.0 * M_PI / numSegments;
    glBegin(GL_TRIANGLES);
    glColor3f(0.5, 0.5, 0.4);
    for (int i = 0; i < numSegments; ++i) {
        GLfloat angle1 = i * segmentAngle;
        GLfloat angle2 = (i + 1) * segmentAngle;

        GLfloat x1 = radius * cos(angle1);
        GLfloat y1 = length * 0.5f;
        GLfloat z1 = radius * sin(angle1);

        GLfloat x2 = radius * cos(angle2);
        GLfloat y2 = length * 0.5f;
        GLfloat z2 = radius * sin(angle2);

        GLfloat x3 = radius * cos(angle1);
        GLfloat y3 = -length * 0.5f;
        GLfloat z3 = radius * sin(angle1);

        GLfloat x4 = radius * cos(angle2);
        GLfloat y4 = -length * 0.5f;
        GLfloat z4 = radius * sin(angle2);

        glVertex3f(x1, y1, z1);
        glVertex3f(x2, y2, z2);
        glVertex3f(x4, y4, z4);

        glVertex3f(x1, y1, z1);
        glVertex3f(x4, y4, z4);
        glVertex3f(x3, y3, z3);
    }
    glEnd();

    glPopMatrix();
}




/****************************************************************************
  function Clone : copy new parameter into myDelta
*****************************************************************************/
void Delta3D::Clone(DeltaParameter newParam)
{
    *(this->myDelta) = newParam;
}
/****************************************************************************
  function GetThetaAngle : return gia tri theta[n]
*****************************************************************************/
float Delta3D::GetThetaAngle(uint8_t n)
{
    if (n >= 0 && n <= 2)
        return myDelta->theta[n];
    else
        return 0;
}
/****************************************************************************/
/*  function Set_EE_Position : tinh goc quay theta tuong ung voi vi tri EE  */
/*        input : Vector3 - Toa do moi cua EE                               */
/*        output: float* theta-Goc quay cua dong co tuong ung voi truc toa  */
/*                do cua base                                               */
/*        update = 1 : cap nhat lai data cho myDelta                        */
/*        return 0 neu tao do nam trong vung hoat dong                      */
/*        return 1 neu tao do nam ngoai vung hoat dong                      */
/****************************************************************************/
/****************************************************************************/
/*  function Set_EE_Position : update configuration from new position of EE */
/*        input : Vector3 - coordinates of new position EE                  */
/*        output: float* theta - the angle of 3 legs                        */
/*        update = 1 : flag update myDelta with new config                  */
/*        return 0 if EE position is in working zone                        */
/*        return 1 otherwise                                                */
/****************************************************************************/
uint8_t Delta3D::Set_EE_Position(Vector3 dstEEPos, float* thetaOutput, uint8_t update)
{
    if (IK_Find_Angles(dstEEPos.x, dstEEPos.y, dstEEPos.z, myDelta, testDelta) == 0) {
        if (thetaOutput != nullptr)
        {
            thetaOutput[0] = testDelta->theta[0];
            thetaOutput[1] = testDelta->theta[1];
            thetaOutput[2] = testDelta->theta[2];
        }

        if (update) {
            *myDelta = *testDelta;
            UpdateDParam(*myDelta);
        }
    }
    else {
        return 1;
    }
    return 0;
}
/****************************************************************************/
/*  function Set_Hips_Angles : xac dinh vi tri EE tuong ung voi goc quay dc */
/*        input : array theta - Goc quay cua dong co                        */
/*        output: vector3 - vi tri EE moi                                   */
/*        update = 1 : cap nhat lai data cho myDelta                        */
/*        return 0 neu tao do nam trong vung hoat dong                      */
/*        return 1 neu tao do nam ngoai vung hoat dong                      */
/****************************************************************************/
/****************************************************************************/
/*  function Set_Hips_Angles :  forward kinematic find EE based on          */
/*                              config of legs                              */
/*        input : array theta - config of legs                              */
/*        output: vector3 - new position of EE                              */
/*        update = 1 : flag update myDelta with new config                  */
/*        return 0 if EE position is in working zone                        */
/*        return 1 otherwise                                                */
/****************************************************************************/
uint8_t Delta3D::Set_Hips_Angles(Vector3* dstEEPos, float* theta, uint8_t update)
{
    if (FK_Find_Position(theta[0], theta[1], theta[2], myDelta, testDelta) == 0) {
        if (dstEEPos != nullptr)
            *dstEEPos = myDelta->eePos;
        if (update) {
            *myDelta = *testDelta;
            UpdateDParam(*myDelta);
        }
    }
    else {
        return 1;
    }
    return 0;
}


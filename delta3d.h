#pragma once

#include <qopenglwidget.h>
#include <qopenglfunctions.h>
#include <qvector3d.h>
#include "vector3.h"
#include <gl/GL.h>

// trigonometric constants
const float sqrt3 = sqrt(3.0);
const float sin120 = sqrt3 / 2.0;
const float cos120 = -0.5;
const float tan60 = sqrt3;
const float sin30 = 0.5;
const float cos30 = sqrt(3) / 2;
const float tan30 = 1 / sqrt3;

class DeltaParameter
{
public:
    // variable declare
    Vector3 baseVertex[3], hipVertex[3];
    Vector3 kneeVertex[3], ankleVertex[3];
    Vector3 eeVertex[3];
    Vector3 eePos;
    float   theta[3];
    float   f, e, rf, re, rBase, rEE;
};

class Delta3D : public QOpenGLWidget, public QOpenGLFunctions
{
    Q_OBJECT

public:

    DeltaParameter* myDelta;
    DeltaParameter* testDelta;

    // function declare
    Vector3 Rotate120(Vector3);
    Vector3 Rotate240(Vector3);
    float   r2(float);
    void    SetEEParam(DeltaParameter* data, Vector3 dstPos);
    uint8_t IK_Find_Angles(float x, float y, float z, DeltaParameter* src_dbot, DeltaParameter* d_bot);
    uint8_t FK_Find_Position(float theta1, float theta2, float theta3, DeltaParameter* src_dbot, DeltaParameter* d_bot);

public:
    explicit Delta3D(QOpenGLWidget* parent = 0);
    Delta3D(float f, float e, float rBase, float rEE, float rf, float re);     // overload
    void Draw();
    void Clone(DeltaParameter);
    float GetThetaAngle(uint8_t);
    uint8_t Set_EE_Position(Vector3 dstEEPos, float* thetaOutput, uint8_t update);
    uint8_t Set_Hips_Angles(Vector3* dstEEPos, float* theta, uint8_t update);

    void drawCylinder(const GLfloat start[3], const GLfloat end[3], GLfloat radius);
    GLfloat start[3], end[3];
    void drawSphere(const GLfloat center[3], GLfloat radius, GLint slices, GLint stacks);
    GLfloat centerSphere[3];

signals:
    void UpdateDParam(DeltaParameter);

};

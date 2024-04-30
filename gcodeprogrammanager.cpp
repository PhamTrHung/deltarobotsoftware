#include "gcodeprogrammanager.h"
#include <QDebug>

GcodeProgramManager::GcodeProgramManager(QObject *parent)
    : QObject{parent}
{}

GcodeProgramManager::~GcodeProgramManager()
{

}

GcodeProgramManager::GcodeProgramManager(QTextEdit *gcodeArea, QPushButton *btnExecute, ConnectionManager *deltaSerialPort)
{
    teGcodeArea = gcodeArea;
    btnExecuteGcodes = btnExecute;
    deltaConnection = deltaSerialPort;

    updateSystemVariable("#1001", -1000);
    updateSystemVariable("#1002", -1000);
    updateSystemVariable("#1003", -1000);

    updateSystemVariable("#1010", NULL_NUMBER);
    updateSystemVariable("#1011", NULL_NUMBER);
    updateSystemVariable("#1012", NULL_NUMBER);

    updateSystemVariable("#X", 0);
    updateSystemVariable("#Y", 0);
    updateSystemVariable("#Z", 0);
    updateSystemVariable("#F", 10);
    updateSystemVariable("#A", 1200);

    connect(deltaSerialPort, SIGNAL(deltaRespondGcodeDone()), this, SLOT(transmitNextGcode()));
}


void GcodeProgramManager::addGcodeLine(QString line)
{
    QString text = teGcodeArea->toPlainText();
    QTextCursor curPos = teGcodeArea->textCursor();
    int pos = curPos.position();
    int i=0;
    //Hàm này giúp cho khi con trỏ thay đổi vị trí thì string in trên editor luôn theo format
    //tức là luôn in trên 1 dòng mới
    for(i = pos; i > -1; --i){
        //Vì compiler ko đoán được phạm vi của i do gắn i với pos, nên
        //ta cần thêm điều kiện này để ko báo lỗi
        if(i >= 0 && i < text.size()){
            if(text[i] == '\n'){
                curPos.setPosition(i+1);
                break;
            }
        }

    }

    if(i == -1){
        curPos.setPosition(0);
    }

    teGcodeArea->setTextCursor(curPos);
    teGcodeArea->insertPlainText(line + "\n");

}

void GcodeProgramManager::updateSystemVariable(QString name, float value)
{
    saveGcodeVaribale(name, value);
    emit justUpdateVariable(gcodeVariables);
}


void GcodeProgramManager::addG01(float x, float y, float z)
{
    addGcodeLine(QString("G01 X%1 Y%2 Z%3").arg(x).arg(y).arg(z));
}

void GcodeProgramManager::addG28()
{
    addGcodeLine("G28");
}

void GcodeProgramManager::addM204(float accel)
{
    addGcodeLine(QString("M204 A%1").arg(accel));
}

void GcodeProgramManager::executeGcode(QString gcode)
{
    if(gcode == "") {
        if(btnExecuteGcodes->isChecked()) btnExecuteGcodes->click();
        return;
    }
    QList<QString> tempGcodeList = gcode.split('\n');

    gcodeList.clear();
    if(startMode == "Begin"){
        gcodeOrder = 0;
    }else{
        gcodeOrder = currentGcodeEditorCursor;
    }

    for(int i = 0; i < tempGcodeList.size(); i++){
        QString line = tempGcodeList.at(i);

        gcodeList.push_back(line);
    }

    tempGcodeList.clear();

    transmitNextGcode();
}

void GcodeProgramManager::stop()
{
    gcodeList.clear();
    gcodeOrder = 0;
}

void GcodeProgramManager::loadProgram(QString fileName)
{
    //QDir directory(QDir::currentPath());
    teGcodeArea->clear();
    QFile file(fileName + ".dtgc");
    if(!file.open(QIODevice::ReadOnly | QIODevice::Text)){
        qDebug() << "Cannot open file to save !";
        return;
    }
    QTextStream in(&file);
    QString strGcode = "";
    while (!in.atEnd()) {
        QString line = in.readLine();
        strGcode.push_back(line + '\n');
    }
    teGcodeArea->setText(strGcode);
}

void GcodeProgramManager::transmitNextGcode()
{
    if(gcodeList.empty()) {
        if(btnExecuteGcodes->isChecked()) btnExecuteGcodes->click();
        return;
    }

    if(gcodeOrder > gcodeList.size()){
        if(btnExecuteGcodes->isChecked()) btnExecuteGcodes->click();
        return;
    }

    while(true){
        currentLine = gcodeList.at(gcodeOrder);
        if(currentLine == ""){
            gcodeOrder++;
            continue;
        }
        QString firstPair = currentLine.split(' ')[0];

        if(firstPair[0] == 'N'){
            QString line = currentLine;
            currentLine = line.replace(firstPair + " ", "");
        }

        bool isGcode = findExeGcodeAndTransmit();

        if(gcodeOrder == gcodeList.size()){
            gcodeOrder = 0;
            gcodeList.clear();

            if(btnExecuteGcodes->isChecked()) btnExecuteGcodes->click();

            break;
        }

        if(isGcode == true) break;
    }

}

void GcodeProgramManager::saveGcodeIntoFile(QString fileName)
{
    QFile file;
    //QDir::setCurrent("E:/DoAnTotNghiep/Program/Qt_app/DeltaRobotSoftware/DeltaRobotSoftware/GcodeFolder");
    file.setFileName(fileName + ".dtgc");
    if(!file.open(QIODevice::WriteOnly | QIODevice::Text)){
        qDebug() << "Cannot open file to save !";
        return;
    }
    QTextStream out(&file);
    out << teGcodeArea->toPlainText();
}

float GcodeProgramManager::getVariableValue(QString name)
{
    if(name == "NULL") return NULL_NUMBER;

    foreach(GcodeVariable var, gcodeVariables){
        if(var.name == name){
            return var.value;
        }
    }
    return name.toFloat();
}

bool GcodeProgramManager::isGlobalVariable(QString name)
{
    if(name == ""){
        return false;
    }

    if(name.length() > 6){
        if(name.indexOf("#GLOBAL") == 0) return true;
    }

    return false;
}

bool GcodeProgramManager::isMovingGcode(QString gcode)
{
    QString movingGcodes = "G01 G00 G1 G0 G02 G03";

    QString prefix = gcode.mid(0, gcode.indexOf(" "));
    if(movingGcodes.indexOf(prefix) > -1) return true;

    return false;
}

bool GcodeProgramManager::findExeGcodeAndTransmit()
{
    currentGcodeEditorCursor = gcodeOrder;
    QTextCursor textCursor = teGcodeArea->textCursor();
    textCursor.movePosition(QTextCursor::Start);
    textCursor.movePosition(QTextCursor::Down, QTextCursor::MoveAnchor, currentGcodeEditorCursor);
    teGcodeArea->setTextCursor(textCursor);

    currentLine = currentLine.replace("  ", " ");


    if(currentLine == ""){
        gcodeOrder += 1;
        return false;
    }

    if(currentLine[0] == ';'){
        gcodeOrder += 1;
        return false;
    }



    //------------ Handle all expression in [ ... ]-----------------------
    int openBracIndex = currentLine.indexOf('[');
    QString expressInBracket = "";
    float resultInBracket;
    int subBracNum = 0;

    while (openBracIndex > -1) {

        for(int i = openBracIndex; i < currentLine.length(); i++){
            expressInBracket += currentLine[i];

            if(currentLine[i] == '[') subBracNum++;
            else if(currentLine[i] == ']') subBracNum--;

            if(subBracNum == 0) break;
        }

        resultInBracket = calculateExpression(expressInBracket);

        currentLine.replace(expressInBracket, QString::number(resultInBracket));

        expressInBracket = "";

        openBracIndex = currentLine.indexOf('[');
    }

    //--------------- Handle programming statement --------------------
    QList<QString> valuePairs = currentLine.split(' ');
    QString transmitGcode = currentLine;

    for(int i=0; i<valuePairs.size(); i++){
        if(valuePairs[i] == "")
            continue;

        //------GOTO-------------
        if(valuePairs[i] == "GOTO" && (i+1) < valuePairs.size()){
            bool isNumber;
            int goID;

            goID = valuePairs[i+1].toInt(&isNumber, 10);

            if(isNumber == true){
                //Find N..
                for(int order = 0; order < gcodeList.size(); ++order){

                    QList<QString> pairs = gcodeList[order].split(' ');
                    if(pairs[0] == "") continue;
                    if(pairs[0][0] == 'N'){
                        int id = pairs[0].mid(1).toInt();
                        if(id == goID){
                            gcodeOrder = order;
                            return false;
                        }
                    }
                }
            }
        }

        //--------If-------------
        if(valuePairs[i] == "IF" && (i+3) < valuePairs.size()){
            if(valuePairs[i+2] == "THEN"){
                QString statement = currentLine.mid(currentLine.indexOf("THEN") + 5);

                bool result = false;

                if(valuePairs[i+1] == "1"){
                    result = true;
                }

                if(result == true){
                    currentLine = statement;
                    transmitGcode = statement;
                    return findExeGcodeAndTransmit();
                }else{
                    gcodeOrder++;
                    return false;
                }
            }
        }

        //---------Variable----------------

        //#100 = 2
        // #100 = #100 + 2
        // #100 = #101 - #102

        if(valuePairs[i].at(0) == '#' && valuePairs.size() > (i+2)){
            if(valuePairs[i+1] == '='){
                QString varName = valuePairs[i];
                QString expression = currentLine.mid(currentLine.indexOf('=') + 2);
                GcodeVariable newVar;

                newVar.name = varName;
                newVar.value = calculateExpression(expression);

                saveGcodeVaribale(newVar);

                if(getVariableValue("#01_X") == NULL_NUMBER && getVariableValue("#01_Y") == NULL_NUMBER &&
                                                               getVariableValue("#01_A") == NULL_NUMBER){
                    emit outOfObjectVariable();
                }
                gcodeOrder++;
                return false;
            }
        }


        //--------While-----------------------

        //---Define subprogram-------------------
        //N15 O2000
        //....
        //N45 M99

        if(valuePairs[i].at(0) == 'O'){
            for(int order = gcodeOrder + 1; order < gcodeList.size(); order++){
                if(gcodeList[order].indexOf("M99") > -1){
                    gcodeOrder = order + 1;
                    return false;
                }
            }
        }

        //-------------Call subprogram ---------------

        //N50 M98 P2000
        //2000 is ID

        //valuePairs.size() > (i+1) -> Đảm bảo phía sau vẫn còn lệnh

        if(valuePairs[i] == "M98" && valuePairs.size() > (i+1)){
            if(valuePairs[i+1].at(0) == 'P'){
                QString subProName = valuePairs[i+1].mid(1);

                if(subProName == "clearObjects"){
                    emit deleteAllObjects();
                    gcodeOrder++;
                    return false;
                }else if(subProName == "deleteFirstObject"){
                    emit deleteFirstObject();
                    gcodeOrder++;
                    return false;
                }else if(subProName == "pauseCamera"){
                    emit pauseCamera();
                    gcodeOrder++;
                    return false;
                }else if(subProName == "captureCamera"){
                    emit captureCamera();
                    gcodeOrder++;
                    return false;
                }else if(subProName == "resumeCamera"){
                    emit resumeCamera();
                    gcodeOrder++;
                    return false;
                }

                //Fine O2000
                for(int order = 0; order < gcodeList.size(); ++order){
                    if(gcodeList[order].indexOf("O" + subProName) > -1){

                        returnPointerIndex++;
                        returnSubProPointer[returnPointerIndex] = gcodeOrder;

                        gcodeOrder = order + 1;

                        return false;
                    }
                }
            }
        }


        //Finish subProgram
        if(valuePairs[i] == "M99"){
            gcodeOrder = returnSubProPointer[returnPointerIndex] + 1;
            returnPointerIndex--;
            return false;
        }

        //Control conveyor
        if (valuePairs[i] == "M301") {
            emit conveyorStop();
        }

        if (valuePairs[i] == "M302") {
            emit conveyorRun();
        }

        //Complete GCode
        if(valuePairs[i] == "M30"){
            gcodeList.clear();
            btnExecuteGcodes->click();
            return true;
        }

    }

    updatePositionIntoSystemVariable(transmitGcode);
    deltaConnection->sendData(transmitGcode);
    gcodeOrder++;

    return true;
}

float GcodeProgramManager::calculateExpression(QString expression)
{
    expression = expression.replace("  ", " ");

    while(1){
        int openIndex = expression.lastIndexOf('[');

        int multiplyIndex = expression.indexOf('*');
        int divideIndex = expression.indexOf('/');
        int moduloIndex = expression.indexOf('%');
        int plusIndex = expression.indexOf('+');
        int subIndex = expression.indexOf("- ");

        int andIndex = expression.indexOf("AND");
        int orIndex = expression.indexOf("OR");
        int xorIndex = expression.indexOf("XOR");

        int eqIndex = expression.indexOf("EQ");
        int neIndex = expression.indexOf("NE");
        int ltIndex = expression.indexOf("LT");
        int leIndex = expression.indexOf("LE");
        int gtIndex = expression.indexOf("GT");
        int geIndex = expression.indexOf("GE");

        if (eqIndex == -1)
        {
            eqIndex = expression.indexOf("==");
        }
        if (neIndex == -1)
        {
            neIndex = expression.indexOf("!=");
        }
        if (ltIndex == -1)
        {
            ltIndex = expression.indexOf("<");
        }
        if (leIndex == -1)
        {
            leIndex = expression.indexOf("<=");
        }
        if (gtIndex == -1)
        {
            gtIndex = expression.indexOf(">");
        }
        if (geIndex == -1)
        {
            geIndex = expression.indexOf(">=");
        }

        if(openIndex > -1){
            int closeIndex = expression.indexOf(']', openIndex);
            QString subExpression = expression.mid(openIndex + 1, closeIndex - openIndex -1);
            float result = calculateExpression(subExpression);

            subExpression = QString("[") + subExpression + "]";

            expression.replace(subExpression, QString::number(result));

            continue;
        }else if ((multiplyIndex > -1 || divideIndex > -1 || moduloIndex > -1 || plusIndex > -1 || subIndex > -1 || andIndex > -1 || orIndex > -1 || xorIndex > -1) && isNotNegative(expression))
        {
            // 3 + 2 * 5 - 4 / 2

            int operaIndex = subIndex;

            operaIndex = (plusIndex > -1) ? plusIndex : operaIndex;
            operaIndex = (andIndex > -1) ? andIndex : operaIndex;
            operaIndex = (orIndex > -1) ? orIndex : operaIndex;
            operaIndex = (xorIndex > -1) ? xorIndex : operaIndex;
            operaIndex = (multiplyIndex > -1) ? multiplyIndex : operaIndex;
            operaIndex = (divideIndex > -1) ? divideIndex : operaIndex;
            operaIndex = (moduloIndex > -1) ? moduloIndex : operaIndex;

            QString value1S = getLeftWord(expression, operaIndex);
            QString value2S = getRightWord(expression, operaIndex);

            float value1 = getVariableValue(value1S);
            float value2 = getVariableValue(value2S);

            float result = value1 - value2;
            QString resultS = QString::number(result);

            QString operaExpression = value1S + " - " + value2S;

            if (multiplyIndex > -1)
            {
                result = value1 * value2;
                resultS = QString::number(result);

                operaExpression = value1S + " * " + value2S;
            }
            else if (divideIndex > -1)
            {
                if (value2 != 0)
                    result = value1 / value2;
                else
                    result = 0;
                resultS = QString::number(result);

                operaExpression = value1S + " / " + value2S;
            }
            else if (moduloIndex > -1)
            {
                if (value2 != 0)
                    result = (int)value1 % (int)value2;
                else
                    result = 0;
                resultS = QString::number(result);

                operaExpression = value1S + " % " + value2S;
            }
            else if (plusIndex > -1)
            {
                result = value1 + value2;
                resultS = QString::number(result);

                operaExpression = value1S + " + " + value2S;
            }
            else if (andIndex > -1)
            {
                result = value1 * value2;
                result = (result > 0) ? 1 : 0;
                resultS = QString::number(result);

                operaExpression = value1S + " AND " + value2S;
            }
            else if (orIndex > -1)
            {
                result = value1 + value2;
                result = (result > 0) ? 1 : 0;
                resultS = QString::number(result);

                operaExpression = value1S + " OR " + value2S;
            }

            if (xorIndex > -1)
            {
                value1 = (value1 > 0) ? 1 : 0;
                value2 = (value2 > 0) ? 1 : 0;
                result = (value1 != value2) ? 1 : 0;

                resultS = QString::number(result);

                operaExpression = value1S + " XOR " + value2S;
            }

            expression.replace(operaExpression, QString::number(result));

            continue;
        }else if (eqIndex > -1 || ltIndex > -1 || gtIndex > -1 || neIndex > -1 || leIndex > -1 || geIndex > -1)
        {
            QString value1S;
            QString value2S;

            float value1;
            float value2;

            int operatorIndex = eqIndex;

            operatorIndex = (neIndex > -1) ? neIndex : operatorIndex;
            operatorIndex = (ltIndex > -1) ? ltIndex : operatorIndex;
            operatorIndex = (leIndex > -1) ? leIndex : operatorIndex;
            operatorIndex = (gtIndex > -1) ? gtIndex : operatorIndex;
            operatorIndex = (geIndex > -1) ? geIndex : operatorIndex;

            value1S = getLeftWord(expression, operatorIndex);
            value2S = getRightWord(expression, operatorIndex);

            value1 = getVariableValue(value1S);

            value2 = getVariableValue(value2S);

            int returnValue = -1;

            returnValue = (eqIndex > -1) ? ((value1 == value2) ? 1 : 0 ) : returnValue;
            returnValue = (neIndex > -1) ? ((value1 != value2) ? 1 : 0) : returnValue;
            returnValue = (ltIndex > -1) ? ((value1 < value2) ? 1 : 0) : returnValue;
            returnValue = (leIndex > -1) ? ((value1 <= value2) ? 1 : 0) : returnValue;
            returnValue = (gtIndex > -1) ? ((value1 > value2) ? 1 : 0) : returnValue;
            returnValue = (geIndex > -1) ? ((value1 >= value2) ? 1 : 0) : returnValue;

            if (returnValue != -1)
                return returnValue;
        }
        else
        {
            float value = getVariableValue(deleteSpaces(expression));

            if (deleteSpaces(expression) == "NULL")
            {
                value = NULL_NUMBER;
            }

            return value;
        }

        return expression.toFloat();
    }
}

void GcodeProgramManager::saveGcodeVaribale(GcodeVariable gvar)
{
    bool isNewVar = true;

    for(int i=0; i<gcodeVariables.length(); i++){
        if(gcodeVariables[i].name == gvar.name){
            gcodeVariables[i].value = gvar.value;
            isNewVar = false;
        }
    }

    if(isNewVar == true) gcodeVariables.push_back(gvar);
}

void GcodeProgramManager::saveGcodeVaribale(QString name, float value)
{
    GcodeVariable newVar;
    newVar.name = name;
    newVar.value = value;
    saveGcodeVaribale(newVar);
}

void GcodeProgramManager::updatePositionIntoSystemVariable(QString statement)
{
    QList<QString> pairs = statement.split(' ');

    float x, y, z, f, a;

    x = getVariableValue("#X");
    y = getVariableValue("#Y");
    z = getVariableValue("#Z");
    f = getVariableValue("#F");
    a = getVariableValue("#A");

    if(statement == "G28"){
        updateSystemVariable("#X", 0);
        updateSystemVariable("#Y", 0);
        updateSystemVariable("#Z", 0);

        emit moveToNewPosition(0, 0, 0, f, a);
        return;
    }

    foreach(QString cmd, pairs){
        QChar prefix = cmd[0];
        QString value = cmd.mid(1);

        if(prefix == 'X'){
            x = value.toFloat();
            updateSystemVariable("#X", x);
        }else if(prefix == 'Y'){
            y = value.toFloat();
            updateSystemVariable("#Y", y);
        }else if(prefix == 'Z'){
            z = value.toFloat();
            updateSystemVariable("#Z", z);
        }else if(prefix == 'F'){
            f = value.toFloat();
            updateSystemVariable("#F", f);
        }else if(prefix == 'A'){
            a = value.toFloat();
            updateSystemVariable("#A", a);
        }
    }

    emit moveToNewPosition(x, y, z, f, a);
}

QString GcodeProgramManager::getLeftWord(QString s, int pos)
{
    if(pos < 0) return "0";
    if(pos > s.length() - 1) return "0";

    QString word;

    while(1){
        if(s[pos] != ' '){
            pos--;
            if(pos < 0) return "0";
        }else{
            break;
        }
    }

    for(int i=pos; i >= 0; --i){
        if(s[i] != ' '){
            word.insert(0, s[i]);
        }else if(word.length() > 0){
            break;
        }
    }

    return word;
}

QString GcodeProgramManager::getRightWord(QString s, int pos)
{
    if (pos < 0)
        return "0";

    if (pos > s.length() - 1)
        return "0";

    QString word;

    while (1)
    {
        if (s[pos] != ' ')
        {
            pos++;
            if (pos == s.length())
            {
                return "0";
            }
        }
        else
        {
            break;
        }
    }

    for (int i = pos + 1; i < s.length(); i++)
    {
        if (s[i] != ' ')
        {
            word += s[i];
        }
        else if (word.length() > 0)
        {
            break;
        }
    }

    return word;
}

QString GcodeProgramManager::deleteSpaces(QString s)
{
    while(s.indexOf(' ') > -1){
        s.replace(" ", "");
    }
    return s;
}

bool GcodeProgramManager::isNotNegative(QString s)
{
    bool isNumeric = false;
    s.toDouble(&isNumeric);

    return !isNumeric;
}

















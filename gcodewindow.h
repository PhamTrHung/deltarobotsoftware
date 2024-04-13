#ifndef GCODEWINDOW_H
#define GCODEWINDOW_H

#include <QDialog>
#include <QTextEdit>
#include <QComboBox>

namespace Ui {
class GCodeWindow;
}

class GCodeWindow : public QDialog
{
    Q_OBJECT

public:
    explicit GCodeWindow(QWidget *parent = nullptr);
    ~GCodeWindow();

    QTextEdit *teGcodeWidget = nullptr;
    QPushButton *btnLoadNewGcodeLine = nullptr;
    QComboBox *cmbProgramList = nullptr;


public slots:
    void addGcodeLine();
    void highlightCurrentLine();
    void formatGcodeText();

signals:
    void addNewGcodeLine(QString newLine);
    void saveGcodeInEditorToFile();
    void loadProgram();

private:
    Ui::GCodeWindow *ui;
};

#endif // GCODEWINDOW_H

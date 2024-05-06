#pragma once

#include <QObject>

#include <qopenglwidget.h>
#include <qopenglfunctions.h>
#include <gl/GLU.h>

class GLWidget : public QOpenGLWidget, public QOpenGLFunctions
{
	Q_OBJECT

public:
	explicit GLWidget(QWidget* parent = nullptr);
	~GLWidget();

protected:
	void initializeGL() override;
	void resizeGL(int w, int h) override;
	void paintGL() override;


};


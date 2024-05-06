#pragma once

#include <QObject>

#include <qmutex.h>
#include <qthread.h>


#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>


class CaptureThread  : public QThread
{
	Q_OBJECT

public:
	CaptureThread(QMutex* lock);
	~CaptureThread();

	void setRunning(bool isRun);
	void setCaptureSize(int w, int h);
	void setUpCaptureImage(cv::VideoCapture* cap);

signals:
	void frameCapture(cv::Mat* data);

protected:
	void run() override;

private:
	bool isRunning{false};
	int camID{ 0 };
	QMutex* dataLock;
	cv::Mat frame;
	int frameW{ 0 }, frameH{ 0 };
	cv::VideoCapture* capture;
};

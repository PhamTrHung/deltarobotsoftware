#include "capturethread.h"


CaptureThread::CaptureThread(QMutex* lock):
	dataLock(lock)
{
}

CaptureThread::~CaptureThread()
{}

void CaptureThread::setRunning(bool isRun)
{
	isRunning = isRun;
}

void CaptureThread::setCaptureSize(int w, int h)
{
	frameW = w;
	frameH = h;
}

void CaptureThread::setUpCaptureImage(cv::VideoCapture* cap)
{
	capture = cap;
}

void CaptureThread::run()
{
	isRunning = true;
	cv::Mat tmpMat;

	cv::VideoCapture cap(camID, cv::CAP_DSHOW);
	cap.set(cv::CAP_PROP_FRAME_WIDTH, frameW);

	cap.set(cv::CAP_PROP_FRAME_HEIGHT, frameH);

	//if (capture == nullptr) return;

	while (isRunning)
	{
		cap.read(tmpMat);

		if (tmpMat.empty()) break;

		dataLock->lock();
		frame = tmpMat;
		dataLock->unlock();
		emit frameCapture(&frame);
	}

	cap.release();
	isRunning = false;
}

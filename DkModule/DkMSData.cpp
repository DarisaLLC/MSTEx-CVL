/***************************************************
 *   DkSegmentation.cpp
 *   
 *   Created on: 12.02.2010
 *       Author: Markus Diem
 *      Company: Vienna University of Technology
 ***************************************************/

#include "DkMSData.h"

#include "DkTimer.h"

DkMSData::DkMSData(const std::vector<cv::Mat>& data) {

	msImgs = data;
	fixInput(msImgs);
}

void DkMSData::fixInput(std::vector<cv::Mat>& imgs) const {

	for (cv::Mat& img : imgs) {

		if (img.channels() > 1)
			cv::cvtColor(img, img, CV_RGB2GRAY);

		img = removeSensorNoise(img);

		//if (img.depth() != CV_32F)
		//	img.convertTo(img, CV_32F, 1.0f/255.0f);
	}
}

std::vector<cv::Mat> DkMSData::getImages() const {

	return msImgs;
}

cv::Mat DkMSData::getVisChannel() const {

	if (!msImgs.empty() && msImgs.size() > 1)
		return msImgs[1];

	return cv::Mat();
}

cv::Mat DkMSData::getBgChannel() const {

	if (!msImgs.empty())
		return msImgs[msImgs.size()-1];	// bg channel is the last channel

	return cv::Mat();
}

/**
 * Converts all channels to a NxC matrix.
 * Where N is the image size (rows x cols) and C
 * is the number of channels.
 * Hence, each row represents a pixel.
 * @return cv::Mat the data matrix
 **/ 
cv::Mat DkMSData::convertToSignal() const {

	if (msImgs.empty())
		return cv::Mat();

	DkTimer dt;
	cv::Mat signal(msImgs[0].rows * msImgs[0].cols, (int)msImgs.size(), msImgs[0].depth(), cv::Scalar(42));

	for (int rIdx = 0; rIdx < msImgs.size(); rIdx++) {
		imageToColumnVector(msImgs.at(rIdx)).copyTo(signal.col(rIdx));
	}

	mout << "signal converted in " << dt << dkendl;

	return signal;
}

cv::Mat DkMSData::removeSensorNoise(const cv::Mat& img) const {

	cv::Mat mImg;
	cv::medianBlur(img, mImg, 5);

	double minV, maxV;
	cv::minMaxLoc(mImg, &minV, &maxV);

	unsigned char minVC = (unsigned char)minV;
	unsigned char maxVC = (unsigned char)maxV;

	cv::Mat resImg = img.clone();

	for (int rIdx = 0; rIdx < resImg.rows; rIdx++) {

		unsigned char* rPtr = resImg.ptr<unsigned char>(rIdx);

		for (int cIdx = 0; cIdx < resImg.cols; cIdx++) {

			if (rPtr[cIdx] > maxVC)
				rPtr[cIdx] = maxVC;
			else if (rPtr[cIdx] < minVC)
				rPtr[cIdx] = minVC;
		}
	}
	
	cv::normalize(resImg, resImg, 255.0f, 0.0f, NORM_MINMAX);

	return resImg;
}

Mat DkMSData::imageToColumnVector(const cv::Mat& img) const {

	if (img.empty())
		return cv::Mat();

	return img.reshape(0, img.rows*img.cols);
}

Mat DkMSData::columnVectorToImage(const cv::Mat& vec) const {

	if (vec.empty() || msImgs.empty())
		return cv::Mat();

	return vec.reshape(0, msImgs[0].rows);
}






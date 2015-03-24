/***************************************************
 *   DkSegmentation.h
 *   
 *   Created on: 12.02.2010
 *       Author: Markus Diem
 *               Florian Kleber
 *      Company: Vienna University of Technology
 ***************************************************/


#pragma once

#include "DkModuleInclude.h"

#include "DkUtils.h"
#include "DkMSData.h"
#include "DkModule.h"

#include "ml.h"

class DK_MODULE_API DkRandomTrees : public DkModule {

public:
	DkRandomTrees(const DkMSData& data = DkMSData(), const cv::Mat&  suImg = cv::Mat());

	void compute();
	std::string toString() const;

	cv::Mat getPredictedImage() const;

protected:
	DkMSData imgs;
	cv::Mat suImg;	// label input
	cv::Mat pImg;	// result
	int nSamples;

	void checkInput() const;
	cv::Ptr<cv::StatModel> trainOnline(const cv::Mat& data, const cv::Mat& fgdImg) const;
	cv::Mat predictImage(const cv::Mat& data, const cv::Ptr<cv::StatModel>& classifier) const;
	void converData(cv::Mat& trainData, cv::Mat& labels, int numPos) const;
};
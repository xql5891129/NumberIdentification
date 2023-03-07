#pragma once

#ifndef PREPROCESS_H
#define PREPROCESS_H

#include<opencv2\opencv.hpp>
#include<iostream>
#include<string>
#include <opencv2\imgproc\types_c.h>

using namespace cv;
using namespace std;

#include "mousedraw.h"
#include "global.h"
#include"features.h"


void preProcess(const Mat& srcImage, Mat& dstImage);
#endif
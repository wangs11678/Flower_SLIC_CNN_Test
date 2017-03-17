#ifndef UTILS_H_INCLUDED
#define UTILS_H_INCLUDED

#include <fstream>
#include <opencv2/opencv.hpp>

//将图像等比例缩小到maxImgSize
void cnn_image_pretreatment(cv::Mat &image, int imgSize);

//生成libsvm中heart_scale格式的txt文件
void cnn_gen_txt_file(cv::Mat &llcFeature, char* testFile);

#endif // UTILS_H_INCLUDED

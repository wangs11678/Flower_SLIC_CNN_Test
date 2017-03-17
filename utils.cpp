#include "utils.h"

using namespace std;
using namespace cv;

void cnn_image_pretreatment(Mat &image, int imgSize)
{
	Mat img;
	resize(image, img, Size(imgSize, imgSize), 0, 0, CV_INTER_LINEAR);
	image = img;
	/*
	//Mat grayImg;
	//cvtColor(image, grayImg, CV_BGR2GRAY);
	//image = grayImg;
	if(image.rows > maxImgSize || image.rows >maxImgSize)
	{
		int max_size = image.rows>image.cols?image.rows:image.cols;
		float scale = float(maxImgSize)/max_size;
		Size dsize = Size(image.cols*scale, image.rows*scale);
		Mat destImg = Mat(dsize, CV_32S);
		resize(image, destImg, dsize);
		image = destImg;
	}
	*/
	//grayImg.release();
}


//生成libsvm中heart_scale格式的txt文件
void cnn_gen_txt_file(Mat &llcFeature, char* testFile)
{
    ofstream tsFile(testFile);
	tsFile << 0 << " ";
    for(int k = 0; k < llcFeature.rows; k++)
    {
        if(llcFeature.at<float>(k, 0) != 0)
            tsFile<< k+1 <<":" << llcFeature.at<float>(k, 0) << " ";
    }
    tsFile << "\n";
}

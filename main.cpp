#include "utils.h"
#include "slic.h"
#include "segment.h"
#include "extract_feature.h"
#include "predict.h"

char modelFile[] = "result/model.txt";
char testFile[] = "result/test.txt";
char resultFile[] = "result/result.txt";
int imgSize = 256;

int main(int argc, char* argv[])
{
	//初始化Caffe===================================================================================
	std::string caffe_root = "/home/wangs/caffe/";
	std::string param_file = caffe_root + "models/bvlc_alexnet/deploy_Test.prototxt";
	std::string pretrained_param_file = caffe_root + "models/bvlc_alexnet/bvlc_alexnet.caffemodel";	
    Caffe_Predefine(param_file, pretrained_param_file);	
	
	//SLIC花卉分割==================================================================================
	const char *flower = argv[1];
	vector<IplImage*> imageRect;
	vector<IplImage*> seg;
	slic_superpixels_segment(flower, imageRect, seg);
 	
 	//对分割图像进行处理=============================================================================
	for(int i = 0; i < seg.size(); i++)
    {  	
		cvShowImage("result", imageRect[i]);
        cv::Mat img(seg[i], 0);	
    	imshow("image", img);
    	
    	//图像预处理=====================================================
        cnn_image_pretreatment(img, imgSize);
        
        //提取特征=======================================================
        Mat fc7 = Mat(4096, 1, CV_32FC1);
        if (!fc7.empty())
		{
		    int j = 0;
		    vector<float> feat = ExtractFeature(img);
		    while (j < feat.size())
		    {
		        fc7.at<float>(j, 0) = feat[j++];
		    }
		}
        
        //生成文档=======================================================
        cnn_gen_txt_file(fc7, testFile);
		
		//测试分类=======================================================
		int labels = SVM_predict(argc, argv, testFile, modelFile, resultFile);
		cout << "predict label: " << labels << endl;
		waitKey();
	}
	//结束===========================================================================================
    return 0;
}

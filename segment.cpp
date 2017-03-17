#include "segment.h"

void slic_superpixels_segment(const char *img, vector<IplImage*> &imageRect, vector<IplImage*> &segment)
{
    /* Load the image and convert to Lab colour space. */
    IplImage *image = cvLoadImage(img, 1);
    IplImage *lab_image = cvCloneImage(image);
    cvCvtColor(image, lab_image, CV_BGR2Lab);
    
    /* Yield the number of superpixels and weight-factors from the user. */
    int w = image->width, h = image->height;
    int nr_superpixels = 30; //atoi(argv[2]);
    int nc = 80; //atoi(argv[3]);
    double step = sqrt((w * h) / (double) nr_superpixels);
    
    /* Perform the SLIC superpixel algorithm. */
    Slic slic;
    slic.generate_superpixels(lab_image, step, nc);
    slic.create_connectivity(lab_image);
    
    /* Display the contours and show the result. */
    //slic.display_contours(image, CV_RGB(255, 0, 0));
    //slic.display_center_grid(image, CV_RGB(0, 0, 255));
    //slic.colour_with_cluster_means(image);   
    
    //cvShowImage("result", image);
    //cvWaitKey(0);
    
    /* Extract the surrounding area of the superpixels and save it. */
    slic.extract_rect_ROI(image, segment);
    
    slic.display_rect_box(image, imageRect, CV_RGB(255, 0, 0));
}

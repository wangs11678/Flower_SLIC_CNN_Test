/*
 * Written by: Pascal Mettes.
 * This file creates an over-segmentation of a provided image based on the SLIC
 * superpixel algorithm, as implemented in slic.h and slic.cpp.
 */
 
#include "slic.h"

void slic_superpixels_segment(const char *img, vector<IplImage*> &imageRect, vector<IplImage*> &segment);

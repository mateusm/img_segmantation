//
//  main.cpp
//  img_segmantation
//
//  Created by Mateus Mesturini Meruvia on 3/11/16.
//  Copyright © 2016 Mateus Mesturini Meruvia. All rights reserved.
//


#include <iostream>
#include <opencv2/opencv.hpp>

#include <opencv/cv.h>
#include <opencv/highgui.h>
#include <opencv/cxcore.h>
#include <opencv/cvaux.h>


#include<stdio.h>
#include<stdlib.h>
#include <string>
#include <sstream>
#include <fstream>
using namespace std;
using namespace cv;

#define NUMBER_IMAGES 3


string image_index[900];
string original_image[900];
string prefix = "/Users/mateusmesturini/Dropbox/Morgan Classes/Senior Project/ISBI2016_ISIC_Part1_Training_Data/";
//string graythresh_folder = "results/graythresh/";
//string colorthresh_folder = "results/colorthresh/";
string destination_graythresh [900];
string destination_colorthresh [900];


Mat src; Mat src_gray;
int thresh = 100;
int max_thresh = 255;
RNG rng(12345);


void read_file(){
    int n = 0;
    int i;
    ifstream infile;
    infile.open ("/Users/mateusmesturini/Dropbox/Morgan Classes/Senior Project/ISBI2016_ISIC_Part1_Training_Data/files_names.txt");
    
    while( !infile.eof())
    {
        getline(infile,image_index[n]); // Saves the line in STRING.
        n++;
        
    }
    infile.close();
    
    
    for (i=0; i<900; i++) {
        original_image[i] = prefix + image_index[i];
        //destination_graythresh[i] = prefix + graythresh_folder + image_index[i];
        //destination_colorthresh[i] = prefix + colorthresh_folder + image_index[i];
        destination_graythresh[i] = prefix + image_index[i] + "graythresh.jpg";
        destination_colorthresh[i] = prefix + image_index[i] + "colorthresh.jpg";
    }
    
}






int main(int argc, const char * argv[]) {
    
    
    
    int i;
    
    read_file();
    
    
    
    for (i=0; i<NUMBER_IMAGES; i++) {
        
        
        
        //src = cvLoadImage(original_image[i].c_str(), 1);
        Mat im_in = imread(original_image[i].c_str(), IMREAD_GRAYSCALE);
        
        Mat im_th;
        cv::threshold(im_in, im_th, 120, 255, THRESH_BINARY_INV);
        
        
        Mat im_floodfill = im_th.clone();
        floodFill(im_floodfill, cv::Point(0,0), Scalar(255));
        
        //Invert floodfilled image
        Mat im_floodfill_inv;
        bitwise_not(im_floodfill, im_floodfill_inv);
        
        // Combine the two images to get the foreground.
        Mat im_out = (im_th | im_floodfill_inv);
        
        
        
        imwrite(destination_graythresh[i].c_str(), im_out);
        //imwrite(destination_graythresh[i].c_str(), im_th);

        //cvSaveImage(destination_colorthresh[i].c_str(), colorThresh);
        
        
    }
    
    
    return 0;
    
    
    
    
    
    
    
    
    
}
#include "writer.h"
#include <iostream>

//g++ -std=c++17 main.cpp writer.cpp -o main `pkg-config --cflags --libs opencv` `pkg-config --cflags --libs hdf5-serial` -lhdf5_cpp -lhdf5
// g++ -std=c++17 main.cpp -o main `pkg-config --cflags --libs opencv hdf5-serial` -lhdf5_cpp -lhdf5

int main(){

    cv::Mat img1 = cv::Mat::zeros(120,260, CV_8UC1);
    cv::Mat img2 = cv::Mat::zeros(120,260, CV_8UC1);
    std::vector<cv::Mat> imgs;
    imgs.push_back(img1);
    imgs.push_back(img2);

    HDF5Writer writer("dp.h5", "disparityMaps");
    writer.writingHDF5(imgs);

    return 0;
}
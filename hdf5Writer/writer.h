#include <vector>
#include <string>
#include <iostream>
#include <opencv2/opencv.hpp>

#include "hdf5/serial/H5Cpp.h"



class HDF5Writer{
    public: 
        HDF5Writer();
        HDF5Writer(std::string fname, std::string dataset);
        ~HDF5Writer();
        void writingHDF5(std::vector<cv::Mat>&data);
    private:

        const std::string FileName;
        const std::string DatasetName;
        H5::H5File*File;
        H5::DataSet*Dataset;
        void openingHDF5(const std::string fname, const std::string dataset );
        

};
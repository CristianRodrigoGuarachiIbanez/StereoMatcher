#include "writer.h"


HDF5Writer::HDF5Writer(){

}


HDF5Writer::HDF5Writer(std::string fname, std::string dataSet): FileName(fname), DatasetName(dataSet){

    openingHDF5(FileName, DatasetName);
    
}

HDF5Writer::~HDF5Writer(){

    delete this->Dataset;
    delete this->File;
}

void HDF5Writer::openingHDF5(const std::string fname, const std::string dataset ){
     /*
     * Create a file.
     */
    this->File = new H5::H5File( fname, H5F_ACC_TRUNC );

}

void HDF5Writer::writingHDF5(std::vector<cv::Mat>&data){

    H5::CompType mtype(sizeof(data));
        // preparation of a dataset and a file.
    hsize_t dim[1];
    dim[0] = data.size();                   // using vector::size()
    int rank = sizeof(dim) / sizeof(hsize_t);
    H5::DataSpace space(rank, dim);
    Dataset = new H5::DataSet(File->createDataSet(DatasetName, mtype, space));
    Dataset->write(data.data(), mtype);     // use vector::data()
}
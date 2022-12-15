#include <stdlib.h>
#include <string>
#include <iostream>
#include <opencv2/opencv.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/hdf.hpp>


#include "methods/ioh.hpp"
#include "methods/sad.hpp"
#include "methods/ncc.hpp"
#include "methods/bp.hpp"
#include "methods/mbp.hpp"

int main(int argc, char const *argv[])
{
    // parse args
    if (argc != 6 && argc != 7)
    {
        std::cout << "usage: main <im0.png> <im1.png> <ndisp> <method> <visualize> <outdir>" << std::endl;
        std::cout << "method field is optinal, default: Blief Prapagation" << std::endl;
        return -1;
    }
    std::string im0 = std::string(argv[1]);
    std::string im1 = std::string(argv[2]);
    int ndisp = atoi(argv[3]);
    std::string outPath = std::string(argv[4]);
    std::string method = std::string(argv[5]);
    bool vis = false;
    if (argc == 7)
        vis = std::string(argv[6]) == "true";

    ioh::IOHelper ioh;
    ioh.setUp(im0, im1, ndisp, outPath);
    // cv::Mat leftMat(3, 3, CV_32F), rightMat(3, 3, CV_32F);
    // cv::Mat cameraMats[2] = {leftMat, rightMat};
    // ioh.readCalib(cameraMats);

    cv::Mat leftImg, rightImg;
    ioh.readImage(leftImg, rightImg);

    // cv::namedWindow("debug", cv::WINDOW_AUTOSIZE);
    // cv::imshow("debug", leftImg);
    // cv::waitKey(0);

    // matching
    std::cout << "use method: " << method << std::endl;
    std::cout << "start matching..." << std::endl;
    cv::Mat disparity;
    clock_t beginTime = clock();
    if (method == "SAD")
    {
        sad::SAD matcher(2, ndisp);
        disparity = matcher.do_match(leftImg, rightImg);
    }
    else if (method == "NCC")
    {
        ncc::NCC matcher(3, ndisp);
        disparity = matcher.do_match(leftImg, rightImg);
    }
    else if (method == "BP")
    {
        bp::BP matcher(leftImg, rightImg, ndisp, 1, 2 * float(ndisp), 5);
        disparity = matcher.do_match();
    }
    else if (method == "MBP")
    {
        mbp::MBP matcher(leftImg, rightImg, ndisp, 1, 2*float(ndisp), 5);
        disparity = matcher.do_match();
    }
    clock_t endTime = clock();
    std::cout << "method: " << method << " ,cost time: " << (double)(endTime - beginTime) / CLOCKS_PER_SEC << std::endl;
    
    disparity *= 65535 / ndisp;
    cv::imwrite(outPath, disparity);
    // for png visualization
    if (vis)
    {
        disparity *= 65535 / ndisp;
        cv::imshow("visualize left disp image", disparity);
        cv::waitKey(0);
    }
    return 0;
}

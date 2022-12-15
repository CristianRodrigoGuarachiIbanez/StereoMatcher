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

//./build/main ./l_images/0001-0750.avi ./r_images/0001-0750.avi 64 ./output MBP big false


int show(int argc, char const * argv[]){


     if (argc != 7 && argc != 8)
    {
        std::cout << "usage: main <video0.avi> <video1.avi> <ndisp> <method> <size> <visualize> <outdir>" << std::endl;
        std::cout << "method field is optinal, default: Blief Prapagation" << std::endl;
        return -1;
    }
    std::string leye = std::string(argv[1]);
    std::string reye = std::string(argv[2]);
    int ndisp = atoi(argv[3]);
    
    std::string method = std::string(argv[4]);
    std::string size = std::string(argv[5]);
    std::string vis = std::string(argv[6]);
    std::string outPath;
    if(argc == 8 || vis == "write"){
        outPath = std::string(argv[7]);
    }
    
    int WIDTH, HEIGHT;
    if(size=="small"){
        WIDTH = 160;
        HEIGHT = 120;
        
    }else{
        WIDTH = 320;
        HEIGHT = 240;
    }
    size_t counter=0;
    std::vector<cv::Mat>images;
  
    cv::VideoCapture LEye(leye);
    cv::VideoCapture REye(reye);

    if(!LEye.isOpened() || !REye.isOpened()){
        std::cout << "Error opening video stream or file" << std::endl;
        return -1;
    }

    while(1){
        if(counter ==1){
            break;
        }
       
        cv::Mat LFrame, RFrame;
        LEye>>LFrame;
        REye>>RFrame;
        
        cv::resize(LFrame, LFrame, cv::Size(WIDTH, HEIGHT), CV_INTER_LINEAR);
        cv::resize(RFrame, RFrame, cv::Size(WIDTH, HEIGHT), CV_INTER_LINEAR);

        if((LFrame.rows != RFrame.rows) || (RFrame.cols != LFrame.cols)){
            std::cerr<<" the amount of rows or cols ist not identical"<<std::endl;
        }

        std::cout << "start matching..." << std::endl;
        std::cout << "frame number -> " << counter<< std::endl;
        cv::Mat disparity;
        clock_t beginTime = clock();

        if (method == "BP"){
            bp::BP matcher(LFrame, RFrame, ndisp, 1, 2 * float(ndisp), 5);
            disparity = matcher.do_match();
        }
        else if (method == "MBP"){
            mbp::MBP matcher(LFrame, RFrame, ndisp, 1, 2*float(ndisp), 5);
            disparity = matcher.do_match();
        }else if(method == "SAD"){
            sad::SAD matcher(2, ndisp);
            disparity = matcher.do_match(LFrame, RFrame);
        }

        clock_t endTime = clock();
        std::cout << "method: " << method << " ,cost time: " << (double)(endTime - beginTime) / CLOCKS_PER_SEC << std::endl;

        
        // for png visualization
        if (vis == "show"){
            disparity *= 65535 / ndisp;
            cv::imshow("visualize left disp image", disparity);
            cv::waitKey(0);
        }else if(vis == "write"){
            disparity *= 65535 / ndisp;
            cv::imwrite(outPath + "/disp_" + std::to_string(counter) + ".png", disparity);
        }else if(vis == "save"){
            disparity *= 65535 / ndisp;
            images.push_back(disparity.clone());
        }
        counter++;

    }
    LEye.release();
    REye.release();
 
    // Closes all the frames
    cv::destroyAllWindows();
    return 0;
}
#ifndef SAD_H
#define SAD_H
#include <iostream>
#include <opencv2/opencv.hpp>

namespace sad{

    class SAD {
        public:
            SAD() : radius(2), disp(30) {}
            SAD(int _radius, int _disp) : radius(_radius), disp(_disp) {}
            cv::Mat do_match(cv::Mat &leftImage, cv::Mat &rightImage);

        private:
            int radius; //kernel size
            int disp;   //search window size
    };
}
#endif
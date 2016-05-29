/* Sample - Filtering
 * Target is to apply filtering using F-transform
 * on the image "input.png". Two different kernels
 * are used, where bigger radius (100 in this case)
 * means higher level of blurriness.
 *
 * Image "output1_filter.png" is created from "input.png"
 * using "kernel1" with radius 3.
 *
 * Image "output2_filter.png" is created from "input.png"
 * using "kernel2" with radius 100.
 *
 * Both kernels are created from linear function, using
 * linear interpolation (parametr ft:LINEAR).
 */

#include "opencv2/core.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/img_hash.hpp"

#include <iostream>

using namespace cv;

void test_by_function(cv::Mat const &input, cv::Mat const &target)
{
    cv::Mat inHash;
    cv::Mat outHash;

    ihash::averageHash(input, inHash);
    ihash::averageHash(target, outHash);
    //the lower the mismatch value, the better
    double const averageMismatch = norm(inHash, outHash, NORM_HAMMING);
    std::cout<<"averageMismatch : "<<averageMismatch<<std::endl;

    ihash::pHash(input, inHash);
    ihash::pHash(target, outHash);
    double const pHashMismatch = norm(inHash, outHash, NORM_HAMMING);
    std::cout<<"pHashMismatch : "<<pHashMismatch<<std::endl;

    ihash::marrHildrethHash(input, inHash);
    ihash::marrHildrethHash(target, outHash);
    double const marrMismatch = norm(inHash, outHash, NORM_HAMMING);
    std::cout<<"marrMismatch : "<<marrMismatch<<std::endl;
}

//benefits of using class is potential performance gain, because
//class will reuse the buffer, function will allocate new memory
//every time you call it
void test_by_class(cv::Mat const &input, cv::Mat const &target)
{
    cv::Mat inHash;
    cv::Mat outHash;

    Ptr<ihash::ImgHashBase> hashFunc = ihash::AverageHash::create();
    hashFunc->compute(input, inHash);
    hashFunc->compute(target, outHash);
    double const averageMismatch = norm(inHash, outHash, NORM_HAMMING);
    std::cout<<"averageMismatch : "<<averageMismatch<<std::endl;

    hashFunc = ihash::PHash::create();
    hashFunc->compute(input, inHash);
    hashFunc->compute(target, outHash);
    double const pHashMismatch = norm(inHash, outHash, NORM_HAMMING);
    std::cout<<"pHashMismatch : "<<pHashMismatch<<std::endl;

    hashFunc = ihash::MarrHildrethHash::create();
    hashFunc->compute(input, inHash);
    hashFunc->compute(target, outHash);
    double const marrMismatch = norm(inHash, outHash, NORM_HAMMING);
    std::cout<<"marrMismatch : "<<marrMismatch<<std::endl;
}

int main(int argc, char **argv)
{    
    Mat input = imread(argv[1]);
	Mat target = imread(argv[2]);
	
    test_by_function(input, target);
    test_by_class(input, target);
	
    return 0;
}

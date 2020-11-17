#ifndef SIMPLEIMAGEMANIPULATION
#define SIMPLEIMAGEMANIPULATION

#include<iostream>
#include<opencv2/core.hpp>
#include<opencv2/imgproc.hpp>
#include<opencv2/highgui.hpp>


class SimpleImageManipulation{
  private:
    cv::Mat image;
    int track_bar_value_max = 100;
    static void BrightnessTrackBar(int track_bar_value, void * obj);
    static void ContrastTrackBar(int track_bar_value, void * obj);
    static void AverageFilterWindowKernelSizeTrackBar(int track_bar_value, void * obj);
    static void GaussianFilterWindowKernelSizeTrackBar(int track_bar_value, void * obj);
    void BrightnessChange(int value);
    void ContrastChange(float value);
    void AverageFilterKernelSizeChange(int value);
    void GaussianFilterKernelSizeChange(int value);
  public:
    SimpleImageManipulation(cv::String image_path);
    void ShowImage();
    void ShowImage(cv::String window_name, cv::Mat image);
    cv::Mat GrayScale();
    cv::Mat Brightness(int brightness);
    void ShowBrightnessWindow();
    cv::Mat Contrast(float contrast);
    void ShowContrastWindow();
    cv::Mat AverageFilter(int kernel_size);
    void ShowAverageFilterWindow();
    cv::Mat GaussianFilter(int kernel_size);
    void ShowGaussianFilterWindow();
};


#endif //SIMPLEIMAGEMANIPULATION

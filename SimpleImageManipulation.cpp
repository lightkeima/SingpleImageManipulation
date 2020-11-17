#include "SimpleImageManipulation.h"
SimpleImageManipulation::SimpleImageManipulation(cv::String image_path){ 
  this->image = cv::imread(image_path);
}

void SimpleImageManipulation::ShowImage(){
  if(!this->image.empty()){
    cv::String windowName = "Image";
    cv::namedWindow(windowName);
    cv::imshow(windowName, image);
    cv::waitKey(0);
    cv::destroyWindow(windowName);
    return;
  } else std::cout << "No image to show!";
}

void SimpleImageManipulation::ShowImage(cv::String window_name, cv::Mat image){
  if(!image.empty()){
    cv::namedWindow(window_name);
    cv::imshow(window_name, image);    
  } else std::cout << "No image to show!";
}


cv::Mat SimpleImageManipulation::GrayScale(){
  if(this->image.empty()){
    cv::Mat null_matrix(0,0, CV_8UC1);
    return null_matrix;
  }
  cv::Mat gray_image(image.rows, image.cols, CV_8UC1);
  for(int i = 0; i < image.rows; ++i){
    for(int j = 0; j < image.cols; ++j){
      cv::Vec3b pixel = image.at<cv::Vec3b>(i,j);
      gray_image.at<uchar>(i,j) = pixel[0]*0.11 + pixel[1]*0.59 + pixel[2]*0.3;
    }
  }
  return gray_image;
}


cv::Mat SimpleImageManipulation::Brightness(int brightness){
  if(this->image.empty()){
    cv::Mat null_matrix(0,0, CV_8UC3);
    return null_matrix;
  }
  cv::Mat _image(image.rows, image.cols, CV_8UC3);
  for(int i = 0; i < image.rows; ++i){
    for(int j = 0; j < image.cols; ++j){
      cv::Vec3b pixel = image.at<cv::Vec3b>(i,j);

      pixel[0] = (pixel[0] + brightness > 255)?255:((pixel[0] + brightness < 0)?0:pixel[0] + brightness);
      pixel[1] = (pixel[1] + brightness > 255)?255:((pixel[1] + brightness < 0)?0:pixel[1] + brightness);
      pixel[2] = (pixel[2] + brightness > 255)?255:((pixel[2] + brightness < 0)?0:pixel[2] + brightness);
      _image.at<cv::Vec3b>(i,j) = pixel;
    }
  }
  return _image;
}

void SimpleImageManipulation::BrightnessTrackBar(int track_bar_value, void * obj){
  SimpleImageManipulation * o = (SimpleImageManipulation*)obj;
  o->BrightnessChange(track_bar_value);
}

void SimpleImageManipulation::BrightnessChange(int value){
  value = (float(value - 50)/50.0)*255;
  cv::String windowName("Brightness");
  ShowImage(windowName, this->Brightness(value));
}

void SimpleImageManipulation::ShowBrightnessWindow(){
  int track_bar_value = 50;
  cv::String windowName("Brightness");
  cv::namedWindow(windowName);
  cv::createTrackbar( "Track bar", windowName, &track_bar_value, track_bar_value_max, BrightnessTrackBar, this);
  BrightnessTrackBar(track_bar_value, this);
  cv::waitKey(0);
  cv::destroyWindow(windowName);
}

cv::Mat SimpleImageManipulation::Contrast(float contrast){
  float factor = (259.0*(255 + contrast))/(255.0*(259 - contrast));
  if(this->image.empty()){
    cv::Mat null_matrix(0,0, CV_8UC3);
    return null_matrix;
  }
  cv::Mat _image(image.rows, image.cols, CV_8UC3);
  for(int i = 0; i < image.rows; ++i){
    for(int j = 0; j < image.cols; ++j){
      cv::Vec3b pixel = image.at<cv::Vec3b>(i,j);
      int B = (float(pixel[0] - 128.0)*factor + 128.0);
      int G = (float(pixel[1] - 128.0)*factor + 128.0);
      int R = (float(pixel[2] - 128.0)*factor + 128.0);
      pixel[0] = (B > 255)?255:((B < 0)?0:B);
      pixel[1] = (G > 255)?255:((G < 0)?0:G);
      pixel[2] = (R > 255)?255:((R < 0)?0:R);
      _image.at<cv::Vec3b>(i,j) = pixel;
    }
  }
  return _image; 
}

void SimpleImageManipulation::ContrastTrackBar(int track_bar_value, void * obj){
  SimpleImageManipulation * o = (SimpleImageManipulation*)obj;
  o->ContrastChange(track_bar_value);
}

void SimpleImageManipulation::ContrastChange(float value){
  value = (float(value - 50.0)/50.0)*255;
  cv::String windowName("Contrast");
  ShowImage(windowName, this->Contrast(value));
}

void SimpleImageManipulation::ShowContrastWindow(){
  int track_bar_value = 50;
  cv::String windowName("Contrast");
  cv::namedWindow(windowName);
  cv::createTrackbar( "Track bar", windowName, &track_bar_value, track_bar_value_max, ContrastTrackBar, this);
  ContrastTrackBar(track_bar_value, this);
  cv::waitKey(0);
  cv::destroyWindow(windowName);
}

cv::Mat SimpleImageManipulation::AverageFilter(int kernel_size){
  cv::Mat _image(image.rows, image.cols, CV_8UC3);
  cv:: Mat kernel(kernel_size, kernel_size, CV_32F);
  // Create a kernel

  for(int i = 0; i < kernel_size; ++i){
    for(int j = 0; j < kernel_size; ++j){
      kernel.at<float>(i,j) = 1.0f/((float)kernel_size*kernel_size);
    }
  }

  // Convolution

  for(int i = 0; i <= image.rows - kernel_size; ++i){
    for(int j = 0; j <= image.cols - kernel_size; ++j){
      cv::Vec3b pixel = image.at<cv::Vec3b>(i,j);
      int BGR[3] = {0,0,0};
      for(int ki = 0; ki < kernel_size; ++ki){
        for(int kj = 0; kj < kernel_size; ++kj){
          for(int channel = 0 ; channel < 3; ++channel){
            BGR[channel] += kernel.at<float>(ki,kj)*(image.at<cv::Vec3b>(i + ki,j + kj)[channel]);
          } 
        }
      }
      pixel[0] = (BGR[0] > 255)?255:((BGR[0] < 0)?0:BGR[0]);
      pixel[1] = (BGR[1] > 255)?255:((BGR[1] < 0)?0:BGR[1]);
      pixel[2] = (BGR[2] > 255)?255:((BGR[2] < 0)?0:BGR[2]);
      _image.at<cv::Vec3b>(i + kernel_size/2,j + kernel_size/2) = pixel;
    }
  }
  return _image; 
}


void SimpleImageManipulation::AverageFilterWindowKernelSizeTrackBar(int track_bar_value, void * obj){
  SimpleImageManipulation * o = (SimpleImageManipulation*)obj;
  o->AverageFilterKernelSizeChange(track_bar_value);
}

void SimpleImageManipulation::AverageFilterKernelSizeChange(int value){
  value = int(value);
  if(value % 2 ==0) ++value;
  if(value > image.cols || value > image.rows){
    if(image.cols > image.rows) value = image.cols;
    else value = image.rows;
  }
  cv::String windowName("AvgFilter");
  ShowImage(windowName, this->AverageFilter(value));
}

void SimpleImageManipulation::ShowAverageFilterWindow(){
  int track_bar_value = 0;
  int _track_bar_value_max;
  cv::String windowName("AvgFilter");
  cv::namedWindow(windowName);
  char TrackbarName[50];
  cv::createTrackbar( "Kernel Size will be ++1 if it's even", windowName, &track_bar_value, 30, AverageFilterWindowKernelSizeTrackBar, this);
  AverageFilterWindowKernelSizeTrackBar(track_bar_value, this);
  cv::waitKey(0);
  cv::destroyWindow(windowName);
}

cv::Mat SimpleImageManipulation::GaussianFilter(int kernel_size){
  cv::Mat _image(image.rows, image.cols, CV_8UC3);
  cv:: Mat kernel(kernel_size, kernel_size, CV_32F);
  // Create a kernel
  float sigma = 1;
  float s = 2.0 * sigma * sigma;
  int x = kernel_size/2;
  float sum = 0.0; 
  for(int i = -x; i <= x; ++i){
    for(int j = -x; j <= x; ++j){
      kernel.at<float>(i + x ,j + x)
       = (1.0f/((3.14*s)))*exp(-(i*i - j*j)/(s));
      sum += kernel.at<float>(i + x ,j + x);
    }
  }
  for (int i = 0; i < kernel_size; ++i) 
      for (int j = 0; j < kernel_size; ++j) 
          kernel.at<float>(i,j) /= sum;  
  // Convolution

  for(int i = 0; i <= image.rows - kernel_size; ++i){
    for(int j = 0; j <= image.cols - kernel_size; ++j){
      cv::Vec3b pixel = image.at<cv::Vec3b>(i,j);
      int BGR[3] = {0,0,0};
      for(int ki = 0; ki < kernel_size; ++ki){
        for(int kj = 0; kj < kernel_size; ++kj){
          for(int channel = 0 ; channel < 3; ++channel){
            BGR[channel] += kernel.at<float>(ki,kj)*(image.at<cv::Vec3b>(i + ki,j + kj)[channel]);
          } 
        }
      }
      pixel[0] = (BGR[0] > 255)?255:((BGR[0] < 0)?0:BGR[0]);
      pixel[1] = (BGR[1] > 255)?255:((BGR[1] < 0)?0:BGR[1]);
      pixel[2] = (BGR[2] > 255)?255:((BGR[2] < 0)?0:BGR[2]);
      _image.at<cv::Vec3b>(i + kernel_size/2,j + kernel_size/2) = pixel;
    }
  }
  return _image; 
}


void SimpleImageManipulation::GaussianFilterWindowKernelSizeTrackBar(int track_bar_value, void * obj){
  SimpleImageManipulation * o = (SimpleImageManipulation*)obj;
  o->GaussianFilterKernelSizeChange(track_bar_value);
}

void SimpleImageManipulation::GaussianFilterKernelSizeChange(int value){
  value = int(value);
  if(value % 2 ==0) ++value;
  if(value > image.cols || value > image.rows){
    if(image.cols > image.rows) value = image.cols;
    else value = image.rows;
  }
  cv::String windowName("Gaussian");
  ShowImage(windowName, this->GaussianFilter(value));
}

void SimpleImageManipulation::ShowGaussianFilterWindow(){
  int track_bar_value = 0;
  int _track_bar_value_max;
  cv::String windowName("Gaussian");
  cv::namedWindow(windowName);
  char TrackbarName[50];
  cv::createTrackbar( "Kernel Size will be ++1 if it's even", windowName, &track_bar_value, 30, GaussianFilterWindowKernelSizeTrackBar, this);
  GaussianFilterWindowKernelSizeTrackBar(track_bar_value, this);
  cv::waitKey(0);
  cv::destroyWindow(windowName);
}
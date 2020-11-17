#include "SimpleImageManipulation.h"
#include <string>
int main(int argc, char *argv[]){
    if(argc <= 2){
      if(argc == 2){
        std::string mode(argv[1]);
        if(mode == "--help"){
          std::cout << "-rgb2gray <image path>: Grayscale image" << std::endl;    
          std::cout << "-brightness <image path>: Change brightness of the image" << std::endl;
          std::cout << "-contrast <image path>: Change the contrast of the image" << std::endl;
          std::cout << "-avg <image path>: Apply Avg Filter image" << std::endl;
          std::cout << "-gauss <image path>: Apply Gaussian Filter image" << std::endl;
        }
      } else {
        std::cout << "Too few arguments" << std::endl;
        std::cout << "--help for more details" << std::endl; 
      }
      return 0;
    }
    std::string mode(argv[1]);
    cv::String filename(argv[2]);
    SimpleImageManipulation * sim = new SimpleImageManipulation(filename);
    if(mode == "-rgb2gray"){
      sim->ShowImage();
      sim->ShowImage("GrayScale", sim->GrayScale());
      cv::waitKey(0);
    }
    else if(mode == "-brightness"){
      sim->ShowImage();
      sim->ShowBrightnessWindow(); 
    }else if(mode == "-contrast"){
      sim->ShowImage();
      sim->ShowContrastWindow();
    }else if(mode == "-avg"){
      sim->ShowImage();
      sim->ShowAverageFilterWindow();
    }else if(mode == "-gauss"){
      sim->ShowImage();
      sim->ShowGaussianFilterWindow();
    }
    return 0;
}

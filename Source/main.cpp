//
//  main.cpp
//  ImageTool
//
//  Created by Adam J Leuer on 2017-11-3.
//  Copyright © 2017 ThoughtWorks, Inc. All rights reserved.

#include <iostream>
#include <istream>
#include <fstream>

#include "Image.hpp"

using namespace std;

static string resourcesPath = "./Resources";

void scaleImage() {
    const string & imageFilePath = resourcesPath + "/Spectrum";
    
    ifstream imageFile;
    imageFile.open(imageFilePath + ".png");
    
    png::image<png::rgb_pixel> image;
    
    image.read(imageFile);
    
    auto scaledImage = scale(image, 2, 8);
    
    scaledImage.write(imageFilePath + " Rescaled" + ".png");
}

void makeRandomImage() {
    png::image<png::rgb_pixel> image = createRandomImage(2880, 1600);
    
    image.write(resourcesPath + "/Random Image.png");
}

void makeRandomRGBImage() {
    png::rgb_pixel red = png::rgb_pixel(0xFF, 0x00, 0x9D);
    png::rgb_pixel green = png::rgb_pixel(0x9B, 0xFF, 0x00);
    png::rgb_pixel blue = png::rgb_pixel(0x00, 0xC7, 0xFF);
    
    png::image<png::rgb_pixel> image = createRandomImageFromPixels(2880, 1600, {red, green, blue});
    
    image.write(resourcesPath + "/Random RGB Image.png");
}


int main(int argc, const char * argv[]) {
    
    makeRandomImage();

    return 0;

}

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

int main(int argc, const char * argv[]) {
    
    const string & imageFileName = "./Spectrum";

    ifstream imageFile;
    imageFile.open(imageFileName + ".png");

    png::image<png::rgb_pixel> image;

    image.read(imageFile);

    auto scaledImage = scale(image, 2);

    scaledImage.write(imageFileName + " Rescaled" + ".png");

    return 0;
}

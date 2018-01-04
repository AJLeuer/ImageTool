//
//  Image.hpp
//  ImageTool
//
//  Created by Adam J Leuer on 2017-11-3.
//  Copyright © 2017 ThoughtWorks, Inc. All rights reserved.
//

#ifndef Image_hpp
#define Image_hpp

#include <iostream>
#include <thread>

#include <png++/png.hpp>

#include "Util.hpp"
#include "Random.hpp"



using namespace std;

typedef unsigned char byte;

png::image<png::rgb_pixel> scale(const png::image<png::rgb_pixel>  & image, unsigned int factor);

png::image<png::rgb_pixel> scale(const png::image<png::rgb_pixel>  & image, unsigned int factor, unsigned int numberOfThreads);

png::image<png::rgb_pixel> scale(const png::image<png::rgb_pixel>  & image, png::image<png::rgb_pixel>  & destinationImage, const unsigned long yMinimum, const unsigned long yMaximum, const unsigned widthScaleFactor, const unsigned heightScaleFactor);

png::basic_rgb_pixel<byte> shiftColors(const png::basic_rgb_pixel<byte> & pixel);



#endif /* Image_hpp */

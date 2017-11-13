//
//  Image.cpp
//  ImageTool
//
//  Created by Adam J Leuer on 2017-11-3.
//  Copyright © 2017 ThoughtWorks, Inc. All rights reserved.
//

#include "Image.hpp"

png::image<png::rgb_pixel> scale(const png::image<png::rgb_pixel>  & image, unsigned factor) {
    
    png::image<png::rgb_pixel> rescaledImage = png::image<png::rgb_pixel>((image.get_width() * factor), (image.get_height() * factor));
    
    const unsigned long rescaledWidth = rescaledImage.get_width();
    const unsigned long rescaledHeight = rescaledImage.get_height();
    
    for (unsigned y = 0, offs = 0; y < rescaledHeight; y++) {
        
        unsigned correspondingYCoord = (y / factor);
        vector<png::basic_rgb_pixel<byte>> correspondingRow = image.get_row(correspondingYCoord);
        
        for (unsigned x = 0; x < rescaledWidth; x++, offs++) {
        
            unsigned correspondingXCoord = (x / factor);
            auto correspondingPixel = correspondingRow.at(correspondingXCoord);
            
            rescaledImage.set_pixel(x, y, correspondingPixel);
        }
    }
    
    return rescaledImage;
}

png::basic_rgb_pixel<byte> shiftColors(const png::basic_rgb_pixel<byte> & pixel) {
    png::basic_rgb_pixel<byte> colorShiftedPixel;
    
    colorShiftedPixel.red = pixel.blue;
    colorShiftedPixel.green = pixel.red;
    colorShiftedPixel.blue = pixel.green;
    
    return colorShiftedPixel;
}

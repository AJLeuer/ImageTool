//
//  Image.cpp
//  ImageTool
//
//  Created by Adam J Leuer on 2017-11-3.
//  Copyright © 2017 ThoughtWorks, Inc. All rights reserved.

#include "Image.hpp"

png::image<png::rgb_pixel> scale(const png::image<png::rgb_pixel>  & image, unsigned factor) {
    
    png::image<png::rgb_pixel> rescaledImage = png::image<png::rgb_pixel>((image.get_width() * factor), (image.get_height() * factor));
    
    return scale(image, rescaledImage, 0, rescaledImage.get_height(), factor, factor);
}


png::image<png::rgb_pixel> scale(const png::image<png::rgb_pixel>  & image, unsigned int factor, unsigned int numberOfThreads) {
    
    png::image<png::rgb_pixel> rescaledImage = png::image<png::rgb_pixel>((image.get_width() * factor), (image.get_height() * factor));
    
    unsigned long rowsPerThread = rescaledImage.get_height() / numberOfThreads;
    
    vector<thread> scalerThreads;
    
    //start scaler threads
    for (unsigned i = 0, destinationYMinimum = 0, destinationYMaximum = (unsigned) rowsPerThread; i < numberOfThreads; i++) {
        
        auto scaleRunner = [& image, & rescaledImage, destinationYMinimum, destinationYMaximum, factor] () {
            scale(image, rescaledImage, destinationYMinimum, destinationYMaximum, factor, factor);
        };
        
        std::thread scalerThread(scaleRunner);
        scalerThreads.push_back(std::move(scalerThread));
        
        destinationYMinimum += rowsPerThread;
        destinationYMaximum += rowsPerThread;
    }
    
    //wait for all threads to finish
    while (scalerThreads.empty() == false) {
        if (scalerThreads.back().joinable() == true) {
            scalerThreads.back().join();
            scalerThreads.pop_back();
        }
        //this_thread::sleep_for(chrono::nanoseconds(10000));
    }
    
    return rescaledImage;
}

png::image<png::rgb_pixel> scale(const png::image<png::rgb_pixel>  & image, png::image<png::rgb_pixel>  & destinationImage, const unsigned long destinationYMinimum, const unsigned long destinationYMaximum, const unsigned widthScaleFactor, const unsigned heightScaleFactor) {
    
    const unsigned long destinationImageWidth = destinationImage.get_width();
    const unsigned long destinationImageHeight = destinationImage.get_height();
    
    for (unsigned long y = destinationYMinimum, offs = 0; (y < destinationImageHeight) && (y < destinationYMaximum); y++) {
        
        unsigned long correspondingYCoord = (y / heightScaleFactor);
        vector<png::basic_rgb_pixel<byte>> correspondingRow = image.get_row(correspondingYCoord);
        
        for (unsigned x = 0; x < destinationImageWidth; x++, offs++) {
            
            unsigned correspondingXCoord = (x / widthScaleFactor);
            auto correspondingPixel = correspondingRow.at(correspondingXCoord);
            
            destinationImage.set_pixel(x, y, correspondingPixel);
        }
    }
    
    
    return destinationImage;
}




png::basic_rgb_pixel<byte> shiftColors(const png::basic_rgb_pixel<byte> & pixel) {
    png::basic_rgb_pixel<byte> colorShiftedPixel;
    
    colorShiftedPixel.red = pixel.blue;
    colorShiftedPixel.green = pixel.red;
    colorShiftedPixel.blue = pixel.green;
    
    return colorShiftedPixel;
}

png::image<png::rgb_pixel> createRandomImage(unsigned width, unsigned height) {
    png::image<png::rgb_pixel> image = png::image<png::rgb_pixel>(width, height);
    

    FastRand<uint8_t> rgbRandomizer(0x00, 0xFF);
    
    for (unsigned x = 0; x < width; x++) {
        for (unsigned y = 0; y < height; y++) {
            
            png::rgb_pixel pixel = png::rgb_pixel{rgbRandomizer(), rgbRandomizer(), rgbRandomizer()};
            
            image.set_pixel(x, y, pixel);
        }
    }
    
    return image;
}


png::image<png::rgb_pixel> createRandomImageFromPixels(unsigned width, unsigned height, vector<png::rgb_pixel> pixels) {
    png::image<png::rgb_pixel> image = png::image<png::rgb_pixel>(width, height);
    
    FastRand<unsigned long> pixelPicker(0, pixels.size() - 1);
    
    for (unsigned x = 0; x < width; x++) {
        for (unsigned y = 0; y < height; y++) {
            
            png::rgb_pixel pixel = pixels.at(pixelPicker.nextValue());
            
            image.set_pixel(x, y, pixel);
        }
    }
    
    return image;
}











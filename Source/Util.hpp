//
//  Util.cpp
//  ImageTool
//
//  Created by Adam J Leuer on 2017-11-9.
//  Copyright © 2017 ThoughtWorks, Inc. All rights reserved.
//
/* The classes below are exported */
#pragma GCC visibility push(default)

#include <iostream>

#include "Random.hpp"

template <typename N>
constexpr N addWithOverflow(const N number, const N numberToAdd, const N pointOfOverflow) {
    //auto overflowCorrectedNumberToAdd = (numberToAdd == 0) ? 0 : (pointOfOverflow % numberToAdd);
    
    auto result = (number + numberToAdd);
    
    if (result >= pointOfOverflow) {
        result = numberToAdd % pointOfOverflow;
    }
    
    return result;
}

template <typename N>
constexpr N subtractWithOverflow(const N number, const N numberToSubtract, const N pointOfOverflow) {
    long result = 0;
    
    if (numberToSubtract > pointOfOverflow) {
        long overflowCorrectedNumberToSubtract = (numberToSubtract == 0) ? 0 : (numberToSubtract % pointOfOverflow);
        result = ((long) number - (long) overflowCorrectedNumberToSubtract);
    }
    else {
        result = ((long)number - (long)numberToSubtract);
    }
    if (result < 0) {
        return (N)(pointOfOverflow + result);
    }
    return (N)result;
    
}

template <typename N>
N generatePossiblyRandomPixelCoord(N defalt, FastRand<N> & randomGenerator) {
    
    float returnRandom = FastRand<float>::defaultRandom(0, 1.0);
    
    if (returnRandom < 0.09) {
        return randomGenerator();
    }
    
    return defalt;
}

#pragma GCC visibility pop

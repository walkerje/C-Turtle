//MIT License
//
//Copyright (c) 2019 Jesse W. Walker
//
//Permission is hereby granted, free of charge, to any person obtaining a copy
//of this software and associated documentation files (the "Software"), to deal
//in the Software without restriction, including without limitation the rights
//to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
//copies of the Software, and to permit persons to whom the Software is
//furnished to do so, subject to the following conditions:
//
//The above copyright notice and this permission notice shall be included in all
//copies or substantial portions of the Software.
//
//THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
//IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
//FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
//AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
//LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
//OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
//SOFTWARE.

/* 
 * File:    Common.hpp
 * Project: C-Turtle
 * Created on May 20, 2019, 2:40 PM
 */

#pragma once

#include <cstdint>
#include <thread>

#ifndef _MSC_VER
    #ifndef cimg_use_openmp
        #define cimg_use_openmp 1
    #endif
#endif

#include "CImg.h"

/*Common header so we don't have to redefine common typedefs,
  such as Image or the vector types.*/
namespace cturtle{
    /**The CImg library namespace alias used by the CTurtle library.*/
    namespace cimg = cimg_library;
    /**The common Image type used by CTurtle.*/
    typedef cimg::CImg<uint8_t> Image;
    
    /**\brief Represents a coordinate pair (e.g, x & y)
     * This class is represented as a low-precision point, because
     * this data type tends to be most easily drawn to a simple canvas.*/
    struct ivec2{
        /**The X component.*/
        int x = 0;
        /**The Y component.*/
        int y = 0;
        
        /**\brief Empty constructor.*/
        ivec2(){}
        /**\brief Assignment constructor.
         *\param x The X value of this ivec2.
         *\param y The Y value of this ivec2.*/
        ivec2(int x, int y) : x(x), y(y){}
        /**\brief Copy constructor.
         *\param other Another instance of ivec2 from which to derive value.*/
        ivec2(const ivec2& other) : x(other.x), y(other.y){}
        
        /*Array access operator overload.*/
        /**\brief Array access operator overload. Useful for convenience.
         *\param index The index of one of the components of this ivec2 (0..1)
         *\return A reference to the index */
        inline int& operator[](int index){
            return ((int*)this)[index];
        }
    };
    
    /**\brief Returns the distance between the two specified points.*/
    inline int distance(const ivec2& a, const ivec2& b){
        return std::sqrt(std::pow(b.x - a.x, 2) + std::pow(b.y - a.y, 2));
    }
    
    inline ivec2 middle(const ivec2& a, const ivec2& b){
       return ivec2((a.x + b.x) / 2, (a.y + b.y) / 2); 
    }
    
    /**\brief Sleeps the calling thread the specified amount of milliseconds.
     *\param ms The total number of milliseconds to sleep.*/
    inline void sleep(long ms){
        if(ms <= 0)
            return;
        std::this_thread::sleep_for(std::chrono::milliseconds(ms));
    }
    
    /**\brief Returns the amount of time, in milliseconds, since the UNIX epoch.*/
    inline unsigned long epochTime(){
        return std::chrono::high_resolution_clock::now().time_since_epoch() 
                    / std::chrono::milliseconds(1);
    }
}
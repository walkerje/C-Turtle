/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:    Common.hpp
 * Project: C-Turtle
 * Created on May 20, 2019, 2:40 PM
 */

#pragma once

#include <cstdint>
#include <thread>
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
    
    /**\brief Sleeps the calling thread the specified amount of milliseconds.
     *\param ms The total number of milliseconds to sleep.*/
    inline void sleep(long ms){
        std::this_thread::sleep_for(std::chrono::milliseconds(ms));
    }
    
    /**\brief Returns the amount of time, in milliseconds, since the UNIX epoch.*/
    inline unsigned long epochTime(){
        return std::chrono::high_resolution_clock::now().time_since_epoch() 
                    / std::chrono::milliseconds(1);
    }
}
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
    namespace cimg = cimg_library;
    typedef cimg::CImg<uint8_t> Image;
    
    struct ivec2{
        int x = 0;
        int y = 0;
        
        ivec2(){}
        ivec2(int x, int y) : x(x), y(y){}
        ivec2(const ivec2& other) : x(other.x), y(other.y){}
        
        /*Array access operator overload.*/
        inline int& operator[](int index){
            return ((int*)this)[index];
        }
    };
    
    /*Sleeps the calling thread for the specified number of milliseconds.*/
    inline void sleep(long ms){
        std::this_thread::sleep_for(std::chrono::milliseconds(ms));
    }
    
    inline unsigned long epochTime(){
        return std::chrono::high_resolution_clock::now().time_since_epoch() 
                    / std::chrono::milliseconds(1);
    }
}
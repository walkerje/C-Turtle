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
#include "linalg.hpp"
#include "CImg.h"

/*Common header so we don't have to redefine common typedefs.*/
namespace cturtle{
    namespace cimg = cimg_library;
    typedef cimg::CImg<uint8_t> Image;
    
    typedef linalg::vec<int, 2>         ivec2;
    typedef linalg::vec<float, 2>       vec2;
    typedef linalg::vec<float, 4>       vec4;
    typedef linalg::mat<float, 4, 4>    mat4;
    
    inline void sleep(long ms){
        std::this_thread::sleep_for(std::chrono::milliseconds(ms));
    }
}
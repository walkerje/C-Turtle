/* 
 * File:    CTurtle.hpp
 * Project: C-Turtle
 * Created on May 13, 2019, 2:31 PM
 */

#pragma once

#ifndef CTURTLE_MSVC_NO_AUTOLINK
    #ifdef _MSC_VER
    /*Automatically link to the necessary windows libraries while under MSVC.*/
    #pragma comment(lib, "kernel32.lib")
    #pragma comment(lib, "gdi32.lib")
    #endif
#elif !defined(_WIN32)
    #ifndef CTURTLE_NO_MSVC_LINK_WARN
        #warn "You must link against X11 Libraries to get a CTurtle display on this system!" 
    #endif
#endif

/*Standard Includes*/
#include <string>
#include <list>

/*Local Includes*/
#include "CImg.h"

namespace cturtle{
    namespace cimg = cimg_library;
    //TODO: Wrap CImgDisplay in TurtleScreen class?
    typedef cimg::CImgDisplay TurtleScreen;
    
    enum TurtleCommandType{
        /*TC_<TYPE> Enumeration*/
        TCT_UNKNOWN,
        TCT_MOVE,
        
        TCT_ENUM_MAX
    };
    
    struct TurtleCommand{
        union{
            
        } data;
        
        TurtleCommandType type = TCT_UNKNOWN;
    };
    
    class Turtle{
    public:
        
    protected:
        std::list<TurtleCommand> commands;
    };
}
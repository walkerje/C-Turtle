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
 * File:    UserIO.hpp
 * Project: C-Turtle
 * Created on May 20, 2019, 1:51 PM
 */

#pragma once
#include "CImg.h"
#include <list>
#include <functional>

namespace cturtle{
    /**\brief The KeyboardKey Enumeration contains declarations for all
     *        accepted keyboard input keys.
     * \see keyFromName()*/
    enum KeyboardKey {
        KEY_ESC = cimg_library::cimg::keyESC,
        KEY_F1 = cimg_library::cimg::keyF1,
        KEY_F2 = cimg_library::cimg::keyF2,
        KEY_F3 = cimg_library::cimg::keyF3,
        KEY_F4 = cimg_library::cimg::keyF4,
        KEY_F5 = cimg_library::cimg::keyF5,
        KEY_F6 = cimg_library::cimg::keyF6,
        KEY_F7 = cimg_library::cimg::keyF7,
        KEY_F8 = cimg_library::cimg::keyF8,
        KEY_F9 = cimg_library::cimg::keyF9,
        KEY_F10 = cimg_library::cimg::keyF10,
        KEY_F11 = cimg_library::cimg::keyF11,
        KEY_F12 = cimg_library::cimg::keyF12,
        KEY_PAUSE = cimg_library::cimg::keyPAUSE,
        KEY_1 = cimg_library::cimg::key1,
        KEY_2 = cimg_library::cimg::key2,
        KEY_3 = cimg_library::cimg::key3,
        KEY_4 = cimg_library::cimg::key4,
        KEY_5 = cimg_library::cimg::key5,
        KEY_6 = cimg_library::cimg::key6,
        KEY_7 = cimg_library::cimg::key7,
        KEY_8 = cimg_library::cimg::key8,
        KEY_9 = cimg_library::cimg::key9,
        KEY_0 = cimg_library::cimg::key0,
        KEY_BACKSPACE = cimg_library::cimg::keyBACKSPACE,
        KEY_INSERT = cimg_library::cimg::keyINSERT,
        KEY_HOME = cimg_library::cimg::keyHOME,
        KEY_PAGEUP = cimg_library::cimg::keyPAGEUP,
        KEY_TAB = cimg_library::cimg::keyTAB,
        KEY_Q = cimg_library::cimg::keyQ,
        KEY_W = cimg_library::cimg::keyW,
        KEY_E = cimg_library::cimg::keyE,
        KEY_R = cimg_library::cimg::keyR,
        KEY_T = cimg_library::cimg::keyT,
        KEY_Y = cimg_library::cimg::keyY,
        KEY_U = cimg_library::cimg::keyU,
        KEY_I = cimg_library::cimg::keyI,
        KEY_O = cimg_library::cimg::keyO,
        KEY_P = cimg_library::cimg::keyP,
        KEY_DELETE = cimg_library::cimg::keyDELETE,
        KEY_END = cimg_library::cimg::keyEND,
        KEY_PAGEDOWN = cimg_library::cimg::keyPAGEDOWN,
        KEY_CAPSLOCK = cimg_library::cimg::keyCAPSLOCK,
        KEY_A = cimg_library::cimg::keyA,
        KEY_S = cimg_library::cimg::keyS,
        KEY_D = cimg_library::cimg::keyD,
        KEY_F = cimg_library::cimg::keyF,
        KEY_G = cimg_library::cimg::keyG,
        KEY_H = cimg_library::cimg::keyH,
        KEY_J = cimg_library::cimg::keyJ,
        KEY_K = cimg_library::cimg::keyK,
        KEY_L = cimg_library::cimg::keyL,
        KEY_ENTER = cimg_library::cimg::keyENTER,
        KEY_SHIFTLEFT = cimg_library::cimg::keySHIFTLEFT,
        KEY_Z = cimg_library::cimg::keyZ,
        KEY_X = cimg_library::cimg::keyX,
        KEY_C = cimg_library::cimg::keyC,
        KEY_V = cimg_library::cimg::keyV,
        KEY_B = cimg_library::cimg::keyB,
        KEY_N = cimg_library::cimg::keyN,
        KEY_M = cimg_library::cimg::keyM,
        KEY_SHIFTRIGHT = cimg_library::cimg::keySHIFTRIGHT,
        KEY_ARROWUP = cimg_library::cimg::keyARROWUP,
        KEY_CTRLLEFT = cimg_library::cimg::keyCTRLLEFT,
        KEY_APPLEFT = cimg_library::cimg::keyAPPLEFT,
        KEY_ALT = cimg_library::cimg::keyALT,
        KEY_SPACE = cimg_library::cimg::keySPACE,
        KEY_ALTGR = cimg_library::cimg::keyALTGR,
        KEY_APPRIGHT = cimg_library::cimg::keyAPPRIGHT,
        KEY_MENU = cimg_library::cimg::keyMENU,
        KEY_CTRLRIGHT = cimg_library::cimg::keyCTRLRIGHT,
        KEY_ARROWLEFT = cimg_library::cimg::keyARROWLEFT,
        KEY_ARROWDOWN = cimg_library::cimg::keyARROWDOWN,
        KEY_ARROWRIGHT = cimg_library::cimg::keyARROWRIGHT,
        KEY_PAD0 = cimg_library::cimg::keyPAD0,
        KEY_PAD1 = cimg_library::cimg::keyPAD1,
        KEY_PAD2 = cimg_library::cimg::keyPAD2,
        KEY_PAD3 = cimg_library::cimg::keyPAD3,
        KEY_PAD4 = cimg_library::cimg::keyPAD4,
        KEY_PAD5 = cimg_library::cimg::keyPAD5,
        KEY_PAD6 = cimg_library::cimg::keyPAD6,
        KEY_PAD7 = cimg_library::cimg::keyPAD7,
        KEY_PAD8 = cimg_library::cimg::keyPAD8,
        KEY_PAD9 = cimg_library::cimg::keyPAD9,
        KEY_PADADD = cimg_library::cimg::keyPADADD,
        KEY_PADSUB = cimg_library::cimg::keyPADSUB,
        KEY_PADMUL = cimg_library::cimg::keyPADMUL,
        KEY_PADDIV = cimg_library::cimg::keyPADDIV
    };
    
    /**Returns a read-only reference to a list of all
     * possible input keys.*/
    const std::map<std::string, KeyboardKey>& listKeys();
    
    /**\brief The MouseButton Enumeration holds all accepted mouse
     *        input buttons.
     *  These button enumerations are represented as bitwise flags.*/
    enum MouseButton{//Stored as bitwise flags from CImgDisplay
        MOUSEB_LEFT,//Left Mouse Button
        MOUSEB_RIGHT,//Right Mouse Button
        MOUSEB_MIDDLE//Middle Mouse Button
    };
    
    struct InputEvent{
        //True for keyboard, false for mouse
        bool type = false;
        //For keyboard; true if key down, false if key up.
        bool isDown = false;
        //mouseX, mouseY
        int mX = 0;
        int mY = 0;
        /*void callback pointer. cast and called when processed.*/
        void* cbPointer = nullptr;
    };
    
    /**\brief Returns a KeyboardKey when given its name as a string.
     * All key names are capitalized, and the only difference from
     * their names as a string representation is the omission of the
     * "KEY_" prefix.
     * \see KeyboardKey*/
    KeyboardKey keyFromName(const std::string& name);
}

#ifdef CTURTLE_IMPLEMENTATION
#include <map>
namespace cturtle{
    namespace{
        const std::map<std::string, KeyboardKey> NAMEDKEYS = {
            {"ESC", KEY_ESC},
            {"F1", KEY_F1},
            {"F2", KEY_F2},
            {"F3", KEY_F3},
            {"F4", KEY_F4},
            {"F5", KEY_F5},
            {"F6", KEY_F6},
            {"F7", KEY_F7},
            {"F8", KEY_F8},
            {"F9", KEY_F9},
            {"F10", KEY_F10},
            {"F11", KEY_F11},
            {"F12", KEY_F12},
            {"PAUSE", KEY_PAUSE},
            {"1", KEY_1},
            {"2", KEY_2},
            {"3", KEY_3},
            {"4", KEY_4},
            {"5", KEY_5},
            {"6", KEY_6},
            {"7", KEY_7},
            {"8", KEY_8},
            {"9", KEY_9},
            {"0", KEY_0},
            {"BACKSPACE", KEY_BACKSPACE},
            {"INSERT", KEY_INSERT},
            {"HOME", KEY_HOME},
            {"PAGEUP", KEY_PAGEUP},
            {"TAB", KEY_TAB},
            {"Q", KEY_Q},
            {"W", KEY_W},
            {"E", KEY_E},
            {"R", KEY_R},
            {"T", KEY_T},
            {"Y", KEY_Y},
            {"U", KEY_U},
            {"I", KEY_I},
            {"O", KEY_O},
            {"P", KEY_P},
            {"DELETE", KEY_DELETE},
            {"END", KEY_END},
            {"PAGEDOWN", KEY_PAGEDOWN},
            {"CAPSLOCK", KEY_CAPSLOCK},
            {"A", KEY_A},
            {"S", KEY_S},
            {"D", KEY_D},
            {"F", KEY_F},
            {"G", KEY_G},
            {"H", KEY_H},
            {"J", KEY_J},
            {"K", KEY_K},
            {"L", KEY_L},
            {"ENTER", KEY_ENTER},
            {"SHIFTLEFT", KEY_SHIFTLEFT},
            {"Z", KEY_Z},
            {"X", KEY_X},
            {"C", KEY_C},
            {"V", KEY_V},
            {"B", KEY_B},
            {"N", KEY_N},
            {"M", KEY_M},
            {"SHIFTRIGHT", KEY_SHIFTRIGHT},
            {"ARROWUP", KEY_ARROWUP},
            {"CTRLLEFT", KEY_CTRLLEFT},
            {"APPLEFT", KEY_APPLEFT},
            {"ALT", KEY_ALT},
            {"SPACE", KEY_SPACE},
            {"ALTGR", KEY_ALTGR},
            {"APPRIGHT", KEY_APPRIGHT},
            {"MENU", KEY_MENU},
            {"CTRLRIGHT", KEY_CTRLRIGHT},
            {"ARROWLEFT", KEY_ARROWLEFT},
            {"ARROWDOWN", KEY_ARROWDOWN},
            {"ARROWRIGHT", KEY_ARROWRIGHT},
            {"PAD0", KEY_PAD0},
            {"PAD1", KEY_PAD1},
            {"PAD2", KEY_PAD2},
            {"PAD3", KEY_PAD3},
            {"PAD4", KEY_PAD4},
            {"PAD5", KEY_PAD5},
            {"PAD6", KEY_PAD6},
            {"PAD7", KEY_PAD7},
            {"PAD8", KEY_PAD8},
            {"PAD9", KEY_PAD9},
            {"PADADD", KEY_PADADD},
            {"PADSUB", KEY_PADSUB},
            {"PADMUL", KEY_PADMUL},
            {"PADDIV", KEY_PADDIV}
        };
    }
    
    const std::map<std::string, KeyboardKey>& getKeys(){
        return NAMEDKEYS;
    }
    
    KeyboardKey keyFromName(const std::string& name){
        return NAMEDKEYS.at(name);
    }
}
#endif
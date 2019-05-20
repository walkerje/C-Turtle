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
#endif

/*Remember to link against X11 libs to get the */

/*Standard Includes*/
#include <cstdint>
#include <cmath>
#include <algorithm>
#include <string>
#include <list>
#include <functional>
#include <utility>

/*Local Includes*/
#include "Common.hpp"
#include "Geometry.hpp"
#include "Color.hpp"
#include "UserIO.hpp"

namespace cturtle{
    /*Callback function typedefs for event listeners.*/
    
    /*Mouse event callback type.*/
    typedef std::function<void(vec2)> MouseFunc;
    
    /*Keyboard event callback type.*/
    typedef std::function<void(KeyboardKey)> KeyFunc;
    
    /*Timer event callback type.*/
    typedef std::function<void(void)> TimerFunc;
    
    /*  AffineTransform
     *      This class handles the maths behind the transformations
     *      of turtle objects. This includes rotation, movement,
     *      and scaling.
     */
    struct AffineTransform{
        
    };

    //RawTurtle prototype definition
    class RawTurtle;
    //TurtleScreen prototype definition
    class TurtleScreen;
    
    //Alias for the CImg library, for convenience.
    namespace cimg = cimg_library;
    
    /*TODO: Document Me*/
    enum ScreenMode{
        SM_STANDARD,
        SM_LOGO,
        SM_WORLD
    };
    
    /* TurtleScreen
     *      Holds and maintains all facilities in relation to displaying
     *      turtles and consuming input events from users through callbacks.
     */
    class TurtleScreen{
    public:
        TurtleScreen() : display(800, 600){
            display.set_title("CTurtle");
            canvas.assign(display);
            swapDisplay(2);
        }
        TurtleScreen(const std::string& title) : display(800, 600){
            display.set_title(title.c_str());
            canvas.assign(display);
            swapDisplay(2);
        }
        TurtleScreen(int width, int height, const std::string& title) : display(width, height){
            display.set_title(title.c_str());
            canvas.assign(display);
            swapDisplay(2);
        }
        
        /*Sets the background color of the screen.*/
        void bgcolor(const Color& color){
            backgroundColor = color;
        }
        
        /*Returns the background color of the screen.*/
        Color bgcolor(){
            return backgroundColor;
        }
        
        //TODO: bgpic()
        void bgpic(const Image& img){
            backgroundImage.assign(img);
            backgroundImage.resize(window_width(), window_height());
        }
        
        /*Returns a reference to the background image.*/
        const Image& bgpic(){
            return backgroundImage;
        }

        /*TODO: Document Me*/        
        void mode(ScreenMode mode){
            curMode = mode;
        }
        
        /*TODO: Document Me*/
        ScreenMode mode(){
            return curMode;
        }
        
        /*TODO: Document Me*/
        void colormode(int val){
            colorCap = val;
        }
        
        /*TODO: Document Me*/
        int colormode(){
            return colorCap;
        }
        
        /*TODO: Document Me*/
        void clearscreen();
        
        /*Alias for @clearscreen*/
        inline void clear(){clearscreen();}
        
        /*Resets all turtles belonging to this screen to their original state.*/
        void resetscreen();
        
        /*Resets all turtles belonging to this screen to their original state.*/
        inline void reset(){resetscreen();}
        
        /*Returns the size of this screen, in pixels.
          Also returns the background color of the screen,
          by assigning the input reference.*/
        vec2 screensize(Color& bg);
        
        /*Returns the size of the screen, in pixels.*/
        inline vec2 screensize(){
            Color temp;
            return screensize(temp);
        }
        
        /*Sets the world coordinates.*/
        void setworldcoordinates(vec2 lowerLeft, vec2 upperRight);
        
        //TODO: Tracer Func
        
        /*TODO: Document Me*/
        void update();
        
        /*Sets the delay set between turtle commands.*/
        void delay(unsigned int ms);
        
        //TODO: Document me more
        /*Returns the delay set between turtle commands in MS.*/
        unsigned int delay();
        
        /*Returns the width of the window, in pixels.*/
        int window_width(){
            return display.window_width();
        }
        
        /*Returns the height of the window, in pixels.*/
        int window_height(){
            return display.window_height();
        }
        
        /*Saves the display as a file, the format of which is dependent
          on the file extension given in the specified file path string.*/
        inline void save(const std::string& file){
            cimg::CImg<uint8_t> screenshotImg;
            display.screenshot(screenshotImg);
            screenshotImg.save(file.c_str());
        }
        
        //TODO: Document me more
        /*Closes this window.*/
        void bye();
        
        /*Returns the canvas image used by this screen.
          In all actuality, this function returns a reference
          to */
        Image& getcanvas(){
            return canvas;
        }
        
        /*Returns the internal CImg display.*/
        cimg::CImgDisplay& getInternalDisplay(){
            return display;
        }
        
        /*Swaps the display.*/
        inline void swap(){swapDisplay();}
    protected:
        cimg::CImgDisplay   display;
        Image               canvas;
        
        Color backgroundColor   = Color::white;
        Image backgroundImage;
        ScreenMode curMode      = SM_STANDARD;
        int colorCap            = 255;
        bool  tracing = true;
        
        vec2 worldLowerLeft, worldUpperRight;
        
        unsigned int delayMS = 10;
        
        /*Swaps the front and back buffers, then displays the front buffer.*/
        inline void swapDisplay(int times = 1){
            for(int i = 0; i < times; i++){
                display.display(canvas);
                /*Reset the display to just have background image or color.*/
                if(!backgroundImage.is_empty()){
                    canvas.draw_image(backgroundImage);
                }else{
                    canvas.draw_rectangle(0, 0, window_width(), window_height(), backgroundColor.rgbPtr());
                }
            }
        }
        
//        std::list<RawTurtle&> turtles;
        
        //TODO: Map to individual buttons (e.g, key is button, val is callback)
//        KeyFunc     keyFunc     = [](char){};
//        MouseFunc   clickFunc   = [](vec2){};
        TimerFunc   timerFunc   = [](void){};
    };
    
    enum TurtleSpeed{
        TS_FASTEST  = 0,
        TS_FAST     = 10,
        TS_NORMAL   = 6,
        TS_SLOW     = 3,
        TS_SLOWEST  = 1
    };

    //TODO: Finish and document
    class RawTurtle{
    public:
        RawTurtle(TurtleScreen& screen) : screen(screen){}
        
        //Motion
        void forward(int pixels);
        inline void fd(int pixels){forward(pixels);}
        
        void backward(int pixels);
        inline void bk(int pixels){backward(pixels);}
        inline void back(int pixels){backward(pixels);}
        
        void right(float amt){
            angle += (!angleMode ? (toRadians(amt)) : amt);
        }
        inline void rt(float angle){right(angle);}
        
        void left(float amt){
            angle -= (!angleMode ? (toRadians(amt)) : amt);
        }
        inline void lt(float angle){left(angle);}
        
        void go_to(int x, int y);//had to change due to C++ keyword "goto"
        inline void setpos(int x, int y){go_to(x,y);}
        inline void setposition(int x, int y){go_to(x,y);}
        
        void setx(int x);
        void sety(int y);
        
        //TODO: refine
        void setheading();
        inline void seth(){setheading();}
        
        void home();
        
        void circle();
        
        void dot();
        
        void clearstamp();
        void clearstamps();
        
        void undo();
        
        void speed(float val){
            moveSpeed = val;
        }
        
        float speed(){
            return moveSpeed;
        }
        
        void degrees(){angleMode = false;}
        inline void radians(){angleMode = true;}
        
        void reset();
        
        virtual ~RawTurtle(){}
    protected:
        TurtleScreen& screen = *((TurtleScreen*)nullptr);
        double angle = 0;
        vec2 position = {0,0};
        bool angleMode = false;//Using Radians = true, degrees = false
        float moveSpeed = TS_NORMAL;
        
        RawTurtle(){}
        //Children which overload this MUST redefine the screen reference.
    };
}
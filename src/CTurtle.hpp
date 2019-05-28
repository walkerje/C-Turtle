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

//TODO: Just a personal note; active v. passive rendering is something to
//think about. I think turtles use a form of passive rendering.

namespace cturtle{
    /*Callback function typedefs for event listeners.*/
    
    /*Mouse event callback type.*/
    typedef std::function<void(ivec2)> MouseFunc;
    
    /*Keyboard event callback type.*/
    typedef std::function<void(KeyboardKey)> KeyFunc;
    
    /*Timer event callback type.*/
    typedef std::function<void(void)> TimerFunc;
    
    //RawTurtle prototype definition
    class RawTurtle;
    //TurtleScreen prototype definition
    class TurtleScreen;
    
    //Alias for the CImg library, for convenience.
    namespace cimg = cimg_library;
    
    /*Shape Registration and deletion.*/
     
    void registerShape(const std::string& name, const Polygon& p);
    inline void addShape(const std::string& name, const Polygon& p){
        registerShape(name, p);
    }
    
    const Polygon& shape(const std::string name);
    
    enum TurtleSpeed{
        TS_FASTEST  = 0,
        TS_FAST     = 10,
        TS_NORMAL   = 6,
        TS_SLOW     = 3,
        TS_SLOWEST  = 1
    };
    
    struct SceneObject{
        //Owns whatever geometry it contains.
        //When the scene object is deconstructed,
        //the geometry is automatically deleted.
        std::unique_ptr<IDrawableGeometry> geom;
        Color color;
        AffineTransform transform;
        
        bool stamp = false;
        int stampid = -1;
        
        SceneObject(){}
        SceneObject(IDrawableGeometry* geom, Color color, const AffineTransform& t) :
            geom(geom), color(color), transform(t){}
        
        SceneObject(IDrawableGeometry* geom, Color color, const AffineTransform& t, int stampid) :
            geom(geom), color(color), transform(t), stamp(true), stampid(stampid){}
    };

    //TODO: Finish and document
    class RawTurtle{
    public:
        /*Implemented in source impl. file*/
        RawTurtle(TurtleScreen& scr);
        
        //Motion
        void forward(int pixels);
        inline void fd(int pixels){forward(pixels);}
        
        void backward(int pixels);
        inline void bk(int pixels){backward(pixels);}
        inline void back(int pixels){backward(pixels);}
        
        void right(float amt);
        inline void rt(float angle){right(angle);}
        
        void left(float amt);
        inline void lt(float angle){left(angle);}
        
        void goTo(int x, int y);
        inline void setpos(int x, int y){goTo(x,y);}
        inline void setposition(int x, int y){goTo(x,y);}
        
        void setx(int x);
        void sety(int y);
        
        //TODO: refine
        void setheading(){}
        inline void seth(){setheading();}
        
        void home();
        
        void circle(int radius, int steps, Color color);
        
        inline void circle(Color color){
            circle(30, 15, color);
        }
        
        void dot(Color color, int size = 10){
            circle(size/2, 4, color);
        }
        
        /*Sets the "filling" state.*/
        void fill(bool state);
        
        inline void begin_fill(){fill(true);}
        inline void end_fill(){fill(false);}
        
        void fillcolor(Color c){fillColor = c;}
        Color fillcolor(){return fillColor;}
        
        //TODO: Stamps boiiiii
        int stamp();
        void clearstamp(int stampid);
        void clearstamps(int stampid = -1);
        
        /*Sets the shape of this turtle.*/
        void shape(const std::string& name){
            cursor = cturtle::shape(name);
        }
        
        void shape(const Polygon& p){
            cursor = p;
        }
        
        /*Returns the shape of this turtle.*/
        const Polygon& shape(){
            return cursor;
        }
        
        void undo();
        
        void speed(float val){
            moveSpeed = val;
        }
        
        float speed(){
            return moveSpeed;
        }
        
        //TODO: Tracer Funcs
        void trace(bool state){
            tracing = state;
        }
        bool trace(){return tracing;}
        
        void draw(const AffineTransform& screenTransform, Image& canvas);
        
        void degrees(){angleMode = false;}
        inline void radians(){angleMode = true;}
        
        /*Resets this turtle.*/
        void reset();
        
        virtual ~RawTurtle(){}
    protected:
        std::list<SceneObject> objects;
        
        std::vector<Point> tracePoints = {{0,0}};
        AffineTransform transform;
        
        /*Pushes the specified object attibutes as an object to this turtle's
          "drawing" list.*/
        inline void pushGeom(const AffineTransform& t, Color color, IDrawableGeometry* geom){
            objects.emplace_back(geom, color, t);
        }
        
        inline void pushStamp(const AffineTransform& t, Color color, IDrawableGeometry* geom){
            objects.emplace_back(geom, color, t, curStamp++);
        }
        
        /*Returns the speed, of any applicable animation,
          in milliseconds, based off of this turtle's speed setting.*/
        inline long getAnimMS(){
            return moveSpeed <= 0 ? 0 : long(((10.0f - moveSpeed)/10.0f) * 1000);
        }
        
        /*Pushes the current transformed point.*/
        inline void pushCurrent(){
            if(tracing)
                tracePoints.push_back(transform.getTranslation());
            if (filling) 
                fillAccum.points.push_back(transform.getTranslation());
        }
        
        //Pen Attributes
        float moveSpeed = TS_NORMAL;
        bool angleMode = false;//Using Radians = true, degrees = false
        bool tracing = true;
        bool filling = false;
        Color penColor = Color::black;
        
        //Accumulors
        Polygon fillAccum;
        Color fillColor = Color::black;
        
        //Cursor (shape)
        Polygon cursor = cturtle::shape("indented triangle");
        int curStamp = 0;
        
        TurtleScreen* screen = nullptr;
        
        /*Inheritors must assign screen reference!*/
        RawTurtle(){}
    };
    
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
        TurtleScreen() : display(800, 600, "CTurte", 0){
            canvas.assign(display);
            swapDisplay(2);
            canvas.fill(255,255,255);
        }
        TurtleScreen(const std::string& title) : display(800, 600){
            display.set_title(title.c_str());
            display.set_normalization(0);
            canvas.assign(display);
            swapDisplay(2);
        }
        TurtleScreen(int width, int height, const std::string& title) : display(width, height){
            display.set_title(title.c_str());
            display.set_normalization(0);
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
        ivec2 screensize(Color& bg);
        
        /*Returns the size of the screen, in pixels.*/
        inline ivec2 screensize(){
            Color temp;
            return screensize(temp);
        }
        
        /*Sets the world coordinates.*/
//        void setworldcoordinates(vec2 lowerLeft, vec2 upperRight);
        //might just leave this function out
        
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
        void save(const std::string& file){
            Image screenshotImg;
            display.screenshot(screenshotImg);
            screenshotImg.save(file.c_str());
        }
        
        //TODO: Document me more
        /*Closes this window.*/
        void bye();
        
        /*Returns the canvas image used by this screen.*/
        Image& getcanvas(){
            return canvas;
        }
        
        /*Returns the internal CImg display.*/
        cimg::CImgDisplay& getInternalDisplay(){
            return display;
        }
        
        /*Returns a boolean indicating if the
          screen has been closed.*/
        inline bool getIsClosed(){
            return getInternalDisplay().is_closed();
        }
        
        /*Draws all geometry from all child turtles.*/
        void redraw();
        
        /*Swaps the display.*/
        inline void swap(){swapDisplay();}
        
        /*Returns the screen-level AffineTransform
          of this screen. This is what puts the origin
          at the center of the screen rather than at
          at the top left, for example.*/
        AffineTransform screentransform(){
            //TODO: Change with the screen modes.
            AffineTransform t;
            t.translate(canvas.width() / 2, canvas.height() / 2);
            return t;
        }
        
        void add(RawTurtle& turtle){
            turtles.push_back(&turtle);
        }
    protected:
        cimg::CImgDisplay   display;
        Image               canvas;
        
        Color backgroundColor   = Color::white;
        Image backgroundImage;
        ScreenMode curMode      = SM_STANDARD;
        int colorCap            = 255;
        bool  tracing = true;
        
        unsigned int delayMS = 10;
        
        /*Swaps the front and back buffers, then displays the front buffer.*/
        inline void swapDisplay(int times = 1){
            for(int i = 0; i < times; i++){
                display.display(canvas);
                display.flush();
                /*Reset the display to just have background image or color.*/
                if(!backgroundImage.is_empty()){
                    canvas.assign(backgroundImage);
                }else{
                    
                    //It really seems to me that these two methods do the
                    //exact same thing-- flicker and all.
                    //TODO: Fix the "flickering" issue.
//                    std::memset(canvas.data(), 255, canvas.size()*sizeof(uint8_t));
                    canvas.draw_rectangle(0, 0, canvas.width(), canvas.height(), backgroundColor.rgbPtr());
                }
            }
        }
        
        std::list<RawTurtle*> turtles;
        
        //TODO: Map to individual buttons (e.g, key is button, val is callback)
//        KeyFunc     keyFunc     = [](char){};
//        MouseFunc   clickFunc   = [](vec2){};
        TimerFunc   timerFunc   = [](void){};
    };
}
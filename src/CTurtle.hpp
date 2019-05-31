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

/**
 * \brief Only namespace which contains functions and classes for this project.
 * 
 */
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
    
    /**\brief Describes the speed at which a Turtle moves and rotates.
     * \sa RawTurtle::getAnimMS()*/
    enum TurtleSpeed{
        TS_FASTEST  = 10,
        TS_FAST     = 9,
        TS_NORMAL   = 6,
        TS_SLOW     = 3,
        TS_SLOWEST  = 1
    };
    
    /**\brief Turtles append Scene Objects to a list to keep 
     *              track of what it has drawn (a history).
     * SceneObject holds a description of something that needs to be on the screen.
     * It's a general object which encompasses ALL things that can be on screen,
     * ranging from stamps, misc. geometry, and strings.*/
    struct SceneObject{
        /**The unique pointer to the geometry of this object.
         *Can be null if the text string is not empty.*/
        std::unique_ptr<IDrawableGeometry> geom;
        /**The color with which to draw this SceneObject.*/
        Color color;
        /**The transform at which to draw this SceneObject.
         * Note that this is concatenated onto the ScreenTransform of
         * the drawing turtle's screen.*/
        AffineTransform transform;
        
        bool stamp = false;
        int stampid = -1;
        
        std::string text;//Stays empty unless this object is for text.
        
        /**Empty constructor.*/
        SceneObject(){}
        
        /**General geometry constructor.
         *\param geom A dynamically allocated pointer to a Geometry object.
         *            Please note that, after this constructor call, the SceneObject
         *            controls the life of the given pointer. Do not delete it yourself.
         *\param color The color to draw the geometry in.
         *\param t The transform at which to draw the geometry.*/
        SceneObject(IDrawableGeometry* geom, Color color, const AffineTransform& t) :
            geom(geom), color(color), transform(t){}
        
        /**Stamp constructor which takes an ID.
         *\param geom The geometry of the stamp. Follows the 
         *            same rules as the Geometry constructor.
         *\param color The color with which to draw the stamp.
         *\param t The transform at which to draw the stamp.
         *\param stampid The ID of the stamp this object is related to..*/
        SceneObject(IDrawableGeometry* geom, Color color, const AffineTransform& t, int stampid) :
            geom(geom), color(color), transform(t), stamp(true), stampid(stampid){}
        
        /**String constructor.
         * Please note that strings are not subject to rotation, scaling, or shear!
         *\param text The text content of this object.
         *\param color The color with which to daraw this string.
         *\param t The transform at which to draw this string.*/
        SceneObject(const std::string& text, Color color, const AffineTransform& t) : 
            text(text), color(color), transform(t){}
    };

    //TODO: Finish and document
    class RawTurtle{
    public:
        /*Implemented in source impl. file*/
        RawTurtle(TurtleScreen& scr);
        
        //Motion
        
        /**\brief Moves the turtle forward the specified number of pixels.*/
        void forward(int pixels);
        /**\copydoc forward(int)*/
        inline void fd(int pixels){forward(pixels);}
        
        /**\brief Moves the turtle backward the specified number of pixels.*/
        void backward(int pixels);
        /**\copydoc backward(int)*/
        inline void bk(int pixels){backward(pixels);}
        /**\copydoc backward(int)*/
        inline void back(int pixels){backward(pixels);}
        
        /**\brief Rotates the turtle the specified number of units to the right.
         * The unit by which the input is specified is determined by the current
         * angle mode. The difference between Clockwise and Counterclockwise
         * is determined by the current screen's mode.
         * \sa degrees()
         * \sa radians()
         * \sa TurtleScreen::mode()*/
        void right(float amt);
        /**\copydoc right(float)*/
        inline void rt(float angle){right(angle);}
        
        /**\brief Rotates the turtle the specified number of units to the left.
         * The unit by which the input is specified is determined by the current
         * angle mode. The difference between Clockwise and Counterclockwise
         * is determined by the current screen's mode.
         * \sa degrees()
         * \sa radians()
         * \sa TurtleScreen::mode()*/
        void left(float amt);
        /**\copydoc left(float)*/
        inline void lt(float angle){left(angle);}
        
        /**\brief Sets the tranform location of this turtle.*/
        void goTo(int x, int y);
        /**\copydoc goTo(int,int)*/
        inline void setpos(int x, int y){goTo(x,y);}
        /**\copydoc goTo(int,int)*/
        inline void setposition(int x, int y){goTo(x,y);}
        
        /**\brief Sets the X-axis transform location of this turtle.*/
        void setx(int x);
        /**\brief Sets the Y-axis transform location of this turtle.*/
        void sety(int y);
        
        /**\brief Sets the rotation of this turtle.
         * The unit by which the input is specified is determined by the current
         * angle mode. The difference between Clockwise and Counterclockwise
         * is determined by the current screen's mode.
         * \sa degrees()
         * \sa radians()
         * \sa TurtleScreen::mode()*/
        void setheading(float angle);
        /**\copydoc setheading(float)*/
        inline void seth(float angle){setheading(angle);}
        
        /**\Brings the turtle back to its origin.
         * Depends on the current screen mode. 
         * If the screen mode is set to "world", The turtle is turned to the right and
         * positive angles are counterclockwise.
         * Otherwise, if it is set to "logo", The turtle face upwards and positive
         * angles are clockwise.
         * \sa TurtleScreen::mode()*/
        void home();
        
        /**\brief Adds a circle to the screen.
         *\param radius The radius, in pixels, of the circle.
         *\param steps The "quality" of the circle. Higher is slow but looks better.
         *\param color The color of the circle.*/
        void circle(int radius, int steps, Color color);
        
        /**\brief Adds a circle to the screen.
         * Default parameters are circle with a radius of 30 with 15 steps.
         *\param color The color of the circle.*/
        inline void circle(Color color){
            circle(30, 15, color);
        }
        
        /**\brief Adds a dot to the screen.
         *\param The color of the dot.
         *\param size The size of the dot.
         */
        void dot(Color color, int size = 10){
            circle(size/2, 4, color);
        }
        
        /**\brief Sets the "filling" state.
         * If the input is false but the prior state is true, a SceneObject
         * is put on the screen in the shape of the previously captured points.
         *\param state Whether or not the turtle is filling a polygon.*/
        void fill(bool state);
        /**\brief Begins filling a polygon.
         *\sa fill(bool)*/
        inline void begin_fill(){fill(true);}
        /**\brief Stops filling a polygon.
         *\sa fill(bool)*/
        inline void end_fill(){fill(false);}
        
        /**\brief Sets the fill color of this turtle.
         *\param c The color with which to fill polygons.*/
        void fillcolor(Color c){fillColor = c;}
        /**\brief Returns the fill color of this turtle.
         *\return The current fill color.*/
        Color fillcolor(){return fillColor;}
        
        /**/
        void write(const std::string& text);
        
        /**\brief Puts the current shape of this turtle on the screen
         *        with the current fill color and the outline of the shape.
         *\return The stamp ID of the put stamp.*/
        int stamp();
        /**\brief Removes the stamp with the specified ID.*/
        void clearstamp(int stampid);
        /**\brief Removes all stamps with an ID less than that which is specified.
         *        If the specified stampid is less than 0, it removes ALL stamps.*/
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
        
        void tilt(float angle){
            cursorTilt += angleMode ? angle : toRadians(angle);
            //TODO: Move to implementation and call redraw on screen.
        }
        
        float tilt(){return angleMode ? cursorTilt : toDegrees(cursorTilt);}
        
        //TODO: Tracer Funcs
        void trace(bool state){
            tracing = state;
        }
        bool trace(){return tracing;}
        
        void penup(){tracing = false;}
        void pendown(){tracing = true;}
        
        void pencolor(Color c){penColor = c;}
        Color pencolor(){return penColor;}
        
        void width(int pixels){penWidth = pixels;}
        int width(){return penWidth;}
        
        void draw(const AffineTransform& screenTransform, Image& canvas);
        
        void degrees(){angleMode = false;}
        inline void radians(){angleMode = true;}
        
        /*Resets this turtle.*/
        void reset();
        
        virtual ~RawTurtle(){}
    protected:
        std::list<SceneObject> objects;
        std::vector<std::pair<Color, Line>> traceLines;
        std::list<AffineTransform> transformStack = {AffineTransform()};
        AffineTransform& transform = transformStack.back();
        
        /*Pushes the specified object attibutes as an object to this turtle's
          "drawing" list.*/
        inline void pushGeom(const AffineTransform& t, Color color, IDrawableGeometry* geom){
            objects.emplace_back(geom, color, t);
        }
        
        inline void pushStamp(const AffineTransform& t, Color color, IDrawableGeometry* geom){
            objects.emplace_back(geom, color, t, curStamp++);
        }
        
        inline void pushText(const AffineTransform& t, Color color, const std::string text){
            objects.emplace_back(text, color, t);
        }
        
        /*Returns the speed, of any applicable animation,
          in milliseconds, based off of this turtle's speed setting.*/
        inline long getAnimMS(){
            return moveSpeed <= 0 ? 0 : long(((10.0f - moveSpeed)/10.0f) * 3000);
        }
        
        /*Pushes the current transformed point.*/
        inline void pushCurrent(){
            if(tracing){
                Point src = traceLines.empty() ? Point() : traceLines.back().second.pointB;
                traceLines.push_back(std::make_pair(penColor, Line(src, transform.getTranslation(), penWidth)));
            }
            if (filling) 
                fillAccum.points.push_back(transform.getTranslation());
            transformStack.push_back(transform);
            transform = transformStack.back();
        }
        
        //Pen Attributes
        float moveSpeed = TS_NORMAL;
        bool angleMode = false;//Using Radians = true, degrees = false
        bool tracing = true;
        int penWidth = 1;
        bool filling = false;
        Color penColor = Color::black;
        
        //Accumulors
        Polygon fillAccum;
        Color fillColor = Color::black;
        
        //Cursor (shape)
        Polygon cursor = cturtle::shape("indented triangle");
        int curStamp = 0;
        float cursorTilt = 0.0f;
        
        TurtleScreen* screen = nullptr;
        
        /*Inheritors must assign screen pointer!*/
        RawTurtle(){}
    };
    
    /*TODO: Document Me*/
    enum ScreenMode{
        SM_STANDARD,
        SM_LOGO//,
//        SM_WORLD
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
        
        /**Returns the screen-level AffineTransform
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
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

//Under UNIX, link X11 and PThread.

/*Standard Includes*/
#include <cstdint>
#include <cmath>
#include <algorithm>
#include <string>
#include <map>
#include <list>
#include <functional>
#include <utility>
#include <memory>
#include <mutex>
#include <iostream>

/*Local Includes*/
#include "Common.hpp"
#include "Geometry.hpp"
#include "Color.hpp"
#include "UserIO.hpp"

/**
 * \brief Only namespace which contains functions and classes for this project.
 * 
 */
namespace cturtle{
    /*Callback function typedefs for event listeners.*/
    
    /*Mouse event callback type.*/
    typedef std::function<void(int, int)> MouseFunc;
    
    /*Keyboard event callback type.*/
    typedef std::function<void()> KeyFunc;
    
    /*Timer event callback type.*/
    typedef std::function<void(void)> TimerFunc;
    
    //Turtle prototype definition
    class Turtle;
    //TurtleScreen prototype definition
    class TurtleScreen;
    
    //Alias for the CImg library, for convenience.
    namespace cimg = cimg_library;
    
    /*Shape Registration.*/
    void __registerShapeImpl(const std::string& name, std::shared_ptr<IDrawableGeometry> geom);
    
    /**Registers the specified drawable geometry as a shape.
     * Please note that type T must inherit from IDrawableGeometry and
     * specify a copy constructor, default or otherwise.*/
    template<typename T>
    void registerShape(const std::string& name, const T& geom){
        __registerShapeImpl(name, std::shared_ptr<IDrawableGeometry>(new T(geom)));
    }
    
    /**Returns the shape with the specified name.*/
    const IDrawableGeometry& shape(const std::string name);
    
    /**\brief Describes the speed at which a Turtle moves and rotates.
     * \sa Turtle::getAnimMS()*/
    enum TurtleSpeed{
        TS_FASTEST  = 0,
        TS_FAST     = 10,
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
        
        //In the case where unownedGeom is 
        IDrawableGeometry* unownedGeom = nullptr;
        
        /**The color with which to draw this SceneObject.*/
        Color color;
        /**The transform at which to draw this SceneObject.
         * Note that this is concatenated onto the ScreenTransform of
         * the drawing turtle's screen.*/
        AffineTransform transform;
        
        /**A boolean indicating if this scene object is a stamp.*/
        bool stamp = false;
        /**The integer representing the stamp ID, if this is a stamp.*/
        int stampid = -1;
        
        /**A text string. If non-empty, this object is a string, regardless
          of the status of the stamp variables.*/
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
         * Please note that, when it comes to stamps, this object DOES NOT OWN
         * the drawable data.
         *\param geom The geometry of the stamp. Follows the 
         *            same rules as the Geometry constructor.
         *\param color The color with which to draw the stamp.
         *\param t The transform at which to draw the stamp.
         *\param stampid The ID of the stamp this object is related to..*/
        SceneObject(IDrawableGeometry* geom, Color color, const AffineTransform& t, int stampid) :
            unownedGeom(geom), color(color), transform(t), stamp(true), stampid(stampid){}
        
        /**String constructor.
         * Please note that strings are not subject to rotation, scaling, or shear!
         *\param text The text content of this object.
         *\param color The color with which to daraw this string.
         *\param t The transform at which to draw this string.*/
        SceneObject(const std::string& text, Color color, const AffineTransform& t) : 
            text(text), color(color), transform(t){}
    };

    /**Pen State structure.
     * Holds all pen attributes.*/
    struct PenState {
        AffineTransform transform;
        float moveSpeed = TS_NORMAL;
        bool tracing = true;
        bool angleMode = false;
        int penWidth = 1;
        bool filling = false;
        Color penColor = Color::black;
        Color fillColor = Color::black;
        unsigned long int objectsBefore = 0;
        IDrawableGeometry* cursor = &const_cast<IDrawableGeometry&> (cturtle::shape("indented triangle"));
        int curStamp = 0;
        bool visible = true;
        float cursorTilt = 0;
        
        //May need stateBegin iterator for scene objects
        
        PenState(){}
        PenState(const PenState& copy){
            transform = copy.transform;
            moveSpeed = copy.moveSpeed;
            tracing = copy.tracing;
            angleMode = copy.angleMode;
            penWidth = copy.penWidth;
            filling = copy.filling;
            penColor = copy.penColor;
            fillColor = copy.fillColor;
            cursor = copy.cursor;
            curStamp = copy.curStamp;
            visible = copy.visible;
            cursorTilt = copy.cursorTilt;
            objectsBefore = copy.objectsBefore;
        }
    };

    //TODO: Finish and document
    class Turtle{
    public:
        /*Implemented in source impl. file*/
        Turtle(TurtleScreen& scr);
        
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
        void fillcolor(Color c){
            pushState();
            state.fillColor = c;
        }
        /**\brief Returns the fill color of this turtle.
         *\return The current fill color.*/
        Color fillcolor(){
            return state.fillColor;
        }
        
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
        
        /**\brief Sets the shape of this turtle.
         *\param p The polygon to derive shape geometry from.*/
        void shape(const IDrawableGeometry& p){
            pushState();
            state.cursor = &const_cast<IDrawableGeometry&>(p);
            updateParent(false, false);
        }
        
        /**\brief Sets the shape of this turtle from the specified shape name.
         *\param name The name of the shape to set.*/
        void shape(const std::string& name){
            pushState();
            state.cursor = &const_cast<IDrawableGeometry&>(cturtle::shape(name));
            updateParent(false, false);
        }
        
        /**\brief Returns the shape of this turtle.*/
        const IDrawableGeometry& shape(){
            return *state.cursor;
        }
        
        /**\brief Undoes the previous action of this turtle.*/
        bool undo();
        
        /**\brief Set, or disable, the undo buffer.
         *\param size The size of the undo buffer.*/
        void setundobuffer(unsigned int size){
            if(size < 1)//clamp lower bound to 1
                size = 1;
            
            undoStackSize = size;
            while(stateStack.size() > size){
                stateStack.pop_front();
            }
        }
        
        /**\brief Returns the size of the undo stack.*/
        unsigned int undobufferentries(){
            return stateStack.size();
        }
        
        /**\brief Sets the speed of this turtle in range of 0 to 10.
         *\param The speed of the turtle, in range of 0 to 10.
         *\sa cturtle::TurtleSpeed*/
        void speed(float val){
            pushState();
            state.moveSpeed = val;
        }
        
        /**\brief Returns the speed of this turtle.*/
        float speed(){
            return state.moveSpeed;
        }
        
        /**\brief Applies a rotation to the */
        void tilt(float angle);
        
        /**\brief Returns the rotation of the cursor. Not the heading,
         *        or the angle at which the forward function will move.*/
        float tilt(){return state.angleMode ? state.cursorTilt : toDegrees(state.cursorTilt);}
        
        /**\brief Set whether or not the turtle is being shown.
         *\param state True when showing, false othewise.*/
        void setshowturtle(bool state);
        
        /**\brief Shows the turtle.
         *        Equivalent to calling setshowturtle(true).
         *\sa setshowturtle(bool)*/
        inline void showturtle(){
            setshowturtle(true);
        }
        
        /**\brief Hides the turtle.
         *\sa setshowturtle(bool)*/
        inline void hideturtle(){
            setshowturtle(false);
        }
        
        /**\brief Sets whether or not the pen is down.*/
        void setpenstate(bool down);
        
        /**\brief Brings the pen up.*/
        inline void penup(){setpenstate(false);}
        /**\brief Brings the pen down.*/
        inline void pendown(){setpenstate(true);}
        
        /**\brief Sets the pen color.
         *\param c The color used by the pen; the color of lines between movements.*/
        void pencolor(Color c){
            pushState();
            state.penColor = c;
        }
        
        /**\brief Returns the pen color; the color of the lines between movements.
         *\return The color of the pen.*/
        Color pencolor(){return state.penColor;}
        
        /**Sets the width of the pen line.
         *\param pixels The total width, in pixels, of the pen line.*/
        void width(int pixels){
            pushState();
            state.penWidth = pixels;
        }
        /**Returns the width of the pen line.
         *\return The width of the line, in pixels.*/
        int width(){return state.penWidth;}
        
        /**\brief Draws this turtle on the specified canvas with the specified transform.
         *\param screenTransform The transform at which to draw the turtle objects.
         *\param canvas The canvas on which to draw this turtle.*/
        void draw(const AffineTransform& screenTransform, Image& canvas);
        
        /**Sets this turtle to use angles measured in degrees.
         *\sa radians()*/
        void degrees(){
            pushState();
            state.angleMode = false;
        }
        /**Sets this turtle to use angles measured in radians.
         *\sa degress()*/
        inline void radians(){
            pushState();
            state.angleMode = true;
        }
        
        /**\brief Resets this turtle.
         * Moves this turtle home, resets all pen attributes,
         * and removes all previously added scene objects.*/
        void reset();
        
        /**Sets this turtles screen.*/
        void setScreen(TurtleScreen* scr){
            screen = scr;
        }
        
        /**\brief Empty virtual destructor.*/
        virtual ~Turtle(){}
    protected:
        std::list<std::list<SceneObject>::iterator> objects;
        std::list<PenState> stateStack = {PenState()};
        AffineTransform& transform = stateStack.front().transform;
        PenState& state = stateStack.front();
        
        /**These variables are used to draw the "travel" line when
         * the turtle is traveling. (e.g, the line between where it's going*/
        Point   travelPoints[2];
        bool    traveling = false;
        
        /*Fill insert iterator*/
        std::list<SceneObject>::iterator fillInsert;
        
        /*Undo stack size.*/
        unsigned int undoStackSize = 100;
        
        /*Accumulator*/
        Polygon fillAccum;
        
        /*Screen pointer. Assign before calling any other function!*/
        TurtleScreen* screen = nullptr;
        
        void pushState();
        bool popState();
        
        /**
         * \brief Internal function used to add geometry to the turtle screen.
         * \param t The transform of the geometry.
         * \param color The color of the geometry.
         * \param geom The geometry to add.
         * \return A boolean indicating if the geometry was added to the scene.
         */
        bool pushGeom(const AffineTransform& t, Color color, IDrawableGeometry* geom);
        
        /**\brief Internal function used to add a stamp object to the turtle screen.
         *\param t The transform at which to draw the stamp.
         *\param color The color with which to draw the stamp.
         *\param geom The geometry of the stamp.*/
        bool pushStamp(const AffineTransform& t, Color color, IDrawableGeometry* geom);
        
        /**\brief Internal function used to add a text object to the turtle screen.
         *\param t The transform at which to draw the text.
         *\param color The color with which to draw the text.
         *\param text The string to draw.*/
        bool pushText(const AffineTransform& t, Color color, const std::string& text);
        
        /**\brief Internal function used to add a trace line object to the turtle screen.
         *\param a Point A
         *\param b Point B*/
        bool pushTraceLine(Point a, Point b);
        
        /**Returns the speed, of any applicable animation
          in milliseconds, based off of this turtle's speed setting.*/
        inline long int getAnimMS(){
            return state.moveSpeed <= 0 ? 0 : long(((11.0f - state.moveSpeed)/10.0f) * 300);
        }
        
        /**Redraws the parent screen.*/
        void updateParent(bool invalidate = false, bool input = true);
        
        /**Performs an interpolation, with animation,
         * between the current transform and the specified one.
         * Pushes a new fill vertex if filling, and applies appropriate
         * lines if the pen is down.*/
        void travelTo(const AffineTransform& dest);
        
        /**Performs an interpolation, with animation,
         * between the current transformation and the previous one.
         * Will *not* pop state.*/
        void travelBack();
        
        /**Inheritors must assign screen pointer!*/
        Turtle(){}
    };
    
    /**\brief ScreenMode Enumeration, used to decide orientation of the drawing calls
     *        on TurtleScreens.
     *\sa TurtleScreen::mode(ScreenMode)*/
    enum ScreenMode{
        SM_STANDARD,
        SM_LOGO//,
//        SM_WORLD
    };
    
    /** TurtleScreen
     *      Holds and maintains all facilities in relation to displaying
     *      turtles and consuming input events from users through callbacks.
     */
    class TurtleScreen{
    public:
        /**Empty constructor.
         * Assigns an 800 x 600 pixel display with a title of "CTurtle".*/
        TurtleScreen() : display(800, 600, "CTurtle", 0){
            canvas.assign(display);
            initEventThread();
            redraw(true);
        }
        /**Title constructor.
         * Assigns an 800 x 600 pixel display with a specified title.
         *\param title The title to assign the display with.*/
        TurtleScreen(const std::string& title) : display(800, 600){
            display.set_title(title.c_str());
            display.set_normalization(0);
            canvas.assign(display);
            initEventThread();
            redraw(true);
        }
        /**Width, height, and title constructor.
         * Assigns the display with the specified dimensions, in pixels, and
         * assigns the display the specified title.
         *\param width The width of the display, in pixels.
         *\param height The height of the display, in pixels.
         *\param title The title of the display.*/
        TurtleScreen(int width, int height, const std::string& title = "CTurtle") : display(width, height){
            display.set_title(title.c_str());
            display.set_normalization(0);
            canvas.assign(display);
            initEventThread();
            redraw(true);
        }
        
        ~TurtleScreen() {
            bye();
        }
        
        /**Sets an internal variable that dictates how many frames
         * are skipped between screen updates; higher numbers will
         * speed up complex turtle drawings.
         *\param countmax The value of the aforementioned variable.
         *\param delayMS This value is sent to function "delay".*/
        void tracer(int countmax, unsigned int delayMS = 10){
            redrawCounterMax = countmax;
            delay(delayMS);
            redraw();
        }
        
        /**Sets the background color of the screen.
         * Please note that, if there is a background image, this color is not
         * applied until it is removed.
         *\param color The background color.
         *\sa bgpic(image)*/
        void bgcolor(const Color& color);
        
        /**Returns the background color of the screen.
         *\return The background color of the screen.*/
        Color bgcolor();
        
        /**\brief Sets the background image of the display.
         * Sets the background image. Please note that the background image
         * takes precedence over background color.
         *\param img The background image.*/
        void bgpic(const Image& img);
        
        /**Returns a const reference to the background image.*/
        const Image& bgpic();

        /**Sets the screen mode of this screen.
         *\param mode The screen mode.
         *\todo Refine this documentation.*/
        void mode(ScreenMode mode);
        
        /**Returns the screen mode of this screen.*/
        ScreenMode mode(){return curMode;}
        
        /**\brief Clears this screen.
         * Deletes all drawings and turtles,
         * Resets the background to plain white,
         * Clears all event bindings,
         */
        void clearscreen();
        
        /**Alias for clearscreen function
         *\sa clearscreen()*/
        inline void clear(){clearscreen();}
        
        /**Resets all turtles belonging to this screen to their original state.*/
        void resetscreen();
        
        /**Resets all turtles belonging to this screen to their original state.*/
        inline void reset(){resetscreen();}
        
        /**Returns the size of this screen, in pixels.
          Also returns the background color of the screen,
          by assigning the input reference.*/
        ivec2 screensize(Color& bg);
        
        /**Returns the size of the screen, in pixels.*/
        inline ivec2 screensize(){
            Color temp;
            return screensize(temp);
        }
        
        /*Sets the world coordinates.*/
//        void setworldcoordinates(vec2 lowerLeft, vec2 upperRight);
        //might just leave this function out
        
        /*TODO: Document Me*/
        void update(bool invalidateDraw = false, bool processInput = true);
        
        /**Sets the delay set between turtle commands.*/
        void delay(unsigned int ms);
        
        /**Returns the delay set between screen swaps in milliseconds.*/
        unsigned int delay();
        
        /**Returns the width of the window, in pixels.*/
        int window_width(){
            return display.window_width();
        }
        
        /**Returns the height of the window, in pixels.*/
        int window_height(){
            return display.window_height();
        }
        
        /**Saves the display as a file, the format of which is dependent
          on the file extension given in the specified file path string.*/
        void save(const std::string& file){
            Image screenshotImg;
            display.snapshot(screenshotImg);
            screenshotImg.save(file.c_str());
        }
        
        /**Enters a loop, lasting until the display has been closed,
         * which updates the screen. This is useful for programs which
         * rely heavily on user input, as events are still called like normal.*/
        void mainloop(){
            while(!display.is_closed()){
                update(false, true);
                std::this_thread::yield();
            }
        }
        
        /**Resets and closes this display.*/
        void bye();
        
        /**Returns the canvas image used by this screen.*/
        Image& getcanvas(){
            return canvas;
        }
        
        /**Returns the internal CImg display.*/
        cimg::CImgDisplay& getInternalDisplay(){
            return display;
        }
        
        /**Returns a boolean indicating if the
          screen has been closed.*/
        inline bool getIsClosed(){
            return getInternalDisplay().is_closed();
        }
        
        /**Draws all geometry from all child turtles and swaps this display.*/
        void redraw(bool invalidate = false);
        
        /**Returns the screen-level AffineTransform
          of this screen. This is what puts the origin
          at the center of the screen rather than at
          at the top left, for example.*/
        AffineTransform screentransform(){
            AffineTransform t;
            t.translate(canvas.width() / 2, canvas.height() / 2);
            t.scale(1,-1.0f);
            //Scale negatively on Y axis to match
            //Python's coordinate system.
            //without this scaling, top left is 0,0
            //instead of the bottom left (which is 0,Y without the scaling)
            return t;
        }
        
        /**TODO: Document Me*/
        void onkeypress(KeyFunc func, KeyboardKey key){
            cacheMutex.lock();
            //determine if key list exists
            if(keyBindings[0].find(key) == keyBindings[0].end()){
                keyBindings[0][key] = std::list<KeyFunc>();
            }
            //then push it to the end of the list
            keyBindings[0][key].push_back(func);
            cacheMutex.unlock();
        }
        
        /**TODO: Document Me*/
        virtual void onkeyrelease(KeyFunc func, KeyboardKey key){
            cacheMutex.lock();
            //determine if key list exists
            if(keyBindings[1].find(key) == keyBindings[1].end()){
                keyBindings[1][key] = std::list<KeyFunc>();
            }
            //then push it to the end of the list
            keyBindings[1][key].push_back(func);
            cacheMutex.unlock();
        }
        
        /**TODO: Document Me*/
        void presskey(KeyboardKey key){
            if(keyBindings[0].find(key) == keyBindings[0].end())
                return;
            for(KeyFunc& func : keyBindings[0][key]){
                func();
            }
        }
        
        /**TODO: Document Me*/
        void releasekey(KeyboardKey key){
            if(keyBindings[1].find(key) == keyBindings[1].end())
                return;
            for(KeyFunc& func : keyBindings[1][key]){
                func();
            }
        }
        
        /**TODO: Document Me*/
        void onclick(MouseFunc func, MouseButton button = MOUSEB_LEFT){
            cacheMutex.lock();
            mouseBindings[button].push_back(func);
            cacheMutex.unlock();
        }
        
        /**Calls all previously added mouse button call-backs.*/
        void pressmouse(int x, int y, MouseButton button){
            for(MouseFunc& func : mouseBindings[button]){
                func(x, y);
            }
        }
        
        void ontimer(TimerFunc func, unsigned int time){
            timerBindings.push_back(std::make_tuple(func, time, epochTime()));
        }
        
        /**Binds the "bye" function to the onclick event for the left
         * mouse button.*/
        void exitonclick(){
            onclick([&](int x, int y) {
                display.close();
                //bye() was having issues in a callback
                //TODO: figure out why
            });
            mainloop();
        }
        
        /**Adds the specified turtle to this screen.*/
        void add(Turtle& turtle){
            turtles.push_back(&turtle);
        }
        
        std::list<SceneObject>& getScene(){
            return objects;
        }
    protected:
        cimg::CImgDisplay   display;
        Image               canvas;
        
        //The turtle composite image.
        //This image copies the canvas and has
        //turtles drawn to it to avoid redrawing a "busy" canvas
        Image turtleComposite;
        int lastTotalObjects = 0;
        
        Color backgroundColor   = Color::white;
        Image backgroundImage;
        ScreenMode curMode      = SM_STANDARD;
        
        /**Redraw delay, in milliseconds.*/
        long int delayMS = 10;
        
        /**Redraw Counter.*/
        int redrawCounter = 0;
        int redrawCounterMax = 0;
        
        void initEventThread();
        
        std::list<SceneObject> objects;
        std::list<Turtle*> turtles;
        
        std::unique_ptr<std::thread> eventThread;
        std::list<InputEvent> cachedEvents;
        bool killEventThread = false;
        std::mutex cacheMutex;
        
        //this is an array. 0 for keyDown bindings, 1 for keyUp bindings.
        std::map<KeyboardKey, std::list<KeyFunc>> keyBindings[2] = {{},{}};
        std::list<MouseFunc> mouseBindings[3] = {{},{},{}};
        std::list<std::tuple<TimerFunc, uint64_t, uint64_t>> timerBindings;
    };
}
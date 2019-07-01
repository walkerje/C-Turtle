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

#define CTURTLE_IMPLEMENTATION
#include "CTurtle.hpp"
#include <cstdlib>
#include <iostream>
#include <vector>
#include <locale>
#include <memory>

namespace cturtle {
    /*Shape Registration =================================*/
    namespace {
        std::map<std::string, std::shared_ptr<IDrawableGeometry>> shapes = {
            {"triangle",
                std::shared_ptr<IDrawableGeometry>(
                new Polygon(
                {
                    {0, 0},
                    {-5, 5},
                    {5, 5}
                }))},
            {"square",
                    
                std::shared_ptr<IDrawableGeometry>(
                new Polygon(
                {
                    {-5, -5},
                    {-5, 5},
                    {5, 5},
                    {5, -5}
                }))},
            {"indented triangle",
                std::shared_ptr<IDrawableGeometry>(
                new Polygon(
                {
                    //CCW
                    {0,0},
                    {-5, 10},
                    {0, 8},
                    {5, 10}
                }))},
            {"arrow",
                std::shared_ptr<IDrawableGeometry>(
                new Polygon(
                {
                    {0, 0},
                    {-5, 5},
                    {-3, 5},
                    {-3, 10},
                    {3, 10},
                    {3, 5},
                    {5, 5}
                }
            ))}
        };
    }
    
    void __registerShapeImpl(const std::string& name, std::shared_ptr<IDrawableGeometry> geom){
        shapes[name] = geom;
    }

    const IDrawableGeometry& shape(const std::string name) {
        return *shapes[name].get();
    }

    /*TurtleScreen =======================================*/
    void TurtleScreen::clearscreen() {
        //1) Delete all drawings and turtles
        //2) White background
        //3) No background image
        //4) No event bindings

        
        for (Turtle* turtle : turtles) {
            turtle->setScreen(nullptr);
        }
        
        turtles.clear();
        backgroundColor = Color::white;
        backgroundImage.assign();
        curMode = SM_STANDARD;
        
        cacheMutex.lock();
        timerBindings.clear();
        keyBindings[0].clear();
        keyBindings[1].clear();
        for(int i = 0; i < 3; i++)
            mouseBindings[i].clear();
        cacheMutex.unlock();
    }
    
    void TurtleScreen::bgcolor(const Color& color){
        backgroundColor = color;
        redraw(true);
    }
    
    Color TurtleScreen::bgcolor(){
        return backgroundColor;
    }

    void TurtleScreen::bgpic(const Image& img) {
        backgroundImage.assign(img);
        backgroundImage.resize(window_width(), window_height());
        redraw(true);
    }
    
    const Image& TurtleScreen::bgpic(){
        return backgroundImage;
    }
    
    void TurtleScreen::mode(ScreenMode mode){
        curMode = mode;
    }

    void TurtleScreen::resetscreen() {
        for (Turtle* turtle : turtles) {
            turtle->reset();
        }
    }

    ivec2 TurtleScreen::screensize(Color& bg) {
        bg = backgroundColor;
        return {display.screen_width(), display.screen_height()};
    }

    void TurtleScreen::update(bool invalidateDraw, bool input) {
        /*Resize canvas.*/
        if(display.is_resized()){
            display.resize();
            invalidateDraw = true;
        }
        redraw(invalidateDraw);
        
        if(input && !timerBindings.empty()){
            //Call timer bindings first.
            uint64_t curTime = epochTime();
            for(auto& timer : timerBindings){
                auto& func = std::get<0>(timer);
                uint64_t reqTime = std::get<1>(timer);
                uint64_t& lastCalled = std::get<2>(timer);

                if(curTime >= lastCalled + reqTime){
                    lastCalled = curTime;
                    func();
                }
            }
        }
        
        /**No events to process in the cache, or we're not processing it right now.*/
        if(cachedEvents.empty() || !input)
            return;//No events to process.
        
        cacheMutex.lock();

        for (InputEvent& event : cachedEvents) {
            if (event.type) {//process keyboard event
                KeyFunc& keyFunc = *reinterpret_cast<KeyFunc*> (event.cbPointer);
                keyFunc();
            } else {//process mouse event
                MouseFunc& mFunc = *reinterpret_cast<MouseFunc*> (event.cbPointer);
                mFunc(event.mX, event.mY);
            }
        }

        cachedEvents.clear();
        cacheMutex.unlock();
    }

    void TurtleScreen::delay(unsigned int ms) {
        delayMS = ms;
    }

    unsigned int TurtleScreen::delay() {
        return delayMS;
    }

    void TurtleScreen::bye() {
        if(eventThread.get() != nullptr){  
            killEventThread = true;
            eventThread->join();
            eventThread.reset(nullptr);
        }
        
        clearscreen();
        
        if(!display.is_closed())
            display.close();
        
    }

    void TurtleScreen::redraw(bool invalidate) {
        if(getIsClosed())
            return;
        int fromBack = 0;
        bool hasInvalidated = invalidate;
        
        //Handle resizes.
        if (display.window_width() != canvas.width() || display.window_height() != canvas.height()) {
            canvas.resize(display);
            hasInvalidated = true;
        }
            
        if (lastTotalObjects != objects.size()) {
            if (lastTotalObjects > objects.size()) {
                //invalidate; size of objects has changed.. 
                //it can check this case automatically.
                //all other cases which cause invalidation
                //must call this function with the first param
                //set to true to force invalidation.
                hasInvalidated = true;
            } else {
                fromBack = objects.size() - lastTotalObjects;
            }
        };
        
        if(hasInvalidated){
            if (!backgroundImage.is_empty()) {
                canvas.assign(backgroundImage);
            } else {
                canvas.draw_rectangle(0, 0, canvas.width(), canvas.height(), backgroundColor.rgbPtr());
            }
        }else{
            if (redrawCounter >= redrawCounterMax) {
                redrawCounter = 0;
            } else {
                redrawCounter++;
                return;
            }
        }
        
        auto latestIter = !hasInvalidated ? std::prev(objects.end(), fromBack) : objects.begin();
        
        AffineTransform screen = screentransform();
        while (latestIter != objects.end()) {
            SceneObject& object = *latestIter;
            AffineTransform t(screen.copyConcatenate(object.transform));
            Color& color = object.color;
            IDrawableGeometry* geom = object.geom.get();
            if (!object.text.empty()) {
                Point trans = t.getTranslation();
                canvas.draw_text(trans.x, trans.y, object.text.c_str(), object.color.rgbPtr());
            } else if (object.stamp && object.unownedGeom != nullptr) {
                object.unownedGeom->draw(screen.copyConcatenate(object.transform), canvas, object.color);
            } else geom->draw(t, canvas, color);
            latestIter++;
        }

        if(canvas.width() != turtleComposite.width() || canvas.height() || turtleComposite.height()){
            turtleComposite.assign(canvas);
        }else{
            //Let's see if the draw_image is accellerated in some way
            turtleComposite.draw_image(0,0,canvas);
        }
        for (Turtle* turt : turtles) {
            turt->draw(screen, turtleComposite);
        }

        lastTotalObjects = objects.size();
        display.display(turtleComposite);
        sleep(delayMS);
    }

    void TurtleScreen::initEventThread() {
        eventThread.reset(new std::thread([&]() {
            //Mouse button states, between updates.
            //Keeps track of release/press etc
            //states for all three mouse buttons for isDown.
            bool mButtons[3] = {false, false, false};
            //Same thing for keys here.
            //(this is a list of keys marked as being in a "down" state)
            std::list<KeyboardKey> mKeys;
            
            while (!display.is_closed() && !killEventThread) {
                //Updates all input.
                if(!display.is_event()){
                    std::this_thread::yield();
                    continue;
                }
                
                cacheMutex.lock();
                
                AffineTransform mouseOffset = screentransform();
                Point mousePos = {(display.mouse_x() - mouseOffset.getTranslateX()) * mouseOffset.getScaleX(),
                               (display.mouse_y() - mouseOffset.getTranslateY()) * mouseOffset.getScaleY()};
                
                //Update mouse button input.
                const unsigned int button = display.button();
                bool buttons[3] = {
                    button & 1, //left
                    button & 2, //right
                    button & 4  //middle
                };

                for (int i = 0; i < 3; i++) {
                    if (!(!mButtons[i] && buttons[i]))//is this button state "down"?
                        continue; //if not, skip its processing loop.

                    for (MouseFunc& func : mouseBindings[i]) {
                        //append to the event cache.
                        InputEvent e;
                        e.type = false;
                        //perform an inverse translation, then apply scaling.
                        e.mX = mousePos.x;
                        e.mY = mousePos.y;
                        e.cbPointer = reinterpret_cast<void*> (&func);
                        cachedEvents.push_back(e);
                    }
                }
                
                const auto& keys = getKeys();
                
                //iterate through every key to determine its state,
                //then call the appropriate callbacks.
                for(const auto& keyPair : keys){
                    KeyboardKey key = keyPair.second;
                    const bool lastDown = std::find(mKeys.begin(), mKeys.end(), key) != mKeys.end();
                    const bool curDown = display.is_key((unsigned int) key);
                    
                    int state = -1;
                    if (!lastDown && curDown) {
                        //Key down.
                        state = 0;
                        mKeys.push_back(key);
                    } else if (lastDown && !curDown) {
                        //Key up.
                        state = 1;
                        mKeys.remove(key);
                    }else continue; //skip on case where it was down and is down
                    
                    try {
                        //will throw if no bindings available for key,
                        //and that's perfectly fine, so we just silently catch
                        auto& bindingList = keyBindings[state][key];
                        for (auto& cb : bindingList) {
                            cb();
                        }
                    } catch (...) {}
                }

                mButtons[0] = buttons[0];
                mButtons[1] = buttons[1];
                mButtons[2] = buttons[2];
                
                cacheMutex.unlock();
            }
        }));
    }

    /*Raw Turtle========================================*/

    Turtle::Turtle(TurtleScreen& scr) {
        screen = &scr;
        screen->add(*this);
        screen->redraw(true);
    }

    //write

    void Turtle::write(const std::string& text) {
        pushText(transform, fillColor, text);
        updateParent(false, false);
    }

    //Stamps

    int Turtle::stamp() {
        pushStamp(AffineTransform(transform).rotate(cursorTilt), fillColor, cursor);
        return curStamp;
    }

    void Turtle::clearstamp(int stampid) {
        auto iter = objects.begin();//iterator which holds an iterator to the screen's scene list.

        while (iter != objects.end()) {
            auto& objIter = *iter;
            if (objIter->stamp && objIter->stampid == stampid) {
                break;
            }
            iter++;
        }

        if (iter != objects.end()){
            objects.erase(iter);
            
            if(screen != nullptr){
                screen->getScene().erase(*iter);
            }
        }
    }

    void Turtle::clearstamps(int stampid) {
        typedef decltype(objects.begin()) iter_t;

        std::list<iter_t> removals;

        iter_t iter = objects.begin();
        while (iter != objects.end()) {
            auto& objIter = *iter;
            if (stampid < 0 ? objIter->stamp : (objIter->stamp && objIter->stampid <= stampid)) {
                removals.push_back(iter);
            }
            iter++;
        }

        for (iter_t& iter : removals) {
            screen->getScene().erase(*iter);
            objects.erase(iter);
        }
    }

    //Movement

    void Turtle::forward(int pixels) {
        if (screen == nullptr)
            return;
        travelTo(AffineTransform(transform).forward(pixels));
    }

    void Turtle::backward(int pixels) {
        if (screen == nullptr)
            return;
        travelTo(AffineTransform(transform).backward(pixels));
    }

    void Turtle::right(float amt) {
        amt = angleMode ? -amt : -toRadians(amt);
        //Flip angle orientation based on screen mode.
        amt = (screen != nullptr) ? screen->mode() == SM_STANDARD ? amt : -amt : SM_STANDARD;
        travelTo(AffineTransform(transform).rotate(amt));
    }

    void Turtle::left(float amt) {
        amt = angleMode ? amt : toRadians(amt);
        //Flip angle orientation based on screen mode.
        amt = (screen != nullptr) ? screen->mode() == SM_STANDARD ? amt : -amt : SM_STANDARD;
        travelTo(AffineTransform(transform).rotate(amt));
    }

    void Turtle::setheading(float amt) {
        //Swap to correct unit if necessary.
        amt = angleMode ? amt : toRadians(amt);
        //Flip angle orientation based on screen mode.
        amt = (screen != nullptr) ? screen->mode() == SM_STANDARD ? amt : -amt : SM_STANDARD;
        travelTo(AffineTransform(transform).setRotation(amt));
    }

    void Turtle::goTo(int x, int y) {//had to change due to C++ keyword "goto"
        travelTo(AffineTransform(transform).setTranslation(x, y));
    };

    void Turtle::setx(int x) {
        travelTo(AffineTransform(transform).setTranslationX(x));
    }

    void Turtle::sety(int y) {
        travelTo(AffineTransform(transform).setTranslationY(y));
    }

    void Turtle::home() {
        //TODO: SetHome?
        travelTo(AffineTransform());
    }

    //Drawing & Misc.

    void Turtle::reset() {
        //Reset objects, transforms, and trace lines
        
        if(screen != nullptr){
            while(!objects.empty()){
                screen->getScene().erase(objects.front());
                objects.pop_front();
            }
            screen->redraw(true);
        }
        
        //Note to self, clearing the list, appending a new transform,
        //then reassigning the transform reference just didn't want to work.
        //I have no idea why. Therefore, we're resetting it in the same
        //manner we initially construct it.
        transformStack = {AffineTransform()};
        transform = transformStack.back();

        //reset values pulled from their initial values.
        moveSpeed = TS_NORMAL;
        angleMode = false;
        tracing = true;
        penWidth = 1;
        filling = false;
        penColor = Color::black;
        fillAccum.points.clear();
        fillColor = Color::black;
        cursor = &const_cast<IDrawableGeometry&>(cturtle::shape("indented triangle"));
        curStamp = 0;
        cursorVisible = true;
        cursorTilt = 0.0f;

        updateParent(true);
    }

    void Turtle::updateParent(bool invalidate, bool input) {
        if (screen != nullptr)
            screen->update(invalidate, input);
    }

    void Turtle::circle(int radius, int steps, Color color) {
        pushGeom(transform, color, new Circle(radius, steps));
        updateParent();
    }

    void Turtle::fill(bool state) {
        if (filling && !state) {
            //excuse long line, but this fixes a particularly hard to find bug
            objects.push_back(screen->getScene().emplace(std::next(fillInsert),
                    new Polygon(fillAccum.points), fillColor, AffineTransform()));
            fillAccum.points.clear();
            updateParent(true, false);
            //trace line geometry in the screen's scene list.
        }else if(!filling && state){
            fillInsert = std::prev(screen->getScene().end());
        }
        filling = state;
    }

    void Turtle::draw(const AffineTransform& screen, Image& canvas) {
        if (this->screen == nullptr || (!cursorVisible && !tracing))
            return;

        if (cursorVisible) {
            if(traveling && tracing){
                //Draw the "Travel-Line" when in the middle of the travelTo func
                travelPoints[0] = screen(travelPoints[0]);
                travelPoints[1] = screen(travelPoints[1]);
                
                drawLine(canvas, travelPoints[0].x, travelPoints[0].y, travelPoints[1].x, travelPoints[1].y, penColor, penWidth);
            }
            //Add the extra rotate to start cursor facing right :)
            const float cursorRot = (this->screen->mode() == SM_STANDARD ? 1.5708f : 0.0f) + cursorTilt;
            AffineTransform cursorTransform = screen.copyConcatenate(transform).rotate(cursorRot);
            cursor->draw(cursorTransform, canvas, fillColor, 1, penColor);
        }
    }

    void Turtle::undo() {
        //\TODO: Need to implement.
        updateParent();
    }

    void Turtle::tilt(float amt) {
        amt = angleMode ? amt : toRadians(amt);
        //Flip angle orientation based on screen mode.
        amt = screen->mode() == SM_STANDARD ? amt : -amt;
        cursorTilt += amt;
        updateParent();
    }

    void Turtle::setshowturtle(bool state) {
        cursorVisible = state;
        updateParent();
    }

    void Turtle::setpenstate(bool down) {
        tracing = down;
    }
    
    void Turtle::travelTo(const AffineTransform& dest) {
        traveling = true;
        
        AffineTransform begin;
        begin.assign(transform);
        
        if (screen != nullptr ? !screen->getIsClosed() : false) {//no point in animating with no screen
            auto& scene = this->screen->getScene();
            const float duration = getAnimMS();
            const unsigned long startTime = epochTime();
            const unsigned long endTime = duration + startTime;

            AffineTransform start;
            start.assign(transform);
            
            float progress = duration == 0 ? 1 : 0;
            while (progress < 1.0f) {
                //We use the time between animation frames to smooth out
                //our animations, making them take the same amount of time
                //regardless of how it's performance.
                unsigned long curTime = epochTime();

                transform.assign(start.lerp(dest, progress));
                travelPoints[0] = begin.getTranslation();
                travelPoints[1] = transform.getTranslation();
                screen->redraw();
                
                progress = ((curTime - startTime) / duration);
                std::this_thread::yield();
            }
        }
        
        //Contents of PushCurrent moved here because every function
        //that called this one called PushCurrent immediately after it.
        if(tracing){
            pushTraceLine(begin.getTranslation(), dest.getTranslation());
        }
        
        transform.assign(dest);
        
        if (filling)
            fillAccum.points.push_back(transform.getTranslation());
        
        transformStack.push_back(transform);
        transform = transformStack.back();
        traveling = false;
        
        updateParent(false, false);
    }
    
    bool Turtle::pushGeom(const AffineTransform& t, Color color, IDrawableGeometry* geom) {
        if (screen != nullptr) {
            screen->getScene().emplace_back(geom, color, t);
            objects.push_back(std::prev(screen->getScene().end()));
            return true;
        }
        return false;
    }

    bool Turtle::pushStamp(const AffineTransform& t, Color color, IDrawableGeometry* geom) {
        if (screen != nullptr) {
            screen->getScene().emplace_back(geom, color, t, curStamp++);
            objects.push_back(std::prev(screen->getScene().end()));
            return true;
        }
        return false;
    }
    
    bool Turtle::pushText(const AffineTransform& t, Color color, const std::string& text) {
        if (screen != nullptr) {
            screen->getScene().emplace_back(text, color, t);
            objects.push_back(std::prev(screen->getScene().end()));
            return true;
        }
        return false;
    }
    
    bool Turtle::pushTraceLine(Point a, Point b){
        if(screen != nullptr){
            screen->getScene().emplace_back(new Line(a, b, penWidth), penColor, AffineTransform());
            objects.push_back(std::prev(screen->getScene().end()));
            return true;
        }
        return false;
    }
}
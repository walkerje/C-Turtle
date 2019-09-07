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
        
        //Gotta do binding alterations under the cache's mutex lock.
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
    
    void TurtleScreen::mode(ScreenMode mode) {
        //Resets & re-orients all turtles.
        
        curMode = mode;
        for (Turtle* t : turtles) {
            t->reset();
        }
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
        std::this_thread::yield();
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
        if(isclosed())
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
            IDrawableGeometry* geom = object.geom.get() ? object.geom.get() : object.unownedGeom;
            
            if(geom != nullptr){
                geom->draw(t, canvas, object.fillColor, object.outlineWidth, object.outlineColor);
            }else if(!object.text.empty()){
                //Draw text
                Point trans = t.getTranslation();
                canvas.draw_text(trans.x, trans.y, object.text.c_str(), object.fillColor.rgbPtr());
            }
            
            latestIter++;
        }

        if(canvas.width() != turtleComposite.width() || canvas.height() || turtleComposite.height()){
            turtleComposite.assign(canvas);
        }else{
            //Let's see if the draw_image is accelerated in some way
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
                Point mousePos = {int((display.mouse_x() - mouseOffset.getTranslateX()) * mouseOffset.getScaleX()),
                               int((display.mouse_y() - mouseOffset.getTranslateY()) * mouseOffset.getScaleY())};
                
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
        reset();
    }

    //write

    void Turtle::write(const std::string& text) {
        pushText(transform, state.fillColor, text);
        updateParent(false, false);
    }

    //Stamps

    int Turtle::stamp() {
        pushStamp(transform, state.fillColor, state.cursor);
        return state.curStamp;
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
        amt = state.angleMode ? -amt : -toRadians(amt);
        //Flip angle orientation based on screen mode.
        travelTo(AffineTransform(transform).rotate(amt));
    }

    void Turtle::left(float amt) {
        amt = state.angleMode ? amt : toRadians(amt);
        //Flip angle orientation based on screen mode.
        travelTo(AffineTransform(transform).rotate(amt));
    }

    void Turtle::setheading(float amt) {
        //Swap to correct unit if necessary.
        amt = state.angleMode ? amt : toRadians(amt);
        //Flip angle orientation based on screen mode.
        amt = (screen != nullptr) ? screen->mode() == SM_STANDARD ? amt : -amt : amt;
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
        travelTo(AffineTransform());
    }

    //Drawing & Misc.

    void Turtle::reset() {
        //Reset objects, transforms, trace lines, state, etc.
        
        //Note to self, clearing the list, appending a new transform,
        //then reassigning the transform reference just didn't want to work.
        //I have no idea why. Therefore, we're resetting it in the same
        //manner we initially construct it.
        stateStack = {PenState()};
        state = stateStack.back();
        transform = state.transform;
        
        if(screen != nullptr){
            //Erase all objects
            while(!objects.empty()){
                screen->getScene().erase(objects.front());
                objects.pop_front();
            }
            
            //Alter cursor tilt and default transform
            //when operating under SM_LOGO mode.
            //This is to bring it up-to-par with Python's
            //implementation of screen modes.
            //I can't decide if this solution is too "hacky" or not;
            //it solves the problem, but I could have done it differently.
            if(screen->mode() == SM_LOGO){
                state.cursorTilt = (-1.5708);
                transform.rotate(1.5708);
            }
        }
        
        updateParent(true, false);
    }
    
    //Conditional parent update.

    void Turtle::updateParent(bool invalidate, bool input) {
        if (screen != nullptr)
            screen->update(invalidate, input);
    }

    void Turtle::circle(int radius, int steps, Color color) {
        pushGeom(transform, color, new Circle(radius, steps));
        updateParent();
    }

    void Turtle::fill(bool val) {
        if (state.filling && !val) {
            //Add the fill polygon
            screen->getScene().emplace_back(new Polygon(fillAccum.points), state.fillColor, AffineTransform());
            objects.push_back(std::prev(screen->getScene().end(), 1));
            
            //Add all trace lines created when tracing out the fill polygon.
            if(state.filling && !fillLines.empty()){
                for(const auto& lineInfo : fillLines){
                    screen->getScene().emplace_back(new Line(lineInfo.first), lineInfo.second, AffineTransform());
                    objects.push_back(std::prev(screen->getScene().end(), 1));
                }
                fillLines.clear();
            }
            
            fillAccum.points.clear();
            updateParent(false, false);
            //trace line geometry in the screen's scene list.
        }
        state.filling = val;
    }

    void Turtle::draw(const AffineTransform& screen, Image& canvas) {
        if (this->screen == nullptr || (!state.visible && !state.tracing))
            return;

        if (state.visible) {
            //Draw all lines queued during filling a shape.
            //This is only populated when the turtle moves between a beginfill
            //and endfill while the pen is down.
            for(auto& lineVal : fillLines){
                Line& line = lineVal.first;
                Color& color = lineVal.second;
                line.draw(screen, canvas, color);
            }
            
            if(traveling && state.tracing){
                //Draw the "Travel-Line" when in the middle of the travelTo func
                travelPoints[0] = screen(travelPoints[0]);
                travelPoints[1] = screen(travelPoints[1]);
                
                drawLine(canvas, travelPoints[0].x, travelPoints[0].y, travelPoints[1].x, travelPoints[1].y, state.penColor, state.penWidth);
            }
            //Add the extra rotate to start cursor facing right :)
            float cursorRot = this->screen->mode() == SM_STANDARD ? 1.5708f : -3.1416; 
            AffineTransform cursorTransform = screen.copyConcatenate(transform).rotate(cursorRot + state.cursorTilt);
            state.cursor->draw(cursorTransform, canvas, state.fillColor, 1, state.penColor);
        }
    }

    bool Turtle::undo() {
        const unsigned long int totalBefore = state.objectsBefore;
        
        if(stateStack.size() >= 2)
            travelBack();//Travel back if stack size >= 2
        
        if(!popState()){
            return false;
        }
        
        auto begin = std::prev(objects.end(), (totalBefore - state.objectsBefore));
        auto iter = begin;
        
        while(iter != objects.end()){
            screen->getScene().erase(*iter);
            iter++;
        }
        
        objects.erase(begin, objects.end());
        
        //Will invalidate due to object removal.
        updateParent(true, false);
        return true;
    }

    void Turtle::tilt(float amt) {
        amt = state.angleMode ? amt : toRadians(amt);
        //Flip angle orientation based on screen mode.
        amt = screen->mode() == SM_STANDARD ? amt : -amt;
        pushState();
        state.cursorTilt += amt;
        updateParent(false, false);
    }

    void Turtle::setshowturtle(bool val) {
        pushState();
        state.visible = val;
        updateParent(false, false);
    }

    void Turtle::setpenstate(bool down) {
        pushState();
        state.tracing = down;
    }
    
    void Turtle::travelTo(const AffineTransform& dest) {
        if(dest == transform)
            return;//No traveling needs to take place.
        
        traveling = true;
        
        AffineTransform begin;
        begin.assign(transform);
        
        if (screen != nullptr ? !screen->isclosed(): false) {//no point in animating with no screen
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
        if(state.tracing && !state.filling){
            pushTraceLine(begin.getTranslation(), dest.getTranslation());
        } else if (state.filling){
            fillAccum.points.push_back(dest.getTranslation());
            if(state.tracing){
                fillLines.push_back({{begin.getTranslation(), dest.getTranslation(), state.penWidth}, state.penColor});
            }
        }
        
        transform.assign(begin);
        pushState();
        transform.assign(dest);
        
        traveling = false;
        updateParent(false, false);
    }
    
    void Turtle::travelBack(){
        //This function is redundant and should be removed.
        //Alternatively, make travelTo function handle this case more efficiently.
        const AffineTransform a = state.transform;
        const AffineTransform b = std::prev(stateStack.end(), 2)->transform;
        
        if(a == b)
            return;//no interpolation or animation needed.
        
        traveling = true;
        
        if (screen != nullptr ? !screen->isclosed() : false) {//no point in animating with no screen
            auto& scene = this->screen->getScene();
            const float duration = getAnimMS();
            const unsigned long startTime = epochTime();
            const unsigned long endTime = duration + startTime;

            AffineTransform start;
            start.assign(a);
            
            float progress = duration == 0 ? 1 : 0;
            while (progress < 1.0f) {
                //We use the time between animation frames to smooth out
                //our animations, making them take the same amount of time
                //regardless of how it's performance.
                unsigned long curTime = epochTime();

                transform.assign(start.lerp(b, progress));
                travelPoints[0] = b.getTranslation();
                travelPoints[1] = transform.getTranslation();
                screen->redraw();
                
                progress = ((curTime - startTime) / duration);
                std::this_thread::yield();
            }
        }
        
        state.transform.assign(b);
        
        traveling = false;
        updateParent(false, false);
    }
    
    void Turtle::pushState(){
        if(stateStack.size() + 1 > undoStackSize)
            stateStack.pop_front();
        stateStack.push_back(PenState(state));
        state = stateStack.back();
        transform = state.transform;
        state.objectsBefore = objects.size();
    }
    
    bool Turtle::popState(){
        if(stateStack.size() == 1)
            return false;
        stateStack.pop_back();
        state = stateStack.back();
        transform = state.transform;
        return true;
    }
    
    bool Turtle::pushGeom(const AffineTransform& t, Color color, IDrawableGeometry* geom) {
        if (screen != nullptr) {
            pushState();
            screen->getScene().emplace_back(geom, color, t);
            objects.push_back(std::prev(screen->getScene().end()));
            return true;
        }
        return false;
    }

    bool Turtle::pushStamp(const AffineTransform& t, Color color, IDrawableGeometry* geom) {
        if (screen != nullptr) {
            pushState();
            const float cursorRot = this->screen->mode() == SM_STANDARD ? 1.5708f : -3.1416; 
            
            AffineTransform trans(t);
            trans.rotate(cursorRot + state.cursorTilt);
            
            screen->getScene().emplace_back(geom, color, trans, state.curStamp++);
            SceneObject& obj = screen->getScene().back();
            obj.outlineWidth = 1;
            obj.outlineColor = state.penColor;
            
            objects.push_back(std::prev(screen->getScene().end()));
            return true;
        }
        return false;
    }
    
    bool Turtle::pushText(const AffineTransform& t, Color color, const std::string& text) {
        if (screen != nullptr) {
            pushState();
            screen->getScene().emplace_back(text, color, t);
            objects.push_back(std::prev(screen->getScene().end()));
            return true;
        }
        return false;
    }
    
    bool Turtle::pushTraceLine(Point a, Point b){
        if(screen != nullptr){
            screen->getScene().emplace_back(new Line(a, b, state.penWidth), state.penColor, AffineTransform());
            objects.push_back(std::prev(screen->getScene().end()));
            //Trace lines do NOT push a state.
            //Their state is encompassed by movement,
            //and these lines are only added when moving anyway.
            return true;
        }
        return false;
    }
}
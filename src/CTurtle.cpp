#define CTURTLE_IMPLEMENTATION
#include "CTurtle.hpp"
#include <cstdlib>

namespace cturtle {
    /*Shape Registration =================================*/
    namespace{
        std::map<std::string, Polygon> shapes = {
            {"triangle", 
                Polygon({
                    {0, 0},
                    {-5, 5},
                    {5, 5}
            })},
            {"square",
                Polygon({
                    {-5, -5},
                    {-5, 5},
                    {5, 5},
                    {5, -5}
            })},
            {"indented triangle",
                Polygon({
                    {0, 7},
                    {-7, 7},
                    {0, 0},
                    {7, 7}
            })}
        };
    }
    
    void registerShape(const std::string& name, const Polygon& p){
        shapes[name] = p;
    }
    
    const Polygon& shape(const std::string name){
        return shapes[name];
    }
    
    /*TurtleScreen =======================================*/
    void TurtleScreen::clearscreen() {
        //1) Delete all drawings and turtles
        //2) White background
        //3) No background image
        //4) No event bindings
        //5) Tracing turned on

        for(RawTurtle* turtle : turtles){
            turtle->setScreen(nullptr);
        }
        turtles.clear();
        backgroundColor = Color::white;
        backgroundImage.assign();
        //TODO: Reset other callbacks
        timerFunc = [](void) {
        };
        curMode = SM_STANDARD;
        redraw();
    }

    void TurtleScreen::resetscreen() {
        for (RawTurtle* turtle : turtles) {
            turtle->reset();
        }
    }

    ivec2 TurtleScreen::screensize(Color& bg) {
        bg = backgroundColor;
        return {display.screen_width(), display.screen_height()};
    }

    void TurtleScreen::update() {
        //TODO: Implement Me?
    }

    void TurtleScreen::delay(unsigned int ms) {
        delayMS = ms;
    }

    unsigned int TurtleScreen::delay() {
        return delayMS;
    }

    void TurtleScreen::bye() {
        resetscreen();
        display.close();
    }

    void TurtleScreen::redraw() {
        //TODO: Move this somewhere else 
        if(getIsClosed())
            return;
        AffineTransform screen = screentransform();
        for (RawTurtle* turtle : turtles) {
            turtle->draw(screen, canvas);
        }
        sleep(delayMS);
        swap();
    }

    /*Raw Turtle========================================*/

    RawTurtle::RawTurtle(TurtleScreen& scr) {
        screen = &scr;
        screen->add(*this);
    }
    
    //write
    void RawTurtle::write(const std::string& text){
        pushText(transform, fillColor, text);
        redrawParent();
    }
    
    //Stamps
    int RawTurtle::stamp(){
        Polygon* p = new Polygon(cursor);
        pushStamp(transform, fillColor, p);
        return curStamp;
    }
    
    void RawTurtle::clearstamp(int stampid){
        auto iter = objects.begin();
        
        while(iter != objects.end()){
            SceneObject& obj = *iter;
            if(obj.stamp && obj.stampid == stampid){
                break;
            }
            iter++;
        }
        
        if(iter != objects.end())
            objects.erase(iter);
    }
    
    void RawTurtle::clearstamps(int stampid){
        typedef decltype(objects.begin()) iter_t;
        
        std::list<iter_t> removals;

        iter_t iter = objects.begin();
        while (iter != objects.end()) {
            SceneObject& obj = *iter;
            if (stampid < 0 ? obj.stamp : (obj.stamp && obj.stampid <= stampid)) {
                removals.push_back(iter);
            }
            iter++;
        }
        
        for(iter_t& iter : removals){
            objects.erase(iter);
        }
    }

    //Movement

    void RawTurtle::forward(int pixels) {
        if(screen == nullptr)
            return;
        travelTo(AffineTransform(transform).forward(pixels));
    }

    void RawTurtle::backward(int pixels) {
        if(screen == nullptr)
            return;
        travelTo(AffineTransform(transform).backward(pixels));
    }

    void RawTurtle::right(float amt) {
        amt = angleMode ? amt : toRadians(amt);
        //Flip angle orientation based on screen mode.
        amt = (screen != nullptr) ? screen->mode() == SM_STANDARD ? amt : -amt : SM_STANDARD; 
        travelTo(AffineTransform(transform).rotate(amt));
    }

    void RawTurtle::left(float amt) {
        amt = angleMode ? -amt : -toRadians(amt);
        //Flip angle orientation based on screen mode.
        amt = (screen != nullptr) ? screen->mode() == SM_STANDARD ? amt : -amt : SM_STANDARD; 
        travelTo(AffineTransform(transform).rotate(amt));
    }
    
    void RawTurtle::setheading(float amt){
        //TODO: Animation for setheading
        amt = angleMode ? amt : toRadians(amt);
        //Flip angle orientation based on screen mode.
        amt = (screen != nullptr) ? screen->mode() == SM_STANDARD ? amt : -amt : SM_STANDARD; 
        transform.setRotation(amt);
        redrawParent();
    }

    void RawTurtle::goTo(int x, int y) {//had to change due to C++ keyword "goto"
        transform.setTranslation(x, y);
        pushCurrent();
        redrawParent();
    };

    void RawTurtle::setx(int x) {
        transform.setTranslationX(x);
        pushCurrent();
        redrawParent();
    }

    void RawTurtle::sety(int y) {
        transform.setTranslationY(y);
        pushCurrent();
        redrawParent();
    }

    void RawTurtle::home() {
        transform.identity();
        //TODO: sethome?
        pushCurrent();
        redrawParent();
    }

    //Drawing & Misc.

    void RawTurtle::reset() {
        //Reset transform.
        transformStack.clear();
        transformStack.push_back(AffineTransform());
        transform = transformStack.back();
        
        //Clear scene objects
        objects.clear();
        
        //Reset all small variables to their defaults
        penColor = Color::black;
        moveSpeed = TS_NORMAL;
        angleMode = false;
        tracing = true;
        penWidth = 1;
        filling = false;
        fillAccum.points.clear();
        fillColor = Color::black;
        cursor = cturtle::shape("indented triangle");
        curStamp = 0;
        cursorVisible = true;
        cursorTilt = 0.0f;
    }
    
    void RawTurtle::redrawParent(){
        if(screen != nullptr)
            screen->redraw();
    }

    void RawTurtle::circle(int radius, int steps, Color color) {
        pushGeom(transform, color, new Circle(radius, steps));
        redrawParent();
    }

    void RawTurtle::fill(bool state) {
        if (filling && !state) {
            pushGeom(AffineTransform(), fillColor, new Polygon(fillAccum.points));
            fillAccum.points.clear();
            redrawParent();
        }
        filling = state;
    }

    void RawTurtle::draw(const AffineTransform& screen, Image& canvas) {
        if(this->screen == nullptr)
            return;
        for (SceneObject& object : objects) {
            AffineTransform t(screen.copyConcatenate(object.transform));
            Color& color = object.color;
            IDrawableGeometry* geom = object.geom.get();
            if(!object.text.empty()){
                Point trans = t.getTranslation();
                canvas.draw_text(trans.x, trans.y, object.text.c_str(), object.color.rgbPtr());
            }else if(object.stamp){
                Polygon* p = static_cast<Polygon*>(geom);
                p->draw(t, canvas, color);
                p->drawOutline(t, canvas);
            }else geom->draw(t, canvas, color);
        }
        
        if(traceLines.empty() && tracing){
            //Draw a line from origin to turtle.
            Point src = screen(Point(0,0));
            Point dest = screen(transform.getTranslation());
            drawLine(canvas, src.x, src.y, dest.x, dest.y, penColor, penWidth);
        }else if(!traceLines.empty()){
            
            for(auto& pair : traceLines){
                Color& color = pair.first;
                Line& line = pair.second;
                line.draw(screen, canvas, color);
            }
            
            if(tracing){
                Point a = screen(traceLines.back().second.pointB);
                Point b = screen(transform.getTranslation());;

                drawLine(canvas, a.x, a.y, b.x, b.y, penColor, penWidth);
            }
        }
        
        if(cursorVisible){
            //Add the extra rotate to start cursor facing right :)
            const float cursorRot = (this->screen->mode() == SM_STANDARD ? 1.5708f : 0.0f) + cursorTilt;
            AffineTransform cursorTransform = screen.copyConcatenate(transform).rotate(cursorRot);
            cursor.draw(cursorTransform, canvas, fillColor);
            cursor.drawOutline(cursorTransform, canvas);
        }
    }

    void RawTurtle::undo() {
        if(transformStack.size() <= 1)
            return;//Cannot undo anymore.
        objects.pop_back();//TODO: Will pop regardless of previous action
        traceLines.pop_back();
        transformStack.pop_back();
        transform = transformStack.back();
        redrawParent();
    }
    
    void RawTurtle::tilt(float amt){
        amt = angleMode ? amt : toRadians(amt);
        //Flip angle orientation based on screen mode.
        amt = screen->mode() == SM_STANDARD ? amt : -amt; 
        cursorTilt += amt;
        redrawParent();
    }
    
    void RawTurtle::setshowturtle(bool state) {
        cursorVisible = state;
        redrawParent();
    }
}
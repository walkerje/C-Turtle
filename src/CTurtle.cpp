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
                    {0, 5},
                    {-5, 5},
                    {0, 0},
                    {5, 5}
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

        turtles.clear();
        backgroundColor = Color::white;
        backgroundImage.assign();
        //TODO: Reset other callbacks
        timerFunc = [](void) {
        };
        tracing = true;
    }

    void TurtleScreen::resetscreen() {
        //        for(auto& turtle : turtles){
        //            turtle.reset();
        //        }
    }

    vec2 TurtleScreen::screensize(Color& bg) {
        bg = backgroundColor;
        return {(float) display.screen_width(), (float) display.screen_height()};
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
        display.close();
    }

    void TurtleScreen::redraw() {
        //TODO: Move this somewhere else 
        if(getIsClosed()){
            exit(EXIT_SUCCESS);
        }
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
    
    //Stamps
    int RawTurtle::stamp(){
        Polygon* p = new Polygon(cursor);
        pushStamp(transform, Color::black, p);
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
        const float duration = getAnimMS();
        const unsigned long startTime = epochTime();
        const unsigned long endTime = duration + startTime;
        
        AffineTransform start;
        start.assign(transform);
        
        float progress = duration == 0 ? 1 : 0;
        while (progress < 1.0f) {
            progress = (epochTime() - startTime) / duration;
            transform.assign(start);
            transform.forward(progress * pixels);
            screen->redraw();
        }
        
        transform.assign(start);
        transform.forward(pixels);
        pushCurrent();
        screen->redraw();
    }

    void RawTurtle::backward(int pixels) {
        const float duration = getAnimMS();
        const unsigned long startTime = epochTime();
        const unsigned long endTime = duration + startTime;
        
        AffineTransform start;
        start.assign(transform);
        
        float progress = duration == 0 ? 1 : 0;
        while (progress < 1.0f) {
            progress = (epochTime() - startTime) / duration;
            transform.assign(start);
            transform.backward(progress * pixels);
            screen->redraw();
        }
        
        transform.assign(start);
        transform.backward(pixels);
        pushCurrent();
        screen->redraw();
    }

    void RawTurtle::right(float amt) {
        amt = angleMode ? amt : toRadians(amt);
        
        const float duration = getAnimMS();
        const unsigned long startTime = epochTime();
        const unsigned long endTime = duration + startTime;
        
        AffineTransform start;
        start.assign(transform);
        
        float progress = duration == 0 ? 1 : 0;
        while (progress < 1.0f) {
            progress = (epochTime() - startTime) / duration;
            transform.assign(start);
            transform.rotate(progress * amt);
            screen->redraw();
        }
        transform.assign(start);
        transform.rotate(amt);
        screen->redraw();
    }

    void RawTurtle::left(float amt) {
        amt = angleMode ? -amt : -toRadians(amt);
        
        const float duration = getAnimMS();
        const unsigned long startTime = epochTime();
        const unsigned long endTime = duration + startTime;
        
        AffineTransform start = transform;
        
        float progress = duration == 0 ? 1 : 0;
        while (progress < 1.0f) {
            progress = (epochTime() - startTime) / duration;
            transform.assign(start);
            transform.rotate(progress * amt);
            screen->redraw();
        }
        
        transform.assign(start);
        transform.rotate(amt);
        screen->redraw();
    }

    void RawTurtle::goTo(int x, int y) {//had to change due to C++ keyword "goto"
        transform.setTranslation(x, y);
        pushCurrent();
        screen->redraw();
    };

    void RawTurtle::setx(int x) {
        transform.setTranslationX(x);
        pushCurrent();
        screen->redraw();
    }

    void RawTurtle::sety(int y) {
        transform.setTranslationY(y);
        pushCurrent();
        screen->redraw();
    }

    void RawTurtle::home() {
        transform.identity();
        //TODO: sethome?
        pushCurrent();
        screen->redraw();
    }

    //Drawing & Misc.

    void RawTurtle::reset() {

    }

    void RawTurtle::circle(int radius, int steps, Color color) {
        pushGeom(transform, color, new Circle(radius, steps));
        screen->redraw();
    }

    void RawTurtle::fill(bool state) {
        if (filling && !state) {
            pushGeom(AffineTransform(), fillColor, new Polygon(fillAccum.points));
            fillAccum.points.clear();
            screen->redraw();
        }
        filling = state;
    }

    void RawTurtle::draw(const AffineTransform& screen, Image& canvas) {
        
        for (SceneObject& object : objects) {
            AffineTransform t(screen.copyConcatenate(object.transform));
            Color& color = object.color;
            IDrawableGeometry* geom = object.geom.get();
            geom->draw(t, canvas, color);
        }

        if (tracing && !tracePoints.empty()) {
            Point cur = screen(tracePoints[0]);

            for (int i = 1; i < tracePoints.size(); i++) {
                cur = screen(tracePoints[i]);
                Point prev = screen(tracePoints[i - 1]);
                canvas.draw_line(prev.x, prev.y, cur.x, cur.y, Color::black.rgbPtr());
            }

            Point tPos = screen(transform.getTranslation());
            canvas.draw_line(cur.x, cur.y, tPos.x, tPos.y, Color::black.rgbPtr());
        }
        
        //Optionally disable cursor?
        //TODO: Is this in tracer options?
        //Add the extra rotate to start cursor facing right :)
        cursor.draw(screen.copyConcatenate(transform).rotate(1.5708f), canvas);
    }

    void RawTurtle::undo() {
        objects.pop_back();
        tracePoints.pop_back();
        transform = objects.back().transform;
    }
}
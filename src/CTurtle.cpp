#define CTURTLE_IMPLEMENTATION
#include "CTurtle.hpp"

namespace cturtle{
    /*TurtleScreen =======================================*/
    void TurtleScreen::clearscreen(){
        //1) Delete all drawings and turtles
        //2) White background
        //3) No background image
        //4) No event bindings
        //5) Tracing turned on
        
//        turtles.clear();
        backgroundColor = Color::white;
        backgroundImage.assign();
        //TODO: Reset other callbacks
        timerFunc = [](void){};
//        tracing = true;
    }
    
    void TurtleScreen::resetscreen(){
//        for(auto& turtle : turtles){
//            turtle.reset();
//        }
    }
    
    vec2 TurtleScreen::screensize(Color& bg){
        bg = backgroundColor;
        return {(float)display.screen_width(), (float)display.screen_height()};
    }
    
    void TurtleScreen::setworldcoordinates(vec2 lowerLeft, vec2 upperRight){
        worldLowerLeft = lowerLeft;
        worldUpperRight = upperRight;
    }
    
    void TurtleScreen::update(){
        //TODO: Implement Me
    }
    
    void TurtleScreen::delay(unsigned int ms){
        delayMS = ms;
    }
    
    unsigned int TurtleScreen::delay(){
        return delayMS;
    }
    
    void TurtleScreen::bye(){
        display.close();
    }
    
    /*Raw Turtle========================================*/
    
}
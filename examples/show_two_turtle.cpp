/* 
 * File:   show_two_turtle.cpp
 * Author: Jesse W. Walker
 */

#include "CTurtle.hpp"

namespace ct = cturtle;

int main(int argc, char** argv) {
    ct::TurtleScreen scr;
    scr.bgcolor({"black"});
    
    ct::Turtle brad(scr);
    ct::Turtle angie(scr);
    
    brad.pencolor({"yellow"});
    brad.speed(ct::TS_FASTEST);
    
    for(int i = 0; i < 36; i++){
        for(int j = 0; j < 4; j++){
            brad.forward(200);
            brad.right(90);
        }
        brad.right(10);
    }
    
    angie.pencolor({"blue"});
    angie.speed(ct::TS_FASTEST);
    
    int size = 1;
    for(int i = 0; i < 300; i++){
        angie.forward(size);
        angie.right(91);
        size += 1;
    }
    
    brad.hideturtle();
    angie.hideturtle();
    
    scr.exitonclick();
    return 0;
}

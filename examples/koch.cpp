/* 
 * File:   show_koch.cpp
 * Author: Jesse W. Walker
 * Derived from http://cs.berea.edu/courses/csc226/tasks/koch-curve.py
 */

#include "CTurtle.hpp"

namespace ct = cturtle;

void koch(ct::Turtle& turtle, int order, float size){
    const int ANGLES[] = {60, -120, 60, 0};
    
    if(order == 0){
        turtle.forward(size);
    }else{
        for(int i = 0; i < 4; i++){
            koch(turtle, order-1, size/3.0f);
            turtle.left(ANGLES[i]);
        }
    }
}

int main(int argc, char** argv) {
    ct::TurtleScreen scr;
    scr.delay(0);
    
    ct::Turtle turtle(scr);
    turtle.speed(ct::TS_FASTEST);
    
    //Move the turtle backwards to get the
    //full fractal on screen.
    turtle.penup();
    turtle.back(250);
    turtle.pendown();
    
    //Call the recursive "Koch" function.
    koch(turtle, 5, 500.0f);
    
    scr.exitonclick();
    return 0;
}

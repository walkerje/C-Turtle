/* 
 * File:   show_undo.cpp
 * Author: Jesse W. Walker
 */

#include "CTurtle.hpp"

namespace ct = cturtle;

void draw_star(ct::Turtle& t){
    unsigned int startStackSz = t.undobufferentries();
    
    t.back(25);
    for(int i = 0; i < 5; i++){
        t.forward(50);
        t.right(144);
    }
    
    unsigned int endStackSz = t.undobufferentries() - startStackSz;
    
    for(int i = 0; i < endStackSz; i++)
        t.undo();
}

int main(int argc, char** argv) {
    ct::TurtleScreen scr;
    scr.tracer(0,0);
    ct::Turtle turtle(scr);
    
    //Set the size of the undo buffer/stack to 1000 total entry capacity.
    turtle.setundobuffer(1000);
    
    scr.onclick([&](int x, int y){
       turtle.penup();
       turtle.goTo(x,y);
       turtle.pendown();
       
       draw_star(turtle);
    });
    
    scr.mainloop();
    return 0;
}

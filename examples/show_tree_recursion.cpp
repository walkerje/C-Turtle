/* 
 * File:   show_recursion_spiral.cpp
 * Author: Jesse W. Walker
 */

#include "CTurtle.hpp"

namespace ct = cturtle;

void tree(ct::RawTurtle& rt, int len) {
    if(len > 5){
        rt.forward(len);
        rt.right(20);
        tree(rt, len - 15);
        rt.left(40);
        tree(rt, len - 15);
        rt.right(20);
        rt.back(len);
    }
}

int main(int argc, char** argv) {
    ct::TurtleScreen scr;
    scr.delay(0);
    ct::RawTurtle rt(scr);
    rt.left(90);
    rt.pencolor({"green"});
    rt.speed(ct::TS_FAST);
    
    scr.onclick([&](int x, int y) {
        rt.penup();
        rt.goTo(x, y);
        rt.pendown();
        tree(rt, 100);
    }, ct::MOUSEB_LEFT);

    scr.mainloop();
    return 0;
}

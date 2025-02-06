/* 
 * File:   show_recursion_spiral.cpp
 * Author: Jesse W. Walker
 */

#include "CTurtle.hpp"

namespace ct = cturtle;

void spiral(ct::Turtle& rt, int len) {
    if (len > 0) {
        rt.forward(len);
        rt.right(90);
        spiral(rt, len - 5);
    }
}

int main(int argc, char** argv) {
    ct::TurtleScreen scr;
    ct::Turtle rt(scr);

    scr.onclick([&](int x, int y) {
        rt.penup();
        rt.goTo(x, y);
        rt.pendown();
        spiral(rt, 100);
    }, ct::MOUSEB_LEFT);

    scr.mainloop();
    return 0;
}

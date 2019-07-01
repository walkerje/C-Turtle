#include "CTurtle.hpp"

namespace ct = cturtle;

int main(int argc, char** argv) {
    ct::TurtleScreen scr;
    ct::Turtle rt(scr);
    
    //Put Fun Turtle Code Here!

    scr.exitonclick();
    return 0;
}

//Make special note of these defines prior to usage.
#define CTURTLE_HEADLESS //Define to configure CTurtle for Headless mode.

#define CTURTLE_HEADLESS_SAVEDIR "./test.gif" //Optional define, default is "./cturtle.gif"
#define CTURTLE_HEADLESS_WIDTH 800 //Optional define, default is 400
#define CTURTLE_HEADLESS_HEIGHT 600 //Optional define, default is 300

#include "CTurtle.hpp"

namespace ct = cturtle;

int main(int argc, char** argv) {
    ct::TurtleScreen scr;
    ct::Turtle rt(scr);

    for(int i = 0; i < 4; i++){
        rt.forward(50);
        rt.right(90);
    }

    scr.bye();
    return 0;
}

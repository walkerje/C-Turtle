<p align="center">
  <img width="460" height="300" src="https://publicdomainvectors.org/photos/Tortoise-.png">
  <br>
</p>

# C-Turtle
#### [Documentation](https://walkerje.github.io/C-Turtle/docs/html/annotated.html)

C-Turtle is a port of Python's Turtle facility for C++11, with the intent of being a close analog to the Python implementation. This package was developed with the intent of student usage under an academic setting, and was designed to be "as easy to use as possible". This package has been released under the MIT license accordingly.
Given that this is intended to be an education-oriented package, to ease the setup process it has been created to be Header-Only. Simply copy CTurtle.hpp (alongside CImg.hpp) into your include path or project and you're ready to go.

This package heavily uses [CImg](http://cimg.eu/) for its display and drawing functions. As such, it must be available in the include path alongside CTurtle itself.

## Direct Comparison between C++ and Python
The following table contains examples, which do the exact same thing, between C-Turtle and Python's Turtle.

<table>
  <tr>
    <td><b>C++</b></td>
    <td><b>Python</b></td>
  </tr>
  <td>
    <pre lang="c++">
    
      #include "CTurtle.hpp"

      namespace ct = cturtle;

      int main(int argc, char** argv) {
          ct::TurtleScreen scr;
          ct::Turtle turtle(scr);
          turtle.speed(ct::TS_SLOWEST);
          turtle.fillcolor({"purple"});
          turtle.begin_fill();
          for (int i = 0; i < 4; i++) {
              turtle.forward(50);
              turtle.right(90);
          }
          turtle.end_fill();
          scr.bye();
          return 0;
      }

  </pre>
  </td>
  <td>
    <pre lang="python">
     
      import turtle

      turt = turtle.Turtle()
      turt.fillcolor("purple")
      turt.speed("slowest")

      turt.begin_fill()
      for i in range(4):
          turt.forward(50)
          turt.right(90)
      turt.end_fill()

      turt.bye()

   </pre>
  </td>
</table>

## Headless Mode
C-Turtle also supports drawing to an animated GIF instead of a display (e.g, "headless"). This is configurable through the "headless" preprocessor definitions, seen in following example. To write GIFs, C-Turtle uses [jo_gif](https://www.jonolick.com/home/gif-writer), a wonderful public domain GIF library created by Jon Olick. This avoids having ImageMagick as a dependency, which is what CImg uses by default to save animated GIFs.

In "headless" mode, TurtleScreen has all functionality relating to input and background images removed. This is due to 1) the lack of a display to receive event notifications, and 2) the lack of a guarantee of a safely-usable filesystem to *load* images from. It does work under the assumption that the filesystem is safe to save to, however.

```C++
//Make special note of these defines prior to usage.
#define CTURTLE_HEADLESS //Define to configure CTurtle for Headless mode.

#define CTURTLE_HEADLESS_SAVEDIR "./test.gif" //Optional define, default is "./cturtle.gif".
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
```

#### Why does headless mode take so long to save a GIF file?
A frame is added to the resulting GIF for every change in state for a Turtle. This includes rotation, pen changes, size changes, etcetera. You can choose to display only every N frames, and thus save only every N frames, by taking advantage of tracer settings (see ```tracer(int countmax, unsigned int delayMS)``` function in TurtleScreen documentation). This dramatically reduces file size and write time in exchange for less frames in the image.

#### Why does headless mode print HTML + Base64 by default?
Headless mode was developed with the intention of being embedded in web applications, namely Runestone Interactive textbooks. As such, it prints HTML to display the results of the executed code by printing a Base64-encoded version of the resulting GIF file. This lets CTurtle be very easily embedded without needing any extra tricks or external File IO with any kind of backend. This can be disabled by having ```#define CTURTLE_HEADLESS_NO_HTML``` before the inclusion of CTurtle.

## Student Work Showcase
As time progresses, and as I am afforded the opportunity, I will provide visual examples of work students have done using this library. None of these are produced by my own work (but did use C-Turtle in their generation), however permission was given to post the works here!

An example of artwork generated in the style of Piet Mondrian as part of an assignment on Recursion.
Azis Toktobaev - Berea College
![Mondrian Art Example](https://i.imgur.com/PoMCwXn.png)

A similar example of artwork also generated in the style of Piet Mondrian as part of an assignment on Recursion. Bryar Frank - Berea College
![Mondrian Art Example 2](https://i.imgur.com/ixf4fUE.jpg)

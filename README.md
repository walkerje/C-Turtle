<p align="center">
  <img width="460" height="300" src="https://publicdomainvectors.org/photos/Tortoise-.png">
  <br>
</p>

# C-Turtle
#### [Documentation](https://walkerje.github.io/C-Turtle/docs/index.html)
#### [Setup / Installation](https://walkerje.github.io/C-Turtle/docs/md__home_jesse_Development_Work_C-Turtle-Doxy_setup.html)

C-Turtle is a port of Python's Turtle facility for C++11, with the intent of being a close analog to the Python implementation. This package was developed with the intent of student usage under an academic setting, and was designed to be "as easy to use as possible"™. This package has been released under the MIT license accordingly.
Given that this is intended to be an education-oriented package, there is a comprehensive and guided setup process available [here](https://walkerje.github.io/C-Turtle/docs/md__home_jesse_Development_Work_C-Turtle-Doxy_setup.html) to ease the process. CMake 3.1 is or greater is required for the setup process.

This package heavily uses [CImg](http://cimg.eu/) for its display and drawing functions.

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
          scr.bgcolor({"white"});
          ct::Turtle rt(scr);
          rt.speed(ct::TS_SLOWEST);
          rt.fillcolor({"purple"});
          rt.begin_fill();
          for (int i = 0; i < 4; i++) {
              rt.forward(50);
              rt.right(90);
          }
          rt.end_fill();
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

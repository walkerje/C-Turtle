<p align="center">
  <img width="460" height="300" src="https://publicdomainvectors.org/photos/Tortoise-.png">
  <br>
</p>

# C-Turtle
#### [Documentation](https://walkerje.github.io/C-Turtle/docs/index.html)

C-Turtle is a port of Python's Turtle facility for C++11, with the intent of being a close analog to the Python implementation. This package was developed with the intent of student usage under an academic setting, and was designed to be "as easy to use as possible"™. This package has been released under the MIT license accordingly.
Given that this is intended to be an education-oriented package, to ease the setup process it has been created to be Header-Only. Simply copy the files into your include path and you're ready to go.

This library requires the definition of CTURTLE_IMPLEMENTATION in only one implementation file (.cpp) prior to the inclusion of "CTurtle.hpp" to be used correctly. This idea was derived from Sean T. Barrett's header-only libraries (https://github.com/nothings) which I've used extensively in the past. This methodology allows for a single implementation, rather than the bulk of the implementation be copied around for every individual source file.

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
    
      #define CTURTLE_IMPLEMENTATION
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

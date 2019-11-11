<p align="center">
  <img width="460" height="300" src="https://publicdomainvectors.org/photos/Tortoise-.png">
  <br>
</p>

# C-Turtle
#### [Documentation](https://walkerje.github.io/C-Turtle/docs/index.html)

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
          scr.bgcolor({"white"});
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

## Student Work Showcase
As time progresses, and as I am afforded the opportunity, I will provide visual examples of work students have done using this library. None of these are produced by my own work (but did use C-Turtle in their generation), however permission was given to post the works here!

An example of artwork generated in the style of Piet Mondrian as part of an assignment on Recursion:
![Mondrian Art Example](https://i.imgur.com/PoMCwXn.png)

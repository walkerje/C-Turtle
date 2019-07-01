<p align="center">
  <img width="460" height="300" src="https://publicdomainvectors.org/photos/Tortoise-.png">
</p>

# C-Turtle - Documentation [Here!](https://walkerje.github.io/C-Turtle/docs/index.html)

## What is it?
A port of Python's Turtle facility for C++, with the intent of being a 1:1 to the Python API. 

## Examples and Comparison of APIs
The following is an example of how to use this library. Included below it is the Python equivalent of the C++ example.
### C++
```cpp
#include "CTurtle.hpp"

namespace ct = cturtle;

int main(int argc, char** argv) {
    ct::TurtleScreen scr;
    scr.bgcolor({"white});
    ct::Turtle rt(scr);
    rt.speed(ct::TS_SLOWEST);    
    rt.fillcolor({"purple});

    rt.begin_fill();
    for(int i = 0; i < 4; i++){
        rt.forward(50);
        rt.right(90);
    }
    rt.end_fill();
    
    scr.exitonclick();
    return 0;
}
```
### Python
```python
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
```

## Author Information
Currently under development by Jesse W. Walker, a student at Berea College, as part of his 2019 summer internship under Runestone Interactive.

## License
MIT

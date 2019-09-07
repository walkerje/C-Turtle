/* 
 * File:   show_two_turtle.cpp
 * Author: Jesse W. Walker
 */

#include "CTurtle.hpp"

namespace ct = cturtle;

class koch{
public:
    koch(ct::Turtle& turtle, int order, int size, int x, int y, ct::Color color)
        : turtleRef(turtle){
        this->order = order;
        this->size = size;
        this->x = x;
        this->y = y;
        this->color = color;
        moveto();
    }
    
    koch(ct::Turtle& turtle) : turtleRef(turtle){
        this->order = 3;
        this->size = 200;
        this->x = -250;
        this->y = 0;
        this->color = {"black"};
        moveto();
    }
    
    void moveto(){
        turtleRef.penup();
        turtleRef.goTo(x, y);
        turtleRef.pendown();
    }
    
    void draw_koch(int newOrder, int newSize){
        const int ANGLES[] = {60, -120, 60, 0};
        
        turtleRef.pencolor(color);
        if(newOrder == 0){
            turtleRef.forward(newSize);
        }else{
            for(int i = 0; i < 4; i++){
                draw_koch(newOrder-1, newSize/3);
                turtleRef.left(ANGLES[i]);
            }
        }
    }
    
    inline void draw_koch(){
        draw_koch(order, size);
    }
    
    void snowflake(){
        for(int i = 0; i < 3; i++){
            draw_koch();
            turtleRef.right(120);
        }
    }
    
private:
    int order;
    int size;
    int x;
    int y;
    
    ct::Color color;
    ct::Turtle& turtleRef;
};

int main(int argc, char** argv) {
    ct::TurtleScreen scr;
    ct::Turtle turtle(scr);
    
    koch k(turtle);
    k.snowflake();
    
    scr.exitonclick();
    return 0;
}

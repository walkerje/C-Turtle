/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:    Geometry.hpp
 * Project: C-Turtle
 * Created on May 20, 2019, 2:33 PM
 */

#pragma once

#include <cstring>//memcpy
#include <vector>//for polygon points

#include "Common.hpp"
#include "Color.hpp"

namespace cturtle{
    typedef ivec2 Point;
    
    /*Converts degrees to radians.*/
    template<typename T>
    inline T toRadians(T val){
        //Magic number here is PI/180
        return T(val * T(0.01745329251));
    }
    
    /*Converts radians to degrees.*/
    template<typename T>
    inline T toDegrees(T val){
        //Magic number here is 180/PI
        return T(val * T(57.2957795131));
    }
    
    /*Performs a linear interpolation.
      Considers first argument as the value,
      with the second two being min and max values.
      Step is considered to be the quantity of "distance"
      the variable is intended to be moved, defined as a percentage
      of the space it has (e.g, difference of min and max).
     
      Step must be in range of 0...1!!*/
    template<typename T>
    inline T lerp(T val, T min, T max, T step){
        const T result = T(val + (step * (max - min)));
        return result > max ? max : result;
    }
    
    class AffineTransform{
    public:
        //0, 0 is x scaling
        //1, 0 is y shearing
        //0, 1 is x shearing
        //1, 1 is y scaling 
        //0, 2 is x translation
        //1, 2 is y translation
        typedef linalg::mat<float, 3, 3> mat_t;
        
        /*The value of this affine transform.*/
        mat_t value;
        
        AffineTransform(){
            identity();
        }
        
        /*Sets this transform to an identity.*/
        void identity(){
            value = mat_t();
            at(0, 0) = at(1, 1) = 1.0f;
        }
        
        Point transform(Point in){
            
        }
        
        inline Point operator()(Point in){
            return transform(in);
        }
        
    protected:
        float& at(int row, int col){
            return value.row(row)[col];
        }
    };
    
    /*An interface virtual class which just defines a common
      drawing function.
     */
    class IDrawableGeometry{
    public:
        IDrawableGeometry(){}
        virtual ~IDrawableGeometry(){}
        
        /*Draws this object to the specified image, using the specified color.*/
        virtual void draw(Image& imgRef, Color c = Color::white) = 0;
    };
    
    class Line : public IDrawableGeometry{
    public:
        Point pointA;
        Point pointB;
        
        Line(){}
        Line(Point a, Point b) : pointA(a), pointB(b){}
        ~Line(){}
        
        /*Draws this line to the specified image with the specified color.*/
        void draw(Image& imgRef, Color c = Color::black) override;
    };
    
    class Circle : public IDrawableGeometry{
    public:
        Point center;
        int radius = 10;
        
        Circle(){}
        Circle(Point center, int radius) : center(center), radius(radius){}
        Circle(const Circle& other) : center(other.center), radius(other.radius){}
        
        /*Draws this circle to the specified image with the specified color.*/
        void draw(Image& imgRef, Color c = Color::black) override;
    };
    
    class Polygon : public IDrawableGeometry{
    public:
        std::vector<Point> points;
        Polygon(){}
        Polygon(const std::initializer_list<Point>& init) :
            points(init){}
        Polygon(const std::vector<Point>& copy){
            points = copy;
        }
        Polygon(const Polygon& other){
            points = other.points;
        }
        ~Polygon(){}
        
        /*Draws this polygon to the specified image with the specified color.*/
        void draw(Image& imgRef, Color c = Color::black) override;
    };
}

#ifdef CTURTLE_IMPLEMENTATION
namespace cturtle{
    void Line::draw(Image& imgRef, Color c){
        imgRef.draw_line((int)pointA.x, (int)pointA.y, (int)pointB.x, (int)pointB.y, c.rgbPtr());
    }

    void Circle::draw(Image& imgRef, Color c) {
        imgRef.draw_circle(center.x, center.y, radius, c.rgbPtr());
    }

    void Polygon::draw(Image& imgRef, Color c) {
        if (points.empty())
            return;
        /*CImg is a pain in the butt and requires all polygons to be
          passed in as an instance of the image object. Therefore,
          we can specify an "int" image with a width of 2 (x,y) and height
          of the total number of elements in the point vector.*/
        cimg::CImg<int> passPts(points.size(), 2);
        int* ptData = &points[0].x;
        
        //we take advantage of vector's contiguous memory here :)
        //this is likely the fastest way to copy the point data.
        for(int i = 0; i < points.size(); i++){
            passPts(i, 0) = ptData[i*2];
            passPts(i, 1) = ptData[(i*2)+1];
        }
        imgRef.draw_polygon(passPts, c.rgbPtr());
    }
}
#endif
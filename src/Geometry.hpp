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
#include <array>//For AffineTransform storage.

//MSVC 2017 doesn't seem to like defining M_PI. We define it ourselves
//when compiling under VisualC++.
#ifndef _MSC_VER
#include <cmath>//for M_PI
#else
#ifndef M_PI
#define M_PI 3.14159265358979323846264338327950288
#endif
#endif

#include "Common.hpp"
#include "Color.hpp"

namespace cturtle {
    class AffineTransform;//Prototype for transform.
    typedef ivec2 Point;

    /*Converts degrees to radians.*/
    template<typename T>
    inline T toRadians(T val) {
        return T(val * (M_PI/180.0));
    }

    /*Converts radians to degrees.*/
    template<typename T>
    inline T toDegrees(T val) {
        return T(val * (180.0/M_PI));
    }

    /*An interface virtual class which just defines a common
      drawing function.
     */
    class IDrawableGeometry {
    public:
        IDrawableGeometry() {
        }

        virtual ~IDrawableGeometry() {
        }

        /*Draws this object to the specified image, using the specified color.*/
        virtual void draw(const AffineTransform& t, Image& imgRef, Color c = Color::white) = 0;
    };

    class Line : public IDrawableGeometry {
    public:
        Point pointA;
        Point pointB;

        Line() {
        }

        Line(Point a, Point b) : pointA(a), pointB(b) {
        }

        ~Line() {
        }

        /*Draws this line to the specified image with the specified color.*/
        void draw(const AffineTransform& t, Image& imgRef, Color c = Color::black) override;
    };

    class Circle : public IDrawableGeometry {
    public:
        int radius = 10;
        int steps = 10;
        
        Circle() {
        }

        Circle(int radius, int steps) : radius(radius), steps(steps){
            
        }

        Circle(const Circle& other) : radius(other.radius), steps(steps){
            
        }

        /*Draws this circle to the specified image with the specified color.*/
        void draw(const AffineTransform& t, Image& imgRef, Color c = Color::black) override;
    };

    class Polygon : public IDrawableGeometry {
    public:
        std::vector<Point> points;

        Polygon() {}

        Polygon(const std::initializer_list<Point>& init) :
            points(init) {
        }

        Polygon(const std::vector<Point>& copy) {
            points = copy;
        }

        Polygon(const Polygon& other) {
            points = other.points;
        }

        ~Polygon() {
        }
        
        void transform(const AffineTransform& t);

        /*Draws this polygon to the specified image with the specified color.*/
        void draw(const AffineTransform& t, Image& imgRef, Color c = Color::black) override;
    };

    class AffineTransform {
    public:
        typedef std::array<float, 9> mat_t;
        
        /*Constructs an empty affine transform.
          Initializes as an identity matrix,
          meaning all transformed points aren't moved. */
        AffineTransform() {
            identity();
        }
        
        AffineTransform(const AffineTransform& other)
            : value(other.value), rotation(other.rotation){}

        /*Sets this transform to an identity.*/
        AffineTransform& identity() {
            value.fill(0.0f);
            at(0, 0) = at(1, 1) = 1.0f;
            rotation = 0;
            return *this;
        }

        float getScaleX() const {
            return constAt(0, 0);
        }

        float getScaleY() const {
            return constAt(1, 1);
        }

        float getShearX() const {
            return constAt(0, 1);
        }

        float getShearY() const {
            return constAt(1, 0);
        }

        float getTranslateX() const {
            return constAt(0, 2);
        }
        
        float getTranslateY() const {
            return constAt(1, 2);
        }
        
        /*Returns the angle of rotation, in radians.*/
        float getRotation(){
            return rotation;
        }
        
        /*Moves this transform "forward" according to its rotation.*/
        AffineTransform& forward(float distance){
            at(0,2) += std::cos(rotation) * distance;//x component
            at(1,2) += std::sin(rotation) * distance;//y component
            return *this;
        }
        
        /*Backwards inline function.
          Just negates the input of a forward function call.*/
        inline AffineTransform& backward(float distance){
            return forward(-distance);
        }
        
        /*Sets the translation of this affine transform.*/
        AffineTransform& setTranslation(int x, int y){
            at(0, 2) = x;
            at(1, 2) = y;
            return *this;
        }
        
        Point getTranslation(){
            return Point((int)at(0,2), (int)at(1, 2));
        }
        
        /*Sets the X translation of this affine transform.*/
        AffineTransform& setTranslationX(int x){
            at(0, 2) = x;
            return *this;
        }
        
        /*Sets the Y translation of this affine transform.*/
        AffineTransform& setTranslationY(int y){
            at(1, 2) = y;
            return *this;
        }

        /*Translates this affine transform.*/
        AffineTransform& translate(int x, int y) {
            at(0, 2) += x * at(0, 0) + y * at(0, 1);
            at(1, 2) += x * at(1, 0) + y * at(1, 1);
            return *this;
        }

        /*Theta is measured in radians.*/
        AffineTransform& rotate(float theta) {
            const float c = std::cos(theta);
            const float s = std::sin(theta);

            const float new00 = at(0, 0) * c + at(0, 1) * s;
            const float new01 = at(0, 0) * -s + at(0, 1) * c;
            const float new10 = at(1, 0) * c + at(1, 1) * s;
            const float new11 = at(1, 0) * -s + at(1, 1) * c;

            at(0, 0) = new00;
            at(0, 1) = new01;
            at(1, 0) = new10;
            at(1, 1) = new11;

            rotation += theta;
            
            return *this;
        }

        /**/
        AffineTransform& rotateAround(int x, int y, float theta) {
            translate(x, y);
            rotate(theta);
            translate(-x, -y);
            return *this;
        }

        AffineTransform& scale(float sx, float sy) {
            at(0, 0) *= sx;
            at(0, 1) *= sy;
            at(1, 0) *= sx;
            at(1, 1) *= sy;
            return *this;
        }

        AffineTransform& shear(float sx, float sy) {
            const float new00 = at(0, 0) + (sy * at(0, 1));
            const float new01 = at(0, 1) + (sx * at(0, 0));
            const float new10 = at(1, 0) + (sy * at(1, 1));
            const float new11 = at(1, 1) + (sx * at(1, 0));

            at(0, 0) = new00;
            at(0, 1) = new01;
            at(1, 0) = new10;
            at(1, 1) = new11;
            return *this;
        }
        
        AffineTransform& concatenate(const AffineTransform& t){
            const float new00 = constAt(0,0) * t.constAt(0,0) + constAt(0,1) * t.constAt(1,0);
            const float new01 = constAt(0,0) * t.constAt(0,1) + constAt(0,1) * t.constAt(1,1);
            const float new02 = constAt(0,0) * t.constAt(0,2) + constAt(0,1) * t.constAt(1,2) + constAt(0,2);
            const float new10 = constAt(1,0) * t.constAt(0,0) + constAt(1,1) * t.constAt(1,0);
            const float new11 = constAt(1,0) * t.constAt(0,1) + constAt(1,1) * t.constAt(1,1);
            const float new12 = constAt(1,0) * t.constAt(0,2) + constAt(1,1) * t.constAt(1,2) + constAt(1,2);
            
            at(0,0) = new00;
            at(0,1) = new01;
            at(0,2) = new02;
            at(1,0) = new10;
            at(1,1) = new11;
            at(1,2) = new12;
            rotation += t.rotation;
            return *this;
        }
        
        /*Creates and returns a concatenated copy of this affine transform.*/
        AffineTransform copyConcatenate(const AffineTransform& t) const{
            AffineTransform copy;
            copy.assign(*this);
            copy.concatenate(t);
            return copy;
        }
        
        /*Returns the determinate of this affine transform.*/
        float getDeterminant() const{
            return constAt(0,0) * constAt(1,1) - constAt(0,1) * constAt(1,0);
        }
        
        /*Inverts this matrix, if possible.*/
        AffineTransform& invert(){
            const float determ = getDeterminant();
            
            if(determ == 0)
                return *this;//Cannot invert.
            
            const float new00 = constAt(1,1) / determ;
            const float new10 = -constAt(1,0) / determ;
            const float new01 = -constAt(0,1) / determ;
            const float new11 = constAt(0,0) / determ;
            const float new02 = (constAt(0,1) * constAt(1,2) - constAt(0,2) * constAt(1,1)) / determ;
            const float new12 = (-constAt(0,0) * constAt(1,2) + constAt(1,0) * constAt(0, 2)) / determ;
            
            at(0,0) = new00;
            at(1,0) = new10;
            at(0,1) = new01;
            at(1,1) = new11;
            at(0,2) = new02;
            at(1,2) = new12;
            
            return *this;
        }
        
        void assign(const AffineTransform& t){
            value = t.value;
            rotation = t.rotation;
        }

        Point transform(Point in, Point* dst = nullptr) const{
            Point temp;
            Point* dstPtr = (dst == nullptr) ? &temp : dst;
            dstPtr->x = (constAt(0, 0) * (in.x) + constAt(0, 1) * (in.y) + constAt(0, 2));
            dstPtr->y = (constAt(1, 0) * (in.x) + constAt(1, 1) * (in.y) + constAt(1, 2));
            return *dstPtr;
        }
        
        /*Transforms the a specified set of points,
          given a starting and ending iterators.
          These iterators CANNOT be constant iterators.*/
        template<typename ITER_T>
        void transformSet(ITER_T cur, ITER_T end){
            while(cur != end){
                transform(&(*cur), &(*cur));
                cur++;
            }
        }

        /*Operator overload to transform a single point, for convenience.*/
        inline Point operator()(Point in) const{
            return transform(in);
        }
    protected:
        /*The value of this affine transform.*/
        mat_t value;
        
        /*The rotation of this transform, in radians.*/
        float rotation = 0;
        
        inline float& at(int row, int col) {
            return value[row*3+col];
        }

        float constAt(int row, int col) const {
            return value[row*3+col];
        }
    };
}

#ifdef CTURTLE_IMPLEMENTATION
namespace cturtle {
    void Line::draw(const AffineTransform& t, Image& imgRef, Color c) {
        const Point a = t(pointA);
        const Point b = t(pointB);
        imgRef.draw_line((int) a.x, (int) a.y, (int) b.x, (int) b.y, c.rgbPtr());
    }

    void Circle::draw(const AffineTransform& t, Image& imgRef, Color c) {
        cimg::CImg<int> passPts(steps, 2);
        
        for(int i = 0; i < steps; i++){
            Point p;
            p.x = radius * std::cos(i * (2*M_PI) / steps);
            p.y = radius * std::sin(i * (2*M_PI) / steps);
            Point tPoint = t(p);
            passPts(i, 0) = tPoint.x;
            passPts(i, 1) = tPoint.y;
        }
        
        imgRef.draw_polygon(passPts, c.rgbPtr());
    }

    void Polygon::transform(const AffineTransform& t) {
        for (Point& p : points) {
            p = t(p);
        }
    }

    void Polygon::draw(const AffineTransform& t, Image& imgRef, Color c) {
        if (points.empty())
            return;
        /*CImg is a pain in the butt and requires all polygons to be
          passed in as an instance of the image object. Therefore,
          we can specify an "int" image with a width of 2 (x,y) and height
          of the total number of elements in the point vector.*/
        cimg::CImg<int> passPts(points.size(), 2);
        
        //we take advantage of vector's contiguous memory here :)
        //this is likely the fastest way to copy the point data.
        for (int i = 0; i < points.size(); i++) {
            const Point pt = t(points[i]);
            passPts(i, 0) = pt.x;
            passPts(i, 1) = pt.y;
        }
        
        imgRef.draw_polygon(passPts, c.rgbPtr());
    }
}
#endif
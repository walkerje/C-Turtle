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
    
    /**\brief An alias for ivec2. Strictly for convenience and clarity.*/
    typedef ivec2 Point;
    
    /**\brief The AffineTransform class provides a myriad of functions to
     *        simply transform points.
     * This class it the backbone of almost all cartesian plane math in CTurtle.
     * An adapted 3x3 matrix of the following link:
     * http://www.opengl-tutorial.org/beginners-tutorials/tutorial-3-matrices/ 
     */
    class AffineTransform {
    public:
        /**Constructs an empty affine transform.
         * Initializes, by default, as an identity transform.*/
        AffineTransform() {
            identity();
        }
        
        /**\brief Copy constructor.
         *\param other The other transform from which to derive value.*/
        AffineTransform(const AffineTransform& other)
            : value(other.value), rotation(other.rotation){}

        /**\brief Sets this transform to an identity.
         * When you concatenate an identity transform onto another object,
         * The resulting point is the same as it would have been pre-concatenation.
         * Such is the point of an identity transform, and is why AffineTransforms
         * are initialized to have this value.
         *\return A reference to this transform. (e.g, *this)*/
        AffineTransform& identity() {
            value.fill(0.0f);
            at(0, 0) = at(1, 1) = 1.0f;
            rotation = 0;
            return *this;
        }

        /**\brief Returns the X scale of this transform.
         *\return Returns the X scale of this transform.*/
        float getScaleX() const {
            return constAt(0, 0);
        }

        /**\brief Returns the Y scale of this transform.
         *\return Returns the Y scale of this transform.*/
        float getScaleY() const {
            return constAt(1, 1);
        }

        /**\brief Returns the X shear of this transform.
         *\return Returns the X shear of this transform.*/
        float getShearX() const {
            return constAt(0, 1);
        }

        
        /**\brief Returns the Y shear of this transform.
         *\return Returns the Y shear of this transform.*/
        float getShearY() const {
            return constAt(1, 0);
        }
        
        /**\brief Returns the X translation of this transform.
         *\return Returns the X translation of this transform.*/
        float getTranslateX() const {
            return constAt(0, 2);
        }
        
        /**\brief Returns the Y translation of this transform.
         *\return Returns the Y translation of this transform.*/
        float getTranslateY() const {
            return constAt(1, 2);
        }
        
        /**\brief Returns rotation of this transform, in radians.
         *\return The rotation of this transform, in radians.*/
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

        /**\brief Sets the translation of this transform.
         *\param x The number of units, or pixels, to transform on the X axis.
         *\param y The number of units, or pixels, to transform on the Y axis.
         *\return A reference to this transform. (e.g, *this)*/
        AffineTransform& setTranslation(int x, int y){
            at(0, 2) = x;
            at(1, 2) = y;
            return *this;
        }
        
        /**\brief Returns the translation of this transform as a point.
         *\return The point which represents the transform.*/
        Point getTranslation(){
            return Point((int)at(0,2), (int)at(1, 2));
        }
        
        /**\brief Sets the X axis translation of this transform.
         *\param x The number of units, or pixels, to transform on the X axis.
         *\return A reference to this transform. (e.g, *this)*/
        AffineTransform& setTranslationX(int x){
            at(0, 2) = x;
            return *this;
        }
        
        /**\brief Set the Y axis translation of this transform.
         *\param y The number of units, or pixels, to transform on the Y axis.
         *\return A reference to this transform. (e.g, *this)*/
        AffineTransform& setTranslationY(int y){
            at(1, 2) = y;
            return *this;
        }

        /**\brief Translates this transform.
         *\param x The number of units, or pixels, to transform on the X axis.
         *\param y The number of units, or pixels, to transform on the Y axis.
         *\return A reference to this transform. (e.g, *this)*/
        AffineTransform& translate(int x, int y) {
            at(0, 2) += x * at(0, 0) + y * at(0, 1);
            at(1, 2) += x * at(1, 0) + y * at(1, 1);
            return *this;
        }


        /**\brief Rotates this transform.
         *\param theta The angle at which to rotate, in radians
         *\return A reference to this transform. (e.g, *this)*/
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

        /**\brief Rotates this transform around a specified point.
         *\param x The X coordinate to rotate around.
         *\param y The Y coordinate to rotate around.
         *\param theta The angle at which to rotate, in radians
         *\return A reference to this transform. (e.g, *this)*/
        AffineTransform& rotateAround(int x, int y, float theta) {
            translate(x, y);
            rotate(theta);
            translate(-x, -y);
            return *this;
        }

        /**\brief Applies a scale transformation to this transform.
         *\param sx The X axis scale factor.
         *\param sy The Y axis scale factor.*/
        AffineTransform& scale(float sx, float sy) {
            at(0, 0) *= sx;
            at(0, 1) *= sy;
            at(1, 0) *= sx;
            at(1, 1) *= sy;
            return *this;
        }

        /**\brief Applies a shear transformation to this transform.
         *\param sx The X axis shear factor.
         *\param sy The Y axis shear factor.
         *\return A reference to this transform. (e.g, *this)*/
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
        
        /**\brief Concatenates this AffineTransform with another.
         *\param t The other AffineTransform to concatenate with.
         *\return A reference to this transform. (e.g, *this)*/
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
        
        /**\brief Creates a copy of this transform, concatenates the input, and returns it.
         *\param t The input to concatenate onto the copy of this transform.
         *\return Returns the concatenated copy of this transform.*/
        AffineTransform copyConcatenate(const AffineTransform& t) const{
            AffineTransform copy;
            copy.assign(*this);
            copy.concatenate(t);
            return copy;
        }
        
        /**\brief Assigns the value of this transform to that of another.
         *\param t The other transform to derive value from.*/
        void assign(const AffineTransform& t){
            value = t.value;
            rotation = t.rotation;
        }

        /**\brief Transforms a point according to this transform.
         *\param in The input point.
         *\param dst The destination pointer to store the value. Can be same as input..
         *\return Returns the translated point.
         *\return Also assigns the value of dst pointer to the result.*/
        Point transform(Point in, Point* dst = nullptr) const{
            Point temp;
            Point* dstPtr = (dst == nullptr) ? &temp : dst;
            dstPtr->x = (constAt(0, 0) * (in.x) + constAt(0, 1) * (in.y) + constAt(0, 2));
            dstPtr->y = (constAt(1, 0) * (in.x) + constAt(1, 1) * (in.y) + constAt(1, 2));
            return *dstPtr;
        }
        
        /**\brief Transforms a set of points given a begin and end iterator.
         *\param cur The beginning iterator of a set.
         *\param end The ending iterator of a set.*/
        template<typename ITER_T>
        void transformSet(ITER_T cur, ITER_T end){
            while(cur != end){
                transform(&(*cur), &(*cur));
                cur++;
            }
        }

        /*Operator overload to transform a single point, for convenience.*/
        /**\brief Operator overload to transform a single point.
         *\param in The point to transform.*/
        inline Point operator()(Point in) const{
            return transform(in);
        }
    protected:
        /**The underlying matrix type.
         * It's defined simply as an array of 9 floats.
         * Retrieved from coordinate pairs using (x*3+y) as indices.*/
        typedef std::array<float, 9> mat_t;
        
        /**The value of this affine transform.*/
        mat_t value;
        
        /**The rotation of this transform, in radians.*/
        float rotation = 0;
        
        /**\brief Returns a reference to the float the specified coordinate.
         *\param row The specified row from which to get a component.
         *\param col The specified column from which to get a component.*/
        inline float& at(int row, int col) {
            return value[row*3+col];
        }

        /**\brief Returns a copy of the float at the specified coordinate.
         *\param row The specified row from which to get a component.
         *\param col The specified column from which to get a component.*/
        float constAt(int row, int col) const {
            return value[row*3+col];
        }
    };

    /**\brief Converts degrees to radians.
     * A generic toRadians function. Performs
     * the following: val*(PI/180.0)
     * \param val The value to convert from degress to radians.
     * \return A value of the same type as val, converted to radians.*/
    template<typename T>
    inline T toRadians(T val) {
        return T(val * (M_PI/180.0));
    }

    /**\brief Converts radians to degrees.
     * A generic toDegrees function. Performs
     * the following: val*(180.0/PI)
     * \param val The value to convert from radians to degrees.
     * \return A value of the same type as val, converted to degrees.*/
    template<typename T>
    inline T toDegrees(T val) {
        return T(val * (180.0/M_PI));
    }

    /**\brief IDrawableGeometry is a base class, intended to be
     *        inherited from by all drawable objects.
     * This class just contains a simple virtual drawing function,
     * intended to be inherited from and to overload the draw function.
     * This allows for the storage of drawable geometry in a generic fashion.*/
    class IDrawableGeometry {
    public:
        /**\brief Empty default constructor.*/
        IDrawableGeometry() {
        }

        /**\brief Empty-- virtual-- default de-constructor.*/
        virtual ~IDrawableGeometry() {
        }

        /**\brief This function is intended to draw all applicable geometry
         *        in this object to the specified image, with the specified transform,
         *        with the specified color.
         * This function is intended to be overloaded by child classes to draw applicable
         * geometry to an image, acting as a canvas.
         * \param t The transform at which to draw the geometry.
         * \param imgRef The canvas on which to draw.
         * \param c The color with to draw the geometry.*/
        virtual void draw(const AffineTransform& t, Image& imgRef, Color c = Color::white) = 0;
    };
    
    /**\brief The Line class holds two points and the functionality to draw a line
     *       between them on a specified canvas.*/
    class Line : public IDrawableGeometry {
    public:
        /**The "From" point.
           Lines drawn with this object start here.*/
        Point pointA;
        /**The "To" point.
           Lines drawn with this object end here.*/
        Point pointB;

        /**\brief Empty default constructor.*/
        Line() {
        }

        /**\brief Value constructor.
         *        merely assigns value of pointA and pointB to respective A and B.
         *\param a The "From" point.
         *\param b The "To" point.*/
        Line(Point a, Point b) : pointA(a), pointB(b) {
        }
        
        /**\brief Copy constructor.
         *        Merely assigns the "to" and "from" points.
         *\param other The other instance of a line from which to derive value.*/
        Line(const Line& other) : pointA(other.pointA), pointB(other.pointB){}

        /**\brief Empty de-constructor.*/
        ~Line() {
        }
        
        
        void draw(const AffineTransform& t, Image& imgRef, Color c = Color::black) override;
    };

    /**\brief The Circle class holds a radius and total number of steps, used
     *        to generate and draw a circles geometry.*/
    class Circle : public IDrawableGeometry {
    public:
        /**Radius, in pixels, of the geometry generated in the draw function.*/
        int radius = 10;
        /**Total number of steps, or vertices, generated in the draw function.
         * The higher this number is, the more "high-quality" it can be considered.*/
        int steps = 10;
        
        /**\brief Empty constructor.*/
        Circle() {
        }

        /**\brief Radius and step assignment constructor.
         *\param radius The radius, in pixels, of this circle.
         *\param steps The number of vertices used by this circle.*/
        Circle(int radius, int steps) : radius(radius), steps(steps){}

        /**\brief Copy constructor.
         *\param other Another instance of a circle from which to derive value.*/
        Circle(const Circle& other) : radius(other.radius), steps(steps){}
        
        void draw(const AffineTransform& t, Image& imgRef, Color c = Color::black) override;
    };

    /**\brief The polygon class merely holds a vector of points and a function
     *        to draw this series to an image.
     * Please note that the contained series of points must be in either
     * clockwise(CW) or counterclockwise(CCW) order!*/
    class Polygon : public IDrawableGeometry {
    public:
        /**The vector of points, drawn by this geometry's draw function.*/
        std::vector<Point> points;

        /**\brief Empty default constructor.*/
        Polygon() {}

        /**\brief   Initializer list instructor which assigns the points
         *          to the contents of the specified initializer list.
         *\param The initializer list from where points are retrieved.*/
        Polygon(const std::initializer_list<Point>& init) :
            points(init) {
        }

        /**\brief A copy constructor for another vector of points.
         *\param copy A vector from which to derive points.*/
        Polygon(const std::vector<Point>& copy) {
            points = copy;
        }

        /**\brief A copy constructor for another polygon.
         *\param other Another polygon from which to derive points.*/
        Polygon(const Polygon& other) {
            points = other.points;
        }

        /**\brief Empty de-constructor.*/
        ~Polygon() {}
        
        /**\brief   Transforms all points in this polygon according to the 
         *          specified transform.
         *\param t The specified transform.*/
        void transform(const AffineTransform& t);

        void draw(const AffineTransform& t, Image& imgRef, Color c = Color::black) override;
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
        
        for (int i = 0; i < points.size(); i++) {
            const Point pt = t(points[i]);
            passPts(i, 0) = pt.x;
            passPts(i, 1) = pt.y;
        }
        
        imgRef.draw_polygon(passPts, c.rgbPtr());
    }
}
#endif
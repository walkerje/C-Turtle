//MIT License
//
//Copyright (c) 2019 Jesse W. Walker
//
//Permission is hereby granted, free of charge, to any person obtaining a copy
//of this software and associated documentation files (the "Software"), to deal
//in the Software without restriction, including without limitation the rights
//to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
//copies of the Software, and to permit persons to whom the Software is
//furnished to do so, subject to the following conditions:
//
//The above copyright notice and this permission notice shall be included in all
//copies or substantial portions of the Software.
//
//THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
//IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
//FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
//AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
//LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
//OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
//SOFTWARE.
        
/* 
 * File:    Geometry.hpp
 * Project: C-Turtle
 * Created on May 20, 2019, 2:33 PM
 */

#pragma once

#include <tuple>
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
    
    /**\brief Draws a line of variable thickness on the specified image.
     * This needed to be implemented because the CImg display backend
     * has no facility to draw lines with a width greater than a single pixel!
     *\param imgRef The image on which to draw the line.
     *\param The X component of the first coordinate.
     *\param The Y component of the first coordinate.
     *\param the X component of the second coordinate.
     *\param the Y component of the second coordinate.
     *\param c The color with which to draw the line.
     *\param width The width of the line.*/
    void drawLine(Image& imgRef, int x1, int y1, int x2, int y2, Color c, unsigned int width = 1);
    
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
        
        /**Moves this transform "forward" according to its rotation.*/
        AffineTransform& forward(float distance){
            at(0,2) += int(std::cos(rotation) * distance);//x component
            at(1,2) += int(std::sin(rotation) * distance);//y component
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
        Point getTranslation() const{
            return Point((int)constAt(0,2), (int)constAt(1, 2));
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
            //6.28319 is a full circle in radians.
            if(rotation + theta > 6.28319){//Loop back around. Avoid overflow.
                theta = (rotation + theta) - 6.28319;
                setRotation(0);
            }
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
        
        /**\brief Sets the rotation of this transform.
         *\param val The angle at which to rotate, in radians.
         *\return A reference to this transform. (e.g, *this)*/
        AffineTransform& setRotation(float val){
            if(rotation != 0.0f)
                rotate(-rotation);
            rotate(val);
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
        
        /**\brief Interpolates between this and the specified transform.
         *        Progress is a float in range of 0 to 1.
         *\param t The destination transform.
         *\param progress A progress float in range of 0 to 1.
         *\return The resulting interpolated transform.*/
        AffineTransform lerp(const AffineTransform& t, float progress) const{
            if(progress <= 0)
                return *this;
            else if(progress >= 1)
                return t;
            AffineTransform result;
            for(int i = 0; i < 9; i++){
                result.value[i] = (progress * (t.value[i] - value[i])) + value[i];
            }
            return result;
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
            //Rounding seems to fix off-by-one issues in regards to rotation.
            dstPtr->x = std::round(constAt(0, 0) * (in.x) + constAt(0, 1) * (in.y) + constAt(0, 2));
            dstPtr->y = std::round(constAt(1, 0) * (in.x) + constAt(1, 1) * (in.y) + constAt(1, 2));
            return *dstPtr;
        }
        
        /**\brief Transforms a set of points given a begin and end iterator.
         *\param cur The beginning iterator of a set.
         *\param end The ending iterator of a set.*/
        template<typename ITER_T>
        void transformSet(ITER_T cur, ITER_T end) const{
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
        
        int width = 1;

        /**\brief Empty default constructor.*/
        Line() {
        }

        /**\brief Value constructor.
         *        merely assigns value of pointA and pointB to respective A and B.
         *\param a The "From" point.
         *\param b The "To" point.*/
        Line(Point a, Point b, int width = 1) : pointA(a), pointB(b), width(width){
        }
        
        /**\brief Copy constructor.
         *        Merely assigns the "to" and "from" points.
         *\param other The other instance of a line from which to derive value.*/
        Line(const Line& other) : pointA(other.pointA), pointB(other.pointB), width(other.width){}

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
        
        /**\brief   Draws the outline of this polygon using a series of lines.
         *\param t The affine transform to draw the outline at.
         *\param imgRef The canvas to draw on.
         *\param c The color to draw the outline in.*/
        void drawOutline(const AffineTransform& t, Image& imgRef, Color c = Color::black);
    };
        
    class Sprite : public IDrawableGeometry{
    public:
        int srcX, srcY, srcW, srcH;
        
        int drawWidth = 0;
        int drawHeight = 0;
        
        Sprite(Image& img) : spriteImg(img){
            srcX = srcY = 0;
            srcW = img.width();
            srcH = img.height();
        }
        
        Sprite(Image& img, int srcX, int srcY, int srcW, int srcH) : spriteImg(img){
            this->srcX = srcX;
            this->srcY = srcY;
            this->srcW = srcW;
            this->srcH = srcH;
        }
        
        Sprite(const Sprite& copy) : spriteImg(copy.spriteImg){
            this->srcX = copy.srcX;
            this->srcY = copy.srcY;
            this->srcW = copy.srcW;
            this->srcH = copy.srcH;
            this->drawWidth = copy.drawWidth;
            this->drawHeight = copy.drawHeight;
        }
        
        ~Sprite(){}
        
        /**Draws this Sprite.
         * Disregards the Color attribute in favor of sprites' colors.*/
        void draw(const AffineTransform& t, Image& imgRef, Color c = Color::black) override;
    protected:
        Image& spriteImg;
    };
    
    class CompoundPolygon : public IDrawableGeometry{
        typedef std::unique_ptr<IDrawableGeometry> unique_geom_t; 
    public:
        CompoundPolygon(){}
        
        //Polygon, Fill, Outline
        typedef std::tuple<std::unique_ptr<IDrawableGeometry>, Color, bool, Color> component_t;

        template<typename T>
        void addcomponent(const T& t, Color fill, Color outline){
            components.push_back(std::make_tuple(unique_geom_t(new T(t)), fill, true, outline));
        }
        
        template<typename T>
        void addcomponent(const T& t, Color fill){
            components.push_back(std::make_tuple(unique_geom_t(new T(t)), fill, false, Color()));
        }
        
        void addpoly(const Polygon& p, Color fill){
            addcomponent(p, fill);
        }
        
        void addpoly(const Polygon& p, Color fill, Color outline){
            addcomponent(p, fill, outline);
        }
        
        /**Draws this CompoundPolygon.
         * Disregards the Color attribute in favor of the components' colors*/
        void draw(const AffineTransform& t, Image& imgRef, Color c = Color::black) override;
    protected:
        std::list<component_t> components;
    };
}

#ifdef CTURTLE_IMPLEMENTATION
namespace cturtle {
    void drawLine(Image& imgRef, int x1, int y1, int x2, int y2, Color c, unsigned int width){
        if (x1 == x2 && y1 == y2) {
            return;
        }else if(width == 1){
            imgRef.draw_line(x1,y1,x2,y2,c.rgbPtr());
            return;
        }
        const double xoffs = std::abs(x1 - x2);
        const double yoffs = std::abs(y1 - y2);
        const double woffs = width / 2.0;
        const int xadjacent = yoffs * woffs / std::sqrt(std::pow(xoffs, 2) + std::pow(yoffs, 2));
        const int yadjacent = xoffs * woffs / std::sqrt(std::pow(xoffs, 2) + std::pow(yoffs, 2));

        //Clockwise
        cimg_library::CImg<int> points(4, 2);
        points(0, 0) = x1 - xadjacent;
        points(0, 1) = y1 + yadjacent;
        points(1, 0) = x1 + xadjacent;
        points(1, 1) = y1 - yadjacent;
        points(2, 0) = x2 + xadjacent;
        points(2, 1) = y2 - yadjacent;
        points(3, 0) = x2 - xadjacent;
        points(3, 1) = y2 + yadjacent;
        imgRef.draw_polygon(points, c.rgbPtr());
    }
    
    void Line::draw(const AffineTransform& t, Image& imgRef, Color c) {
        const Point a = t(pointA);
        const Point b = t(pointB);
        if(a.x == b.x && a.y == b.y)
            return;//no point in drawing a line between like points
        drawLine(imgRef, a.x, a.y, b.x, b.y, c, width);
    }

    void Circle::draw(const AffineTransform& t, Image& imgRef, Color c) {
        cimg::CImg<int> passPts(steps, 2);
        
        for(int i = 0; i < steps; i++){
            Point p;
            p.x = int(radius * std::cos(i * (2*M_PI) / steps));
            p.y = int(radius * std::sin(i * (2*M_PI) / steps));
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
    
    void Polygon::drawOutline(const AffineTransform& t, Image& imgRef, Color c){
        if(points.size() < 2)
            return;
        
        typedef decltype(points.begin()) iter_t;
        
        iter_t cur = points.begin()++;
        iter_t last = points.begin();
        
        while(cur != points.end()){
            Point a = t(*cur);
            Point b = t(*last);
            imgRef.draw_line(a.x, a.y, b.x, b.y, c.rgbPtr());
            last = cur;
            cur++;
        }
        
        /*Draw a line between the first and last points.*/
        Point a = t(points.front());
        Point b = t(points.back());
        imgRef.draw_line(a.x, a.y, b.x, b.y, c.rgbPtr());
    }
    
    void Sprite::draw(const AffineTransform& t, Image& imgRef, Color c){
        //Vertex order is as follows for the constructed quad.
        // 0--3        3
        // | /        /|
        // |/        / |
        // 1        1--2
        
        const int halfW = drawWidth / 2;
        const int halfH = drawHeight / 2;
        
        Point destPoints[4] = {
            {-halfW, halfH},   //0
            {-halfW, -halfH},    //1
            {halfW, -halfH},     //2
            {halfW, halfH}     //3
        };
        
        Point texturePoints[4] = {
            {srcX, srcY},
            {srcX, srcY+srcH},
            {srcX+srcW, srcY},
            {srcX+srcW, srcY+srcH}
        };
        
        /**Transforms the set of points.*/
        for(int i = 0; i < 4; i++){
            destPoints[i] = t(destPoints[i]);
        }
        
        imgRef.draw_triangle(destPoints[0][0], destPoints[0][1], destPoints[1][0], destPoints[1][1], destPoints[3][0], destPoints[3][1],
                  spriteImg, texturePoints[0][0], texturePoints[0][1], texturePoints[1][0], texturePoints[1][1], texturePoints[3][0], texturePoints[3][1]);
        imgRef.draw_triangle(destPoints[1][0], destPoints[1][1], destPoints[2][0], destPoints[2][1], destPoints[3][0], destPoints[3][1],
                  spriteImg, texturePoints[1][0], texturePoints[1][1], texturePoints[2][0], texturePoints[2][1], texturePoints[3][0], texturePoints[3][1]);
    }
    
    void CompoundPolygon::draw(const AffineTransform& t, Image& imgRef, Color c){
        for(component_t& comp : components){
            IDrawableGeometry* p = std::get<0>(comp).get();
            Color fill = std::get<1>(comp);
            bool doOutline = std::get<2>(comp);
            Color outline = std::get<3>(comp);
            
            p->draw(t, imgRef, fill);
            //TODO: Fix Outlines for Generic drawables
//            if(doOutline)
//                p->drawOutline(t, imgRef, outline);
        }
    }
}
#endif
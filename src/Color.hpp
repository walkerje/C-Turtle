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
 * File:    Color.hpp
 * Project: C-Turtle
 * Created on May 20, 2019, 1:46 PM
 */

#pragma once
#include <random>

namespace cturtle{
    /** \brief Color: Unsigned 8-bit RGB Color Implementation
     *         Just contains R, G and B elements.  
     * Color
     *      Defines an interface for RGB Colors.
     *      Also provides a way to retrieve color by name strings in the form
     *      of a static function. Color documentation from the specified link:
     *      https://www.tcl.tk/man/tcl8.4/TkCmd/colors.htm
     */
    struct Color{
        static const Color alice_blue;
        static const Color AliceBlue;
        static const Color antique_white;
        static const Color AntiqueWhite;
        static const Color AntiqueWhite1;
        static const Color AntiqueWhite2;
        static const Color AntiqueWhite3;
        static const Color AntiqueWhite4;
        static const Color aquamarine;
        static const Color aquamarine1;
        static const Color aquamarine2;
        static const Color aquamarine3;
        static const Color aquamarine4;
        static const Color azure;
        static const Color azure1;
        static const Color azure2;
        static const Color azure3;
        static const Color azure4;
        static const Color beige;
        static const Color bisque;
        static const Color bisque1;
        static const Color bisque2;
        static const Color bisque3;
        static const Color bisque4;
        static const Color black;
        static const Color blanched_almond;
        static const Color BlanchedAlmond;
        static const Color blue;
        static const Color blue_violet;
        static const Color blue1;
        static const Color blue2;
        static const Color blue3;
        static const Color blue4;
        static const Color BlueViolet;
        static const Color brown;
        static const Color brown1;
        static const Color brown2;
        static const Color brown3;
        static const Color brown4;
        static const Color burlywood;
        static const Color burlywood1;
        static const Color burlywood2;
        static const Color burlywood3;
        static const Color burlywood4;
        static const Color cadet_blue;
        static const Color CadetBlue;
        static const Color CadetBlue1;
        static const Color CadetBlue2;
        static const Color CadetBlue3;
        static const Color CadetBlue4;
        static const Color chartreuse;
        static const Color chartreuse1;
        static const Color chartreuse2;
        static const Color chartreuse3;
        static const Color chartreuse4;
        static const Color chocolate;
        static const Color chocolate1;
        static const Color chocolate2;
        static const Color chocolate3;
        static const Color chocolate4;
        static const Color coral;
        static const Color coral1;
        static const Color coral2;
        static const Color coral3;
        static const Color coral4;
        static const Color cornflower_blue;
        static const Color CornflowerBlue;
        static const Color cornsilk;
        static const Color cornsilk1;
        static const Color cornsilk2;
        static const Color cornsilk3;
        static const Color cornsilk4;
        static const Color cyan;
        static const Color cyan1;
        static const Color cyan2;
        static const Color cyan3;
        static const Color cyan4;
        static const Color dark_blue;
        static const Color dark_cyan;
        static const Color dark_goldenrod;
        static const Color dark_gray;
        static const Color dark_green;
        static const Color dark_grey;
        static const Color dark_khaki;
        static const Color dark_magenta;
        static const Color dark_olive_green;
        static const Color dark_orange;
        static const Color dark_orchid;
        static const Color dark_red;
        static const Color dark_salmon;
        static const Color dark_sea_green;
        static const Color dark_slate_blue;
        static const Color dark_slate_gray;
        static const Color dark_slate_grey;
        static const Color dark_turquoise;
        static const Color dark_violet;
        static const Color DarkBlue;
        static const Color DarkCyan;
        static const Color DarkGoldenrod;
        static const Color DarkGoldenrod1;
        static const Color DarkGoldenrod2;
        static const Color DarkGoldenrod3;
        static const Color DarkGoldenrod4;
        static const Color DarkGray;
        static const Color DarkGreen;
        static const Color DarkGrey;
        static const Color DarkKhaki;
        static const Color DarkMagenta;
        static const Color DarkOliveGreen;
        static const Color DarkOliveGreen1;
        static const Color DarkOliveGreen2;
        static const Color DarkOliveGreen3;
        static const Color DarkOliveGreen4;
        static const Color DarkOrange;
        static const Color DarkOrange1;
        static const Color DarkOrange2;
        static const Color DarkOrange3;
        static const Color DarkOrange4;
        static const Color DarkOrchid;
        static const Color DarkOrchid1;
        static const Color DarkOrchid2;
        static const Color DarkOrchid3;
        static const Color DarkOrchid4;
        static const Color DarkRed;
        static const Color DarkSalmon;
        static const Color DarkSeaGreen;
        static const Color DarkSeaGreen1;
        static const Color DarkSeaGreen2;
        static const Color DarkSeaGreen3;
        static const Color DarkSeaGreen4;
        static const Color DarkSlateBlue;
        static const Color DarkSlateGray;
        static const Color DarkSlateGray1;
        static const Color DarkSlateGray2;
        static const Color DarkSlateGray3;
        static const Color DarkSlateGray4;
        static const Color DarkSlateGrey;
        static const Color DarkTurquoise;
        static const Color DarkViolet;
        static const Color deep_pink;
        static const Color deep_sky_blue;
        static const Color DeepPink;
        static const Color DeepPink1;
        static const Color DeepPink2;
        static const Color DeepPink3;
        static const Color DeepPink4;
        static const Color DeepSkyBlue;
        static const Color DeepSkyBlue1;
        static const Color DeepSkyBlue2;
        static const Color DeepSkyBlue3;
        static const Color DeepSkyBlue4;
        static const Color dim_gray;
        static const Color dim_grey;
        static const Color DimGray;
        static const Color DimGrey;
        static const Color dodger_blue;
        static const Color DodgerBlue;
        static const Color DodgerBlue1;
        static const Color DodgerBlue2;
        static const Color DodgerBlue3;
        static const Color DodgerBlue4;
        static const Color firebrick;
        static const Color firebrick1;
        static const Color firebrick2;
        static const Color firebrick3;
        static const Color firebrick4;
        static const Color floral_white;
        static const Color FloralWhite;
        static const Color forest_green;
        static const Color ForestGreen;
        static const Color gainsboro;
        static const Color ghost_white;
        static const Color GhostWhite;
        static const Color gold;
        static const Color gold1;
        static const Color gold2;
        static const Color gold3;
        static const Color gold4;
        static const Color goldenrod;
        static const Color goldenrod1;
        static const Color goldenrod2;
        static const Color goldenrod3;
        static const Color goldenrod4;
        static const Color gray;
        static const Color gray0;
        static const Color gray1;
        static const Color gray2;
        static const Color gray3;
        static const Color gray4;
        static const Color gray5;
        static const Color gray6;
        static const Color gray7;
        static const Color gray8;
        static const Color gray9;
        static const Color gray10;
        static const Color gray11;
        static const Color gray12;
        static const Color gray13;
        static const Color gray14;
        static const Color gray15;
        static const Color gray16;
        static const Color gray17;
        static const Color gray18;
        static const Color gray19;
        static const Color gray20;
        static const Color gray21;
        static const Color gray22;
        static const Color gray23;
        static const Color gray24;
        static const Color gray25;
        static const Color gray26;
        static const Color gray27;
        static const Color gray28;
        static const Color gray29;
        static const Color gray30;
        static const Color gray31;
        static const Color gray32;
        static const Color gray33;
        static const Color gray34;
        static const Color gray35;
        static const Color gray36;
        static const Color gray37;
        static const Color gray38;
        static const Color gray39;
        static const Color gray40;
        static const Color gray41;
        static const Color gray42;
        static const Color gray43;
        static const Color gray44;
        static const Color gray45;
        static const Color gray46;
        static const Color gray47;
        static const Color gray48;
        static const Color gray49;
        static const Color gray50;
        static const Color gray51;
        static const Color gray52;
        static const Color gray53;
        static const Color gray54;
        static const Color gray55;
        static const Color gray56;
        static const Color gray57;
        static const Color gray58;
        static const Color gray59;
        static const Color gray60;
        static const Color gray61;
        static const Color gray62;
        static const Color gray63;
        static const Color gray64;
        static const Color gray65;
        static const Color gray66;
        static const Color gray67;
        static const Color gray68;
        static const Color gray69;
        static const Color gray70;
        static const Color gray71;
        static const Color gray72;
        static const Color gray73;
        static const Color gray74;
        static const Color gray75;
        static const Color gray76;
        static const Color gray77;
        static const Color gray78;
        static const Color gray79;
        static const Color gray80;
        static const Color gray81;
        static const Color gray82;
        static const Color gray83;
        static const Color gray84;
        static const Color gray85;
        static const Color gray86;
        static const Color gray87;
        static const Color gray88;
        static const Color gray89;
        static const Color gray90;
        static const Color gray91;
        static const Color gray92;
        static const Color gray93;
        static const Color gray94;
        static const Color gray95;
        static const Color gray96;
        static const Color gray97;
        static const Color gray98;
        static const Color gray99;
        static const Color gray100;
        static const Color green;
        static const Color green_yellow;
        static const Color green1;
        static const Color green2;
        static const Color green3;
        static const Color green4;
        static const Color GreenYellow;
        static const Color grey;
        static const Color grey0;
        static const Color grey1;
        static const Color grey2;
        static const Color grey3;
        static const Color grey4;
        static const Color grey5;
        static const Color grey6;
        static const Color grey7;
        static const Color grey8;
        static const Color grey9;
        static const Color grey10;
        static const Color grey11;
        static const Color grey12;
        static const Color grey13;
        static const Color grey14;
        static const Color grey15;
        static const Color grey16;
        static const Color grey17;
        static const Color grey18;
        static const Color grey19;
        static const Color grey20;
        static const Color grey21;
        static const Color grey22;
        static const Color grey23;
        static const Color grey24;
        static const Color grey25;
        static const Color grey26;
        static const Color grey27;
        static const Color grey28;
        static const Color grey29;
        static const Color grey30;
        static const Color grey31;
        static const Color grey32;
        static const Color grey33;
        static const Color grey34;
        static const Color grey35;
        static const Color grey36;
        static const Color grey37;
        static const Color grey38;
        static const Color grey39;
        static const Color grey40;
        static const Color grey41;
        static const Color grey42;
        static const Color grey43;
        static const Color grey44;
        static const Color grey45;
        static const Color grey46;
        static const Color grey47;
        static const Color grey48;
        static const Color grey49;
        static const Color grey50;
        static const Color grey51;
        static const Color grey52;
        static const Color grey53;
        static const Color grey54;
        static const Color grey55;
        static const Color grey56;
        static const Color grey57;
        static const Color grey58;
        static const Color grey59;
        static const Color grey60;
        static const Color grey61;
        static const Color grey62;
        static const Color grey63;
        static const Color grey64;
        static const Color grey65;
        static const Color grey66;
        static const Color grey67;
        static const Color grey68;
        static const Color grey69;
        static const Color grey70;
        static const Color grey71;
        static const Color grey72;
        static const Color grey73;
        static const Color grey74;
        static const Color grey75;
        static const Color grey76;
        static const Color grey77;
        static const Color grey78;
        static const Color grey79;
        static const Color grey80;
        static const Color grey81;
        static const Color grey82;
        static const Color grey83;
        static const Color grey84;
        static const Color grey85;
        static const Color grey86;
        static const Color grey87;
        static const Color grey88;
        static const Color grey89;
        static const Color grey90;
        static const Color grey91;
        static const Color grey92;
        static const Color grey93;
        static const Color grey94;
        static const Color grey95;
        static const Color grey96;
        static const Color grey97;
        static const Color grey98;
        static const Color grey99;
        static const Color grey100;
        static const Color honeydew;
        static const Color honeydew1;
        static const Color honeydew2;
        static const Color honeydew3;
        static const Color honeydew4;
        static const Color hot_pink;
        static const Color HotPink;
        static const Color HotPink1;
        static const Color HotPink2;
        static const Color HotPink3;
        static const Color HotPink4;
        static const Color indian_red;
        static const Color IndianRed;
        static const Color IndianRed1;
        static const Color IndianRed2;
        static const Color IndianRed3;
        static const Color IndianRed4;
        static const Color ivory;
        static const Color ivory1;
        static const Color ivory2;
        static const Color ivory3;
        static const Color ivory4;
        static const Color khaki;
        static const Color khaki1;
        static const Color khaki2;
        static const Color khaki3;
        static const Color khaki4;
        static const Color lavender;
        static const Color lavender_blush;
        static const Color LavenderBlush;
        static const Color LavenderBlush1;
        static const Color LavenderBlush2;
        static const Color LavenderBlush3;
        static const Color LavenderBlush4;
        static const Color lawn_green;
        static const Color LawnGreen;
        static const Color lemon_chiffon;
        static const Color LemonChiffon;
        static const Color LemonChiffon1;
        static const Color LemonChiffon2;
        static const Color LemonChiffon3;
        static const Color LemonChiffon4;
        static const Color light_blue;
        static const Color light_coral;
        static const Color light_cyan;
        static const Color light_goldenrod;
        static const Color light_goldenrod_yellow;
        static const Color light_gray;
        static const Color light_green;
        static const Color light_grey;
        static const Color light_pink;
        static const Color light_salmon;
        static const Color light_sea_green;
        static const Color light_sky_blue;
        static const Color light_slate_blue;
        static const Color light_slate_gray;
        static const Color light_slate_grey;
        static const Color light_steel_blue;
        static const Color light_yellow;
        static const Color LightBlue;
        static const Color LightBlue1;
        static const Color LightBlue2;
        static const Color LightBlue3;
        static const Color LightBlue4;
        static const Color LightCoral;
        static const Color LightCyan;
        static const Color LightCyan1;
        static const Color LightCyan2;
        static const Color LightCyan3;
        static const Color LightCyan4;
        static const Color LightGoldenrod;
        static const Color LightGoldenrod1;
        static const Color LightGoldenrod2;
        static const Color LightGoldenrod3;
        static const Color LightGoldenrod4;
        static const Color LightGoldenrodYellow;
        static const Color LightGray;
        static const Color LightGreen;
        static const Color LightGrey;
        static const Color LightPink;
        static const Color LightPink1;
        static const Color LightPink2;
        static const Color LightPink3;
        static const Color LightPink4;
        static const Color LightSalmon;
        static const Color LightSalmon1;
        static const Color LightSalmon2;
        static const Color LightSalmon3;
        static const Color LightSalmon4;
        static const Color LightSeaGreen;
        static const Color LightSkyBlue;
        static const Color LightSkyBlue1;
        static const Color LightSkyBlue2;
        static const Color LightSkyBlue3;
        static const Color LightSkyBlue4;
        static const Color LightSlateBlue;
        static const Color LightSlateGray;
        static const Color LightSlateGrey;
        static const Color LightSteelBlue;
        static const Color LightSteelBlue1;
        static const Color LightSteelBlue2;
        static const Color LightSteelBlue3;
        static const Color LightSteelBlue4;
        static const Color LightYellow;
        static const Color LightYellow1;
        static const Color LightYellow2;
        static const Color LightYellow3;
        static const Color LightYellow4;
        static const Color lime_green;
        static const Color LimeGreen;
        static const Color linen;
        static const Color magenta;
        static const Color magenta1;
        static const Color magenta2;
        static const Color magenta3;
        static const Color magenta4;
        static const Color maroon;
        static const Color maroon1;
        static const Color maroon2;
        static const Color maroon3;
        static const Color maroon4;
        static const Color medium_aquamarine;
        static const Color medium_blue;
        static const Color medium_orchid;
        static const Color medium_purple;
        static const Color medium_sea_green;
        static const Color medium_slate_blue;
        static const Color medium_spring_green;
        static const Color medium_turquoise;
        static const Color medium_violet_red;
        static const Color MediumAquamarine;
        static const Color MediumBlue;
        static const Color MediumOrchid;
        static const Color MediumOrchid1;
        static const Color MediumOrchid2;
        static const Color MediumOrchid3;
        static const Color MediumOrchid4;
        static const Color MediumPurple;
        static const Color MediumPurple1;
        static const Color MediumPurple2;
        static const Color MediumPurple3;
        static const Color MediumPurple4;
        static const Color MediumSeaGreen;
        static const Color MediumSlateBlue;
        static const Color MediumSpringGreen;
        static const Color MediumTurquoise;
        static const Color MediumVioletRed;
        static const Color midnight_blue;
        static const Color MidnightBlue;
        static const Color mint_cream;
        static const Color MintCream;
        static const Color misty_rose;
        static const Color MistyRose;
        static const Color MistyRose1;
        static const Color MistyRose2;
        static const Color MistyRose3;
        static const Color MistyRose4;
        static const Color moccasin;
        static const Color navajo_white;
        static const Color NavajoWhite;
        static const Color NavajoWhite1;
        static const Color NavajoWhite2;
        static const Color NavajoWhite3;
        static const Color NavajoWhite4;
        static const Color navy;
        static const Color navy_blue;
        static const Color NavyBlue;
        static const Color old_lace;
        static const Color OldLace;
        static const Color olive_drab;
        static const Color OliveDrab;
        static const Color OliveDrab1;
        static const Color OliveDrab2;
        static const Color OliveDrab3;
        static const Color OliveDrab4;
        static const Color orange;
        static const Color orange_red;
        static const Color orange1;
        static const Color orange2;
        static const Color orange3;
        static const Color orange4;
        static const Color OrangeRed;
        static const Color OrangeRed1;
        static const Color OrangeRed2;
        static const Color OrangeRed3;
        static const Color OrangeRed4;
        static const Color orchid;
        static const Color orchid1;
        static const Color orchid2;
        static const Color orchid3;
        static const Color orchid4;
        static const Color pale_goldenrod;
        static const Color pale_green;
        static const Color pale_turquoise;
        static const Color pale_violet_red;
        static const Color PaleGoldenrod;
        static const Color PaleGreen;
        static const Color PaleGreen1;
        static const Color PaleGreen2;
        static const Color PaleGreen3;
        static const Color PaleGreen4;
        static const Color PaleTurquoise;
        static const Color PaleTurquoise1;
        static const Color PaleTurquoise2;
        static const Color PaleTurquoise3;
        static const Color PaleTurquoise4;
        static const Color PaleVioletRed;
        static const Color PaleVioletRed1;
        static const Color PaleVioletRed2;
        static const Color PaleVioletRed3;
        static const Color PaleVioletRed4;
        static const Color papaya_whip;
        static const Color PapayaWhip;
        static const Color peach_puff;
        static const Color PeachPuff;
        static const Color PeachPuff1;
        static const Color PeachPuff2;
        static const Color PeachPuff3;
        static const Color PeachPuff4;
        static const Color peru;
        static const Color pink;
        static const Color pink1;
        static const Color pink2;
        static const Color pink3;
        static const Color pink4;
        static const Color plum;
        static const Color plum1;
        static const Color plum2;
        static const Color plum3;
        static const Color plum4;
        static const Color powder_blue;
        static const Color PowderBlue;
        static const Color purple;
        static const Color purple1;
        static const Color purple2;
        static const Color purple3;
        static const Color purple4;
        static const Color red;
        static const Color red1;
        static const Color red2;
        static const Color red3;
        static const Color red4;
        static const Color rosy_brown;
        static const Color RosyBrown;
        static const Color RosyBrown1;
        static const Color RosyBrown2;
        static const Color RosyBrown3;
        static const Color RosyBrown4;
        static const Color royal_blue;
        static const Color RoyalBlue;
        static const Color RoyalBlue1;
        static const Color RoyalBlue2;
        static const Color RoyalBlue3;
        static const Color RoyalBlue4;
        static const Color saddle_brown;
        static const Color SaddleBrown;
        static const Color salmon;
        static const Color salmon1;
        static const Color salmon2;
        static const Color salmon3;
        static const Color salmon4;
        static const Color sandy_brown;
        static const Color SandyBrown;
        static const Color sea_green;
        static const Color SeaGreen;
        static const Color SeaGreen1;
        static const Color SeaGreen2;
        static const Color SeaGreen3;
        static const Color SeaGreen4;
        static const Color seashell;
        static const Color seashell1;
        static const Color seashell2;
        static const Color seashell3;
        static const Color seashell4;
        static const Color sienna;
        static const Color sienna1;
        static const Color sienna2;
        static const Color sienna3;
        static const Color sienna4;
        static const Color sky_blue;
        static const Color SkyBlue;
        static const Color SkyBlue1;
        static const Color SkyBlue2;
        static const Color SkyBlue3;
        static const Color SkyBlue4;
        static const Color slate_blue;
        static const Color slate_gray;
        static const Color slate_grey;
        static const Color SlateBlue;
        static const Color SlateBlue1;
        static const Color SlateBlue2;
        static const Color SlateBlue3;
        static const Color SlateBlue4;
        static const Color SlateGray;
        static const Color SlateGray1;
        static const Color SlateGray2;
        static const Color SlateGray3;
        static const Color SlateGray4;
        static const Color SlateGrey;
        static const Color snow;
        static const Color snow1;
        static const Color snow2;
        static const Color snow3;
        static const Color snow4;
        static const Color spring_green;
        static const Color SpringGreen;
        static const Color SpringGreen1;
        static const Color SpringGreen2;
        static const Color SpringGreen3;
        static const Color SpringGreen4;
        static const Color steel_blue;
        static const Color SteelBlue;
        static const Color SteelBlue1;
        static const Color SteelBlue2;
        static const Color SteelBlue3;
        static const Color SteelBlue4;
        static const Color tan;
        static const Color tan1;
        static const Color tan2;
        static const Color tan3;
        static const Color tan4;
        static const Color thistle;
        static const Color thistle1;
        static const Color thistle2;
        static const Color thistle3;
        static const Color thistle4;
        static const Color tomato;
        static const Color tomato1;
        static const Color tomato2;
        static const Color tomato3;
        static const Color tomato4;
        static const Color turquoise;
        static const Color turquoise1;
        static const Color turquoise2;
        static const Color turquoise3;
        static const Color turquoise4;
        static const Color violet;
        static const Color violet_red;
        static const Color VioletRed;
        static const Color VioletRed1;
        static const Color VioletRed2;
        static const Color VioletRed3;
        static const Color VioletRed4;
        static const Color wheat;
        static const Color wheat1;
        static const Color wheat2;
        static const Color wheat3;
        static const Color wheat4;
        static const Color white;
        static const Color white_smoke;
        static const Color WhiteSmoke;
        static const Color yellow;
        static const Color yellow_green;
        static const Color yellow1;
        static const Color yellow2;
        static const Color yellow3;
        static const Color yellow4;
        static const Color YellowGreen;
        
        typedef uint8_t component_t;

        component_t r;
        component_t g;
        component_t b;
        
        /*\brief Color constructor for unsigned 8-bit RGB values.
          \param r Red component.
          \param g Green component. 
          \param b Blue component.*/
        Color(component_t r, component_t g, component_t b) :
            r(r), g(g), b(b){};
        
        /*\brief Copy constructor.
          \param other Constant reference to other instance of a color object.*/
        Color(const Color& other) : 
            r(other.r), g(other.g), b(other.b){}
        
        /*\brief Name constructor.
                 Takes a literal color name as an input.
          \param name The name of the color from which to derive value.
          \sa fromName()*/
        Color(const std::string& name) : Color(fromName(name)){}
        
        /*\brief Default constructor.
                 Initializes this color to white. (all components 255)*/
        Color(){r = g = b = 255;}
        
        /*\brief Returns a pointer to the first component of this color.
                 This is useful for functions which require color as an input array.
          Returns a read-only pointer to the elements, in sequential order.*/
        const component_t* const rgbPtr() const{
            return &r;
        }
        
        /*TODO: Document Me*/
        static Color fromName(const std::string& name);
    };
    
    /**Returns a randomly generated color.*/
    Color randomColor();
}
    
#ifdef CTURTLE_IMPLEMENTATION
#include <map>

#include "Common.hpp"
namespace cturtle{
    const Color Color::alice_blue(240,248,255);
    const Color Color::AliceBlue(240,248,255);
    const Color Color::antique_white(250,235,215);
    const Color Color::AntiqueWhite(250,235,215);
    const Color Color::AntiqueWhite1(255,239,219);
    const Color Color::AntiqueWhite2(238,223,204);
    const Color Color::AntiqueWhite3(205,192,176);
    const Color Color::AntiqueWhite4(139,131,120);
    const Color Color::aquamarine(127,255,212);
    const Color Color::aquamarine1(127,255,212);
    const Color Color::aquamarine2(118,238,198);
    const Color Color::aquamarine3(102,205,170);
    const Color Color::aquamarine4(69,139,116);
    const Color Color::azure(240,255,255);
    const Color Color::azure1(240,255,255);
    const Color Color::azure2(224,238,238);
    const Color Color::azure3(193,205,205);
    const Color Color::azure4(131,139,139);
    const Color Color::beige(245,245,220);
    const Color Color::bisque(255,228,196);
    const Color Color::bisque1(255,228,196);
    const Color Color::bisque2(238,213,183);
    const Color Color::bisque3(205,183,158);
    const Color Color::bisque4(139,125,107);
    const Color Color::black(0,0,0);
    const Color Color::blanched_almond(255,235,205);
    const Color Color::BlanchedAlmond(255,235,205);
    const Color Color::blue(0,0,255);
    const Color Color::blue_violet(138,43,226);
    const Color Color::blue1(0,0,255);
    const Color Color::blue2(0,0,238);
    const Color Color::blue3(0,0,205);
    const Color Color::blue4(0,0,139);
    const Color Color::BlueViolet(138,43,226);
    const Color Color::brown(165,42,42);
    const Color Color::brown1(255,64,64);
    const Color Color::brown2(238,59,59);
    const Color Color::brown3(205,51,51);
    const Color Color::brown4(139,35,35);
    const Color Color::burlywood(222,184,135);
    const Color Color::burlywood1(255,211,155);
    const Color Color::burlywood2(238,197,145);
    const Color Color::burlywood3(205,170,125);
    const Color Color::burlywood4(139,115,85);
    const Color Color::cadet_blue(95,158,160);
    const Color Color::CadetBlue(95,158,160);
    const Color Color::CadetBlue1(152,245,255);
    const Color Color::CadetBlue2(142,229,238);
    const Color Color::CadetBlue3(122,197,205);
    const Color Color::CadetBlue4(83,134,139);
    const Color Color::chartreuse(127,255,0);
    const Color Color::chartreuse1(127,255,0);
    const Color Color::chartreuse2(118,238,0);
    const Color Color::chartreuse3(102,205,0);
    const Color Color::chartreuse4(69,139,0);
    const Color Color::chocolate(210,105,30);
    const Color Color::chocolate1(255,127,36);
    const Color Color::chocolate2(238,118,33);
    const Color Color::chocolate3(205,102,29);
    const Color Color::chocolate4(139,69,19);
    const Color Color::coral(255,127,80);
    const Color Color::coral1(255,114,86);
    const Color Color::coral2(238,106,80);
    const Color Color::coral3(205,91,69);
    const Color Color::coral4(139,62,47);
    const Color Color::cornflower_blue(100,149,237);
    const Color Color::CornflowerBlue(100,149,237);
    const Color Color::cornsilk(255,248,220);
    const Color Color::cornsilk1(255,248,220);
    const Color Color::cornsilk2(238,232,205);
    const Color Color::cornsilk3(205,200,177);
    const Color Color::cornsilk4(139,136,120);
    const Color Color::cyan(0,255,255);
    const Color Color::cyan1(0,255,255);
    const Color Color::cyan2(0,238,238);
    const Color Color::cyan3(0,205,205);
    const Color Color::cyan4(0,139,139);
    const Color Color::dark_blue(0,0,139);
    const Color Color::dark_cyan(0,139,139);
    const Color Color::dark_goldenrod(184,134,11);
    const Color Color::dark_gray(169,169,169);
    const Color Color::dark_green(0,100,0);
    const Color Color::dark_grey(169,169,169);
    const Color Color::dark_khaki(189,183,107);
    const Color Color::dark_magenta(139,0,139);
    const Color Color::dark_olive_green(85,107,47);
    const Color Color::dark_orange(255,140,0);
    const Color Color::dark_orchid(153,50,204);
    const Color Color::dark_red(139,0,0);
    const Color Color::dark_salmon(233,150,122);
    const Color Color::dark_sea_green(143,188,143);
    const Color Color::dark_slate_blue(72,61,139);
    const Color Color::dark_slate_gray(47,79,79);
    const Color Color::dark_slate_grey(47,79,79);
    const Color Color::dark_turquoise(0,206,209);
    const Color Color::dark_violet(148,0,211);
    const Color Color::DarkBlue(0,0,139);
    const Color Color::DarkCyan(0,139,139);
    const Color Color::DarkGoldenrod(184,134,11);
    const Color Color::DarkGoldenrod1(255,185,15);
    const Color Color::DarkGoldenrod2(238,173,14);
    const Color Color::DarkGoldenrod3(205,149,12);
    const Color Color::DarkGoldenrod4(139,101,8);
    const Color Color::DarkGray(169,169,169);
    const Color Color::DarkGreen(0,100,0);
    const Color Color::DarkGrey(169,169,169);
    const Color Color::DarkKhaki(189,183,107);
    const Color Color::DarkMagenta(139,0,139);
    const Color Color::DarkOliveGreen(85,107,47);
    const Color Color::DarkOliveGreen1(202,255,112);
    const Color Color::DarkOliveGreen2(188,238,104);
    const Color Color::DarkOliveGreen3(162,205,90);
    const Color Color::DarkOliveGreen4(110,139,61);
    const Color Color::DarkOrange(255,140,0);
    const Color Color::DarkOrange1(255,127,0);
    const Color Color::DarkOrange2(238,118,0);
    const Color Color::DarkOrange3(205,102,0);
    const Color Color::DarkOrange4(139,69,0);
    const Color Color::DarkOrchid(153,50,204);
    const Color Color::DarkOrchid1(191,62,255);
    const Color Color::DarkOrchid2(178,58,238);
    const Color Color::DarkOrchid3(154,50,205);
    const Color Color::DarkOrchid4(104,34,139);
    const Color Color::DarkRed(139,0,0);
    const Color Color::DarkSalmon(233,150,122);
    const Color Color::DarkSeaGreen(143,188,143);
    const Color Color::DarkSeaGreen1(193,255,193);
    const Color Color::DarkSeaGreen2(180,238,180);
    const Color Color::DarkSeaGreen3(155,205,155);
    const Color Color::DarkSeaGreen4(105,139,105);
    const Color Color::DarkSlateBlue(72,61,139);
    const Color Color::DarkSlateGray(47,79,79);
    const Color Color::DarkSlateGray1(151,255,255);
    const Color Color::DarkSlateGray2(141,238,238);
    const Color Color::DarkSlateGray3(121,205,205);
    const Color Color::DarkSlateGray4(82,139,139);
    const Color Color::DarkSlateGrey(47,79,79);
    const Color Color::DarkTurquoise(0,206,209);
    const Color Color::DarkViolet(148,0,211);
    const Color Color::deep_pink(255,20,147);
    const Color Color::deep_sky_blue(0,191,255);
    const Color Color::DeepPink(255,20,147);
    const Color Color::DeepPink1(255,20,147);
    const Color Color::DeepPink2(238,18,137);
    const Color Color::DeepPink3(205,16,118);
    const Color Color::DeepPink4(139,10,80);
    const Color Color::DeepSkyBlue(0,191,255);
    const Color Color::DeepSkyBlue1(0,191,255);
    const Color Color::DeepSkyBlue2(0,178,238);
    const Color Color::DeepSkyBlue3(0,154,205);
    const Color Color::DeepSkyBlue4(0,104,139);
    const Color Color::dim_gray(105,105,105);
    const Color Color::dim_grey(105,105,105);
    const Color Color::DimGray(105,105,105);
    const Color Color::DimGrey(105,105,105);
    const Color Color::dodger_blue(30,144,255);
    const Color Color::DodgerBlue(30,144,255);
    const Color Color::DodgerBlue1(30,144,255);
    const Color Color::DodgerBlue2(28,134,238);
    const Color Color::DodgerBlue3(24,116,205);
    const Color Color::DodgerBlue4(16,78,139);
    const Color Color::firebrick(178,34,34);
    const Color Color::firebrick1(255,48,48);
    const Color Color::firebrick2(238,44,44);
    const Color Color::firebrick3(205,38,38);
    const Color Color::firebrick4(139,26,26);
    const Color Color::floral_white(255,250,240);
    const Color Color::FloralWhite(255,250,240);
    const Color Color::forest_green(34,139,34);
    const Color Color::ForestGreen(34,139,34);
    const Color Color::gainsboro(220,220,220);
    const Color Color::ghost_white(248,248,255);
    const Color Color::GhostWhite(248,248,255);
    const Color Color::gold(255,215,0);
    const Color Color::gold1(255,215,0);
    const Color Color::gold2(238,201,0);
    const Color Color::gold3(205,173,0);
    const Color Color::gold4(139,117,0);
    const Color Color::goldenrod(218,165,32);
    const Color Color::goldenrod1(255,193,37);
    const Color Color::goldenrod2(238,180,34);
    const Color Color::goldenrod3(205,155,29);
    const Color Color::goldenrod4(139,105,20);
    const Color Color::gray(190,190,190);
    const Color Color::gray0(0,0,0);
    const Color Color::gray1(3,3,3);
    const Color Color::gray2(5,5,5);
    const Color Color::gray3(8,8,8);
    const Color Color::gray4(10,10,10);
    const Color Color::gray5(13,13,13);
    const Color Color::gray6(15,15,15);
    const Color Color::gray7(18,18,18);
    const Color Color::gray8(20,20,20);
    const Color Color::gray9(23,23,23);
    const Color Color::gray10(26,26,26);
    const Color Color::gray11(28,28,28);
    const Color Color::gray12(31,31,31);
    const Color Color::gray13(33,33,33);
    const Color Color::gray14(36,36,36);
    const Color Color::gray15(38,38,38);
    const Color Color::gray16(41,41,41);
    const Color Color::gray17(43,43,43);
    const Color Color::gray18(46,46,46);
    const Color Color::gray19(48,48,48);
    const Color Color::gray20(51,51,51);
    const Color Color::gray21(54,54,54);
    const Color Color::gray22(56,56,56);
    const Color Color::gray23(59,59,59);
    const Color Color::gray24(61,61,61);
    const Color Color::gray25(64,64,64);
    const Color Color::gray26(66,66,66);
    const Color Color::gray27(69,69,69);
    const Color Color::gray28(71,71,71);
    const Color Color::gray29(74,74,74);
    const Color Color::gray30(77,77,77);
    const Color Color::gray31(79,79,79);
    const Color Color::gray32(82,82,82);
    const Color Color::gray33(84,84,84);
    const Color Color::gray34(87,87,87);
    const Color Color::gray35(89,89,89);
    const Color Color::gray36(92,92,92);
    const Color Color::gray37(94,94,94);
    const Color Color::gray38(97,97,97);
    const Color Color::gray39(99,99,99);
    const Color Color::gray40(102,102,102);
    const Color Color::gray41(105,105,105);
    const Color Color::gray42(107,107,107);
    const Color Color::gray43(110,110,110);
    const Color Color::gray44(112,112,112);
    const Color Color::gray45(115,115,115);
    const Color Color::gray46(117,117,117);
    const Color Color::gray47(120,120,120);
    const Color Color::gray48(122,122,122);
    const Color Color::gray49(125,125,125);
    const Color Color::gray50(127,127,127);
    const Color Color::gray51(130,130,130);
    const Color Color::gray52(133,133,133);
    const Color Color::gray53(135,135,135);
    const Color Color::gray54(138,138,138);
    const Color Color::gray55(140,140,140);
    const Color Color::gray56(143,143,143);
    const Color Color::gray57(145,145,145);
    const Color Color::gray58(148,148,148);
    const Color Color::gray59(150,150,150);
    const Color Color::gray60(153,153,153);
    const Color Color::gray61(156,156,156);
    const Color Color::gray62(158,158,158);
    const Color Color::gray63(161,161,161);
    const Color Color::gray64(163,163,163);
    const Color Color::gray65(166,166,166);
    const Color Color::gray66(168,168,168);
    const Color Color::gray67(171,171,171);
    const Color Color::gray68(173,173,173);
    const Color Color::gray69(176,176,176);
    const Color Color::gray70(179,179,179);
    const Color Color::gray71(181,181,181);
    const Color Color::gray72(184,184,184);
    const Color Color::gray73(186,186,186);
    const Color Color::gray74(189,189,189);
    const Color Color::gray75(191,191,191);
    const Color Color::gray76(194,194,194);
    const Color Color::gray77(196,196,196);
    const Color Color::gray78(199,199,199);
    const Color Color::gray79(201,201,201);
    const Color Color::gray80(204,204,204);
    const Color Color::gray81(207,207,207);
    const Color Color::gray82(209,209,209);
    const Color Color::gray83(212,212,212);
    const Color Color::gray84(214,214,214);
    const Color Color::gray85(217,217,217);
    const Color Color::gray86(219,219,219);
    const Color Color::gray87(222,222,222);
    const Color Color::gray88(224,224,224);
    const Color Color::gray89(227,227,227);
    const Color Color::gray90(229,229,229);
    const Color Color::gray91(232,232,232);
    const Color Color::gray92(235,235,235);
    const Color Color::gray93(237,237,237);
    const Color Color::gray94(240,240,240);
    const Color Color::gray95(242,242,242);
    const Color Color::gray96(245,245,245);
    const Color Color::gray97(247,247,247);
    const Color Color::gray98(250,250,250);
    const Color Color::gray99(252,252,252);
    const Color Color::gray100(255,255,255);
    const Color Color::green(0,255,0);
    const Color Color::green_yellow(173,255,47);
    const Color Color::green1(0,255,0);
    const Color Color::green2(0,238,0);
    const Color Color::green3(0,205,0);
    const Color Color::green4(0,139,0);
    const Color Color::GreenYellow(173,255,47);
    const Color Color::grey(190,190,190);
    const Color Color::grey0(0,0,0);
    const Color Color::grey1(3,3,3);
    const Color Color::grey2(5,5,5);
    const Color Color::grey3(8,8,8);
    const Color Color::grey4(10,10,10);
    const Color Color::grey5(13,13,13);
    const Color Color::grey6(15,15,15);
    const Color Color::grey7(18,18,18);
    const Color Color::grey8(20,20,20);
    const Color Color::grey9(23,23,23);
    const Color Color::grey10(26,26,26);
    const Color Color::grey11(28,28,28);
    const Color Color::grey12(31,31,31);
    const Color Color::grey13(33,33,33);
    const Color Color::grey14(36,36,36);
    const Color Color::grey15(38,38,38);
    const Color Color::grey16(41,41,41);
    const Color Color::grey17(43,43,43);
    const Color Color::grey18(46,46,46);
    const Color Color::grey19(48,48,48);
    const Color Color::grey20(51,51,51);
    const Color Color::grey21(54,54,54);
    const Color Color::grey22(56,56,56);
    const Color Color::grey23(59,59,59);
    const Color Color::grey24(61,61,61);
    const Color Color::grey25(64,64,64);
    const Color Color::grey26(66,66,66);
    const Color Color::grey27(69,69,69);
    const Color Color::grey28(71,71,71);
    const Color Color::grey29(74,74,74);
    const Color Color::grey30(77,77,77);
    const Color Color::grey31(79,79,79);
    const Color Color::grey32(82,82,82);
    const Color Color::grey33(84,84,84);
    const Color Color::grey34(87,87,87);
    const Color Color::grey35(89,89,89);
    const Color Color::grey36(92,92,92);
    const Color Color::grey37(94,94,94);
    const Color Color::grey38(97,97,97);
    const Color Color::grey39(99,99,99);
    const Color Color::grey40(102,102,102);
    const Color Color::grey41(105,105,105);
    const Color Color::grey42(107,107,107);
    const Color Color::grey43(110,110,110);
    const Color Color::grey44(112,112,112);
    const Color Color::grey45(115,115,115);
    const Color Color::grey46(117,117,117);
    const Color Color::grey47(120,120,120);
    const Color Color::grey48(122,122,122);
    const Color Color::grey49(125,125,125);
    const Color Color::grey50(127,127,127);
    const Color Color::grey51(130,130,130);
    const Color Color::grey52(133,133,133);
    const Color Color::grey53(135,135,135);
    const Color Color::grey54(138,138,138);
    const Color Color::grey55(140,140,140);
    const Color Color::grey56(143,143,143);
    const Color Color::grey57(145,145,145);
    const Color Color::grey58(148,148,148);
    const Color Color::grey59(150,150,150);
    const Color Color::grey60(153,153,153);
    const Color Color::grey61(156,156,156);
    const Color Color::grey62(158,158,158);
    const Color Color::grey63(161,161,161);
    const Color Color::grey64(163,163,163);
    const Color Color::grey65(166,166,166);
    const Color Color::grey66(168,168,168);
    const Color Color::grey67(171,171,171);
    const Color Color::grey68(173,173,173);
    const Color Color::grey69(176,176,176);
    const Color Color::grey70(179,179,179);
    const Color Color::grey71(181,181,181);
    const Color Color::grey72(184,184,184);
    const Color Color::grey73(186,186,186);
    const Color Color::grey74(189,189,189);
    const Color Color::grey75(191,191,191);
    const Color Color::grey76(194,194,194);
    const Color Color::grey77(196,196,196);
    const Color Color::grey78(199,199,199);
    const Color Color::grey79(201,201,201);
    const Color Color::grey80(204,204,204);
    const Color Color::grey81(207,207,207);
    const Color Color::grey82(209,209,209);
    const Color Color::grey83(212,212,212);
    const Color Color::grey84(214,214,214);
    const Color Color::grey85(217,217,217);
    const Color Color::grey86(219,219,219);
    const Color Color::grey87(222,222,222);
    const Color Color::grey88(224,224,224);
    const Color Color::grey89(227,227,227);
    const Color Color::grey90(229,229,229);
    const Color Color::grey91(232,232,232);
    const Color Color::grey92(235,235,235);
    const Color Color::grey93(237,237,237);
    const Color Color::grey94(240,240,240);
    const Color Color::grey95(242,242,242);
    const Color Color::grey96(245,245,245);
    const Color Color::grey97(247,247,247);
    const Color Color::grey98(250,250,250);
    const Color Color::grey99(252,252,252);
    const Color Color::grey100(255,255,255);
    const Color Color::honeydew(240,255,240);
    const Color Color::honeydew1(240,255,240);
    const Color Color::honeydew2(224,238,224);
    const Color Color::honeydew3(193,205,193);
    const Color Color::honeydew4(131,139,131);
    const Color Color::hot_pink(255,105,180);
    const Color Color::HotPink(255,105,180);
    const Color Color::HotPink1(255,110,180);
    const Color Color::HotPink2(238,106,167);
    const Color Color::HotPink3(205,96,144);
    const Color Color::HotPink4(139,58,98);
    const Color Color::indian_red(205,92,92);
    const Color Color::IndianRed(205,92,92);
    const Color Color::IndianRed1(255,106,106);
    const Color Color::IndianRed2(238,99,99);
    const Color Color::IndianRed3(205,85,85);
    const Color Color::IndianRed4(139,58,58);
    const Color Color::ivory(255,255,240);
    const Color Color::ivory1(255,255,240);
    const Color Color::ivory2(238,238,224);
    const Color Color::ivory3(205,205,193);
    const Color Color::ivory4(139,139,131);
    const Color Color::khaki(240,230,140);
    const Color Color::khaki1(255,246,143);
    const Color Color::khaki2(238,230,133);
    const Color Color::khaki3(205,198,115);
    const Color Color::khaki4(139,134,78);
    const Color Color::lavender(230,230,250);
    const Color Color::lavender_blush(255,240,245);
    const Color Color::LavenderBlush(255,240,245);
    const Color Color::LavenderBlush1(255,240,245);
    const Color Color::LavenderBlush2(238,224,229);
    const Color Color::LavenderBlush3(205,193,197);
    const Color Color::LavenderBlush4(139,131,134);
    const Color Color::lawn_green(124,252,0);
    const Color Color::LawnGreen(124,252,0);
    const Color Color::lemon_chiffon(255,250,205);
    const Color Color::LemonChiffon(255,250,205);
    const Color Color::LemonChiffon1(255,250,205);
    const Color Color::LemonChiffon2(238,233,191);
    const Color Color::LemonChiffon3(205,201,165);
    const Color Color::LemonChiffon4(139,137,112);
    const Color Color::light_blue(173,216,230);
    const Color Color::light_coral(240,128,128);
    const Color Color::light_cyan(224,255,255);
    const Color Color::light_goldenrod(238,221,130);
    const Color Color::light_goldenrod_yellow(250,250,210);
    const Color Color::light_gray(211,211,211);
    const Color Color::light_green(144,238,144);
    const Color Color::light_grey(211,211,211);
    const Color Color::light_pink(255,182,193);
    const Color Color::light_salmon(255,160,122);
    const Color Color::light_sea_green(32,178,170);
    const Color Color::light_sky_blue(135,206,250);
    const Color Color::light_slate_blue(132,112,255);
    const Color Color::light_slate_gray(119,136,153);
    const Color Color::light_slate_grey(119,136,153);
    const Color Color::light_steel_blue(176,196,222);
    const Color Color::light_yellow(255,255,224);
    const Color Color::LightBlue(173,216,230);
    const Color Color::LightBlue1(191,239,255);
    const Color Color::LightBlue2(178,223,238);
    const Color Color::LightBlue3(154,192,205);
    const Color Color::LightBlue4(104,131,139);
    const Color Color::LightCoral(240,128,128);
    const Color Color::LightCyan(224,255,255);
    const Color Color::LightCyan1(224,255,255);
    const Color Color::LightCyan2(209,238,238);
    const Color Color::LightCyan3(180,205,205);
    const Color Color::LightCyan4(122,139,139);
    const Color Color::LightGoldenrod(238,221,130);
    const Color Color::LightGoldenrod1(255,236,139);
    const Color Color::LightGoldenrod2(238,220,130);
    const Color Color::LightGoldenrod3(205,190,112);
    const Color Color::LightGoldenrod4(139,129,76);
    const Color Color::LightGoldenrodYellow(250,250,210);
    const Color Color::LightGray(211,211,211);
    const Color Color::LightGreen(144,238,144);
    const Color Color::LightGrey(211,211,211);
    const Color Color::LightPink(255,182,193);
    const Color Color::LightPink1(255,174,185);
    const Color Color::LightPink2(238,162,173);
    const Color Color::LightPink3(205,140,149);
    const Color Color::LightPink4(139,95,101);
    const Color Color::LightSalmon(255,160,122);
    const Color Color::LightSalmon1(255,160,122);
    const Color Color::LightSalmon2(238,149,114);
    const Color Color::LightSalmon3(205,129,98);
    const Color Color::LightSalmon4(139,87,66);
    const Color Color::LightSeaGreen(32,178,170);
    const Color Color::LightSkyBlue(135,206,250);
    const Color Color::LightSkyBlue1(176,226,255);
    const Color Color::LightSkyBlue2(164,211,238);
    const Color Color::LightSkyBlue3(141,182,205);
    const Color Color::LightSkyBlue4(96,123,139);
    const Color Color::LightSlateBlue(132,112,255);
    const Color Color::LightSlateGray(119,136,153);
    const Color Color::LightSlateGrey(119,136,153);
    const Color Color::LightSteelBlue(176,196,222);
    const Color Color::LightSteelBlue1(202,225,255);
    const Color Color::LightSteelBlue2(188,210,238);
    const Color Color::LightSteelBlue3(162,181,205);
    const Color Color::LightSteelBlue4(110,123,139);
    const Color Color::LightYellow(255,255,224);
    const Color Color::LightYellow1(255,255,224);
    const Color Color::LightYellow2(238,238,209);
    const Color Color::LightYellow3(205,205,180);
    const Color Color::LightYellow4(139,139,122);
    const Color Color::lime_green(50,205,50);
    const Color Color::LimeGreen(50,205,50);
    const Color Color::linen(250,240,230);
    const Color Color::magenta(255,0,255);
    const Color Color::magenta1(255,0,255);
    const Color Color::magenta2(238,0,238);
    const Color Color::magenta3(205,0,205);
    const Color Color::magenta4(139,0,139);
    const Color Color::maroon(176,48,96);
    const Color Color::maroon1(255,52,179);
    const Color Color::maroon2(238,48,167);
    const Color Color::maroon3(205,41,144);
    const Color Color::maroon4(139,28,98);
    const Color Color::medium_aquamarine(102,205,170);
    const Color Color::medium_blue(0,0,205);
    const Color Color::medium_orchid(186,85,211);
    const Color Color::medium_purple(147,112,219);
    const Color Color::medium_sea_green(60,179,113);
    const Color Color::medium_slate_blue(123,104,238);
    const Color Color::medium_spring_green(0,250,154);
    const Color Color::medium_turquoise(72,209,204);
    const Color Color::medium_violet_red(199,21,133);
    const Color Color::MediumAquamarine(102,205,170);
    const Color Color::MediumBlue(0,0,205);
    const Color Color::MediumOrchid(186,85,211);
    const Color Color::MediumOrchid1(224,102,255);
    const Color Color::MediumOrchid2(209,95,238);
    const Color Color::MediumOrchid3(180,82,205);
    const Color Color::MediumOrchid4(122,55,139);
    const Color Color::MediumPurple(147,112,219);
    const Color Color::MediumPurple1(171,130,255);
    const Color Color::MediumPurple2(159,121,238);
    const Color Color::MediumPurple3(137,104,205);
    const Color Color::MediumPurple4(93,71,139);
    const Color Color::MediumSeaGreen(60,179,113);
    const Color Color::MediumSlateBlue(123,104,238);
    const Color Color::MediumSpringGreen(0,250,154);
    const Color Color::MediumTurquoise(72,209,204);
    const Color Color::MediumVioletRed(199,21,133);
    const Color Color::midnight_blue(25,25,112);
    const Color Color::MidnightBlue(25,25,112);
    const Color Color::mint_cream(245,255,250);
    const Color Color::MintCream(245,255,250);
    const Color Color::misty_rose(255,228,225);
    const Color Color::MistyRose(255,228,225);
    const Color Color::MistyRose1(255,228,225);
    const Color Color::MistyRose2(238,213,210);
    const Color Color::MistyRose3(205,183,181);
    const Color Color::MistyRose4(139,125,123);
    const Color Color::moccasin(255,228,181);
    const Color Color::navajo_white(255,222,173);
    const Color Color::NavajoWhite(255,222,173);
    const Color Color::NavajoWhite1(255,222,173);
    const Color Color::NavajoWhite2(238,207,161);
    const Color Color::NavajoWhite3(205,179,139);
    const Color Color::NavajoWhite4(139,121,94);
    const Color Color::navy(0,0,128);
    const Color Color::navy_blue(0,0,128);
    const Color Color::NavyBlue(0,0,128);
    const Color Color::old_lace(253,245,230);
    const Color Color::OldLace(253,245,230);
    const Color Color::olive_drab(107,142,35);
    const Color Color::OliveDrab(107,142,35);
    const Color Color::OliveDrab1(192,255,62);
    const Color Color::OliveDrab2(179,238,58);
    const Color Color::OliveDrab3(154,205,50);
    const Color Color::OliveDrab4(105,139,34);
    const Color Color::orange(255,165,0);
    const Color Color::orange_red(255,69,0);
    const Color Color::orange1(255,165,0);
    const Color Color::orange2(238,154,0);
    const Color Color::orange3(205,133,0);
    const Color Color::orange4(139,90,0);
    const Color Color::OrangeRed(255,69,0);
    const Color Color::OrangeRed1(255,69,0);
    const Color Color::OrangeRed2(238,64,0);
    const Color Color::OrangeRed3(205,55,0);
    const Color Color::OrangeRed4(139,37,0);
    const Color Color::orchid(218,112,214);
    const Color Color::orchid1(255,131,250);
    const Color Color::orchid2(238,122,233);
    const Color Color::orchid3(205,105,201);
    const Color Color::orchid4(139,71,137);
    const Color Color::pale_goldenrod(238,232,170);
    const Color Color::pale_green(152,251,152);
    const Color Color::pale_turquoise(175,238,238);
    const Color Color::pale_violet_red(219,112,147);
    const Color Color::PaleGoldenrod(238,232,170);
    const Color Color::PaleGreen(152,251,152);
    const Color Color::PaleGreen1(154,255,154);
    const Color Color::PaleGreen2(144,238,144);
    const Color Color::PaleGreen3(124,205,124);
    const Color Color::PaleGreen4(84,139,84);
    const Color Color::PaleTurquoise(175,238,238);
    const Color Color::PaleTurquoise1(187,255,255);
    const Color Color::PaleTurquoise2(174,238,238);
    const Color Color::PaleTurquoise3(150,205,205);
    const Color Color::PaleTurquoise4(102,139,139);
    const Color Color::PaleVioletRed(219,112,147);
    const Color Color::PaleVioletRed1(255,130,171);
    const Color Color::PaleVioletRed2(238,121,159);
    const Color Color::PaleVioletRed3(205,104,127);
    const Color Color::PaleVioletRed4(139,71,93);
    const Color Color::papaya_whip(255,239,213);
    const Color Color::PapayaWhip(255,239,213);
    const Color Color::peach_puff(255,218,185);
    const Color Color::PeachPuff(255,218,185);
    const Color Color::PeachPuff1(255,218,185);
    const Color Color::PeachPuff2(238,203,173);
    const Color Color::PeachPuff3(205,175,149);
    const Color Color::PeachPuff4(139,119,101);
    const Color Color::peru(205,133,63);
    const Color Color::pink(255,192,203);
    const Color Color::pink1(255,181,197);
    const Color Color::pink2(238,169,184);
    const Color Color::pink3(205,145,158);
    const Color Color::pink4(139,99,108);
    const Color Color::plum(221,160,221);
    const Color Color::plum1(255,187,255);
    const Color Color::plum2(238,174,238);
    const Color Color::plum3(205,150,205);
    const Color Color::plum4(139,102,139);
    const Color Color::powder_blue(176,224,230);
    const Color Color::PowderBlue(176,224,230);
    const Color Color::purple(160,32,240);
    const Color Color::purple1(155,48,255);
    const Color Color::purple2(145,44,238);
    const Color Color::purple3(125,38,205);
    const Color Color::purple4(85,26,139);
    const Color Color::red(255,0,0);
    const Color Color::red1(255,0,0);
    const Color Color::red2(238,0,0);
    const Color Color::red3(205,0,0);
    const Color Color::red4(139,0,0);
    const Color Color::rosy_brown(188,143,143);
    const Color Color::RosyBrown(188,143,143);
    const Color Color::RosyBrown1(255,193,193);
    const Color Color::RosyBrown2(238,180,180);
    const Color Color::RosyBrown3(205,155,155);
    const Color Color::RosyBrown4(139,105,105);
    const Color Color::royal_blue(65,105,225);
    const Color Color::RoyalBlue(65,105,225);
    const Color Color::RoyalBlue1(72,118,255);
    const Color Color::RoyalBlue2(67,110,238);
    const Color Color::RoyalBlue3(58,95,205);
    const Color Color::RoyalBlue4(39,64,139);
    const Color Color::saddle_brown(139,69,19);
    const Color Color::SaddleBrown(139,69,19);
    const Color Color::salmon(250,128,114);
    const Color Color::salmon1(255,140,105);
    const Color Color::salmon2(238,130,98);
    const Color Color::salmon3(205,112,84);
    const Color Color::salmon4(139,76,57);
    const Color Color::sandy_brown(244,164,96);
    const Color Color::SandyBrown(244,164,96);
    const Color Color::sea_green(46,139,87);
    const Color Color::SeaGreen(46,139,87);
    const Color Color::SeaGreen1(84,255,159);
    const Color Color::SeaGreen2(78,238,148);
    const Color Color::SeaGreen3(67,205,128);
    const Color Color::SeaGreen4(46,139,87);
    const Color Color::seashell(255,245,238);
    const Color Color::seashell1(255,245,238);
    const Color Color::seashell2(238,229,222);
    const Color Color::seashell3(205,197,191);
    const Color Color::seashell4(139,134,130);
    const Color Color::sienna(160,82,45);
    const Color Color::sienna1(255,130,71);
    const Color Color::sienna2(238,121,66);
    const Color Color::sienna3(205,104,57);
    const Color Color::sienna4(139,71,38);
    const Color Color::sky_blue(135,206,235);
    const Color Color::SkyBlue(135,206,235);
    const Color Color::SkyBlue1(135,206,255);
    const Color Color::SkyBlue2(126,192,238);
    const Color Color::SkyBlue3(108,166,205);
    const Color Color::SkyBlue4(74,112,139);
    const Color Color::slate_blue(106,90,205);
    const Color Color::slate_gray(112,128,144);
    const Color Color::slate_grey(112,128,144);
    const Color Color::SlateBlue(106,90,205);
    const Color Color::SlateBlue1(131,111,255);
    const Color Color::SlateBlue2(122,103,238);
    const Color Color::SlateBlue3(105,89,205);
    const Color Color::SlateBlue4(71,60,139);
    const Color Color::SlateGray(112,128,144);
    const Color Color::SlateGray1(198,226,255);
    const Color Color::SlateGray2(185,211,238);
    const Color Color::SlateGray3(159,182,205);
    const Color Color::SlateGray4(108,123,139);
    const Color Color::SlateGrey(112,128,144);
    const Color Color::snow(255,250,250);
    const Color Color::snow1(255,250,250);
    const Color Color::snow2(238,233,233);
    const Color Color::snow3(205,201,201);
    const Color Color::snow4(139,137,137);
    const Color Color::spring_green(0,255,127);
    const Color Color::SpringGreen(0,255,127);
    const Color Color::SpringGreen1(0,255,127);
    const Color Color::SpringGreen2(0,238,118);
    const Color Color::SpringGreen3(0,205,102);
    const Color Color::SpringGreen4(0,139,69);
    const Color Color::steel_blue(70,130,180);
    const Color Color::SteelBlue(70,130,180);
    const Color Color::SteelBlue1(99,184,255);
    const Color Color::SteelBlue2(92,172,238);
    const Color Color::SteelBlue3(79,148,205);
    const Color Color::SteelBlue4(54,100,139);
    const Color Color::tan(210,180,140);
    const Color Color::tan1(255,165,79);
    const Color Color::tan2(238,154,73);
    const Color Color::tan3(205,133,63);
    const Color Color::tan4(139,90,43);
    const Color Color::thistle(216,191,216);
    const Color Color::thistle1(255,225,255);
    const Color Color::thistle2(238,210,238);
    const Color Color::thistle3(205,181,205);
    const Color Color::thistle4(139,123,139);
    const Color Color::tomato(255,99,71);
    const Color Color::tomato1(255,99,71);
    const Color Color::tomato2(238,92,66);
    const Color Color::tomato3(205,79,57);
    const Color Color::tomato4(139,54,38);
    const Color Color::turquoise(64,224,208);
    const Color Color::turquoise1(0,245,255);
    const Color Color::turquoise2(0,229,238);
    const Color Color::turquoise3(0,197,205);
    const Color Color::turquoise4(0,134,139);
    const Color Color::violet(238,130,238);
    const Color Color::violet_red(208,32,144);
    const Color Color::VioletRed(208,32,144);
    const Color Color::VioletRed1(255,62,150);
    const Color Color::VioletRed2(238,58,140);
    const Color Color::VioletRed3(205,50,120);
    const Color Color::VioletRed4(139,34,82);
    const Color Color::wheat(245,222,179);
    const Color Color::wheat1(255,231,186);
    const Color Color::wheat2(238,216,174);
    const Color Color::wheat3(205,186,150);
    const Color Color::wheat4(139,126,102);
    const Color Color::white(255,255,255);
    const Color Color::white_smoke(245,245,245);
    const Color Color::WhiteSmoke(245,245,245);
    const Color Color::yellow(255,255,0);
    const Color Color::yellow_green(154,205,50);
    const Color Color::yellow1(255,255,0);
    const Color Color::yellow2(238,238,0);
    const Color Color::yellow3(205,205,0);
    const Color Color::yellow4(139,139,0);
    const Color Color::YellowGreen(154,205,50);

    namespace {/*Anonymous namespace for internal name-to-color map*/
        const std::map<std::string, const Color&> NAMEDCOLORS = {
            {"alice blue", Color::alice_blue},
            {"AliceBlue", Color::AliceBlue},
            {"antique white", Color::antique_white},
            {"AntiqueWhite", Color::AntiqueWhite},
            {"AntiqueWhite1", Color::AntiqueWhite1},
            {"AntiqueWhite2", Color::AntiqueWhite2},
            {"AntiqueWhite3", Color::AntiqueWhite3},
            {"AntiqueWhite4", Color::AntiqueWhite4},
            {"aquamarine", Color::aquamarine},
            {"aquamarine1", Color::aquamarine1},
            {"aquamarine2", Color::aquamarine2},
            {"aquamarine3", Color::aquamarine3},
            {"aquamarine4", Color::aquamarine4},
            {"azure", Color::azure},
            {"azure1", Color::azure1},
            {"azure2", Color::azure2},
            {"azure3", Color::azure3},
            {"azure4", Color::azure4},
            {"beige", Color::beige},
            {"bisque", Color::bisque},
            {"bisque1", Color::bisque1},
            {"bisque2", Color::bisque2},
            {"bisque3", Color::bisque3},
            {"bisque4", Color::bisque4},
            {"black", Color::black},
            {"blanched almond", Color::blanched_almond},
            {"BlanchedAlmond", Color::BlanchedAlmond},
            {"blue", Color::blue},
            {"blue violet", Color::blue_violet},
            {"blue1", Color::blue1},
            {"blue2", Color::blue2},
            {"blue3", Color::blue3},
            {"blue4", Color::blue4},
            {"BlueViolet", Color::BlueViolet},
            {"brown", Color::brown},
            {"brown1", Color::brown1},
            {"brown2", Color::brown2},
            {"brown3", Color::brown3},
            {"brown4", Color::brown4},
            {"burlywood", Color::burlywood},
            {"burlywood1", Color::burlywood1},
            {"burlywood2", Color::burlywood2},
            {"burlywood3", Color::burlywood3},
            {"burlywood4", Color::burlywood4},
            {"cadet blue", Color::cadet_blue},
            {"CadetBlue", Color::CadetBlue},
            {"CadetBlue1", Color::CadetBlue1},
            {"CadetBlue2", Color::CadetBlue2},
            {"CadetBlue3", Color::CadetBlue3},
            {"CadetBlue4", Color::CadetBlue4},
            {"chartreuse", Color::chartreuse},
            {"chartreuse1", Color::chartreuse1},
            {"chartreuse2", Color::chartreuse2},
            {"chartreuse3", Color::chartreuse3},
            {"chartreuse4", Color::chartreuse4},
            {"chocolate", Color::chocolate},
            {"chocolate1", Color::chocolate1},
            {"chocolate2", Color::chocolate2},
            {"chocolate3", Color::chocolate3},
            {"chocolate4", Color::chocolate4},
            {"coral", Color::coral},
            {"coral1", Color::coral1},
            {"coral2", Color::coral2},
            {"coral3", Color::coral3},
            {"coral4", Color::coral4},
            {"cornflower blue", Color::cornflower_blue},
            {"CornflowerBlue", Color::CornflowerBlue},
            {"cornsilk", Color::cornsilk},
            {"cornsilk1", Color::cornsilk1},
            {"cornsilk2", Color::cornsilk2},
            {"cornsilk3", Color::cornsilk3},
            {"cornsilk4", Color::cornsilk4},
            {"cyan", Color::cyan},
            {"cyan1", Color::cyan1},
            {"cyan2", Color::cyan2},
            {"cyan3", Color::cyan3},
            {"cyan4", Color::cyan4},
            {"dark blue", Color::dark_blue},
            {"dark cyan", Color::dark_cyan},
            {"dark goldenrod", Color::dark_goldenrod},
            {"dark gray", Color::dark_gray},
            {"dark green", Color::dark_green},
            {"dark grey", Color::dark_grey},
            {"dark khaki", Color::dark_khaki},
            {"dark magenta", Color::dark_magenta},
            {"dark olive green", Color::dark_olive_green},
            {"dark orange", Color::dark_orange},
            {"dark orchid", Color::dark_orchid},
            {"dark red", Color::dark_red},
            {"dark salmon", Color::dark_salmon},
            {"dark sea green", Color::dark_sea_green},
            {"dark slate blue", Color::dark_slate_blue},
            {"dark slate gray", Color::dark_slate_gray},
            {"dark slate grey", Color::dark_slate_grey},
            {"dark turquoise", Color::dark_turquoise},
            {"dark violet", Color::dark_violet},
            {"DarkBlue", Color::DarkBlue},
            {"DarkCyan", Color::DarkCyan},
            {"DarkGoldenrod", Color::DarkGoldenrod},
            {"DarkGoldenrod1", Color::DarkGoldenrod1},
            {"DarkGoldenrod2", Color::DarkGoldenrod2},
            {"DarkGoldenrod3", Color::DarkGoldenrod3},
            {"DarkGoldenrod4", Color::DarkGoldenrod4},
            {"DarkGray", Color::DarkGray},
            {"DarkGreen", Color::DarkGreen},
            {"DarkGrey", Color::DarkGrey},
            {"DarkKhaki", Color::DarkKhaki},
            {"DarkMagenta", Color::DarkMagenta},
            {"DarkOliveGreen", Color::DarkOliveGreen},
            {"DarkOliveGreen1", Color::DarkOliveGreen1},
            {"DarkOliveGreen2", Color::DarkOliveGreen2},
            {"DarkOliveGreen3", Color::DarkOliveGreen3},
            {"DarkOliveGreen4", Color::DarkOliveGreen4},
            {"DarkOrange", Color::DarkOrange},
            {"DarkOrange1", Color::DarkOrange1},
            {"DarkOrange2", Color::DarkOrange2},
            {"DarkOrange3", Color::DarkOrange3},
            {"DarkOrange4", Color::DarkOrange4},
            {"DarkOrchid", Color::DarkOrchid},
            {"DarkOrchid1", Color::DarkOrchid1},
            {"DarkOrchid2", Color::DarkOrchid2},
            {"DarkOrchid3", Color::DarkOrchid3},
            {"DarkOrchid4", Color::DarkOrchid4},
            {"DarkRed", Color::DarkRed},
            {"DarkSalmon", Color::DarkSalmon},
            {"DarkSeaGreen", Color::DarkSeaGreen},
            {"DarkSeaGreen1", Color::DarkSeaGreen1},
            {"DarkSeaGreen2", Color::DarkSeaGreen2},
            {"DarkSeaGreen3", Color::DarkSeaGreen3},
            {"DarkSeaGreen4", Color::DarkSeaGreen4},
            {"DarkSlateBlue", Color::DarkSlateBlue},
            {"DarkSlateGray", Color::DarkSlateGray},
            {"DarkSlateGray1", Color::DarkSlateGray1},
            {"DarkSlateGray2", Color::DarkSlateGray2},
            {"DarkSlateGray3", Color::DarkSlateGray3},
            {"DarkSlateGray4", Color::DarkSlateGray4},
            {"DarkSlateGrey", Color::DarkSlateGrey},
            {"DarkTurquoise", Color::DarkTurquoise},
            {"DarkViolet", Color::DarkViolet},
            {"deep pink", Color::deep_pink},
            {"deep sky blue", Color::deep_sky_blue},
            {"DeepPink", Color::DeepPink},
            {"DeepPink1", Color::DeepPink1},
            {"DeepPink2", Color::DeepPink2},
            {"DeepPink3", Color::DeepPink3},
            {"DeepPink4", Color::DeepPink4},
            {"DeepSkyBlue", Color::DeepSkyBlue},
            {"DeepSkyBlue1", Color::DeepSkyBlue1},
            {"DeepSkyBlue2", Color::DeepSkyBlue2},
            {"DeepSkyBlue3", Color::DeepSkyBlue3},
            {"DeepSkyBlue4", Color::DeepSkyBlue4},
            {"dim gray", Color::dim_gray},
            {"dim grey", Color::dim_grey},
            {"DimGray", Color::DimGray},
            {"DimGrey", Color::DimGrey},
            {"dodger blue", Color::dodger_blue},
            {"DodgerBlue", Color::DodgerBlue},
            {"DodgerBlue1", Color::DodgerBlue1},
            {"DodgerBlue2", Color::DodgerBlue2},
            {"DodgerBlue3", Color::DodgerBlue3},
            {"DodgerBlue4", Color::DodgerBlue4},
            {"firebrick", Color::firebrick},
            {"firebrick1", Color::firebrick1},
            {"firebrick2", Color::firebrick2},
            {"firebrick3", Color::firebrick3},
            {"firebrick4", Color::firebrick4},
            {"floral white", Color::floral_white},
            {"FloralWhite", Color::FloralWhite},
            {"forest green", Color::forest_green},
            {"ForestGreen", Color::ForestGreen},
            {"gainsboro", Color::gainsboro},
            {"ghost white", Color::ghost_white},
            {"GhostWhite", Color::GhostWhite},
            {"gold", Color::gold},
            {"gold1", Color::gold1},
            {"gold2", Color::gold2},
            {"gold3", Color::gold3},
            {"gold4", Color::gold4},
            {"goldenrod", Color::goldenrod},
            {"goldenrod1", Color::goldenrod1},
            {"goldenrod2", Color::goldenrod2},
            {"goldenrod3", Color::goldenrod3},
            {"goldenrod4", Color::goldenrod4},
            {"gray", Color::gray},
            {"gray0", Color::gray0},
            {"gray1", Color::gray1},
            {"gray2", Color::gray2},
            {"gray3", Color::gray3},
            {"gray4", Color::gray4},
            {"gray5", Color::gray5},
            {"gray6", Color::gray6},
            {"gray7", Color::gray7},
            {"gray8", Color::gray8},
            {"gray9", Color::gray9},
            {"gray10", Color::gray10},
            {"gray11", Color::gray11},
            {"gray12", Color::gray12},
            {"gray13", Color::gray13},
            {"gray14", Color::gray14},
            {"gray15", Color::gray15},
            {"gray16", Color::gray16},
            {"gray17", Color::gray17},
            {"gray18", Color::gray18},
            {"gray19", Color::gray19},
            {"gray20", Color::gray20},
            {"gray21", Color::gray21},
            {"gray22", Color::gray22},
            {"gray23", Color::gray23},
            {"gray24", Color::gray24},
            {"gray25", Color::gray25},
            {"gray26", Color::gray26},
            {"gray27", Color::gray27},
            {"gray28", Color::gray28},
            {"gray29", Color::gray29},
            {"gray30", Color::gray30},
            {"gray31", Color::gray31},
            {"gray32", Color::gray32},
            {"gray33", Color::gray33},
            {"gray34", Color::gray34},
            {"gray35", Color::gray35},
            {"gray36", Color::gray36},
            {"gray37", Color::gray37},
            {"gray38", Color::gray38},
            {"gray39", Color::gray39},
            {"gray40", Color::gray40},
            {"gray41", Color::gray41},
            {"gray42", Color::gray42},
            {"gray43", Color::gray43},
            {"gray44", Color::gray44},
            {"gray45", Color::gray45},
            {"gray46", Color::gray46},
            {"gray47", Color::gray47},
            {"gray48", Color::gray48},
            {"gray49", Color::gray49},
            {"gray50", Color::gray50},
            {"gray51", Color::gray51},
            {"gray52", Color::gray52},
            {"gray53", Color::gray53},
            {"gray54", Color::gray54},
            {"gray55", Color::gray55},
            {"gray56", Color::gray56},
            {"gray57", Color::gray57},
            {"gray58", Color::gray58},
            {"gray59", Color::gray59},
            {"gray60", Color::gray60},
            {"gray61", Color::gray61},
            {"gray62", Color::gray62},
            {"gray63", Color::gray63},
            {"gray64", Color::gray64},
            {"gray65", Color::gray65},
            {"gray66", Color::gray66},
            {"gray67", Color::gray67},
            {"gray68", Color::gray68},
            {"gray69", Color::gray69},
            {"gray70", Color::gray70},
            {"gray71", Color::gray71},
            {"gray72", Color::gray72},
            {"gray73", Color::gray73},
            {"gray74", Color::gray74},
            {"gray75", Color::gray75},
            {"gray76", Color::gray76},
            {"gray77", Color::gray77},
            {"gray78", Color::gray78},
            {"gray79", Color::gray79},
            {"gray80", Color::gray80},
            {"gray81", Color::gray81},
            {"gray82", Color::gray82},
            {"gray83", Color::gray83},
            {"gray84", Color::gray84},
            {"gray85", Color::gray85},
            {"gray86", Color::gray86},
            {"gray87", Color::gray87},
            {"gray88", Color::gray88},
            {"gray89", Color::gray89},
            {"gray90", Color::gray90},
            {"gray91", Color::gray91},
            {"gray92", Color::gray92},
            {"gray93", Color::gray93},
            {"gray94", Color::gray94},
            {"gray95", Color::gray95},
            {"gray96", Color::gray96},
            {"gray97", Color::gray97},
            {"gray98", Color::gray98},
            {"gray99", Color::gray99},
            {"gray100", Color::gray100},
            {"green", Color::green},
            {"green yellow", Color::green_yellow},
            {"green1", Color::green1},
            {"green2", Color::green2},
            {"green3", Color::green3},
            {"green4", Color::green4},
            {"GreenYellow", Color::GreenYellow},
            {"grey", Color::grey},
            {"grey0", Color::grey0},
            {"grey1", Color::grey1},
            {"grey2", Color::grey2},
            {"grey3", Color::grey3},
            {"grey4", Color::grey4},
            {"grey5", Color::grey5},
            {"grey6", Color::grey6},
            {"grey7", Color::grey7},
            {"grey8", Color::grey8},
            {"grey9", Color::grey9},
            {"grey10", Color::grey10},
            {"grey11", Color::grey11},
            {"grey12", Color::grey12},
            {"grey13", Color::grey13},
            {"grey14", Color::grey14},
            {"grey15", Color::grey15},
            {"grey16", Color::grey16},
            {"grey17", Color::grey17},
            {"grey18", Color::grey18},
            {"grey19", Color::grey19},
            {"grey20", Color::grey20},
            {"grey21", Color::grey21},
            {"grey22", Color::grey22},
            {"grey23", Color::grey23},
            {"grey24", Color::grey24},
            {"grey25", Color::grey25},
            {"grey26", Color::grey26},
            {"grey27", Color::grey27},
            {"grey28", Color::grey28},
            {"grey29", Color::grey29},
            {"grey30", Color::grey30},
            {"grey31", Color::grey31},
            {"grey32", Color::grey32},
            {"grey33", Color::grey33},
            {"grey34", Color::grey34},
            {"grey35", Color::grey35},
            {"grey36", Color::grey36},
            {"grey37", Color::grey37},
            {"grey38", Color::grey38},
            {"grey39", Color::grey39},
            {"grey40", Color::grey40},
            {"grey41", Color::grey41},
            {"grey42", Color::grey42},
            {"grey43", Color::grey43},
            {"grey44", Color::grey44},
            {"grey45", Color::grey45},
            {"grey46", Color::grey46},
            {"grey47", Color::grey47},
            {"grey48", Color::grey48},
            {"grey49", Color::grey49},
            {"grey50", Color::grey50},
            {"grey51", Color::grey51},
            {"grey52", Color::grey52},
            {"grey53", Color::grey53},
            {"grey54", Color::grey54},
            {"grey55", Color::grey55},
            {"grey56", Color::grey56},
            {"grey57", Color::grey57},
            {"grey58", Color::grey58},
            {"grey59", Color::grey59},
            {"grey60", Color::grey60},
            {"grey61", Color::grey61},
            {"grey62", Color::grey62},
            {"grey63", Color::grey63},
            {"grey64", Color::grey64},
            {"grey65", Color::grey65},
            {"grey66", Color::grey66},
            {"grey67", Color::grey67},
            {"grey68", Color::grey68},
            {"grey69", Color::grey69},
            {"grey70", Color::grey70},
            {"grey71", Color::grey71},
            {"grey72", Color::grey72},
            {"grey73", Color::grey73},
            {"grey74", Color::grey74},
            {"grey75", Color::grey75},
            {"grey76", Color::grey76},
            {"grey77", Color::grey77},
            {"grey78", Color::grey78},
            {"grey79", Color::grey79},
            {"grey80", Color::grey80},
            {"grey81", Color::grey81},
            {"grey82", Color::grey82},
            {"grey83", Color::grey83},
            {"grey84", Color::grey84},
            {"grey85", Color::grey85},
            {"grey86", Color::grey86},
            {"grey87", Color::grey87},
            {"grey88", Color::grey88},
            {"grey89", Color::grey89},
            {"grey90", Color::grey90},
            {"grey91", Color::grey91},
            {"grey92", Color::grey92},
            {"grey93", Color::grey93},
            {"grey94", Color::grey94},
            {"grey95", Color::grey95},
            {"grey96", Color::grey96},
            {"grey97", Color::grey97},
            {"grey98", Color::grey98},
            {"grey99", Color::grey99},
            {"grey100", Color::grey100},
            {"honeydew", Color::honeydew},
            {"honeydew1", Color::honeydew1},
            {"honeydew2", Color::honeydew2},
            {"honeydew3", Color::honeydew3},
            {"honeydew4", Color::honeydew4},
            {"hot pink", Color::hot_pink},
            {"HotPink", Color::HotPink},
            {"HotPink1", Color::HotPink1},
            {"HotPink2", Color::HotPink2},
            {"HotPink3", Color::HotPink3},
            {"HotPink4", Color::HotPink4},
            {"indian red", Color::indian_red},
            {"IndianRed", Color::IndianRed},
            {"IndianRed1", Color::IndianRed1},
            {"IndianRed2", Color::IndianRed2},
            {"IndianRed3", Color::IndianRed3},
            {"IndianRed4", Color::IndianRed4},
            {"ivory", Color::ivory},
            {"ivory1", Color::ivory1},
            {"ivory2", Color::ivory2},
            {"ivory3", Color::ivory3},
            {"ivory4", Color::ivory4},
            {"khaki", Color::khaki},
            {"khaki1", Color::khaki1},
            {"khaki2", Color::khaki2},
            {"khaki3", Color::khaki3},
            {"khaki4", Color::khaki4},
            {"lavender", Color::lavender},
            {"lavender blush", Color::lavender_blush},
            {"LavenderBlush", Color::LavenderBlush},
            {"LavenderBlush1", Color::LavenderBlush1},
            {"LavenderBlush2", Color::LavenderBlush2},
            {"LavenderBlush3", Color::LavenderBlush3},
            {"LavenderBlush4", Color::LavenderBlush4},
            {"lawn green", Color::lawn_green},
            {"LawnGreen", Color::LawnGreen},
            {"lemon chiffon", Color::lemon_chiffon},
            {"LemonChiffon", Color::LemonChiffon},
            {"LemonChiffon1", Color::LemonChiffon1},
            {"LemonChiffon2", Color::LemonChiffon2},
            {"LemonChiffon3", Color::LemonChiffon3},
            {"LemonChiffon4", Color::LemonChiffon4},
            {"light blue", Color::light_blue},
            {"light coral", Color::light_coral},
            {"light cyan", Color::light_cyan},
            {"light goldenrod", Color::light_goldenrod},
            {"light goldenrod yellow", Color::light_goldenrod_yellow},
            {"light gray", Color::light_gray},
            {"light green", Color::light_green},
            {"light grey", Color::light_grey},
            {"light pink", Color::light_pink},
            {"light salmon", Color::light_salmon},
            {"light sea green", Color::light_sea_green},
            {"light sky blue", Color::light_sky_blue},
            {"light slate blue", Color::light_slate_blue},
            {"light slate gray", Color::light_slate_gray},
            {"light slate grey", Color::light_slate_grey},
            {"light steel blue", Color::light_steel_blue},
            {"light yellow", Color::light_yellow},
            {"LightBlue", Color::LightBlue},
            {"LightBlue1", Color::LightBlue1},
            {"LightBlue2", Color::LightBlue2},
            {"LightBlue3", Color::LightBlue3},
            {"LightBlue4", Color::LightBlue4},
            {"LightCoral", Color::LightCoral},
            {"LightCyan", Color::LightCyan},
            {"LightCyan1", Color::LightCyan1},
            {"LightCyan2", Color::LightCyan2},
            {"LightCyan3", Color::LightCyan3},
            {"LightCyan4", Color::LightCyan4},
            {"LightGoldenrod", Color::LightGoldenrod},
            {"LightGoldenrod1", Color::LightGoldenrod1},
            {"LightGoldenrod2", Color::LightGoldenrod2},
            {"LightGoldenrod3", Color::LightGoldenrod3},
            {"LightGoldenrod4", Color::LightGoldenrod4},
            {"LightGoldenrodYellow", Color::LightGoldenrodYellow},
            {"LightGray", Color::LightGray},
            {"LightGreen", Color::LightGreen},
            {"LightGrey", Color::LightGrey},
            {"LightPink", Color::LightPink},
            {"LightPink1", Color::LightPink1},
            {"LightPink2", Color::LightPink2},
            {"LightPink3", Color::LightPink3},
            {"LightPink4", Color::LightPink4},
            {"LightSalmon", Color::LightSalmon},
            {"LightSalmon1", Color::LightSalmon1},
            {"LightSalmon2", Color::LightSalmon2},
            {"LightSalmon3", Color::LightSalmon3},
            {"LightSalmon4", Color::LightSalmon4},
            {"LightSeaGreen", Color::LightSeaGreen},
            {"LightSkyBlue", Color::LightSkyBlue},
            {"LightSkyBlue1", Color::LightSkyBlue1},
            {"LightSkyBlue2", Color::LightSkyBlue2},
            {"LightSkyBlue3", Color::LightSkyBlue3},
            {"LightSkyBlue4", Color::LightSkyBlue4},
            {"LightSlateBlue", Color::LightSlateBlue},
            {"LightSlateGray", Color::LightSlateGray},
            {"LightSlateGrey", Color::LightSlateGrey},
            {"LightSteelBlue", Color::LightSteelBlue},
            {"LightSteelBlue1", Color::LightSteelBlue1},
            {"LightSteelBlue2", Color::LightSteelBlue2},
            {"LightSteelBlue3", Color::LightSteelBlue3},
            {"LightSteelBlue4", Color::LightSteelBlue4},
            {"LightYellow", Color::LightYellow},
            {"LightYellow1", Color::LightYellow1},
            {"LightYellow2", Color::LightYellow2},
            {"LightYellow3", Color::LightYellow3},
            {"LightYellow4", Color::LightYellow4},
            {"lime green", Color::lime_green},
            {"LimeGreen", Color::LimeGreen},
            {"linen", Color::linen},
            {"magenta", Color::magenta},
            {"magenta1", Color::magenta1},
            {"magenta2", Color::magenta2},
            {"magenta3", Color::magenta3},
            {"magenta4", Color::magenta4},
            {"maroon", Color::maroon},
            {"maroon1", Color::maroon1},
            {"maroon2", Color::maroon2},
            {"maroon3", Color::maroon3},
            {"maroon4", Color::maroon4},
            {"medium aquamarine", Color::medium_aquamarine},
            {"medium blue", Color::medium_blue},
            {"medium orchid", Color::medium_orchid},
            {"medium purple", Color::medium_purple},
            {"medium sea green", Color::medium_sea_green},
            {"medium slate blue", Color::medium_slate_blue},
            {"medium spring green", Color::medium_spring_green},
            {"medium turquoise", Color::medium_turquoise},
            {"medium violet red", Color::medium_violet_red},
            {"MediumAquamarine", Color::MediumAquamarine},
            {"MediumBlue", Color::MediumBlue},
            {"MediumOrchid", Color::MediumOrchid},
            {"MediumOrchid1", Color::MediumOrchid1},
            {"MediumOrchid2", Color::MediumOrchid2},
            {"MediumOrchid3", Color::MediumOrchid3},
            {"MediumOrchid4", Color::MediumOrchid4},
            {"MediumPurple", Color::MediumPurple},
            {"MediumPurple1", Color::MediumPurple1},
            {"MediumPurple2", Color::MediumPurple2},
            {"MediumPurple3", Color::MediumPurple3},
            {"MediumPurple4", Color::MediumPurple4},
            {"MediumSeaGreen", Color::MediumSeaGreen},
            {"MediumSlateBlue", Color::MediumSlateBlue},
            {"MediumSpringGreen", Color::MediumSpringGreen},
            {"MediumTurquoise", Color::MediumTurquoise},
            {"MediumVioletRed", Color::MediumVioletRed},
            {"midnight blue", Color::midnight_blue},
            {"MidnightBlue", Color::MidnightBlue},
            {"mint cream", Color::mint_cream},
            {"MintCream", Color::MintCream},
            {"misty rose", Color::misty_rose},
            {"MistyRose", Color::MistyRose},
            {"MistyRose1", Color::MistyRose1},
            {"MistyRose2", Color::MistyRose2},
            {"MistyRose3", Color::MistyRose3},
            {"MistyRose4", Color::MistyRose4},
            {"moccasin", Color::moccasin},
            {"navajo white", Color::navajo_white},
            {"NavajoWhite", Color::NavajoWhite},
            {"NavajoWhite1", Color::NavajoWhite1},
            {"NavajoWhite2", Color::NavajoWhite2},
            {"NavajoWhite3", Color::NavajoWhite3},
            {"NavajoWhite4", Color::NavajoWhite4},
            {"navy", Color::navy},
            {"navy blue", Color::navy_blue},
            {"NavyBlue", Color::NavyBlue},
            {"old lace", Color::old_lace},
            {"OldLace", Color::OldLace},
            {"olive drab", Color::olive_drab},
            {"OliveDrab", Color::OliveDrab},
            {"OliveDrab1", Color::OliveDrab1},
            {"OliveDrab2", Color::OliveDrab2},
            {"OliveDrab3", Color::OliveDrab3},
            {"OliveDrab4", Color::OliveDrab4},
            {"orange", Color::orange},
            {"orange red", Color::orange_red},
            {"orange1", Color::orange1},
            {"orange2", Color::orange2},
            {"orange3", Color::orange3},
            {"orange4", Color::orange4},
            {"OrangeRed", Color::OrangeRed},
            {"OrangeRed1", Color::OrangeRed1},
            {"OrangeRed2", Color::OrangeRed2},
            {"OrangeRed3", Color::OrangeRed3},
            {"OrangeRed4", Color::OrangeRed4},
            {"orchid", Color::orchid},
            {"orchid1", Color::orchid1},
            {"orchid2", Color::orchid2},
            {"orchid3", Color::orchid3},
            {"orchid4", Color::orchid4},
            {"pale goldenrod", Color::pale_goldenrod},
            {"pale green", Color::pale_green},
            {"pale turquoise", Color::pale_turquoise},
            {"pale violet red", Color::pale_violet_red},
            {"PaleGoldenrod", Color::PaleGoldenrod},
            {"PaleGreen", Color::PaleGreen},
            {"PaleGreen1", Color::PaleGreen1},
            {"PaleGreen2", Color::PaleGreen2},
            {"PaleGreen3", Color::PaleGreen3},
            {"PaleGreen4", Color::PaleGreen4},
            {"PaleTurquoise", Color::PaleTurquoise},
            {"PaleTurquoise1", Color::PaleTurquoise1},
            {"PaleTurquoise2", Color::PaleTurquoise2},
            {"PaleTurquoise3", Color::PaleTurquoise3},
            {"PaleTurquoise4", Color::PaleTurquoise4},
            {"PaleVioletRed", Color::PaleVioletRed},
            {"PaleVioletRed1", Color::PaleVioletRed1},
            {"PaleVioletRed2", Color::PaleVioletRed2},
            {"PaleVioletRed3", Color::PaleVioletRed3},
            {"PaleVioletRed4", Color::PaleVioletRed4},
            {"papaya whip", Color::papaya_whip},
            {"PapayaWhip", Color::PapayaWhip},
            {"peach puff", Color::peach_puff},
            {"PeachPuff", Color::PeachPuff},
            {"PeachPuff1", Color::PeachPuff1},
            {"PeachPuff2", Color::PeachPuff2},
            {"PeachPuff3", Color::PeachPuff3},
            {"PeachPuff4", Color::PeachPuff4},
            {"peru", Color::peru},
            {"pink", Color::pink},
            {"pink1", Color::pink1},
            {"pink2", Color::pink2},
            {"pink3", Color::pink3},
            {"pink4", Color::pink4},
            {"plum", Color::plum},
            {"plum1", Color::plum1},
            {"plum2", Color::plum2},
            {"plum3", Color::plum3},
            {"plum4", Color::plum4},
            {"powder blue", Color::powder_blue},
            {"PowderBlue", Color::PowderBlue},
            {"purple", Color::purple},
            {"purple1", Color::purple1},
            {"purple2", Color::purple2},
            {"purple3", Color::purple3},
            {"purple4", Color::purple4},
            {"red", Color::red},
            {"red1", Color::red1},
            {"red2", Color::red2},
            {"red3", Color::red3},
            {"red4", Color::red4},
            {"rosy brown", Color::rosy_brown},
            {"RosyBrown", Color::RosyBrown},
            {"RosyBrown1", Color::RosyBrown1},
            {"RosyBrown2", Color::RosyBrown2},
            {"RosyBrown3", Color::RosyBrown3},
            {"RosyBrown4", Color::RosyBrown4},
            {"royal blue", Color::royal_blue},
            {"RoyalBlue", Color::RoyalBlue},
            {"RoyalBlue1", Color::RoyalBlue1},
            {"RoyalBlue2", Color::RoyalBlue2},
            {"RoyalBlue3", Color::RoyalBlue3},
            {"RoyalBlue4", Color::RoyalBlue4},
            {"saddle brown", Color::saddle_brown},
            {"SaddleBrown", Color::SaddleBrown},
            {"salmon", Color::salmon},
            {"salmon1", Color::salmon1},
            {"salmon2", Color::salmon2},
            {"salmon3", Color::salmon3},
            {"salmon4", Color::salmon4},
            {"sandy brown", Color::sandy_brown},
            {"SandyBrown", Color::SandyBrown},
            {"sea green", Color::sea_green},
            {"SeaGreen", Color::SeaGreen},
            {"SeaGreen1", Color::SeaGreen1},
            {"SeaGreen2", Color::SeaGreen2},
            {"SeaGreen3", Color::SeaGreen3},
            {"SeaGreen4", Color::SeaGreen4},
            {"seashell", Color::seashell},
            {"seashell1", Color::seashell1},
            {"seashell2", Color::seashell2},
            {"seashell3", Color::seashell3},
            {"seashell4", Color::seashell4},
            {"sienna", Color::sienna},
            {"sienna1", Color::sienna1},
            {"sienna2", Color::sienna2},
            {"sienna3", Color::sienna3},
            {"sienna4", Color::sienna4},
            {"sky blue", Color::sky_blue},
            {"SkyBlue", Color::SkyBlue},
            {"SkyBlue1", Color::SkyBlue1},
            {"SkyBlue2", Color::SkyBlue2},
            {"SkyBlue3", Color::SkyBlue3},
            {"SkyBlue4", Color::SkyBlue4},
            {"slate blue", Color::slate_blue},
            {"slate gray", Color::slate_gray},
            {"slate grey", Color::slate_grey},
            {"SlateBlue", Color::SlateBlue},
            {"SlateBlue1", Color::SlateBlue1},
            {"SlateBlue2", Color::SlateBlue2},
            {"SlateBlue3", Color::SlateBlue3},
            {"SlateBlue4", Color::SlateBlue4},
            {"SlateGray", Color::SlateGray},
            {"SlateGray1", Color::SlateGray1},
            {"SlateGray2", Color::SlateGray2},
            {"SlateGray3", Color::SlateGray3},
            {"SlateGray4", Color::SlateGray4},
            {"SlateGrey", Color::SlateGrey},
            {"snow", Color::snow},
            {"snow1", Color::snow1},
            {"snow2", Color::snow2},
            {"snow3", Color::snow3},
            {"snow4", Color::snow4},
            {"spring green", Color::spring_green},
            {"SpringGreen", Color::SpringGreen},
            {"SpringGreen1", Color::SpringGreen1},
            {"SpringGreen2", Color::SpringGreen2},
            {"SpringGreen3", Color::SpringGreen3},
            {"SpringGreen4", Color::SpringGreen4},
            {"steel blue", Color::steel_blue},
            {"SteelBlue", Color::SteelBlue},
            {"SteelBlue1", Color::SteelBlue1},
            {"SteelBlue2", Color::SteelBlue2},
            {"SteelBlue3", Color::SteelBlue3},
            {"SteelBlue4", Color::SteelBlue4},
            {"tan", Color::tan},
            {"tan1", Color::tan1},
            {"tan2", Color::tan2},
            {"tan3", Color::tan3},
            {"tan4", Color::tan4},
            {"thistle", Color::thistle},
            {"thistle1", Color::thistle1},
            {"thistle2", Color::thistle2},
            {"thistle3", Color::thistle3},
            {"thistle4", Color::thistle4},
            {"tomato", Color::tomato},
            {"tomato1", Color::tomato1},
            {"tomato2", Color::tomato2},
            {"tomato3", Color::tomato3},
            {"tomato4", Color::tomato4},
            {"turquoise", Color::turquoise},
            {"turquoise1", Color::turquoise1},
            {"turquoise2", Color::turquoise2},
            {"turquoise3", Color::turquoise3},
            {"turquoise4", Color::turquoise4},
            {"violet", Color::violet},
            {"violet red", Color::violet_red},
            {"VioletRed", Color::VioletRed},
            {"VioletRed1", Color::VioletRed1},
            {"VioletRed2", Color::VioletRed2},
            {"VioletRed3", Color::VioletRed3},
            {"VioletRed4", Color::VioletRed4},
            {"wheat", Color::wheat},
            {"wheat1", Color::wheat1},
            {"wheat2", Color::wheat2},
            {"wheat3", Color::wheat3},
            {"wheat4", Color::wheat4},
            {"white", Color::white},
            {"white smoke", Color::white_smoke},
            {"WhiteSmoke", Color::WhiteSmoke},
            {"yellow", Color::yellow},
            {"yellow green", Color::yellow_green},
            {"yellow1", Color::yellow1},
            {"yellow2", Color::yellow2},
            {"yellow3", Color::yellow3},
            {"yellow4", Color::yellow4},
            {"YellowGreen", Color::YellowGreen}
        };
    }
    
    Color randomColor(){
        static std::default_random_engine rng(epochTime());
        static std::uniform_int_distribution<int> rng_dist(0, 255);
        return Color((uint8_t)rng_dist(rng), (uint8_t)rng_dist(rng), (uint8_t)rng_dist(rng));
    }
    
    /**\brief Retrieves a read-only reference to a color
    *         associated with the specified input name string.
    * Default colors have an associated name string you can use to retrieve
    * their values. All of the names can be found here:
    * https://www.tcl.tk/man/tcl8.4/TkCmd/colors.htm */
    Color Color::fromName(const std::string& name){
        if(name == "random"){
            return randomColor();
        }
        return NAMEDCOLORS.at(name);
    }
}
#endif
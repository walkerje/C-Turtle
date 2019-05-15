/* 
 * File:    CTurtle.hpp
 * Project: C-Turtle
 * Created on May 13, 2019, 2:31 PM
 */

#pragma once

#ifndef CTURTLE_MSVC_NO_AUTOLINK
    #ifdef _MSC_VER
    /*Automatically link to the necessary windows libraries while under MSVC.*/
    #pragma comment(lib, "kernel32.lib")
    #pragma comment(lib, "gdi32.lib")
    #endif
#elif !defined(_WIN32)
    #ifndef CTURTLE_NO_MSVC_LINK_WARN
        #warn "You must link against X11 Libraries to get a CTurtle display on this system!" 
    #endif
#endif

/*Standard Includes*/
#include <cstdint>
#include <string>
#include <list>
#include <functional>
#include <utility>

/*Local Includes*/
#include "CImg.h"
#include "linalg.hpp"

namespace cturtle{
    /*Math Typedefs*/
    typedef linalg::vec<float, 2> vec2;
    typedef linalg::vec<float, 4> vec4;
    typedef linalg::mat<float, 4, 4> mat4;
    
    /* Color
     *      Defines an interface for RGBA Colors.
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
        component_t a;
        
        /*TODO: Document Me*/
        Color(unsigned char r, unsigned char g, unsigned char b, unsigned char a) :
            r(r), g(g), b(b), a(a){};
        
        /*TODO: Document Me*/
        Color(const Color& other) : 
            r(other.r), g(other.g), b(other.b), a(other.a){}
        
        /*TODO: Document Me*/
        Color(const std::string& name) : Color(fromName(name)){}
        
        Color(){r = g = b = a = 255;}
        
        /*TODO: Document Me*/
        static const Color& fromName(const std::string& name);
    };
    
    namespace cimg = cimg_library;
    
    /**/
    enum KeyboardKey {
        KEY_ESC = cimg::cimg::keyESC,
        KEY_F1 = cimg::cimg::keyF1,
        KEY_F2 = cimg::cimg::keyF2,
        KEY_F3 = cimg::cimg::keyF3,
        KEY_F4 = cimg::cimg::keyF4,
        KEY_F5 = cimg::cimg::keyF5,
        KEY_F6 = cimg::cimg::keyF6,
        KEY_F7 = cimg::cimg::keyF7,
        KEY_F8 = cimg::cimg::keyF8,
        KEY_F9 = cimg::cimg::keyF9,
        KEY_F10 = cimg::cimg::keyF10,
        KEY_F11 = cimg::cimg::keyF11,
        KEY_F12 = cimg::cimg::keyF12,
        KEY_PAUSE = cimg::cimg::keyPAUSE,
        KEY_1 = cimg::cimg::key1,
        KEY_2 = cimg::cimg::key2,
        KEY_3 = cimg::cimg::key3,
        KEY_4 = cimg::cimg::key4,
        KEY_5 = cimg::cimg::key5,
        KEY_6 = cimg::cimg::key6,
        KEY_7 = cimg::cimg::key7,
        KEY_8 = cimg::cimg::key8,
        KEY_9 = cimg::cimg::key9,
        KEY_0 = cimg::cimg::key0,
        KEY_BACKSPACE = cimg::cimg::keyBACKSPACE,
        KEY_INSERT = cimg::cimg::keyINSERT,
        KEY_HOME = cimg::cimg::keyHOME,
        KEY_PAGEUP = cimg::cimg::keyPAGEUP,
        KEY_TAB = cimg::cimg::keyTAB,
        KEY_Q = cimg::cimg::keyQ,
        KEY_W = cimg::cimg::keyW,
        KEY_E = cimg::cimg::keyE,
        KEY_R = cimg::cimg::keyR,
        KEY_T = cimg::cimg::keyT,
        KEY_Y = cimg::cimg::keyY,
        KEY_U = cimg::cimg::keyU,
        KEY_I = cimg::cimg::keyI,
        KEY_O = cimg::cimg::keyO,
        KEY_P = cimg::cimg::keyP,
        KEY_DELETE = cimg::cimg::keyDELETE,
        KEY_END = cimg::cimg::keyEND,
        KEY_PAGEDOWN = cimg::cimg::keyPAGEDOWN,
        KEY_CAPSLOCK = cimg::cimg::keyCAPSLOCK,
        KEY_A = cimg::cimg::keyA,
        KEY_S = cimg::cimg::keyS,
        KEY_D = cimg::cimg::keyD,
        KEY_F = cimg::cimg::keyF,
        KEY_G = cimg::cimg::keyG,
        KEY_H = cimg::cimg::keyH,
        KEY_J = cimg::cimg::keyJ,
        KEY_K = cimg::cimg::keyK,
        KEY_L = cimg::cimg::keyL,
        KEY_ENTER = cimg::cimg::keyENTER,
        KEY_SHIFTLEFT = cimg::cimg::keySHIFTLEFT,
        KEY_Z = cimg::cimg::keyZ,
        KEY_X = cimg::cimg::keyX,
        KEY_C = cimg::cimg::keyC,
        KEY_V = cimg::cimg::keyV,
        KEY_B = cimg::cimg::keyB,
        KEY_N = cimg::cimg::keyN,
        KEY_M = cimg::cimg::keyM,
        KEY_SHIFTRIGHT = cimg::cimg::keySHIFTRIGHT,
        KEY_ARROWUP = cimg::cimg::keyARROWUP,
        KEY_CTRLLEFT = cimg::cimg::keyCTRLLEFT,
        KEY_APPLEFT = cimg::cimg::keyAPPLEFT,
        KEY_ALT = cimg::cimg::keyALT,
        KEY_SPACE = cimg::cimg::keySPACE,
        KEY_ALTGR = cimg::cimg::keyALTGR,
        KEY_APPRIGHT = cimg::cimg::keyAPPRIGHT,
        KEY_MENU = cimg::cimg::keyMENU,
        KEY_CTRLRIGHT = cimg::cimg::keyCTRLRIGHT,
        KEY_ARROWLEFT = cimg::cimg::keyARROWLEFT,
        KEY_ARROWDOWN = cimg::cimg::keyARROWDOWN,
        KEY_ARROWRIGHT = cimg::cimg::keyARROWRIGHT,
        KEY_PAD0 = cimg::cimg::keyPAD0,
        KEY_PAD1 = cimg::cimg::keyPAD1,
        KEY_PAD2 = cimg::cimg::keyPAD2,
        KEY_PAD3 = cimg::cimg::keyPAD3,
        KEY_PAD4 = cimg::cimg::keyPAD4,
        KEY_PAD5 = cimg::cimg::keyPAD5,
        KEY_PAD6 = cimg::cimg::keyPAD6,
        KEY_PAD7 = cimg::cimg::keyPAD7,
        KEY_PAD8 = cimg::cimg::keyPAD8,
        KEY_PAD9 = cimg::cimg::keyPAD9,
        KEY_PADADD = cimg::cimg::keyPADADD,
        KEY_PADSUB = cimg::cimg::keyPADSUB,
        KEY_PADMUL = cimg::cimg::keyPADMUL,
        KEY_PADDIV = cimg::cimg::keyPADDIV
    };
    
    /*May need to make this match TKinter names, depending on requirements
      of the project.*/
    /*Returns a key with the specified name.
      Will throw a runtime exception if no key with the specified name exists.*/
    KeyboardKey keyFromName(const std::string& name);
    
//    class RawTurtle;
    class TurtleScreen;
    
    /*TODO: Document Me*/
    enum ScreenMode{
        SM_STANDARD,
        SM_LOGO,
        SM_WORLD
    };
    
    /*Callback function typedefs for event listeners.*/
    typedef std::function<void(vec2)> MouseFunc;
    typedef std::function<void(KeyboardKey)> KeyFunc;
    typedef std::function<void(void)> TimerFunc;
    
    /* TurtleScreen
     *      Holds and maintains all facilities in relation to displaying
     *      turtles and consuming input events from users through callbacks.
     */
    class TurtleScreen{
    public:
        TurtleScreen() : display(800, 600){
            display.set_title("CTurtle");
        }
        TurtleScreen(const std::string& title) : display(800, 600){
            display.set_title(title.c_str());
        }
        TurtleScreen(int width, int height, const std::string& title) : display(width, height){
            display.set_title(title.c_str());
        }
        
        /*Sets the background color of the screen.*/
        void bgcolor(const Color& color);
        
        /*Returns the background color of the screen.*/
        Color bgcolor();
        
        //TODO: bgpic()

        /*TODO: Document Me*/        
        void mode(ScreenMode mode);
        
        /*TODO: Document Me*/
        ScreenMode mode();
        
        /*TODO: Document Me*/
        void colormode(int val);
        
        /*TODO: Document Me*/
        int colormode();
        
        /*TODO: Document Me*/
        void clearscreen();
        
        /*Alias for @clearscreen*/
        inline void clear(){clearscreen();}
        
        /*Resets all turtles belonging to this screen to their original state.*/
        void resetscreen();
        
        /*Resets all turtles belonging to this screen to their original state.*/
        inline void reset(){resetscreen();}
        
        /*Returns the size of this screen, in pixels.
          Also returns the background color of the screen,
          by assigning the input reference.*/
        vec2 screensize(Color& bg);
        
        /*Returns the size of the screen, in pixels.*/
        inline vec2 screensize(){
            Color temp;
            return screensize(temp);
        }
        
        /*Sets the world coordinates.*/
        void setworldcoordinates(vec2 lowerLeft, vec2 upperRight);
        
        //TODO: Tracer Func
        
        /*TODO: Document Me*/
        void update();
        
        /*Sets the delay set between turtle commands.*/
        void delay(unsigned int ms);
        
        /*Returns the delay set between turtle commands in MS.*/
        unsigned int delay();
        
        /*Returns the width of the window, in pixels.*/
        int window_width(){
            return display.window_width();
        }
        
        /*Returns the height of the window, in pixels.*/
        int window_height(){
            return display.window_height();
        }
        
        /*Closes this window.*/
        void bye();
    protected:
        cimg::CImgDisplay display;
        cimg::CImg<uint8_t> image;
        
        Color backgroundColor   = Color::white;
        ScreenMode curMode      = SM_STANDARD;
        int colorCap            = 255;
        
        vec2 worldLowerLeft, worldUpperRight;
        
        KeyFunc     keyFunc     = [](char){};
        MouseFunc   clickFunc   = [](vec2){};
        TimerFunc   timerFunc   = [](void){};
    };
    
//    //TODO: Finish and document
//    class RawTurtle{
//    public:
//        RawTurtle(TurtleScreen& screen) : screen(screen){}
//        
//        virtual ~RawTurtle(){}
//    protected:
//        RawTurtle(){}
//        
//        mat4 transformMatrix;
//        TurtleScreen& screen;
//    };
}
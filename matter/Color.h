#pragma once

namespace Funtasia {
    class GLColor;

    class Color {
       public:
        GLColor ToGLColor();

        unsigned char r = 0;
        unsigned char g = 0;
        unsigned char b = 0;
        unsigned char a = 255;
    };
}
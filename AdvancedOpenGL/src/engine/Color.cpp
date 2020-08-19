#include "Color.h"

Color::Color() : r(255), g(255), b(255), a(255), glArray(nullptr) {}

Color::Color(uint8_t r, uint8_t g, uint8_t b, uint8_t a)
: r(r), g(g), b(b), a(a), glArray(nullptr) {}

Color::Color(uint32_t i) : glArray(nullptr)
{
    unsigned char r,g,b,a; 
    r = static_cast<unsigned char>(i & 0x000000FF); 
    g = static_cast<unsigned char>((i & 0x0000FF00) >> 8); 
    b = static_cast<unsigned char>((i & 0x00FF0000) >> 16); 
    a = static_cast<unsigned char>((i & 0xFF000000) >> 24);
}

Color::~Color() {}

void Color::setColor(uint8_t p_r, uint8_t p_g, uint8_t p_b, uint8_t p_a) 
{
    r = p_r;
    g = p_g;
    b = p_b;
    a = p_a;
}


Color Color::lerp(Color value1, Color value2, float amount)
{
    uint8_t r = Maths::clamp<uint8_t>(static_cast<uint8_t>(Maths::lerp(value1.r, value2.r, amount)), 0, 255);   
    uint8_t g = Maths::clamp<uint8_t>(static_cast<uint8_t>(Maths::lerp(value1.g, value2.g, amount)), 0, 255); 
    uint8_t b = Maths::clamp<uint8_t>(static_cast<uint8_t>(Maths::lerp(value1.b, value2.b, amount)), 0, 255); 
    uint8_t a = Maths::clamp<uint8_t>(static_cast<uint8_t>(Maths::lerp(value1.a, value2.a, amount)), 0, 255); 
    
    return Color(r, g, b, a);
}
		
Color Color::multiply(Color value, float scale)
{
    uint8_t r = (uint8_t)(value.r * scale);
    uint8_t g = (uint8_t)(value.g * scale);
    uint8_t b = (uint8_t)(value.b * scale);
    uint8_t a = (uint8_t)(value.a * scale);
    
    return Color(r, g, b, a);
}	

Vector3 Color::toVector3()
{
    Vector3 vector = Vector3(r, g, b);
    return vector;
}

Vector4 Color::toVector4()
{
    Vector4 vector = Vector4(r, g, b, a);
    return vector;
}

Color Color::black {0, 0, 0};
Color Color::white {255, 255, 255};
Color Color::red {255, 0, 0};
Color Color::green {0, 255, 0};
Color Color::blue {0, 0, 255};
Color Color::yellow {255, 255, 0};
Color Color::lightYellow {255, 255, 225};
Color Color::lightBlue {170, 217, 230};
Color Color::lightPink {255, 180, 200};
Color Color::lightGreen {142, 240, 142};

GLfloat* Color::toGlArray() {
    glArray = new GLfloat[4] { (float)r/255.0f, (float)g/255.0f, (float)b/255.0f, (float)a/255.0f };
    return glArray;
}

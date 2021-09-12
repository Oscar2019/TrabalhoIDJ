#pragma once
#include <cmath>

const float PI = std::acos(-1.0f);

struct Vec2{
    float x;
    float y;
    Vec2(float x = 0.0, float y = 0.0);
    static Vec2 sum(Vec2 vec_a, Vec2 vec_b);
    static Vec2 subtraction(Vec2 vec_a, Vec2 vec_b);
    static Vec2 multiplication(Vec2 vec, float scalar);
    static float magnitude(Vec2 vec);
    static Vec2 normalize(Vec2 vec);
    static float distance(Vec2 vec_a, Vec2 vec_b);
    static float inclination(Vec2 vec_b);
    static Vec2 rotate(Vec2 vec, float theta);
    static Vec2 opposite(Vec2 vec);
};

Vec2 operator+(Vec2 vec_a, Vec2 vec_b);
Vec2 operator-(Vec2 vec_a, Vec2 vec_b);
Vec2 operator-(Vec2 vec);
Vec2 operator*(Vec2 vec, float scalar);
Vec2 operator*(float scalar, Vec2 vec);
void operator+=(Vec2 &vec_a, Vec2 vec_b);
void operator-=(Vec2 &vec_a, Vec2 vec_b);
void operator*=(Vec2 &vec, float scalar);

struct Rect{
    float x;
    float y;
    float w;
    float h;
    Rect(float x = 0.0f, float y = 0.0f, float w = 0.0f, float h = 0.0f);
    static Rect sum(Rect &rect, Vec2 vec);
    static Vec2 center(Rect &rect);
    static float distance(Rect &rect_a, Rect &rect_b);
    static bool is_inside(Rect &rect, Vec2 vec);
};


Rect operator+(Rect &rect, Vec2 vec);
void operator+=(Rect &rect, Vec2 vec);



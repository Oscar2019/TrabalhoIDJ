#include "Geometry.h"

Vec2::Vec2(float x, float y) : x(x), y(y){

}

Vec2 Vec2::sum(Vec2 vec_a, Vec2 vec_b){
    return Vec2(vec_a.x + vec_b.x, vec_a.y + vec_b.y);
}

Vec2 Vec2::subtraction(Vec2 vec_a, Vec2 vec_b){
    return Vec2(vec_a.x - vec_b.x, vec_a.y - vec_b.y);
}

Vec2 Vec2::multiplication(Vec2 vec, float scalar){
    return Vec2(vec.x * scalar, vec.y * scalar);
}

float Vec2::magnitude(Vec2 vec){
    return std::hypot(vec.x, vec.y);
}

Vec2 Vec2::normalize(Vec2 vec){
    float magnitude = Vec2::magnitude(vec);
    return multiplication(vec, 1/magnitude);
}

float Vec2::distance(Vec2 vec_a, Vec2 vec_b){
    float delta_x = vec_a.x - vec_b.x;
    float delta_y = vec_a.y - vec_b.y;
    return std::hypot(delta_x, delta_y);
}

Vec2 Vec2::rotate(Vec2 vec, float theta){
    float x_novo = vec.x * std::cos(theta) + vec.y * std::sin(theta);
    float y_novo = vec.y * std::cos(theta) - vec.x * std::sin(theta);
    return Vec2(x_novo, y_novo);
}

Vec2 Vec2::opposite(Vec2 vec){
    return Vec2(-vec.x, -vec.y);
}

Vec2 operator+(Vec2 vec_a, Vec2 vec_b){
    return Vec2::sum(vec_a, vec_b);
}

Vec2 operator-(Vec2 vec_a, Vec2 vec_b){
    return Vec2::subtraction(vec_a, vec_b);
}

Vec2 operator-(Vec2 vec){
    return Vec2::opposite(vec);
}

Vec2 operator*(Vec2 vec, float scalar){
    return Vec2::multiplication(vec, scalar);
}

Vec2 operator*(float scalar, Vec2 vec){
    return Vec2::multiplication(vec, scalar);
}

void operator+=(Vec2 &vec_a, Vec2 vec_b){
    vec_a.x += vec_b.x;
    vec_a.y += vec_b.y;
}

void operator-=(Vec2 &vec_a, Vec2 vec_b){
    vec_a.x -= vec_b.x;
    vec_a.y -= vec_b.y;
}

void operator*=(Vec2 &vec, float scalar){
    vec.x *= scalar;
    vec.y *= scalar;
}

Rect::Rect(float x, float y, float w, float h) : x(x), y(y), w(w), h(h){

}

Rect Rect::sum(Rect &rect, Vec2 vec){
    return Rect(rect.x, rect.y, rect.w, rect.h);
}

Vec2 Rect::center(Rect &rect){
    return Vec2((rect.x + rect.w) / 2, (rect.y + rect.h) / 2);
}

float Rect::distance(Rect &rect_a, Rect &rect_b){
    Vec2 center_a = Rect::center(rect_a);
    Vec2 center_b = Rect::center(rect_b);
    return Vec2::distance(center_a, center_b);
}

bool Rect::is_inside(Rect &rect, Vec2 vec){
    return rect.x <= vec.x && vec.x <= rect.x + rect.w && rect.y <= vec.y && vec.y <= rect.y + rect.h;
}

Rect operator+(Rect &rect, Vec2 vec){
    return Rect::sum(rect, vec);    
}

void operator+=(Rect &rect, Vec2 vec){
    rect.x += vec.x;
    rect.y += vec.y; 
}


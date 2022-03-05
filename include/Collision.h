#include "Geometry.h"
#include <algorithm>
#include <cmath>


static inline bool IsColliding(Rect& a, Rect& b, float angleOfA, float angleOfB) {
    Vec2 A[] = { Vec2( a.x, a.y + a.h ),
                    Vec2( a.x + a.w, a.y + a.h ),
                    Vec2( a.x + a.w, a.y ),
                    Vec2( a.x, a.y )
                };
    Vec2 B[] = { Vec2( b.x, b.y + b.h ),
                    Vec2( b.x + b.w, b.y + b.h ),
                    Vec2( b.x + b.w, b.y ),
                    Vec2( b.x, b.y )
                };

    for (auto& v : A) {
        v = Vec2::rotate(v - Rect::center(a), angleOfA) + Rect::center(a);
    }

    for (auto& v : B) {
        v = Vec2::rotate(v - Rect::center(b), angleOfB) + Rect::center(b);
    }

    Vec2 axes[] = { Vec2::normalize(A[0] - A[1]), Vec2::normalize(A[1] - A[2]), Vec2::normalize(B[0] - B[1]), Vec2::normalize(B[1] - B[2]) };

    for (auto& axis : axes) {
        float P[4];

        for (int i = 0; i < 4; ++i) P[i] = Vec2::dot(A[i], axis);

        float minA = *std::min_element(P, P + 4);
        float maxA = *std::max_element(P, P + 4);

        for (int i = 0; i < 4; ++i) P[i] = Vec2::dot(B[i], axis);

        float minB = *std::min_element(P, P + 4);
        float maxB = *std::max_element(P, P + 4);

        if (maxA < minB || minA > maxB)
            return false;
    }

    return true;
}
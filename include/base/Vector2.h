#ifndef VECTOR2_H
#define VECTOR2_H


#include <iostream>
#include <math.h>



class Vector2
{

public:
    friend std::ostream& operator<<(std::ostream& os, const Vector2& vec);
    float x,y;

    Vector2();
    Vector2(float x, float y);

    Vector2& Add(const Vector2& vec);
    Vector2& Subtract(const Vector2& vec);
    Vector2& Multiply(const Vector2& vec);
    Vector2& Divide(const Vector2& vec);




    //Normalises vector2
    void Normalise();

    //Just a bunch of overloaded operators
    friend Vector2& operator+(const Vector2& v1, const Vector2& v2);
    friend Vector2& operator-(const Vector2& v1, const Vector2& v2);
    friend Vector2& operator*(const Vector2& v1, const Vector2& v2);
    friend Vector2& operator/(const Vector2& v1, const Vector2& v2);
    friend Vector2 operator/(const Vector2& v1, int v2);
    friend Vector2 operator/(int v2, const Vector2& v1);

    Vector2 operator*(const int& i);
    Vector2& operator+=(const Vector2& vec);
    Vector2& operator -=(const Vector2& vec);
    Vector2& operator *=(const Vector2& vec);
    Vector2& operator /=(const Vector2& vec);
    bool operator==(const Vector2& vec) const;
    bool operator!=(const Vector2& vec) const;


    [[nodiscard]] Vector2 getNormal() const {
        return {-y, x};
    }
    static Vector2 getNormal(const Vector2& vec1, const Vector2& vec2) {
        Vector2 direction = vec2 - vec1;
        return direction.getNormal();
    }
};


#endif //VECTOR2_H

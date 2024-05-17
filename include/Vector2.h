#ifndef VECTOR2_H
#define VECTOR2_H


#include <iostream>
#include <Math.h>



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
    friend Vector2& operator+(Vector2& v1, Vector2& v2);
    friend Vector2& operator-(Vector2& v1, Vector2& v2);
    friend Vector2& operator*(Vector2& v1, Vector2& v2);
    friend Vector2& operator/(Vector2& v1, Vector2& v2);
    friend Vector2 operator/(Vector2& v1, int v2);
    friend Vector2 operator/(int v2, Vector2& v1);

    Vector2 operator*(const int& i);
    Vector2& operator+=(const Vector2& vec);
    Vector2& operator -=(const Vector2& vec);
    Vector2& operator *=(const Vector2& vec);
    Vector2& operator /=(const Vector2& vec);
    bool operator==(const Vector2& vec) const;
};


#endif //VECTOR2_H

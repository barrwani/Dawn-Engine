#include "../include/Vector2.h"

Vector2::Vector2()
{
    x = 0.0f;
    y = 0.0f;
}

Vector2::Vector2(float x, float y)
{
    this->x = x;
    this->y = y;
}

Vector2 &Vector2::Add(const Vector2 &vec)
{
    this->x += vec.x;
    this->y += vec.y;

    return *this;
}


Vector2 &Vector2::Subtract(const Vector2 &vec)
{
    this->x -= vec.x;
    this->y -= vec.y;

    return *this;
}

Vector2 &Vector2::Multiply(const Vector2 &vec)
{
    this->x *= vec.x;
    this->y *= vec.y;

    return *this;
}

Vector2& Vector2::Divide(const Vector2 &vec)
{
    this->x /= vec.x;
    this->y /= vec.y;

    return *this;
}
void Vector2::Normalise()
{
    float length = sqrt((x * x) + (y * y));
    if (length!=0)
    {
        x /= length;
        y /= length;
    }
}

Vector2 &operator+(Vector2 &v1, Vector2 &v2)
{
    return v1.Add(v2);
}

Vector2 &operator-(Vector2 &v1, Vector2 &v2)
{
    return v1.Subtract(v2);
}

Vector2 &operator*(Vector2 &v1, Vector2 &v2)
{
    return v1.Multiply(v2);
}

Vector2 &operator/(Vector2 &v1, Vector2 &v2)
{
    return v1.Divide(v2);
}

Vector2 Vector2::operator*(const int& i)
{
    this->x *= i;
    this->y *= i;
    return *this;
}


Vector2 operator/(Vector2& v1, int v2)
{
    return {v1.x  / v2, v1.y / v2};
}

Vector2 operator/(int v2, Vector2& v1)
{
    return { v2 / v1.x, v2 / v1.y};
}

Vector2 &Vector2::operator-=(const Vector2 &vec)
{
    return this->Subtract(vec);
}

Vector2 &Vector2::operator*=(const Vector2 &vec)
{
    return this->Multiply(vec);
}

Vector2 &Vector2::operator/=(const Vector2 &vec)
{
    return this->Divide(vec);
}

Vector2 &Vector2::operator+=(const Vector2 &vec)
{
    return this->Add(vec);
}

std::ostream& operator<<(std::ostream& os, const Vector2& vec)
{
    os << "(" << vec.x << "," << vec.y << ")";
    return os;
}

bool Vector2::operator==(const Vector2 &vec) const
{
    return (x == vec.x && y == vec.y);
}



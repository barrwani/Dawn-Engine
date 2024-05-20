#include "../../include/base/Vector2.h"

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

Vector2 &operator+(const Vector2 &v1, const Vector2 &v2)
{
    Vector2 result = v1;
    return result.Add(v2);
}

Vector2 &operator-(const Vector2 &v1, const Vector2 &v2)
{
    Vector2 result = v1;
    return result.Subtract(v2);
}

Vector2 &operator*(const Vector2 &v1, const Vector2 &v2)
{
    Vector2 result = v1;
    return result.Multiply(v2);
}

Vector2 &operator/(const Vector2 &v1, const Vector2 &v2)
{
    Vector2 result = v1;
    return result.Divide(v2);
}

Vector2 Vector2::operator*(const int& i)
{
    this->x *= i;
    this->y *= i;
    return *this;
}

bool Vector2::operator!=(const Vector2 &vec) const
{
    return (x != vec.x || y != vec.y);
}


Vector2 operator/(const Vector2& v1, const int v2)
{
    return {v1.x  / v2, v1.y / v2};
}

Vector2 operator/(const int v2, const Vector2& v1)
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



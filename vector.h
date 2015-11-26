#ifndef VECTOR_H
#define VECTOR_H

#include "main.h"
#include <math.h>

#define temp template <typename tmp>

temp class Vector
{
public:
    Vector(){};
    Vector(tmp, tmp);

    Vector operator=(Vector);
    Vector operator+(Vector);
    Vector operator-(Vector);
    Vector operator*(double);
    Vector operator/(double);
    void Set(tmp, tmp);
    double GetLenght(); // Длина вектора

    void SetNormal(); // Нормализация вектора

    tmp x;
    tmp y;
};


temp Vector<tmp>::Vector(tmp _x, tmp _y)
{
    x = _x;
    y = _y;
}
temp Vector<tmp> Vector<tmp>::operator=(Vector vector)
{
    return Vector(x = vector.x, y = vector.y);
}


temp Vector<tmp> Vector<tmp>::operator+(Vector vector)
{
    return Vector(x + vector.x, y + vector.y);
}

temp Vector<tmp> Vector<tmp>::operator-(Vector vector)
{
    return Vector(x - vector.x, y - vector.y);
}

temp Vector<tmp> Vector<tmp>::operator*(double scale)
{
    return Vector(x * scale, y * scale);
}

temp Vector<tmp> Vector<tmp>::operator/(double scale)
{
    return Vector(x / scale, y / scale);
}

temp void Vector<tmp>::Set(tmp _x, tmp _y)
{
    x = _x;
    y = _y;
}

temp double Vector<tmp>::GetLenght()
{
    return sqrt(pow(x, 2.0) + pow(y, 2.0));
}

temp void Vector<tmp>::SetNormal()
{

    if(this->GetLenght() != 0.0)
    {
        double lenght = this->GetLenght();
        x /= lenght;
        y /= lenght;
    }
}



#endif // VECTOR_H


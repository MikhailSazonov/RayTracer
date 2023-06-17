#pragma once

#include "Matrix.hpp"
#include "Vector3D.hpp"

#include <ostream>

namespace Math
{
    //! @brief The class that represents a point in 3D space
    class Point3D : public Operators::Matrix<4, 1>
    {
        friend class Vector3D;

    public:
        Point3D() = default;

        Point3D(double x, double y, double z);

        Point3D(const Point3D &);

        Point3D(Point3D &&);

        Point3D(const Operators::Matrix<4, 1> &);

        Point3D &operator=(const Point3D &);

        Point3D &operator=(Point3D &&);

        Point3D &operator+=(const Vector3D &);

        Point3D operator+(const Vector3D &) const;

        Point3D &operator-=(const Vector3D &);

        Point3D operator-(const Vector3D &) const;

        // result is vector
        Vector3D operator-(const Point3D &) const;

        // bool
        bool operator==(const Point3D &other) const;

        bool operator!=(const Point3D &other) const;

    public:
        double &x_{data_[0][0]};
        double &y_{data_[1][0]};
        double &z_{data_[2][0]};

    private:
        double &w_{data_[3][0]};
    };

    std::ostream &operator<<(std::ostream &stream, const Point3D &vec);

}


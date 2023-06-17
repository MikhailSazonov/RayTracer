#pragma once

#include "Matrix.hpp"
#include "BasicsFwd.hpp"

#include <ostream>
#include <cmath>

namespace Math
{
    //! @brief The class that represents a vector in 3D space
    class Vector3D : public Operators::Matrix<4, 1>
    {
        friend class Point3D;

    public:
        Vector3D() = default;

        Vector3D(double x, double y, double z);

        Vector3D(const Vector3D &);

        Vector3D(Vector3D &&);

        Vector3D(const Operators::Matrix<4, 1> &);

        Vector3D &operator=(const Vector3D &);

        Vector3D &operator=(Vector3D &&);

        // arithmetical operators
        Vector3D &operator+=(const Vector3D &);

        Vector3D operator+(const Vector3D &) const;

        Vector3D &operator-=(const Vector3D &);

        Vector3D operator-(const Vector3D &) const;

        Vector3D &operator*=(const Vector3D &);

        Vector3D operator*(const Vector3D &) const;

        Vector3D &operator/=(const Vector3D &);

        Vector3D operator/(const Vector3D &) const;

        Vector3D &operator*=(double);

        Vector3D operator*(double) const;

        Vector3D &operator/=(double);

        Vector3D operator/(double) const;

        double dot(const Vector3D &) const;

        inline double length() const
        {
            return sqrt(dot(*this));
        }

        void normalize();

        //! result is point
        //! defined in Point3D.cpp
        Point3D operator+(const Point3D &) const;

        /** @defgroup bool_opps Boolean operators
         * @{
         */
        bool operator==(const Vector3D &other) const;

        bool operator!=(const Vector3D &other) const;
        /** @} */

    public:
        double &x_{data_[0][0]};
        double &y_{data_[1][0]};
        double &z_{data_[2][0]};

    private:
        double &w_{data_[3][0]};
    };

    std::ostream &operator<<(std::ostream &stream, const Vector3D &vec);

    inline double cos(const Vector3D& left, const Vector3D& right) {
        return left.dot(right) / (left.length() * right.length());
    }

}


#include "Point3D.hpp"

namespace Math {
    Point3D::Point3D(double x, double y, double z)
        : Operators::Matrix<4, 1>{x, y, z, 1} {}

    Point3D::Point3D(const Matrix<4, 1>& other)
        : Operators::Matrix<4, 1>(other) {
            // assert(other[3][0] == 1);
        }

    Point3D::Point3D(const Point3D& other)
        : Operators::Matrix<4, 1>(matrixCast(other)) {}

    Point3D::Point3D(Point3D&& other)
        : Operators::Matrix<4, 1>(matrixCast(other)) {}

    Point3D& Point3D::operator=(const Point3D& other) {
        matrixCast(*this) = matrixCast(other);
        return *this;
    }

    Point3D& Point3D::operator=(Point3D&& other) {
        matrixCast(*this) = matrixCast(other);
        return *this;
    }

    Point3D& Point3D::operator+=(const Vector3D& other) {
        matrixCast(*this) += matrixCast(other);
        return *this;
    }

    Point3D Point3D::operator+(const Vector3D& other) const {
        return Point3D(matrixCast(*this) + matrixCast(other));
    }

    Point3D& Point3D::operator-=(const Vector3D& other) {
        matrixCast(*this) -= matrixCast(other);
        return *this;
    }

    Point3D Point3D::operator-(const Vector3D& other) const {
        return Point3D(matrixCast(*this) - matrixCast(other));
    }

    Vector3D Point3D::operator-(const Point3D& other) const {
        Vector3D result(matrixCast(*this));
        matrixCast(result) -= matrixCast(other);
        return result;
    }

    // NB: Vector3D func definition
    Point3D Vector3D::operator+(const Point3D& other) const {
        Point3D result(matrixCast(*this));
        matrixCast(result) += matrixCast(other);
        return result;
    }

    bool Point3D::operator==(const Point3D& other) const {
        return matrixCast(*this) == matrixCast(other);
    }

    bool Point3D::operator!=(const Point3D& other) const {
        return matrixCast(*this) != matrixCast(other);
    }

    std::ostream& operator<<(std::ostream& stream, const Point3D& point) {
        stream << "Point with \nx\ty\tz\n" <<
            point.x_ << '\t' << point.y_ << '\t' << point.z_ << '\n';
        return stream;
    }
}

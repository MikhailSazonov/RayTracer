#include "Vector3D.hpp"

namespace Math {
    void Vector3D::normalize() {
        double len = length();
        if (std::abs(len) >= 1e-9) {
            x_ /= len;
            y_ /= len;
            z_ /= len;
        }
    }

    Vector3D::Vector3D(double x, double y, double z)
        : Operators::Matrix<4, 1>{x, y, z, 0} {
        }

    Vector3D::Vector3D(const Operators::Matrix<4, 1>& other)
        : Operators::Matrix<4, 1>(other) {
        }

    Vector3D::Vector3D(const Vector3D& other)
        : Operators::Matrix<4, 1>(matrixCast(other)) {}

    Vector3D::Vector3D(Vector3D&& other)
        : Operators::Matrix<4, 1>(matrixCast(other)) {}

    Vector3D& Vector3D::operator=(const Vector3D& other) {
        matrixCast(*this) = matrixCast(other);
        return *this;
    }

    Vector3D& Vector3D::operator=(Vector3D&& other) {
        matrixCast(*this) = matrixCast(other);
        return *this;
    }

    // operators
    Vector3D& Vector3D::operator+=(const Vector3D& other) {
        matrixCast(*this) += matrixCast(other);
        return *this;
    }

    Vector3D Vector3D::operator+(const Vector3D& other) const {
        return Vector3D(matrixCast(*this) + matrixCast(other));
    }

    Vector3D& Vector3D::operator-=(const Vector3D& other) {
        matrixCast(*this) -= matrixCast(other);
        return *this;
    }

    Vector3D Vector3D::operator-(const Vector3D& other) const {
        return Vector3D(matrixCast(*this) - matrixCast(other));
    }

    Vector3D& Vector3D::operator*=(const Vector3D& other) {
        matrixCast(*this) ^= matrixCast(other);
        return *this;
    }

    Vector3D Vector3D::operator*(const Vector3D& other) const {
        return Vector3D(matrixCast(*this) ^ matrixCast(other));
    }

    // NB: w_ is 0
    Vector3D& Vector3D::operator/=(const Vector3D& other) {
        x_ /= other.x_;
        y_ /= other.y_;
        z_ /= other.z_;
        return *this;
    }

    Vector3D Vector3D::operator/(const Vector3D& other) const {
        auto result = *this;
        result /= other;
        return result;
    }

    Vector3D& Vector3D::operator*=(double value) {
        matrixCast(*this) *= value;
        return *this;
    }

    Vector3D Vector3D::operator*(double value) const {
        return Vector3D(matrixCast(*this) * value);
    }

    Vector3D& Vector3D::operator/=(double value) {
        matrixCast(*this) /= value;
        return *this;
    }

    Vector3D Vector3D::operator/(double value) const {
        return Vector3D(matrixCast(*this) / value);
    }

    bool Vector3D::operator==(const Vector3D& other) const {
        return matrixCast(*this) == matrixCast(other);
    }

    bool Vector3D::operator!=(const Vector3D& other) const {
        return matrixCast(*this) != matrixCast(other);
    }

    double Vector3D::dot(const Vector3D& other) const {
        return x_ * other.x_ + y_ * other.y_ + z_ * other.z_;
    }

    std::ostream& operator<<(std::ostream& stream, const Vector3D& vec) {
        stream << "Vector with \nx\ty\tz\n" <<
            vec.x_ << '\t' << vec.y_ << '\t' << vec.z_ << '\n';
        return stream;
    }

}

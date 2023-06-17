#pragma once

#include <cstddef>
#include <initializer_list>
#include <cassert>
#include <memory>
#include <iostream>
#include <fstream>

namespace Math::Operators
{

    class MatrixBase
    {
    };

    struct MatrixInfo
    {
        MatrixBase &base;
        size_t N;
        size_t M;
    };

    /**
     * @brief The matrix class.
     *
     * Template class that represents a matrix of size N x M
     * it contains all the basic operations that can be done on a matrix
     *
     * @param N The number of rows
     * @param M The number of columns
     * @param V The type of the values in the matrix (default: double)
     */
    template <size_t N, size_t M, typename V = double>
    class Matrix : public MatrixBase
    {
    public:
        //! @brief The default constructor. calls the default constructor of V
        Matrix()
        {
            for (size_t i = 0; i < N; ++i)
            {
                for (size_t j = 0; j < M; ++j)
                {
                    data_[i][j] = V();
                }
            }
        }

        /**
         * @brief Construct a new Matrix object
         *
         * from a list of values
         *
         * @param l The list of values
         */
        Matrix(std::initializer_list<V> l)
        {
            assert(l.size() == N * M);
            auto iter = l.begin();
            for (size_t i = 0; i < N; ++i)
            {
                for (size_t j = 0; j < M; ++j)
                {
                    data_[i][j] = *iter++;
                }
            }
        }

        /**
         * @brief Construct a new Matrix object
         *
         * from a list of list of values
         *
         * @param l The list of list of values
         */
        Matrix(std::initializer_list<std::initializer_list<V>> l)
        {
            assert(l.size() == N);
            auto iter = l.begin();
            for (size_t i = 0; i < N; ++i)
            {
                assert(iter->size() == M);
                auto inner_iter = iter->begin();
                for (size_t j = 0; j < M; ++j)
                {
                    data_[i][j] = *inner_iter++;
                }
                ++iter;
            }
        }

        //! @brief rerutns the data at the index idx
        V *operator[](size_t idx)
        {
            return data_[idx];
        }

        //! @brief rerutns the data at the index idx const
        const V *operator[](size_t idx) const
        {
            return data_[idx];
        }

        /**
         * @brief matrix sum
         *
         * @param other The other matrix
         *
         * @return The result of the sum
         */
        Matrix<N, M> &operator+=(const Matrix<N, M> &other)
        {
            for (size_t i = 0; i < N; ++i)
            {
                for (size_t j = 0; j < M; ++j)
                {
                    data_[i][j] += other[i][j];
                }
            }
            return *this;
        }

        /**
         * @brief matrix substraction
         *
         * @param other The other matrix
         *
         * @return The result of the substraction
         */
        Matrix<N, M> &operator-=(const Matrix<N, M> &other)
        {
            for (size_t i = 0; i < N; ++i)
            {
                for (size_t j = 0; j < M; ++j)
                {
                    data_[i][j] -= other[i][j];
                }
            }
            return *this;
        }

        /**
         * @brief matrix multiplication
         *
         * @param other The other matrix
         *
         * @return The result of the multiplication
         */
        Matrix<N, M> &operator^=(const Matrix<N, M> &other)
        {
            for (size_t i = 0; i < N; ++i)
            {
                for (size_t j = 0; j < M; ++j)
                {
                    data_[i][j] *= other[i][j];
                }
            }
            return *this;
        }

        /**
         * @brief matrix division
         *
         * @param other The other matrix
         *
         * @return The result of the division
         */
        Matrix<N, M> &operator%=(const Matrix<N, M> &other)
        {
            for (size_t i = 0; i < N; ++i)
            {
                for (size_t j = 0; j < M; ++j)
                {
                    data_[i][j] /= other[i][j];
                }
            }
            return *this;
        }

        Matrix<N, M> &operator*=(double value)
        {
            for (size_t i = 0; i < N; ++i)
            {
                for (size_t j = 0; j < M; ++j)
                {
                    data_[i][j] *= value;
                }
            }
            return *this;
        }

        Matrix<N, M> &operator/=(double value)
        {
            for (size_t i = 0; i < N; ++i)
            {
                for (size_t j = 0; j < M; ++j)
                {
                    data_[i][j] /= value;
                }
            }
            return *this;
        }

        Matrix<N, M> operator+(const Matrix<N, M> &other) const
        {
            auto result = *this;
            result += other;
            return result;
        }

        Matrix<N, M> operator-(const Matrix<N, M> &other) const
        {
            auto result = *this;
            result -= other;
            return result;
        }

        Matrix<N, M> operator^(const Matrix<N, M> &other) const
        {
            auto result = *this;
            result ^= other;
            return result;
        }

        Matrix<N, M> operator%(const Matrix<N, M> &other) const
        {
            auto result = *this;
            result %= other;
            return result;
        }

        Matrix<N, M> operator*(double value) const
        {
            auto result = *this;
            result *= value;
            return result;
        }

        Matrix<N, M> operator/(double value) const
        {
            auto result = *this;
            result /= value;
            return result;
        }

        Matrix<M, N> T()
        {
            Matrix<M, N> result;
            for (size_t i = 0; i < N; ++i)
            {
                for (size_t j = 0; j < M; ++j)
                {
                    result[j][i] = data_[i][j];
                }
            }
            return result;
        }

        template <size_t T>
        Matrix<N, T> operator*(const Matrix<M, T> &other) const
        {
            auto result = Matrix<N, T>();
            for (size_t i = 0; i < N; ++i)
            {
                for (size_t j = 0; j < T; ++j)
                {
                    for (size_t k = 0; k < M; ++k)
                    {
                        result[i][j] += data_[i][k] * other[k][j];
                    }
                }
            }
            return result;
        }

        Matrix<N, M> &operator*=(const Matrix<M, M> &other)
        {
            auto result = Matrix<N, M>();
            result = *this * other;
            *this = result;
            return *this;
        }

        // bool operators
        bool operator==(const Matrix<N, M> &other) const
        {
            for (size_t i = 0; i < N; ++i)
            {
                for (size_t j = 0; j < M; ++j)
                {
                    if (data_[i][j] != other.data_[i][j])
                    {
                        return false;
                    }
                }
            }
            return true;
        }

        bool operator!=(const Matrix<N, M> &other) const
        {
            return !(*this == other);
        }

        inline Matrix<N, M> &matrixCast(Matrix<N, M> &obj) const
        {
            return obj;
        }

        inline const Matrix<N, M> &matrixCast(const Matrix<N, M> &obj) const
        {
            return obj;
        }

    protected:
        V data_[N][M];
    };

    template <size_t U>
    Matrix<U, U> Id()
    {
        Matrix<U, U> result;
        for (size_t i = 0; i < U; ++i)
        {
            result[i][i] = 1.;
        }
        return result;
    }

    template <size_t N, size_t M>
    std::ostream &operator<<(std::ostream &stream, const Matrix<N, M> &mat)
    {
        std::cout << "Matrix " << N << "x" << M << ":\n";
        for (size_t i = 0; i < N; ++i)
        {
            for (size_t j = 0; j < M; ++j)
            {
                std::cout << mat[i][j] << "\t";
            }
            std::cout << '\n';
        }
        return stream;
    }

}


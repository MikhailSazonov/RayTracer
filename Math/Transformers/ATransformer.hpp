#pragma once

#include <Basics/Matrix.hpp>
#include <Solutions/MatrixInv.hpp>

namespace Math::Operators
{
    class ATransformer
    {
    protected:
        ATransformer(const Matrix<4, 4> &);

        virtual void setInvOperator(const std::vector<double> &);

    public:
        template <size_t N, size_t M>
        void transform(Matrix<N, M> &matrix)
        {
            matrix = operator_ * matrix;
        }

        inline const Matrix<4, 4> &getOp() const
        {
            return operator_;
        }

        inline const Matrix<4, 4> &getInvOp() const
        {
            return inv_operator_;
        }

        ATransformer &operator*=(const ATransformer &next);

    protected:
        Matrix<4, 4> operator_;
        Matrix<4, 4> inv_operator_;
    };

}


#ifndef LIBTENSOR_TOD_MULT1_H
#define LIBTENSOR_TOD_MULT1_H

#include <libtensor/timings.h>
#include <libtensor/core/noncopyable.h>
#include <libtensor/core/scalar_transf_double.h>
#include <libtensor/core/tensor_transf.h>
#include "dense_tensor_i.h"

namespace libtensor {


/** \brief Element-wise multiplication and division
    \tparam N Tensor order.

    The operation multiplies or divides two tensors element by element.

    \f[ a_i = a_i b_i \qquad a_i = \frac{a_i}{b_i} \f]
    \f[ a_i = a_i + c a_i b_i \qquad a_i = a_i + c \frac{a_i}{b_i} \f]

    The numerator and the result are the same tensor. Both tensors must
    have the same dimensions or an exception will be thrown. When
    the division is requested, no checks are performed to ensure that
    the denominator is non-zero.

    \ingroup libtensor_dense_tensor_tod
 **/
template<size_t N>
class tod_mult1 : public timings< tod_mult1<N> >, public noncopyable {
public:
    static const char *k_clazz; //!< Class name

private:
    dense_tensor_rd_i<N, double> &m_tb; //!< Second argument
    permutation<N> m_permb;
    bool m_recip; //!< Reciprocal (multiplication by 1/bi)
    double m_c; //!< Scaling coefficient

public:
    /** \brief Creates the operation
        \param tb Second argument.
        \param recip \c false (default) sets up multiplication and
            \c true sets up element-wise division.
        \param c Scalar transformation
     **/
    tod_mult1(dense_tensor_rd_i<N, double> &tb,
            const tensor_transf<N, double> &trb, bool recip = false,
            const scalar_transf<double> &c = scalar_transf<double>());

    /** \brief Creates the operation
        \param tb Second argument.
        \param recip \c false (default) sets up multiplication and
            \c true sets up element-wise division.
        \param c Coefficient
     **/
    tod_mult1(dense_tensor_rd_i<N, double> &tb,
            bool recip = false, double c = 1.0) :
        m_tb(tb), m_recip(recip), m_c(c)
    { }

    /** \brief Creates the operation
        \param tb Second argument.
        \param p Permutation of argument
        \param recip \c false (default) sets up multiplication and
            \c true sets up element-wise division.
        \param c Coefficient
     **/
    tod_mult1(dense_tensor_rd_i<N, double> &tb, const permutation<N> &p,
        bool recip = false, double c = 1.0) :
        m_tb(tb), m_permb(p), m_recip(recip), m_c(c)
    { }

    /** \brief Performs the operation, replaces the output.
        \param zero If true, replace A, otherwise add to A
        \param ta Tensor A.
     **/
    void perform(bool zero, dense_tensor_wr_i<N, double> &ta);
};


} // namespace libtensor

#endif // LIBTENSOR_TOD_MULT1_H

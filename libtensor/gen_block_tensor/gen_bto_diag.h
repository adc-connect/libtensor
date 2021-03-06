#ifndef LIBTENSOR_GEN_BTO_DIAG_H
#define LIBTENSOR_GEN_BTO_DIAG_H

#include <libtensor/timings.h>
#include <libtensor/core/mask.h>
#include <libtensor/core/noncopyable.h>
#include <libtensor/core/symmetry.h>
#include <libtensor/core/tensor_transf.h>
#include "assignment_schedule.h"
#include "gen_block_stream_i.h"
#include "gen_block_tensor_i.h"

namespace libtensor {


/** \brief Extracts a general diagonal from a block %tensor
    \tparam N Tensor order.
    \tparam M Result tensor order.
    \tparam Traits Block tensor operation traits.
    \tparam Timed Timed implementation.

    This block tensor operation extracts a general diagonal of a block tensor.

    The traits class has to provide definitions for
    - \c element_type -- Type of data elements
    - \c bti_traits -- Type of block tensor interface traits class
    - \c template temp_block_type<N>::type -- Type of temporary tensor block
    - \c template to_diag_type<N, M>::type -- Type of tensor operation to_diag

    \ingroup libtensor_gen_bto
 **/
template<size_t N, size_t M, typename Traits, typename Timed>
class gen_bto_diag : public timings<Timed>, public noncopyable {
public:
    static const char *k_clazz; //!< Class name
    enum {
        NA = N, //!< Order of the argument
        NB = M //!< Order of the result
    };

public:
    //! Type of tensor elements
    typedef typename Traits::element_type element_type;

    //! Block tensor interface traits
    typedef typename Traits::bti_traits bti_traits;

    //! Type of read-only block
    typedef typename
            bti_traits::template rd_block_type<N>::type rd_block_type;

    //! Type of write-only block
    typedef typename
            bti_traits::template wr_block_type<M>::type wr_block_type;

    typedef tensor_transf<M, element_type> tensor_transf_type;

private:
    gen_block_tensor_rd_i<NA, bti_traits> &m_bta; //!< Input block %tensor
    sequence<NA, size_t> m_msk; //!< Diagonal %mask
    tensor_transf_type m_tr; //!< Tensor transformation
    block_index_space<NB> m_bis; //!< Block %index space of the result
    symmetry<NB, element_type> m_sym; //!< Symmetry of the result
    assignment_schedule<NB, element_type> m_sch; //!< Assignment schedule

public:
    //!    \name Construction and destruction
    //@{

    /** \brief Initializes the diagonal extraction operation
        \param bta Input block %tensor
        \param msk Mask which specifies the indexes to take the diagonal
        \param tr Transformation to be applied before adding to the resulr
     **/
    gen_bto_diag(
            gen_block_tensor_rd_i<N, bti_traits> &bta,
            const sequence<N, size_t> &msk,
            const tensor_transf_type &tr = tensor_transf_type());

    //@}

    /** \brief Returns the block index space of the result
     **/
    const block_index_space<NB> &get_bis() const {
        return m_bis;
    }

    /** \brief Returns the symmetry of the result
     **/
    const symmetry<NB, element_type> &get_symmetry() const {
        return m_sym;
    }

    /** \brief Returns the list of canonical non-zero blocks of the result
     **/
    const assignment_schedule<NB, element_type> &get_schedule() const {
        return m_sch;
    }

    /** \brief Computes and writes the blocks of the result to an output stream
        \param out Output stream.
     **/
    void perform(gen_block_stream_i<NB, bti_traits> &out);

    /** \brief Computes one block of the result
        \param zero Zero target block first
        \param blkb Target block
        \param ib Index of target block
        \param trb Tensor transformation
     **/
    void compute_block(
        bool zero,
        const index<NB> &ib,
        const tensor_transf_type &trb,
        wr_block_type &blkb);

    /** \brief Same as compute_block(), except it doesn't run a timer
     **/
    void compute_block_untimed(
        bool zero,
        const index<NB> &ib,
        const tensor_transf_type &trb,
        wr_block_type &blkb);

private:
    /** \brief Forms the block %index space of the output or throws an
            exception if the input is incorrect.
     **/
    static block_index_space<M> mk_bis(const block_index_space<NA> &bis,
            const sequence<NA, size_t> &msk);

    /** \brief Sets up the symmetry of the operation result
     **/
    void make_symmetry();

    /** \brief Sets up the assignment schedule for the operation.
     **/
    void make_schedule();
};


} // namespace libtensor

#endif // LIBTENSOR_GEN_BTO_DIAG_H

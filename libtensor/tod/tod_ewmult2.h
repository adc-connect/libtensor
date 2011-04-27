#ifndef LIBTENSOR_TOD_EWMULT2_H
#define LIBTENSOR_TOD_EWMULT2_H

#include "../defs.h"
#include "../timings.h"
#include "../core/tensor_i.h"
#include "loop_list_elem.h"
#include "tod_additive.h"
#include "bad_dimensions.h"

namespace libtensor {


/**	\brief General element-wise multiplication and division of two tensors
	\tparam N First argument's %tensor order less the number of shared
		indexes.
	\tparam M Second argument's %tensor order less the number of shared
		indexes.
	\tparam K Number of shared indexes.

	This operation computes the generalized elementwise (Hadamard) product
	of two tensors. It takes two arguments and performs the following
	$$ c_{ij\cdots mn\cdots pq\cdots} =
		a_{ij\cdots pq\cdots} b_{mn\cdots pq\cdots} $$
	Both arguments have $K > 0$ shared indexes $pq\cdots$. In addition,
	the first argument has $N \ge 0$ and the second argument has $M \ge 0$
	extra indexes that are not subject to the operation. The result
	has $N+M+K$ indexes. $N$, $M$ and $K$ are the template parameters of
	the operation.

	The arguments A and B may be given in a permuted form. In this case
	permutations should be specified upon construction. The permutations for
	A and B rearrange the indexes to the standard form: $ij\cdots pq\cdots$
	and $mn\cdots pq\cdots$, respectively. The permutation for C transforms
	the standard index ordering $ij\cdots mn\cdots pq\cdots$ to the desired
	form.

	The output tensor C specified upon calling perform() must agree in
	dimensions with the input tensors A and B taking all permutations into
	account. A and B themselves must agree in the dimensions of the shared
	indexes. Any disagreement will raise bad_dimensions.

	\sa tod_contract2

	\ingroup libtensor_tod
 **/
template<size_t N, size_t M, size_t K>
class tod_ewmult2 :
	public tod_additive<N + M + K>,
	public timings< tod_ewmult2<N, M, K> > {

public:
	static const char *k_clazz; //!< Class name

public:
	static const size_t k_ordera = N + K;
	static const size_t k_orderb = M + K;
	static const size_t k_orderc = N + M + K;

private:
	tensor_i<k_ordera, double> &m_ta; //!< First argument (A)
	permutation<k_ordera> m_perma; //!< Permutation of first argument (A)
	tensor_i<k_orderb, double> &m_tb; //!< Second argument (B)
	permutation<k_orderb> m_permb; //!< Permutation of second argument (B)
	permutation<k_orderc> m_permc; //!< Permutation of result (C)
	double m_d; //!< Scaling coefficient
	dimensions<k_orderc> m_dimsc; //!< Result dimensions

public:
	//!	\name Construction and destruction
	//@{

	/**	\brief Initializes the operation
		\param ta First argument (A).
		\param tb Second argument (B).
		\param recip Reciprocal flag.
		\param d Scaling coefficient.
	 **/
	tod_ewmult2(tensor_i<k_ordera, double> &ta,
		tensor_i<k_orderb, double> &tb, double d = 1.0);

	/**	\brief Initializes the operation
		\param ta First argument (A).
		\param perma Permutation of A.
		\param tb Second argument (B).
		\param permb Permutation of B.
		\param permc Permutation of result (C).
		\param recip Reciprocal flag.
		\param d Scaling coefficient.
	 **/
	tod_ewmult2(tensor_i<k_ordera, double> &ta,
		const permutation<k_ordera> &perma,
		tensor_i<k_orderb, double> &tb,
		const permutation<k_orderb> &permb,
		const permutation<k_orderc> &permc, double d = 1.0);

	/**	\brief Virtual destructor
	 **/
	virtual ~tod_ewmult2();

	//@}


	//!	\name Implementation of tod_additive<N + M + K>
	//@{

	virtual void prefetch();
	virtual void perform(tensor_i<k_orderc, double> &tc);
	virtual void perform(tensor_i<k_orderc, double> &tc, double d);

	//@}

private:
	/**	\brief Computes the dimensions of the result tensor
	 **/
	static dimensions<N + M + K> make_dimsc(
		const dimensions<k_ordera> &dimsa,
		const permutation<k_ordera> &perma,
		const dimensions<k_orderb> &dimsb,
		const permutation<k_orderb> &permb,
		const permutation<k_orderc> &permc);

	/**	\brief Computes the result
	 **/
	void do_perform(tensor_i<k_orderc, double> &tc, bool zero, double d);

};


} // namespace libtensor

#ifndef LIBTENSOR_INSTANTIATE_TEMPLATES
#include "tod_ewmult2_impl.h"
#endif // LIBTENSOR_INSTANTIATE_TEMPLATES

#endif // LIBTENSOR_TOD_EWMULT2_H

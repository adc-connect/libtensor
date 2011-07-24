#ifndef LIBTENSOR_SO_MERGE_IMPL_PART_H
#define LIBTENSOR_SO_MERGE_IMPL_PART_H

#include <list>
#include "../../core/block_index_subspace_builder.h"
#include "../../defs.h"
#include "../../exception.h"
#include "../se_part.h"
#include "../so_merge.h"
#include "../symmetry_element_set_adapter.h"
#include "../symmetry_operation_impl_base.h"

namespace libtensor {


/**	\brief Implementation of so_merge<N, M, T> for se_part<N, T>
	\tparam N Tensor order.
	\tparam T Tensor element type.

	The implementation merges the masked dimensions together.

	\ingroup libtensor_symmetry
 **/
template<size_t N, size_t M, size_t K, typename T>
class symmetry_operation_impl< so_merge<N, M, K, T>, se_part<N - M + K, T> > :
public
symmetry_operation_impl_base< so_merge<N, M, K, T>, se_part<N - M + K, T> > {

public:
	static const char *k_clazz; //!< Class name

public:
	typedef so_merge<N, M, T> operation_t;
	typedef se_part<N - M + K, T> element_t;
	typedef symmetry_operation_params<operation_t>
		symmetry_operation_params_t;

protected:
	virtual void do_perform(symmetry_operation_params_t &params) const;

};


template<size_t N, size_t M, size_t K, typename T>
const char *
symmetry_operation_impl<so_merge<N, M, K, T>, se_part<N - M + K, T> >::k_clazz =
	"symmetry_operation_impl< so_merge<N, M, K, T>, se_part<N - M + K, T> >";


template<size_t N, size_t M, size_t K, typename T>
void
symmetry_operation_impl< so_merge<N, M, K, T>,
se_part<N - M + K, T> >::do_perform(
        symmetry_operation_params_t &params) const {

	static const char *method =
		"do_perform(symmetry_operation_params_t&)";

	//	Adapter type for the input group
	//
	typedef se_part<N, T> el1_t;
	typedef symmetry_element_set_adapter<N, T, el1_t> adapter1_t;
	typedef symmetry_element_set_adapter<N - M + K, T, element_t> adapter_t;

	//	Verify that the projection mask is correct
    size_t nm = 0;
    mask<N> tm;
    for (register size_t k = 0; k < K; k++) {
	    const mask<N> &m = params.msk[k];
	    for(size_t i = 0; i < N; i++) {
	        if (m[i]) continue;

	        if (tm[i]) {
	            throw bad_parameter(g_ns, k_clazz, method, __FILE__, __LINE__,
	                    "params.msk[k]");
	        }
	        tm[i] = true;
	        nm++;
	    }
	}
	if(nm != M) {
		throw bad_parameter(g_ns, k_clazz, method, __FILE__, __LINE__,
			"params.msk");
	}

    params.grp2.clear();
    if (params.grp1.is_empty()) return;

	// Determine index map N -> N - M + K
	sequence<N, size_t> map;
	for (size_t i = 0, j = 0; i < N; i++) {
	    if (tm[i]) {
	        size_t k = 0;
	        for ( ; k < K; k++) { if (params.msk[k][i]) break; }

	        const mask<N> &m = params.msk[k];
	        for (k = 0; k < i; k++) { if (m[k]) break; }
	        if (k != i) { map[i] = map[k]; continue; }
	    }

	    map[i] = j++;
	}

	combine_part<N, T> cp(params.grp1);
	el1_t el1(cp.get_bis(), cp.get_pdims());
	cp.perform(el);

	const dimensions<N> &pdims1 = el1.get_pdims();

	// Create result parition dimensions
	index<N - M + K> ia, ib;
	for (size_t i = 0; i < N; i++) {
#ifdef LIBTENSOR_DEBUG
	    if (ib[map[i] != 0 && ib[map[i]] != pdims1[i] - 1) {
	        throw bad_symmetry(g_ns, k_clazz, method,
	                __FILE__, __LINE__, "pdims.");
	    }
#endif
	    ib[map[i]] = pdims[i] - 1;
	}
	dimensions<N - M + K> pdims2(index_range<N - M + K>(ia, ib));

	element_t el2(params.bis, pdims2);

    // merge the partitions
	abs_index<N - M + K> ai(pdims2);
	do {

	    const index<N - M + K> &i2a = ai.get_index();
	    index<N> i1a;
	    for (size_t i = 0; i < N; i++) i1a[i] = i2a[map[i]];

	    if (el1.is_forbidden(i1a)) {
	        el2.mark_forbidden(i2a);
	        continue;
	    }

	    bool found = false;
	    index<N> i1b = el1.get_direct_map(i1a);
	    while (! found && i1a < i1b) {
	        // Check if i1b can be converted into a proper result index
	        size_t i = 0;
	        for (; i < N; i++) {
	            if (! tm[i]) continue;

	            size_t j = i + 1;
	            for (; j < N; i++) {
	                if (map[i] != map[j]) continue;

	                if (i1b[i] != i1b[j]) break;
	            }
	            if (j != N) break;
	        }
	        if (i == N) found = true;
	        else i1b = el1.get_direct_map(i1b);
	    }

	    if (! found) continue;

	    index<N - M + K> i2b;
	    for (size_t i = 0; i < N; i++) i2b[map[i]] = i1b[i];

	    el2.add_map(i2a, i2b, el1.get_sign(i1a, i1b));

	} while (ai.inc());

	params.grp2.insert(el2);
}


} // namespace libtensor

#endif // LIBTENSOR_SO_MERGE_IMPL_PERM_H

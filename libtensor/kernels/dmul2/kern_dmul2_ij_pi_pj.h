#ifndef LIBTENSOR_KERN_DMUL2_IJ_PI_PJ_H
#define LIBTENSOR_KERN_DMUL2_IJ_PI_PJ_H

#include "kern_dmul2_i_p_pi.h"
#include "kern_dmul2_i_pi_p.h"

namespace libtensor {


/** \brief Specialized kernel for \f$ c_{ij} = c_{ij} + a_{pi} b_{pj} d \f$
    \tparam LA Linear algebra.

    \ingroup libtensor_kernels
 **/
template<typename LA>
class kern_dmul2_ij_pi_pj : public kernel_base<LA, 2, 1> {
public:
    static const char *k_clazz; //!< Kernel name

public:
    typedef typename kernel_base<LA, 2, 1>::device_context_ref
        device_context_ref;
    typedef typename kernel_base<LA, 2, 1>::list_t list_t;
    typedef typename kernel_base<LA, 2, 1>::iterator_t iterator_t;

private:
    double m_d;
    size_t m_ni, m_nj, m_np;
    size_t m_spa, m_spb, m_sic;

public:
    virtual ~kern_dmul2_ij_pi_pj() { }

    virtual const char *get_name() const {
        return k_clazz;
    }

    virtual void run(device_context_ref ctx, const loop_registers<2, 1> &r);

    static kernel_base<LA, 2, 1> *match(const kern_dmul2_i_p_pi<LA> &z,
        list_t &in, list_t &out);
    static kernel_base<LA, 2, 1> *match(const kern_dmul2_i_pi_p<LA> &z,
        list_t &in, list_t &out);

};


} // namespace libtensor

#endif // LIBTENSOR_KERN_DMUL2_IJ_PI_PJ_H

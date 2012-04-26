#ifndef LIBTENSOR_LABELED_BTENSOR_EXPR_EWMULT_EVAL_FUNCTOR_10XX_H
#define LIBTENSOR_LABELED_BTENSOR_EXPR_EWMULT_EVAL_FUNCTOR_10XX_H

namespace libtensor {
namespace labeled_btensor_expr {


template<size_t N, size_t M, size_t K, typename T, typename E1, typename E2,
    size_t NT1, size_t NO1, size_t NT2, size_t NO2>
class ewmult_eval_functor;


/** \brief Functor for evaluating element-wise product (tensor + expression)

    \ingroup libtensor_btensor_expr
 **/
template<size_t N, size_t M, size_t K, typename T, typename E1, typename E2,
    size_t NT2, size_t NO2>
class ewmult_eval_functor<N, M, K, T, E1, E2, 1, 0, NT2, NO2> {
public:
    static const char *k_clazz; //!< Class name
    static const size_t k_ordera = N + K; //!< Order of the first %tensor
    static const size_t k_orderb = M + K; //!< Order of the second %tensor
    static const size_t k_orderc = N + M + K; //!< Order of the result

    //!    Contraction expression core type
    typedef ewmult_core<N, M, K, T, E1, E2> core_t;

    //!    Contraction expression type
    typedef expr<k_orderc, T, core_t> expression_t;

    //!    Expression core type of A
    typedef typename E1::core_t core_a_t;

    //!    Expression core type of B
    typedef typename E2::core_t core_b_t;

    //!    Evaluating container type of A
    typedef typename expr<k_ordera, T, core_a_t>::eval_container_t
        eval_container_a_t;

    //!    Anonymous evaluator type of B
    typedef anon_eval<k_orderb, T, core_b_t> anon_eval_b_t;

    //!    Sub-expressions labels
    typedef ewmult_subexpr_labels<N, M, K, T, E1, E2> subexpr_labels_t;

private:
    eval_container_a_t m_eval_a; //!< Container for tensor A
    arg<k_ordera, T, tensor_tag> m_arg_a; //!< Tensor argument for A
    anon_eval_b_t m_eval_b; //!< Anonymous evaluator for sub-expression B
    ewmult_perm_builder<N, M, K> m_perm_bld;
    permutation<k_ordera> m_perm_a;
    permutation<k_orderb> m_perm_b;
    permutation<k_orderc> m_perm_c;
    btod_ewmult2<N, M, K> *m_op; //!< Contraction operation
    arg<k_orderc, T, oper_tag> *m_arg; //!< Composed operation argument

public:
    ewmult_eval_functor(expression_t &expr,
        const subexpr_labels_t &labels_ab,
        const letter_expr<k_orderc> &label_c);

    ~ewmult_eval_functor();

    void evaluate();

    void clean();

    arg<N + M + K, T, oper_tag> get_arg() const { return *m_arg; }

private:
    void create_arg();
    void destroy_arg();

};


template<size_t N, size_t M, size_t K, typename T, typename E1, typename E2,
    size_t NT2, size_t NO2>
const char *ewmult_eval_functor<N, M, K, T, E1, E2, 1, 0, NT2, NO2>::
    k_clazz = "ewmult_eval_functor<N, M, K, T, E1, E2, 1, 0, NT2, NO2>";


template<size_t N, size_t M, size_t K, typename T, typename E1, typename E2,
    size_t NT2, size_t NO2>
ewmult_eval_functor<N, M, K, T, E1, E2, 1, 0, NT2, NO2>::
ewmult_eval_functor(expression_t &expr, const subexpr_labels_t &labels_ab,
    const letter_expr<k_orderc> &label_c) :

    m_eval_a(expr.get_core().get_expr_1(), labels_ab.get_label_a()),
    m_arg_a(m_eval_a.get_arg(tensor_tag(), 0)),
    m_eval_b(expr.get_core().get_expr_2(), labels_ab.get_label_b()),
    m_perm_bld(labels_ab.get_label_a(), labels_ab.get_label_b(),
        label_c, expr.get_core().get_ewidx()),
    m_perm_a(permutation<k_ordera>(m_arg_a.get_perm()).permute(m_perm_bld.get_perma())),
    m_perm_b(m_perm_bld.get_permb()),
    m_perm_c(m_perm_bld.get_permc()),
    m_op(0), m_arg(0) {

}


template<size_t N, size_t M, size_t K, typename T, typename E1, typename E2,
    size_t NT2, size_t NO2>
ewmult_eval_functor<N, M, K, T, E1, E2, 1, 0, NT2, NO2>::
~ewmult_eval_functor() {

    destroy_arg();
}


template<size_t N, size_t M, size_t K, typename T, typename E1, typename E2,
    size_t NT2, size_t NO2>
void ewmult_eval_functor<N, M, K, T, E1, E2, 1, 0, NT2, NO2>::evaluate() {

    m_eval_b.evaluate();
    create_arg();
}


template<size_t N, size_t M, size_t K, typename T, typename E1, typename E2,
    size_t NT2, size_t NO2>
void ewmult_eval_functor<N, M, K, T, E1, E2, 1, 0, NT2, NO2>::clean() {

    destroy_arg();
    m_eval_b.clean();
}


template<size_t N, size_t M, size_t K, typename T, typename E1, typename E2,
    size_t NT2, size_t NO2>
void ewmult_eval_functor<N, M, K, T, E1, E2, 1, 0, NT2, NO2>::create_arg() {

    destroy_arg();
    m_op = new btod_ewmult2<N, M, K>(m_arg_a.get_btensor(), m_perm_a,
        m_eval_b.get_btensor(), m_perm_b, m_perm_c);
    m_arg = new arg<N + M + K, T, oper_tag>(*m_op, m_arg_a.get_coeff());
}


template<size_t N, size_t M, size_t K, typename T, typename E1, typename E2,
    size_t NT2, size_t NO2>
void ewmult_eval_functor<N, M, K, T, E1, E2, 1, 0, NT2, NO2>::destroy_arg() {

    delete m_arg; m_arg = 0;
    delete m_op; m_op = 0;
}


} // namespace labeled_btensor_expr
} // namespace libtensor

#endif // LIBTENSOR_LABELED_BTENSOR_EXPR_EWMULT_EVAL_FUNCTOR_10XX_H

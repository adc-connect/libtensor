#ifndef LIBTENSOR_EXPR_UNARY_NODE_BASE_H
#define LIBTENSOR_EXPR_UNARY_NODE_BASE_H

#include "node.h"

namespace libtensor {
namespace expr {


/** \brief Base class of unary tensor operation nodes

    \ingroup libtensor_expr
 **/
class unary_node_base : public node {
private:
    node *m_arg;

public:
    /** \brief Creates an unary node base
        \param op Operation name.
        \param n Order of result.
        \param arg Node argument.
     **/
    unary_node_base(const std::string &op, size_t n, const node &arg) :
        node(op, n), m_arg(arg.clone())
    { }

    /** \brief Copy constructor
     **/
    unary_node_base(const unary_node_base &n) :
        node(n), m_arg(n.m_arg->clone())
    { }

    /** \brief Virtual destructor
     **/
    virtual ~unary_node_base() {
        delete m_arg;
    }

    /** \brief Creates a copy of the node via new
     **/
    virtual node *clone() const = 0;

    /** \brief Returns internal node
     **/
    node &get_arg() {
        return *m_arg;
    }

    /** \brief Returns internal node (const version)
     **/
    const node &get_arg() const {
        return *m_arg;
    }

};


} // namespace expr
} // namespace libtensor

#endif // LIBTENSOR_EXPR_UNARY_NODE_BASE_H

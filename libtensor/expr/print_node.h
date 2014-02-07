#ifndef LIBTENSOR_EXPR_PRINT_NODE_H
#define LIBTENSOR_EXPR_PRINT_NODE_H

#include <iostream>
#include <libtensor/expr/dag/node.h>

namespace libtensor {
namespace expr {


/** \brief Prints the contents of a node
    \param n Node.
    \param os Output stream.

    \ingroup libtensor_expr
 **/
void print_node(const node &n, std::ostream &os);


} // namespace expr
} // namespace libtensor


#endif // LIBTENSOR_EXPR_PRINT_NODE_H

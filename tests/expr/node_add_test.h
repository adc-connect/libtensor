#ifndef LIBTENSOR_NODE_ADD_TEST_H
#define LIBTENSOR_NODE_ADD_TEST_H

#include <libtest/unit_test.h>

namespace libtensor {


/** \brief Tests the libtensor::node_add class

    \ingroup libtensor_tests_expr
**/
class node_add_test : public libtest::unit_test {
public:
    virtual void perform();

private:
    void test_1();

};


} // namespace libtensor

#endif // LIBTENSOR_NODE_ADD_TEST_H


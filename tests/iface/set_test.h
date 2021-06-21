#ifndef LIBTENSOR_SET_TEST_H
#define LIBTENSOR_SET_TEST_H

#include <libtest/unit_test.h>

namespace libtensor {

/** \brief Tests the libtensor::set function

    \ingroup libtensor_tests_iface
 **/
class set_test : public libtest::unit_test {
public:
    virtual void perform();

private:
    void test_s_1(double d);
    void test_s_2(double d);
    void test_d_1(double d);
    void test_d_2(double d);
    void test_x_1(double d);
    void test_x_2(double d);
};

} // namespace libtensor

#endif // LIBTENSOR_SET_TEST_H

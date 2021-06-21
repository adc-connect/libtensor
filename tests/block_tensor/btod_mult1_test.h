#ifndef LIBTENSOR_BTOD_MULT1_TEST_H
#define LIBTENSOR_BTOD_MULT1_TEST_H

#include <libtest/unit_test.h>

namespace libtensor {

/** \brief Tests the libtensor::btod_mult1 class

    \ingroup libtensor_tests_btod
**/
class btod_mult1_test : public libtest::unit_test {
public:
    virtual void perform();

private:
    void test_1(bool, bool);
    void test_2(bool, bool);
    void test_3(bool, bool);
    void test_4(bool, bool);
    void test_5(bool, bool);
};

} // namespace libtensor

#endif // LIBTENSOR_BTOD_MULT1_TEST_H

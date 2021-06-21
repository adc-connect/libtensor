#ifndef LIBTENSOR_COMBINE_PART_TEST_H
#define LIBTENSOR_COMBINE_PART_TEST_H

#include <libtest/unit_test.h>

namespace libtensor {


/** \brief Tests the class libtensor::combine_part

    \ingroup libtensor_tests_sym
 **/
class combine_part_test : public libtest::unit_test {
public:
    virtual void perform();

private:
    void test_1();
    void test_2(bool symm);
    void test_3(bool symm1, bool symm2);
    void test_4a(bool symm1, bool symm2,
            bool forbidden);
    void test_4b(bool symm1, bool symm2);

};


} // namespace libtensor

#endif // LIBTENSOR_SO_DIRPROD_IMPL_PART_TEST_H


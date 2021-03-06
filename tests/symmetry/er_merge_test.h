#ifndef LIBTENSOR_ER_MERGE_TEST_H
#define LIBTENSOR_ER_MERGE_TEST_H

#include "se_label_test_base.h"

namespace libtensor {

/** \brief Tests the libtensor::er_merge class

    \ingroup libtensor_tests_sym
 **/
class er_merge_test : public se_label_test_base {
public:
    virtual void perform();

private:
    void test_1(const std::string &id);
    void test_2(const std::string &id);
    void test_3(const std::string &id);
    void test_4(const std::string &id);
};

} // namespace libtensor

#endif // LIBTENSOR_ER_MERGE_TEST_H


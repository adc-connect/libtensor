#ifndef LIBTENSOR_CONTRACT_TEST_H
#define	LIBTENSOR_CONTRACT_TEST_H

#include <libtest.h>

namespace libtensor {

/**	\brief Tests the libtensor::contract function

	\ingroup libtensor_tests
**/
class contract_test : public libtest::unit_test {
public:
	virtual void perform() throw(libtest::test_exception);

private:
	void test_subexpr_labels_1() throw(libtest::test_exception);

	void test_1() throw(libtest::test_exception);

};

} // namespace libtensor

#endif // LIBTENSOR_CONTRACT_TEST_H

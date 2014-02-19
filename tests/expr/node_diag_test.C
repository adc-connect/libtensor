#include <memory>
#include <libtensor/exception.h>
#include <libtensor/expr/dag/node_diag.h>
#include <libtensor/expr/iface/node_ident_any_tensor.h>
#include "node_diag_test.h"

namespace libtensor {


void node_diag_test::perform() throw(libtest::test_exception) {

    test_1();
}


using namespace expr;


void node_diag_test::test_1() throw(libtest::test_exception) {

    static const char testname[] = "node_diag_test::test_1()";

    try {

    std::vector<size_t> idx(2);
    idx[0] = 0; idx[1] = 0;

    node_diag d1(1, idx, 0);

    if(d1.get_didx() != 0) {
        fail_test(testname, __FILE__, __LINE__, "d1.get_didx() != 0");
    }

    std::auto_ptr<node_diag> d1copy(dynamic_cast<node_diag*>(d1.clone()));
    if(d1copy->get_idx() != idx) {
        fail_test(testname, __FILE__, __LINE__, "Inconsistent tensor indices.");
    }
    if(d1copy->get_didx() != 0) {
        fail_test(testname, __FILE__, __LINE__, "d1copy->get_didx() != 0");
    }


    } catch(exception &e) {
        fail_test(testname, __FILE__, __LINE__, e.what());
    }
}


} // namespace libtensor
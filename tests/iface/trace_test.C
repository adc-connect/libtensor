#include <cmath>
#include <sstream>
#include <libtensor/core/scalar_transf_double.h>
#include <libtensor/block_tensor/btod_add.h>
#include <libtensor/block_tensor/btod_copy.h>
#include <libtensor/block_tensor/btod_random.h>
#include <libtensor/block_tensor/btod_trace.h>
#include <libtensor/libtensor.h>
#include "trace_test.h"

namespace libtensor {


void trace_test::perform() {

    allocator<double>::init();

    try {

        test_t_1();
        test_t_2();
        test_t_3();
        test_e_1();
        test_e_2();
        test_e_3();

    } catch(...) {
        allocator<double>::shutdown();
        throw;
    }

    allocator<double>::shutdown();
}


void trace_test::test_t_1() {

    static const char testname[] = "trace_test::test_t_1()";

    try {

    bispace<1> si(10);
    si.split(5).split(7);
    bispace<2> sij(si&si);
    btensor<2> bt(sij);

    btod_random<2>().perform(bt);
    double d_ref = btod_trace<1>(bt).calculate();

    letter i, j;
    double d = trace(i, j, bt(i|j));
    check_ref(testname, d, d_ref);

    } catch(exception &e) {
        fail_test(testname, __FILE__, __LINE__, e.what());
    }

}


void trace_test::test_t_2() {

    static const char testname[] = "trace_test::test_t_2()";

    try {

    bispace<1> si(10), sj(11);
    si.split(5).split(7);
    sj.split(3).split(6);
    bispace<4> sijkl((si|sj)&(si|sj));
    btensor<4> bt(sijkl);

    btod_random<4>().perform(bt);
    double d_ref = btod_trace<2>(bt).calculate();

    letter i, j, k, l;
    double d = trace(i|j, k|l, bt(i|j|k|l));
    check_ref(testname, d, d_ref);

    } catch(exception &e) {
        fail_test(testname, __FILE__, __LINE__, e.what());
    }

}


void trace_test::test_t_3() {

    static const char testname[] = "trace_test::test_t_3()";

    try {

    bispace<1> si(10);
    si.split(5).split(7);
    bispace<4> sijkl(si&si&si&si);
    btensor<4> bt(sijkl), bt1(sijkl);

    btod_random<4>().perform(bt);
    btod_copy<4>(bt, permutation<4>().permute(1, 2)).perform(bt1);
    double d_ref = btod_trace<2>(bt1).calculate();

    letter i, j, k, l;
    double d = trace(i|k, j|l, bt(i|j|k|l));
    check_ref(testname, d, d_ref);

    } catch(exception &e) {
        fail_test(testname, __FILE__, __LINE__, e.what());
    }

}


void trace_test::test_e_1() {

    static const char testname[] = "trace_test::test_e_1()";

    try {

    bispace<1> si(10);
    si.split(5).split(7);
    bispace<2> sij(si&si);
    btensor<2> bt1(sij), bt2(sij), bt3(sij);

    btod_random<2>().perform(bt1);
    btod_random<2>().perform(bt2);
    btod_add<2> add(bt1, 1.0);
    add.add_op(bt2, 1.0);
    add.perform(bt3);
    double d_ref = btod_trace<1>(bt3).calculate();

    letter i, j;
    double d = trace(i, j, bt1(i|j) + bt2(i|j));
    check_ref(testname, d, d_ref);

    } catch(exception &e) {
        fail_test(testname, __FILE__, __LINE__, e.what());
    }

}


void trace_test::test_e_2() {

    static const char testname[] = "trace_test::test_e_2()";

    try {

    bispace<1> si(10);
    si.split(5).split(7);
    bispace<2> sij(si&si);
    btensor<2> bt1(sij), bt2(sij), bt3(sij);
    permutation<2> p10; p10.permute(0, 1);

    btod_random<2>().perform(bt1);
    btod_random<2>().perform(bt2);
    btod_add<2> add(bt1, p10, 1.0);
    add.add_op(bt2, 1.0);
    add.perform(bt3);
    double d_ref = btod_trace<1>(bt3).calculate();

    letter i, j;
    double d = trace(i, j, bt1(j|i) + bt2(i|j));
    check_ref(testname, d, d_ref);

    } catch(exception &e) {
        fail_test(testname, __FILE__, __LINE__, e.what());
    }

}


void trace_test::test_e_3() {

    static const char testname[] = "trace_test::test_e_3()";

    try {

    bispace<1> si(10), sj(11);
    si.split(5).split(7);
    sj.split(3).split(6);
    bispace<4> sijkl((si|sj)&(si|sj));
    btensor<4> bt1(sijkl), bt2(sijkl), bt3(sijkl);

    btod_random<4>().perform(bt1);
    btod_random<4>().perform(bt2);
    btod_add<4> add(bt1, 1.0);
    add.add_op(bt2, 1.0);
    add.perform(bt3);
    double d_ref = btod_trace<2>(bt3).calculate();

    letter i, j, k, l;
    double d = trace(i|j, k|l, bt1(i|j|k|l) + bt2(i|j|k|l));
    check_ref(testname, d, d_ref);

    } catch(exception &e) {
        fail_test(testname, __FILE__, __LINE__, e.what());
    }

}


void trace_test::check_ref(const char *testname, double d, double d_ref)
    {

    if(fabs(d - d_ref) > fabs(d_ref * 1e-14)) {
        std::ostringstream ss;
        ss << "Result doesn't match reference: " << d << " (res), "
            << d_ref << " (ref), " << d - d_ref << " (diff)";
        fail_test(testname, __FILE__, __LINE__, ss.str().c_str());
    }
}


} // namespace libtensor

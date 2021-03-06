#include <libtensor/core/scalar_transf_double.h>
#include <libtensor/block_tensor/btod_add.h>
#include <libtensor/block_tensor/btod_copy.h>
#include <libtensor/block_tensor/btod_diag.h>
#include <libtensor/block_tensor/btod_random.h>
#include <libtensor/libtensor.h>
#include "../compare_ref.h"
#include "diag_test.h"

namespace libtensor {


void diag_test::perform() {

    allocator<double>::init();

    try {

        test_t_1();
        test_t_2();
        test_t_3();
        test_t_4();
        test_t_5();
        test_t_6();
        test_t_7();
        test_e_1();
        test_x_1();

    } catch(...) {
        allocator<double>::shutdown();
        throw;
    }

    allocator<double>::shutdown();
}


void diag_test::test_t_1() {

    static const char testname[] = "diag_test::test_t_1()";

    try {

    bispace<1> sp_i(10);
    bispace<2> sp_ij(sp_i&sp_i);

    btensor<2> t1(sp_ij);
    btensor<1> t2(sp_i), t2_ref(sp_i);

    btod_random<2>().perform(t1);
    t1.set_immutable();

    sequence<2, size_t> msk(0);
    msk[0] = 1; msk[1] = 1;
    permutation<1> perm;
    btod_diag<2, 1>(t1, msk, perm).perform(t2_ref);

    letter i, j;
    t2(i) = diag(i, i|j, t1(j|i));

    compare_ref<1>::compare(testname, t2, t2_ref, 1e-15);

    } catch(exception &e) {
        fail_test(testname, __FILE__, __LINE__, e.what());
    }
}


void diag_test::test_t_2() {

    static const char testname[] = "diag_test::test_t_2()";

    try {

    bispace<1> sp_i(10), sp_a(11);
    bispace<2> sp_ia(sp_i|sp_a);
    bispace<3> sp_ija((sp_i&sp_i)|sp_a);

    btensor<3> t1(sp_ija);
    btensor<2> t2(sp_ia), t2_ref(sp_ia);

    btod_random<3>().perform(t1);
    t1.set_immutable();

    sequence<3, size_t> msk(0);
    msk[0] = 1; msk[1] = 1;
    permutation<2> perm;
    btod_diag<3, 2>(t1, msk, perm).perform(t2_ref);

    letter i, j, a;
    t2(i|a) = diag(i, i|j, t1(i|j|a));

    compare_ref<2>::compare(testname, t2, t2_ref, 1e-15);

    } catch(exception &e) {
        fail_test(testname, __FILE__, __LINE__, e.what());
    }
}


void diag_test::test_t_3() {

    static const char testname[] = "diag_test::test_t_3()";

    try {

    bispace<1> sp_i(10), sp_a(11), sp_j(sp_i);
    bispace<2> sp_ai(sp_a|sp_i);
    bispace<3> sp_iaj(sp_i|sp_a|sp_j, (sp_i&sp_j)|sp_a);

    btensor<3> t1(sp_iaj);
    btensor<2> t2(sp_ai), t2_ref(sp_ai);

    btod_random<3>().perform(t1);
    t1.set_immutable();

    sequence<3, size_t> msk(0);
    msk[0] = 1; msk[2] = 1;
    permutation<2> perm;
    perm.permute(0, 1); // ia->ai
    btod_diag<3, 2>(t1, msk, perm).perform(t2_ref);

    letter i, j, a;
    t2(a|i) = diag(i, i|j, t1(i|a|j));

    compare_ref<2>::compare(testname, t2, t2_ref, 1e-15);

    } catch(exception &e) {
        fail_test(testname, __FILE__, __LINE__, e.what());
    }
}


void diag_test::test_t_4() {

    static const char testname[] = "diag_test::test_t_4()";

    try {

    bispace<1> sp_i(10);
    bispace<2> sp_ij(sp_i&sp_i);

    btensor<2> t1(sp_ij);
    btensor<1> t2(sp_i), t2_ref(sp_i);

    btod_random<2>().perform(t1);
    t1.set_immutable();

    sequence<2, size_t> msk(0);
    msk[0] = 1; msk[1] = 1;
    permutation<1> perm;
    btod_diag<2, 1>(t1, msk, perm, -1.0).perform(t2_ref);

    letter i, j;
    t2(i) = - diag(i, i|j, t1(i|j));

    compare_ref<1>::compare(testname, t2, t2_ref, 1e-15);

    } catch(exception &e) {
        fail_test(testname, __FILE__, __LINE__, e.what());
    }
}


void diag_test::test_t_5() {

    static const char testname[] = "diag_test::test_t_5()";

    try {

    bispace<1> sp_i(10);
    bispace<2> sp_ij(sp_i&sp_i);
    bispace<3> sp_ijk(sp_i&sp_i&sp_i);
    bispace<4> sp_ijkl(sp_i&sp_i&sp_i&sp_i);

    btensor<4> t1(sp_ijkl);
    btensor<3> tt(sp_ijk);
    btensor<2> t2(sp_ij), t2_ref(sp_ij);

    btod_random<4>().perform(t1);
    t1.set_immutable();

    sequence<4, size_t> m1212(0);
    m1212[0] = 1; m1212[1] = 2; m1212[2] = 1; m1212[3] = 2;

    btod_diag<4, 2>(t1, m1212, permutation<2>(), 0.5).perform(t2_ref);

    letter i, j, k, l;
    t2(i|j) = 0.5 * diag(i|j, i|k|j|l, t1(i|j|k|l));

    compare_ref<2>::compare(testname, t2, t2_ref, 1e-15);

    } catch(exception &e) {
        fail_test(testname, __FILE__, __LINE__, e.what());
    }
}


void diag_test::test_t_6() {

    static const char testname[] = "diag_test::test_t_6()";

    try {

    bispace<1> sp_i(10);
    bispace<2> sp_ij(sp_i&sp_i);

    btensor<2> t1(sp_ij);
    btensor<1> t2(sp_i), t2_ref(sp_i);

    btod_random<2>().perform(t1);
    t1.set_immutable();

    sequence<2, size_t> m11(0);
    m11[0] = 1; m11[1] = 1;

    btod_diag<2, 1>(t1, m11, permutation<1>(), -1.0).perform(t2_ref);

    letter i, j;
    t2(i) = diag(i, i|j, -t1(i|j));

    compare_ref<1>::compare(testname, t2, t2_ref, 1e-15);

    } catch(exception &e) {
        fail_test(testname, __FILE__, __LINE__, e.what());
    }
}


void diag_test::test_t_7() {

    static const char testname[] = "diag_test::test_t_7()";

    try {

    bispace<1> sp_i(5);
    bispace<3> sp_ijk(sp_i&sp_i&sp_i);
    bispace<5> sp_ijklm(sp_i&sp_i&sp_i&sp_i&sp_i);

    btensor<5> t1(sp_ijklm);
    btensor<3> t2(sp_ijk), t2_ref(sp_ijk);

    btod_random<5>().perform(t1);
    t1.set_immutable();

    sequence<5, size_t> m01212(0);
    m01212[0] = 0; m01212[1] = 1; m01212[2] = 2; m01212[3] = 1; m01212[4] = 2;

    btod_diag<5, 3>(t1, m01212, permutation<3>().permute(1, 2).permute(0, 1),
        1.0).perform(t2_ref);

    letter i, j, k, l, m;
    t2(k|i|j) = diag(j|k, j|l|k|m, t1(i|j|k|l|m));

    compare_ref<3>::compare(testname, t2, t2_ref, 1e-15);

    } catch(exception &e) {
        fail_test(testname, __FILE__, __LINE__, e.what());
    }
}


void diag_test::test_e_1() {

    static const char testname[] = "diag_test::test_e_1()";

    try {

    bispace<1> sp_i(10);
    bispace<2> sp_ij(sp_i&sp_i);

    btensor<2> t1a(sp_ij), t1b(sp_ij);
    btensor<1> t2a(sp_i), t2b(sp_i), t2(sp_i), t2_ref(sp_i);

    btod_random<2>().perform(t1a);
    btod_random<2>().perform(t1b);
    t1a.set_immutable();
    t1b.set_immutable();

    sequence<2, size_t> msk(0);
    msk[0] = 1; msk[1] = 1;
    permutation<1> perm;
    btod_diag<2, 1>(t1a, msk, perm).perform(t2a);
    btod_diag<2, 1>(t1b, msk, perm).perform(t2b);
    btod_add<1> add(t2a);
    add.add_op(t2b);
    add.perform(t2_ref);

    letter i, j;
    t2(i) = diag(i, i|j, t1a(j|i) + t1b(i|j));

    compare_ref<1>::compare(testname, t2, t2_ref, 1e-15);

    } catch(exception &e) {
        fail_test(testname, __FILE__, __LINE__, e.what());
    }
}


void diag_test::test_x_1() {

    static const char testname[] = "diag_test::test_x_1()";

    try {

    bispace<1> sp_i(10), sp_a(16);
    sp_i.split(5);
    sp_a.split(8);
    bispace<1> sp_j(sp_i);
    bispace<2> sp_ia(sp_i|sp_a), sp_jb(sp_i|sp_a);
    bispace<3> sp_iaj(sp_i|sp_a|sp_j, (sp_i&sp_j)|sp_a);
    bispace<4> sp_iajb(sp_ia&sp_jb);

    btensor<2> t1(sp_ia), t3(sp_ia), t3_ref(sp_ia);
    btensor<4> t2(sp_iajb);
    btensor<3> tx(sp_iaj);

    btod_random<2>().perform(t1);
    t1.set_immutable();
    btod_random<4>().perform(t2);
    t2.set_immutable();

    btod_copy<2>(t1).perform(t3_ref);
    sequence<4, size_t> msk(0);
    msk[0] = 1; msk[1] = 2; msk[2] = 1; msk[3] = 2;
    btod_diag<4, 2>(t2, msk, permutation<2>(), -1.0).perform(t3_ref, 1.0);

    letter i, j, a, b;
    t3(i|a) = t1(i|a) - diag(i|a, i|j|a|b, t2(i|a|j|b));

    compare_ref<2>::compare(testname, t3, t3_ref, 1e-15);

    } catch(exception &e) {
        fail_test(testname, __FILE__, __LINE__, e.what());
    }
}


} // namespace libtensor

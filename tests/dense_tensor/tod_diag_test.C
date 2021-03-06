#include <cmath>
#include <ctime>
#include <libtensor/core/allocator.h>
#include <libtensor/dense_tensor/dense_tensor.h>
#include <libtensor/dense_tensor/dense_tensor_ctrl.h>
#include <libtensor/dense_tensor/tod_diag.h>
#include "../compare_ref.h"
#include "../test_utils.h"

using namespace libtensor;


/** \test Extract a single diagonal: \f$ b_i = a_{ii} \f$
 **/
int test_1() {

    static const char testname[] = "tod_diag_test::test_1()";

    typedef allocator<double> allocator;

    try {

    libtensor::index<1> i1a, i1b;
    i1b[0] = 10;
    libtensor::index<2> i2a, i2b;
    i2b[0] = 10; i2b[1] = 10;
    dimensions<1> dims1(index_range<1>(i1a, i1b));
    dimensions<2> dims2(index_range<2>(i2a, i2b));
    size_t sza = dims2.get_size(), szb = dims1.get_size();

    dense_tensor<2, double, allocator> ta(dims2);
    dense_tensor<1, double, allocator> tb(dims1), tb_ref(dims1);

    {
    dense_tensor_ctrl<2, double> tca(ta);
    dense_tensor_ctrl<1, double> tcb(tb), tcb_ref(tb_ref);

    double *pa = tca.req_dataptr();
    double *pb = tcb.req_dataptr();
    double *pb_ref = tcb_ref.req_dataptr();

    for(size_t i = 0; i < sza; i++) pa[i] = drand48();
    for(size_t i = 0; i < szb; i++) pb[i] = drand48();

    for(size_t i = 0; i < szb; i++) {
        libtensor::index<2> idxa; idxa[0] = i; idxa[1] = i;
        libtensor::index<1> idxb; idxb[0] = i;
        abs_index<2> aidxa(idxa, dims2);
        abs_index<1> aidxb(idxb, dims1);
        pb_ref[aidxb.get_abs_index()] = pa[aidxa.get_abs_index()];
    }

    tca.ret_dataptr(pa); pa = 0;
    tcb.ret_dataptr(pb); pb = 0;
    tcb_ref.ret_dataptr(pb_ref); pb_ref = 0;
    }

    sequence<2, size_t> m; m[0] = 1; m[1] = 1;
    tod_diag<2, 1>(ta, m).perform(true, tb);

    compare_ref<1>::compare(testname, tb, tb_ref, 1e-15);

    } catch(exception &e) {
        return fail_test(testname, __FILE__, __LINE__, e.what());
    }

    return 0;
}


/** \test Extract a single diagonal with one index intact:
        \f$ b_{ij} = a_{iij} \f$
 **/
int test_2() {

    static const char testname[] = "tod_diag_test::test_2()";

    typedef allocator<double> allocator;

    try {

    size_t ni = 6, nj = 11;
    libtensor::index<2> i2a, i2b;
    i2b[0] = ni - 1; i2b[1] = nj - 1;
    libtensor::index<3> i3a, i3b;
    i3b[0] = ni - 1; i3b[1] = ni - 1; i3b[2] = nj - 1;
    dimensions<2> dims2(index_range<2>(i2a, i2b));
    dimensions<3> dims3(index_range<3>(i3a, i3b));
    size_t sza = dims3.get_size(), szb = dims2.get_size();

    dense_tensor<3, double, allocator> ta(dims3);
    dense_tensor<2, double, allocator> tb(dims2), tb_ref(dims2);

    {
    dense_tensor_ctrl<3, double> tca(ta);
    dense_tensor_ctrl<2, double> tcb(tb), tcb_ref(tb_ref);

    double *pa = tca.req_dataptr();
    double *pb = tcb.req_dataptr();
    double *pb_ref = tcb_ref.req_dataptr();

    for(size_t i = 0; i < sza; i++) pa[i] = drand48();
    for(size_t i = 0; i < szb; i++) pb[i] = drand48();

    for(size_t i = 0; i < ni; i++) {
    for(size_t j = 0; j < nj; j++) {
        libtensor::index<3> idxa; idxa[0] = i; idxa[1] = i; idxa[2] = j;
        libtensor::index<2> idxb; idxb[0] = i; idxb[1] = j;
        abs_index<3> aidxa(idxa, dims3);
        abs_index<2> aidxb(idxb, dims2);
        pb_ref[aidxb.get_abs_index()] = pa[aidxa.get_abs_index()];
    }
    }

    tca.ret_dataptr(pa); pa = 0;
    tcb.ret_dataptr(pb); pb = 0;
    tcb_ref.ret_dataptr(pb_ref); pb_ref = 0;
    }

    sequence<3, size_t> m; m[0] = 1; m[1] = 1; m[2] = 0;
    tod_diag<3, 2>(ta, m).perform(true, tb);

    compare_ref<2>::compare(testname, tb, tb_ref, 1e-15);

    } catch(exception &e) {
        return fail_test(testname, __FILE__, __LINE__, e.what());
    }

    return 0;
}


/** \test Extract a single diagonal with one index intact:
        \f$ b_{ij} = a_{iji} \f$
 **/
int test_3() {

    static const char testname[] = "tod_diag_test::test_3()";

    typedef allocator<double> allocator;

    try {

    size_t ni = 6, nj = 11;
    libtensor::index<2> i2a, i2b;
    i2b[0] = ni - 1; i2b[1] = nj - 1;
    libtensor::index<3> i3a, i3b;
    i3b[0] = ni - 1; i3b[1] = nj - 1; i3b[2] = ni - 1;
    dimensions<2> dims2(index_range<2>(i2a, i2b));
    dimensions<3> dims3(index_range<3>(i3a, i3b));
    size_t sza = dims3.get_size(), szb = dims2.get_size();

    dense_tensor<3, double, allocator> ta(dims3);
    dense_tensor<2, double, allocator> tb(dims2), tb_ref(dims2);

    {
    dense_tensor_ctrl<3, double> tca(ta);
    dense_tensor_ctrl<2, double> tcb(tb), tcb_ref(tb_ref);

    double *pa = tca.req_dataptr();
    double *pb = tcb.req_dataptr();
    double *pb_ref = tcb_ref.req_dataptr();

    for(size_t i = 0; i < sza; i++) pa[i] = drand48();
    for(size_t i = 0; i < szb; i++) pb[i] = drand48();

    for(size_t i = 0; i < ni; i++) {
    for(size_t j = 0; j < nj; j++) {
        libtensor::index<3> idxa; idxa[0] = i; idxa[1] = j; idxa[2] = i;
        libtensor::index<2> idxb; idxb[0] = i; idxb[1] = j;
        abs_index<3> aidxa(idxa, dims3);
        abs_index<2> aidxb(idxb, dims2);
        pb_ref[aidxb.get_abs_index()] = pa[aidxa.get_abs_index()];
    }
    }

    tca.ret_dataptr(pa); pa = 0;
    tcb.ret_dataptr(pb); pb = 0;
    tcb_ref.ret_dataptr(pb_ref); pb_ref = 0;
    }

    sequence<3, size_t> m; m[0] = 1; m[1] = 0; m[2] = 1;
    tod_diag<3, 2>(ta, m).perform(true, tb);

    compare_ref<2>::compare(testname, tb, tb_ref, 1e-15);

    } catch(exception &e) {
        return fail_test(testname, __FILE__, __LINE__, e.what());
    }

    return 0;
}


/** \test Extract a single diagonal with one index intact:
        \f$ b_{ji} = a_{jii} \f$
 **/
int test_4() {

    static const char testname[] = "tod_diag_test::test_4()";

    typedef allocator<double> allocator;

    try {

    size_t ni = 6, nj = 11;
    libtensor::index<2> i2a, i2b;
    i2b[0] = nj - 1; i2b[1] = ni - 1;
    libtensor::index<3> i3a, i3b;
    i3b[0] = nj - 1; i3b[1] = ni - 1; i3b[2] = ni - 1;
    dimensions<2> dims2(index_range<2>(i2a, i2b));
    dimensions<3> dims3(index_range<3>(i3a, i3b));
    size_t sza = dims3.get_size(), szb = dims2.get_size();

    dense_tensor<3, double, allocator> ta(dims3);
    dense_tensor<2, double, allocator> tb(dims2), tb_ref(dims2);

    {
    dense_tensor_ctrl<3, double> tca(ta);
    dense_tensor_ctrl<2, double> tcb(tb), tcb_ref(tb_ref);

    double *pa = tca.req_dataptr();
    double *pb = tcb.req_dataptr();
    double *pb_ref = tcb_ref.req_dataptr();

    for(size_t i = 0; i < sza; i++) pa[i] = drand48();
    for(size_t i = 0; i < szb; i++) pb[i] = drand48();

    for(size_t i = 0; i < ni; i++) {
    for(size_t j = 0; j < nj; j++) {
        libtensor::index<3> idxa; idxa[0] = j; idxa[1] = i; idxa[2] = i;
        libtensor::index<2> idxb; idxb[0] = j; idxb[1] = i;
        abs_index<3> aidxa(idxa, dims3);
        abs_index<2> aidxb(idxb, dims2);
        pb_ref[aidxb.get_abs_index()] = pa[aidxa.get_abs_index()];
    }
    }

    tca.ret_dataptr(pa); pa = 0;
    tcb.ret_dataptr(pb); pb = 0;
    tcb_ref.ret_dataptr(pb_ref); pb_ref = 0;
    }

    sequence<3, size_t> m; m[0] = 0; m[1] = 1; m[2] = 1;
    tod_diag<3, 2>(ta, m).perform(true, tb);

    compare_ref<2>::compare(testname, tb, tb_ref, 1e-15);

    } catch(exception &e) {
        return fail_test(testname, __FILE__, __LINE__, e.what());
    }

    return 0;
}


/** \test Extract a single diagonal with one index intact and permuted:
        output \f$ b_{ij} = a_{jii} \f$
 **/
int test_5() {

    static const char testname[] = "tod_diag_test::test_5()";

    typedef allocator<double> allocator;

    try {

    size_t ni = 6, nj = 11;
    libtensor::index<2> i2a, i2b;
    i2b[0] = ni - 1; i2b[1] = nj - 1;
    libtensor::index<3> i3a, i3b;
    i3b[0] = nj - 1; i3b[1] = ni - 1; i3b[2] = ni - 1;
    dimensions<2> dims2(index_range<2>(i2a, i2b));
    dimensions<3> dims3(index_range<3>(i3a, i3b));
    size_t sza = dims3.get_size(), szb = dims2.get_size();

    dense_tensor<3, double, allocator> ta(dims3);
    dense_tensor<2, double, allocator> tb(dims2), tb_ref(dims2);

    {
    dense_tensor_ctrl<3, double> tca(ta);
    dense_tensor_ctrl<2, double> tcb(tb), tcb_ref(tb_ref);

    double *pa = tca.req_dataptr();
    double *pb = tcb.req_dataptr();
    double *pb_ref = tcb_ref.req_dataptr();

    for(size_t i = 0; i < sza; i++) pa[i] = drand48();
    for(size_t i = 0; i < szb; i++) pb[i] = drand48();

    for(size_t i = 0; i < ni; i++) {
    for(size_t j = 0; j < nj; j++) {
        libtensor::index<3> idxa; idxa[0] = j; idxa[1] = i; idxa[2] = i;
        libtensor::index<2> idxb; idxb[0] = i; idxb[1] = j;
        abs_index<3> aidxa(idxa, dims3);
        abs_index<2> aidxb(idxb, dims2);
        pb_ref[aidxb.get_abs_index()] = pa[aidxa.get_abs_index()];
    }
    }

    tca.ret_dataptr(pa); pa = 0;
    tcb.ret_dataptr(pb); pb = 0;
    tcb_ref.ret_dataptr(pb_ref); pb_ref = 0;
    }

    sequence<3, size_t> m; m[0] = 0; m[1] = 1; m[2] = 1;
    permutation<2> permb; permb.permute(0, 1);
    tensor_transf<2, double> tr(permb);
    tod_diag<3, 2>(ta, m, tr).perform(true, tb);

    compare_ref<2>::compare(testname, tb, tb_ref, 1e-15);

    } catch(exception &e) {
        return fail_test(testname, __FILE__, __LINE__, e.what());
    }

    return 0;
}

/** \test Extract a single diagonal with one index intact and permuted:
        output \f$ b_{jik} = a_{ikjk} \f$
 **/
int test_6() {

    static const char testname[] = "tod_diag_test::test_6()";

    typedef allocator<double> allocator;

    try {

    size_t ni = 2, nj = 3, nk = 5;
    libtensor::index<3> i3a, i3b;
    i3b[0] = nj - 1; i3b[1] = ni - 1; i3b[2] = nk - 1;
    libtensor::index<4> i4a, i4b;
    i4b[0] = ni - 1; i4b[1] = nk - 1; i4b[2] = nj - 1; i4b[3] = nk - 1;
    dimensions<3> dims3(index_range<3>(i3a, i3b));
    dimensions<4> dims4(index_range<4>(i4a, i4b));
    size_t sza = dims4.get_size(), szb = dims3.get_size();

    dense_tensor<4, double, allocator> ta(dims4);
    dense_tensor<3, double, allocator> tb(dims3), tb_ref(dims3);

    {
    dense_tensor_ctrl<4, double> tca(ta);
    dense_tensor_ctrl<3, double> tcb(tb), tcb_ref(tb_ref);

    double *pa = tca.req_dataptr();
    double *pb = tcb.req_dataptr();
    double *pb_ref = tcb_ref.req_dataptr();

    for(size_t i = 0; i < sza; i++) pa[i] = drand48();
    for(size_t i = 0; i < szb; i++) pb[i] = drand48();

    for(size_t i = 0; i < ni; i++) {
    for(size_t j = 0; j < nj; j++) {
    for(size_t k = 0; k < nk; k++) {
        libtensor::index<4> idxa; idxa[0] = i; idxa[1] = k; idxa[2] = j; idxa[3] = k;
        libtensor::index<3> idxb; idxb[0] = j; idxb[1] = i; idxb[2] = k;
        abs_index<4> aidxa(idxa, dims4);
        abs_index<3> aidxb(idxb, dims3);
        pb_ref[aidxb.get_abs_index()] = pa[aidxa.get_abs_index()];
    }
    }
    }

    tca.ret_dataptr(pa); pa = 0;
    tcb.ret_dataptr(pb); pb = 0;
    tcb_ref.ret_dataptr(pb_ref); pb_ref = 0;
    }

    sequence<4, size_t> m; m[0] = 0; m[1] = 1; m[2] = 0; m[3] = 1;
    permutation<3> permb; permb.permute(0, 1).permute(0, 2);
    tensor_transf<3, double> tr(permb);
    tod_diag<4, 3>(ta, m, tr).perform(true, tb);

    compare_ref<3>::compare(testname, tb, tb_ref, 1e-15);

    } catch(exception &e) {
        return fail_test(testname, __FILE__, __LINE__, e.what());
    }

    return 0;
}


/** \test Extract a two diagonals and permute:
        output \f$ b_{ji} = a_{ijij} \f$
 **/
int test_7() {

    static const char testname[] = "tod_diag_test::test_7()";

    typedef allocator<double> allocator;

    try {

    size_t ni = 2, nj = 3;
    libtensor::index<2> i2a, i2b;
    i2b[0] = nj - 1; i2b[1] = ni - 1;
    libtensor::index<4> i4a, i4b;
    i4b[0] = ni - 1; i4b[1] = nj - 1; i4b[2] = ni - 1; i4b[3] = nj - 1;
    dimensions<2> dims2(index_range<2>(i2a, i2b));
    dimensions<4> dims4(index_range<4>(i4a, i4b));
    size_t sza = dims4.get_size(), szb = dims2.get_size();

    dense_tensor<4, double, allocator> ta(dims4);
    dense_tensor<2, double, allocator> tb(dims2), tb_ref(dims2);

    {
    dense_tensor_ctrl<4, double> tca(ta);
    dense_tensor_ctrl<2, double> tcb(tb), tcb_ref(tb_ref);

    double *pa = tca.req_dataptr();
    double *pb = tcb.req_dataptr();
    double *pb_ref = tcb_ref.req_dataptr();

    for(size_t i = 0; i < sza; i++) pa[i] = drand48();
    for(size_t i = 0; i < szb; i++) pb[i] = drand48();

    for(size_t i = 0; i < ni; i++) {
    for(size_t j = 0; j < nj; j++) {
        libtensor::index<4> idxa; idxa[0] = i; idxa[1] = j; idxa[2] = i; idxa[3] = j;
        libtensor::index<2> idxb; idxb[0] = j; idxb[1] = i;
        abs_index<4> aidxa(idxa, dims4);
        abs_index<2> aidxb(idxb, dims2);
        pb_ref[aidxb.get_abs_index()] = pa[aidxa.get_abs_index()];
    }
    }

    tca.ret_dataptr(pa); pa = 0;
    tcb.ret_dataptr(pb); pb = 0;
    tcb_ref.ret_dataptr(pb_ref); pb_ref = 0;
    }

    sequence<4, size_t> m; m[0] = 1; m[1] = 2; m[2] = 1; m[3] = 2;
    permutation<2> permb; permb.permute(0, 1);
    tensor_transf<2, double> tr(permb);
    tod_diag<4, 2>(ta, m, tr).perform(true, tb);

    compare_ref<2>::compare(testname, tb, tb_ref, 1e-15);

    } catch(exception &e) {
        return fail_test(testname, __FILE__, __LINE__, e.what());
    }

    return 0;
}


/** \test Extract a two diagonals with one index intact and permuted:
        output \f$ b_{kji} = a_{ikjiij} \f$
 **/
int test_8() {

    static const char testname[] = "tod_diag_test::test_8()";

    typedef allocator<double> allocator;

    try {

    size_t ni = 2, nj = 3, nk = 5;
    libtensor::index<3> i3a, i3b;
    i3b[0] = nk - 1; i3b[1] = nj - 1; i3b[2] = ni - 1;
    libtensor::index<6> i6a, i6b;
    i6b[0] = ni - 1; i6b[1] = nk - 1; i6b[2] = nj - 1;
    i6b[3] = ni - 1; i6b[4] = ni - 1; i6b[5] = nj - 1;
    dimensions<3> dims3(index_range<3>(i3a, i3b));
    dimensions<6> dims6(index_range<6>(i6a, i6b));
    size_t sza = dims6.get_size(), szb = dims3.get_size();

    dense_tensor<6, double, allocator> ta(dims6);
    dense_tensor<3, double, allocator> tb(dims3), tb_ref(dims3);

    {
    dense_tensor_ctrl<6, double> tca(ta);
    dense_tensor_ctrl<3, double> tcb(tb), tcb_ref(tb_ref);

    double *pa = tca.req_dataptr();
    double *pb = tcb.req_dataptr();
    double *pb_ref = tcb_ref.req_dataptr();

    for(size_t i = 0; i < sza; i++) pa[i] = drand48();
    for(size_t i = 0; i < szb; i++) pb[i] = drand48();

    for(size_t i = 0; i < ni; i++) {
    for(size_t j = 0; j < nj; j++) {
    for(size_t k = 0; k < nk; k++) {
        libtensor::index<6> idxa;
        idxa[0] = i; idxa[1] = k; idxa[2] = j;
        idxa[3] = i; idxa[4] = i; idxa[5] = j;
        libtensor::index<3> idxb; idxb[0] = k; idxb[1] = j; idxb[2] = i;
        abs_index<6> aidxa(idxa, dims6);
        abs_index<3> aidxb(idxb, dims3);
        pb_ref[aidxb.get_abs_index()] = pa[aidxa.get_abs_index()];
    }
    }
    }

    tca.ret_dataptr(pa); pa = 0;
    tcb.ret_dataptr(pb); pb = 0;
    tcb_ref.ret_dataptr(pb_ref); pb_ref = 0;
    }

    sequence<6, size_t> m;
    m[0] = 1; m[1] = 0; m[2] = 2; m[3] = 1; m[4] = 1; m[5] = 2;
    permutation<3> permb; permb.permute(0, 1).permute(1, 2);
    tensor_transf<3, double> tr(permb);
    tod_diag<6, 3>(ta, m, tr).perform(true, tb);

    compare_ref<3>::compare(testname, tb, tb_ref, 1e-15);

    } catch(exception &e) {
        return fail_test(testname, __FILE__, __LINE__, e.what());
    }

    return 0;
}


/** \test Extract two diagonals with one index intact and permuted:
        output \f$ b_{ijk} = a_{kiijj} \f$
 **/
int test_9() {

    static const char testname[] = "tod_diag_test::test_9()";

    typedef allocator<double> allocator;

    try {

    size_t ni = 2, nj = 3, nk = 5;
    libtensor::index<3> i3a, i3b;
    i3b[0] = ni - 1; i3b[1] = nj - 1; i3b[2] = nk - 1;
    libtensor::index<5> i5a, i5b;
    i5b[0] = nk - 1; i5b[1] = ni - 1; i5b[2] = ni - 1;
    i5b[3] = nj - 1; i5b[4] = nj - 1;
    dimensions<3> dims3(index_range<3>(i3a, i3b));
    dimensions<5> dims5(index_range<5>(i5a, i5b));
    size_t sza = dims5.get_size(), szb = dims3.get_size();

    dense_tensor<5, double, allocator> ta(dims5);
    dense_tensor<3, double, allocator> tb(dims3), tb_ref(dims3);

    {
    dense_tensor_ctrl<5, double> tca(ta);
    dense_tensor_ctrl<3, double> tcb(tb), tcb_ref(tb_ref);

    double *pa = tca.req_dataptr();
    double *pb = tcb.req_dataptr();
    double *pb_ref = tcb_ref.req_dataptr();

    for(size_t i = 0; i < sza; i++) pa[i] = drand48();
    for(size_t i = 0; i < szb; i++) pb[i] = drand48();

    for(size_t i = 0; i < ni; i++) {
    for(size_t j = 0; j < nj; j++) {
    for(size_t k = 0; k < nk; k++) {
        libtensor::index<5> idxa; idxa[0] = k; idxa[1] = i; idxa[2] = i;
        idxa[3] = j; idxa[4] = j;
        libtensor::index<3> idxb; idxb[0] = i; idxb[1] = j; idxb[2] = k;
        abs_index<5> aidxa(idxa, dims5);
        abs_index<3> aidxb(idxb, dims3);
        pb_ref[aidxb.get_abs_index()] = pa[aidxa.get_abs_index()];
    }
    }
    }

    tca.ret_dataptr(pa); pa = 0;
    tcb.ret_dataptr(pb); pb = 0;
    tcb_ref.ret_dataptr(pb_ref); pb_ref = 0;
    }

    sequence<5, size_t> m; m[0] = 0; m[1] = 1; m[2] = 1; m[3] = 2; m[4] = 2;
    permutation<3> permb; permb.permute(0, 1).permute(1, 2);
    tensor_transf<3, double> tr(permb);
    tod_diag<5, 3>(ta, m, tr).perform(true, tb);

    compare_ref<3>::compare(testname, tb, tb_ref, 1e-15);

    } catch(exception &e) {
        return fail_test(testname, __FILE__, __LINE__, e.what());
    }

    return 0;
}


int main() {

    srand48(time(0));

    return

    test_1() |
    test_2() |
    test_3() |
    test_4() |
    test_5() |
    test_6() |
    test_7() |
    test_8() |
    test_9() |

    0;
}



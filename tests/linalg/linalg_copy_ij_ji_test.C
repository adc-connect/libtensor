#include "test_utils.h"
#include <libtensor/exception.h>
#include <libtensor/linalg/linalg.h>
#include <libtensor/linalg/linalg_generic.h>
#include <sstream>
#include <vector>

using namespace libtensor;

int test_copy_ij_ji(size_t ni, size_t nj, size_t sja, size_t sic) {

  std::ostringstream ss;
  ss << "test_copy_ij_ji(" << ni << ", " << nj << ", " << sja << ", " << sic << ")";
  std::string tnss = ss.str();

  try {

    size_t sza = nj * sja, szc = ni * sic;
    std::vector<double> a(sza, 0.0), c(szc, 0.0), c_ref(szc, 0.0);

    for (size_t i = 0; i < sza; i++) a[i] = drand48();
    for (size_t i = 0; i < szc; i++) c[i] = c_ref[i] = drand48();

    linalg::copy_ij_ji(0, ni, nj, &a[0], sja, &c[0], sic);
    linalg_generic::copy_ij_ji(0, ni, nj, &a[0], sja, &c_ref[0], sic);

    for (size_t i = 0; i < szc; i++) {
      if (!cmp(c[i] - c_ref[i], c_ref[i])) {
        return fail_test(tnss.c_str(), __FILE__, __LINE__, "Incorrect result.");
      }
    }

  } catch (exception& e) {
    return fail_test(tnss.c_str(), __FILE__, __LINE__, e.what());
  }

  return 0;
}

int main() {

  return

        test_copy_ij_ji(1, 1, 1, 1) | test_copy_ij_ji(1, 2, 1, 2) |
        test_copy_ij_ji(2, 1, 2, 1) | test_copy_ij_ji(16, 16, 16, 16) |
        test_copy_ij_ji(3, 17, 5, 17) | test_copy_ij_ji(2, 2, 2, 3) |
        test_copy_ij_ji(2, 2, 4, 3) |

        0;
}


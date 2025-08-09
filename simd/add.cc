#include <iostream>
#include <x86intrin.h>
#include <cassert>
#include <format>

__attribute__((target("avx2")))

int main() {
  std::array<double, 4 * 100 + 3> a1{};
  std::array<double, 4 * 100 + 3> a2{};
  std::array<double, 4 * 100 + 3> result{};
  for (int i = 0; i < a1.size(); ++i) {
    a1[i] = i;
    a2[i] = 2 * i;
  }

  int index = 0;
  for (; index <= a1.size() - 4; index += 4) {
    __m256d reg1 = _mm256_loadu_pd(a1.data() + index);
    __m256d reg2 = _mm256_loadu_pd(a2.data() + index);
    __m256d reg3 = _mm256_add_pd(reg1, reg2);
    _mm256_storeu_pd(result.data() + index, reg3);
  }

  for (; index < a1.size(); ++index) {
    result[index] += a1[index] + a2[index];
  }

  for (int i = 0; i < a1.size(); ++i) {
    assert(result[i] == a1[i] + a2[i]);
  }

  int analytic_sum = 3 * (4 * 100 + 2) * (4 * 100 + 2 + 1) / 2;
  __m256d simd_running_total = _mm256_setzero_pd();
  int rindex = 0;
  for (; rindex <= result.size() - 4; rindex += 4) {
    __m256d reg = _mm256_loadu_pd(result.data() + rindex);
    simd_running_total = _mm256_add_pd(simd_running_total, reg);
  }

  // {d1, d2, d3, d4}
  // -> {d1, d2} ; {d3, d4}
  // -> {d1 + d3, d2 + d4}
  // -> {(d1 + d3) + (d2 + d4), (d2 + d4) + (d2 + d4)}
  // -> d1 + d3 + d2 + d4
  __m128d lower = _mm256_castpd256_pd128(simd_running_total);
  __m128d upper = _mm256_extractf128_pd(simd_running_total, 1);
  __m128d sum_lower_upper = _mm_add_pd(lower, upper);
  __m128d upper_upper = _mm_unpackhi_pd(sum_lower_upper, sum_lower_upper);
  __m128d simd_reduction = _mm_add_pd(sum_lower_upper, upper_upper);
  double simd_sum = _mm_cvtsd_f64(simd_reduction);

  for (; rindex < result.size(); ++rindex) {
    simd_sum += result[rindex];
  } 
  std::cout
    << std::format(
        "Analytic sum: {}. SIMD sum: {}",
        analytic_sum,
        simd_sum
    )
    << std::endl;
}

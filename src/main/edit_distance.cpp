#include "include/edit_distance.h"
#include <algorithm>
#include <cmath>
#include <cstdint>
#include <vector>

namespace spell_sweeper {
std::uint8_t
edit_distance::get_damerau_levenshtein(const std::string_view word_a,
                                       const std::string_view word_b,
                                       std::uint8_t alphabet_length) {
  std::uint8_t length_a = word_a.size();
  std::uint8_t length_b = word_b.size();
  std::uint8_t infinity = length_a + length_b;

  std::uint8_t dp[length_a + 2][length_b + 2];
  dp[0][0] = infinity;

  for (int i = 0; i <= length_a; i++) {
    dp[i + 1][1] = i;
    dp[i + 1][0] = infinity;
  }
  for (int j = 0; j <= length_b; j++) {
    dp[1][j + 1] = j;
    dp[0][j + 1] = infinity;
  }

  int da[alphabet_length];
  for (int i = 0; i < alphabet_length; i++)
    da[i] = 0;

  for (int i = 1; i <= length_a; i++) {
    int db = 0;
    for (int j = 1; j <= length_b; j++) {
      int k = da[(std::size_t)word_b[j - 1]];
      int l = db;
      int d = (word_a[i - 1] == word_b[j - 1]) ? 0 : 1;
      if (d == 0)
        db = j;
      dp[i + 1][j + 1] =
          std::min({dp[i][j] + d, dp[i + 1][j] + 1, dp[i][j + 1] + 1,
                    dp[k][l] + (i - k - 1) + 1 + (j - l - 1)});
    }
    da[(std::size_t)word_a[i - 1]] = i;
  }

  return dp[length_a + 1][length_b + 1];
}

double edit_distance::get_jaro(const std::string_view word_a,
                               const std::string_view word_b) {
  if (word_a == word_b)
    return 1;

  std::uint8_t length_a = word_a.length();
  std::uint8_t length_b = word_b.length();

  if (length_a == 0 || length_b == 0)
    return 0.0;

  std::uint8_t max_dist =
      (std::uint8_t)std::floor(std::max(length_a, length_b) / 2) - 1;
  std::uint8_t match = 0;

  std::vector<std::uint8_t> hash_a(length_a, 0);
  std::vector<std::uint8_t> hash_b(length_b, 0);

  for (uint8_t i = 0; i < length_a; i++)
    for (uint8_t j = std::max(0, i - max_dist);
         j < std::min<std::uint8_t>(length_b, i + max_dist + 1); j++)
      if (word_a[i] == word_b[j] && hash_b[j] == 0) {
        hash_a[i] = 1;
        hash_b[j] = 1;
        match++;
        break;
      }

  if (match == 0)
    return 0.0;

  double transpositions = 0;
  std::uint8_t point = 0;

  for (std::uint8_t i = 0; i < length_a; i++)
    if (hash_a[i]) {
      while (hash_b[point] == 0)
        point++;
      if (word_a[i] != word_b[point++])
        transpositions++;
    }

  transpositions /= 2;

  return (((double)match) / ((double)length_a) +
          ((double)match) / ((double)length_b) +
          ((double)match - transpositions) / ((double)match)) /
         3.0;
}

double edit_distance::get_jaro_winkler(const std::string_view word_a,
                                       const std::string_view word_b) {
  double jaro = get_jaro(word_a, word_b);
  if (jaro > 0.7) {
    std::uint8_t prefix = 0;

    for (std::uint8_t i = 0; i < std::min(word_a.length(), word_b.length());
         i++)
      if (word_a[i] == word_b[i])
        prefix++;
      else
        break;

    prefix = std::min<std::uint8_t>(4, prefix);
    jaro += 0.1 * prefix * (1 - jaro);
  }

  return jaro;
}
} // namespace spell_sweeper

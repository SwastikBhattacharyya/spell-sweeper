#include "include/edit_distance.h"
#include <algorithm>
#include <cstdint>

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
} // namespace spell_sweeper

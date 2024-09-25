#ifndef SPELL_SWEEPER_EDIT_DISTANCE_H
#define SPELL_SWEEPER_EDIT_DISTANCE_H

#include <cstdint>
#include <string_view>

namespace spell_sweeper {
class edit_distance {
public:
  static std::uint8_t get_damerau_levenshtein(const std::string_view word_a,
                                              const std::string_view word_b,
                                              std::uint8_t alphabet_length);
  static double get_jaro(const std::string_view word_a,
                         const std::string_view word_b);
  static double get_jaro_winkler(const std::string_view word_a,
                                 const std::string_view word_b);
};
} // namespace spell_sweeper

#endif // SPELL_SWEEPER_EDIT_DISTANCE_H

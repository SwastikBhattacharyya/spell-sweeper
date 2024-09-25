#ifndef SPELL_SWEEPER_INCLUDE_PROCESSOR_H
#define SPELL_SWEEPER_INCLUDE_PROCESSOR_H

#include <array>
#include <string>
#include <vector>

namespace spell_sweeper {
class processor {
public:
  static std::vector<std::array<std::string, 3>>
  split_input(const std::string& input);
  static std::string
  join_split_words(const std::vector<std::array<std::string, 3>>& input);
  static std::vector<std::string> get_words(const std::string& input);
  static std::array<std::string, 3> split_word(const std::string& word);
  static std::string join_word(const std::array<std::string, 3> split_word);
  static std::string replace_word(const std::string& new_word,
                                  const std::string& old_word);
};
} // namespace spell_sweeper

#endif //! SPELL_SWEEPER_INCLUDE_PROCESSOR_H

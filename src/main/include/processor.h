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
    static std::vector<std::string> get_words(const std::string& input);
    static std::array<std::string, 3> split_word(const std::string& word);
};
} // namespace spell_sweeper

#endif //! SPELL_SWEEPER_INCLUDE_PROCESSOR_H

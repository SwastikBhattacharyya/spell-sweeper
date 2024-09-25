#include "include/processor.h"

#include <stdint.h>
#include <string>
#include <vector>

namespace spell_sweeper {
std::vector<std::array<std::string, 3>>
processor::split_input(const std::string& word) {
  std::vector<std::array<std::string, 3>> split_input;
  std::vector<std::string> words = processor::get_words(word);
  std::array<std::string, 3> split_word;

  for (std::size_t i = 0; i < words.size(); i++) {
    split_word = processor::split_word(words[i]);
    split_input.push_back(split_word);
  }

  return split_input;
}

std::string processor::join_split_words(
    const std::vector<std::array<std::string, 3>>& input) {
  std::string joined_string = "";
  for (size_t i = 0; i < input.size(); i++)
    joined_string += processor::join_word(input[i]);

  return joined_string;
}

std::vector<std::string> processor::get_words(const std::string& input) {
  std::vector<std::string> results;
  std::string temp;

  for (uint8_t i = 0; i < input.size(); i++) {
    if (input[i] == ' ' || input[i] == '\n') {
      if (!temp.empty()) {
        results.push_back(temp);
        temp.clear();
      }
      results.push_back(std::string(1, input[i]));
    } else
      temp += input[i];
  }

  if (!temp.empty())
    results.push_back(temp);

  return results;
}

std::array<std::string, 3> processor::split_word(const std::string& word) {
  std::string starting_punctuations;
  std::string middle_word;
  std::string ending_punctuations;

  if (word == " " || word == "\n")
    return std::array<std::string, 3>{"", word, ""};

  for (uint8_t i = 0; i < word.size(); i++) {
    char character = word[i];
    if (!std::isalnum(character)) {
      starting_punctuations += character;
    } else {
      middle_word = word.substr(i);
      break;
    }
  }

  if (middle_word.size() == 0)
    return std::array<std::string, 3>{starting_punctuations, "", ""};

  for (uint8_t i = middle_word.size() - 1; i >= 0; i--) {
    char character = middle_word[i];
    if (std::isalnum(character)) {
      ending_punctuations = middle_word.substr(i + 1);
      middle_word = middle_word.substr(0, i + 1);
      break;
    }
  }

  return std::array<std::string, 3>{starting_punctuations, middle_word,
                                    ending_punctuations};
}

std::string processor::join_word(const std::array<std::string, 3> split_word) {
  std::string word = split_word[0] + split_word[1] + split_word[2];
  return word;
}
} // namespace spell_sweeper

#include "include/app.h"
#include "include/processor.h"
#include <algorithm>
#include <boost/archive/binary_iarchive.hpp>
#include <boost/archive/binary_oarchive.hpp>
#include <fstream>
#include <iostream>
#include <iterator>

namespace spell_sweeper {
app::app(const std::string& input_file, const std::string& output_file) {
  this->input_file = input_file;
  this->output_file = output_file;
}

int8_t app::init() {
  std::ifstream file("resources/data.bin");
  if (file.fail()) {
    std::ifstream words_file("resources/words.txt");
    if (words_file.fail())
      return -1;
    std::vector<std::string> words = app_data.read_dictionary(words_file);
    words_file.close();

    this->app_data.init_bk_tree(words);
    this->app_data.init_bloom_filter();
    return 0;
  }
  boost::archive::binary_iarchive read_archive{file};
  read_archive >> this->app_data;
  file.close();
  return 0;
}

int8_t app::run() {
  std::ifstream file(this->input_file);
  if (file.fail()) {
    std::cout << "Failed to open input file" << '\n';
    return -1;
  }

  std::string input((std::istreambuf_iterator<char>(file)),
                    std::istreambuf_iterator<char>());
  std::vector<std::array<std::string, 3>> split_input =
      spell_sweeper::processor::split_input(input);

  for (uint64_t i = 0; i < split_input.size(); i++) {
    std::string word = split_input[i][1];
    if (word == " " || word == "\n")
      continue;
    std::string word_lower = word;
    std::transform(word_lower.begin(), word_lower.end(), word_lower.begin(),
                   [](unsigned char c) { return std::tolower(c); });

    if (!this->app_data.filter.lookup(word_lower) ||
        (this->app_data.filter.lookup(word_lower) &&
         this->app_data.tree.search(word_lower) == -1)) {

      uint8_t tolerance = 1;
      std::vector<std::string_view> suggestions =
          this->app_data.tree.get_similar_words(word_lower, tolerance);
      while (true) {
        std::cout << "\033[2J\033[1;1H";
        std::cout << word << " is spelled incorrectly" << '\n';
        std::cout << "Suggestions: " << '\n';
        for (uint64_t i = 0; i < suggestions.size(); i++)
          std::cout << i + 1 << ": " << suggestions[i] << '\n';
        std::cout << '\n';
        std::cout << "1. Apply Suggestion (value will be clamped)" << '\n';
        std::cout << "2. Add word to dictionary" << '\n';
        std::cout << "3. Ignore word" << '\n';

        uint16_t user_input;
        std::cout << ">>> ";
        std::cin >> user_input;
        if (user_input == 1) {
          uint64_t suggestion;
          std::cout << "Enter suggestion number: ";
          std::cin >> suggestion;
          suggestion = std::clamp((uint64_t)suggestion, (uint64_t)1,
                                  (uint64_t)suggestions.size());
          split_input[i][1] = processor::replace_word(
              std::string(suggestions[suggestion - 1]), word);
          break;
        } else if (user_input == 2) {
          this->app_data.tree.add(word_lower);
          this->app_data.filter = spell_sweeper::bloom_filter();
          this->app_data.init_bloom_filter();
          std::ofstream file_write("resources/data.bin");
          boost::archive::binary_oarchive write_archive{file_write};
          write_archive << this->app_data;
          file_write.close();
          break;
        } else if (user_input == 3) {
          break;
        }
      }
    }
  }

  std::string joined = spell_sweeper::processor::join_split_words(split_input);
  std::ofstream write_file(this->output_file);
  write_file << joined;
  write_file.close();

  return 0;
}
} // namespace spell_sweeper

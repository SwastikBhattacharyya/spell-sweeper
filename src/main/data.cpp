#include "include/data.h"
#include <cctype>

namespace spell_sweeper {
std::vector<std::string>
spell_sweeper::data::read_dictionary(std::ifstream& file) {
    std::vector<std::string> words;
    std::string word;
    while (!file.eof()) {
        std::getline(file, word);
        std::transform(word.begin(), word.end(), word.begin(),
                       [](unsigned char c) { return std::tolower(c); });
        if (!word.empty())
            words.push_back(word);
    }

    return words;
}

void spell_sweeper::data::init_bk_tree(const std::vector<std::string>& words) {
    this->tree = bk_tree(words);
}

void spell_sweeper::data::init_bloom_filter() {
    std::vector<std::string_view> words =
        this->tree.get_similar_words("", MAX_WORD_LEN);
    this->filter.init(words.size(), 0.01);
    for (const std::string_view& word : words)
        this->filter.insert(word);
}
} // namespace spell_sweeper

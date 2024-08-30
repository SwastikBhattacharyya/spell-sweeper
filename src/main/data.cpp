#include "include/data.h"
#include <cctype>

namespace spell_sweeper {
void spell_sweeper::data::read_dictionary(std::ifstream& file) {
    std::string word;
    while (!file.eof()) {
        std::getline(file, word);
        std::transform(word.begin(), word.end(), word.begin(),
                       [](unsigned char c) { return std::tolower(c); });
        this->words.push_back(word);
    }
}

void spell_sweeper::data::init_bk_tree() { this->tree = bk_tree(this->words); }

void spell_sweeper::data::init_bloom_filter() {
    this->filter.init(this->words.size(), 0.01);
    for (const std::string& word : this->words)
        this->filter.insert(word);
}
} // namespace spell_sweeper

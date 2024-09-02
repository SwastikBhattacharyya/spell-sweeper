#ifndef SPELL_SWEEPER_INCLUDE_DATA_H
#define SPELL_SWEEPER_INCLUDE_DATA_H

#include "include/bk_tree.h"
#include "include/bloom_filter.h"
#include <fstream>
#include <string>
#include <vector>

namespace spell_sweeper {
#define MAX_WORD_LEN 128

class data {
  public:
    bk_tree tree;
    bloom_filter filter;

  private:
    friend class boost::serialization::access;

    template <typename Archive>
    void serialize(Archive& archive, const unsigned int version) {
        archive& this->tree;
        archive& this->filter;
    }

  public:
    data() = default;
    std::vector<std::string> read_dictionary(std::ifstream& file);
    void init_bk_tree(const std::vector<std::string>& words);
    void init_bloom_filter();
};
}; // namespace spell_sweeper

#endif // !SPELL_SWEEPER_INCLUDE_DATA_H

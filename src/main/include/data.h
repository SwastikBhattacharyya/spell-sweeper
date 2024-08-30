#ifndef SPELL_SWEEPER_INCLUDE_DATA_H
#define SPELL_SWEEPER_INCLUDE_DATA_H

#include "include/bk_tree.h"
#include "include/bloom_filter.h"
#include <fstream>
#include <string>
#include <vector>

namespace spell_sweeper {
class data {
  public:
    std::vector<std::string> words;
    bk_tree tree;
    bloom_filter filter;

  public:
    data() = default;
    void read_dictionary(std::ifstream& file);
    void init_bk_tree();
    void init_bloom_filter();
};
}; // namespace spell_sweeper

#endif // !SPELL_SWEEPER_INCLUDE_DATA_H

#ifndef SPELL_SWEEPER_INCLUDE_BK_TREE_H
#define SPELL_SWEEPER_INCLUDE_BK_TREE_H

#include <cstdint>
#include <memory>
#include <string_view>
#include <unordered_map>
#include <vector>

namespace spell_sweeper {
class bk_tree {
  public:
    class node {
      public:
        std::string_view word;
        std::unordered_map<int, std::shared_ptr<node>> next;

      public:
        node(const std::string_view& word);
    };
    std::shared_ptr<node> head;

  public:
    int add(const std::string_view& word);
    int search(const std::string_view& word);
    std::vector<std::string_view>
    get_similar_words(const std::string_view& word,
                      std::uint8_t tolerance) const;
};
} // namespace spell_sweeper

#endif // !SPELL_SWEEPER_INCLUDE_BK_TREE_H

#ifndef SPELL_SWEEPER_INCLUDE_BK_TREE_H
#define SPELL_SWEEPER_INCLUDE_BK_TREE_H

#include <cstdint>
#include <memory>
#include <string>
#include <unordered_map>
#include <vector>

namespace spell_sweeper {
class bk_tree {
  public:
    class node {
      public:
        std::string word;
        std::unordered_map<int, std::shared_ptr<node>> next;

      public:
        node(const std::string_view& word);
    };
    std::shared_ptr<node> head;

  private:
    int add_node_from(std::shared_ptr<bk_tree::node> node,
                      std::shared_ptr<bk_tree::node> current);

  public:
    bk_tree() = default;
    bk_tree(std::vector<std::string> words);
    int add(const std::string_view& word);
    int search(const std::string_view& word);
    int remove(const std::string_view& word);
    std::vector<std::string_view>
    get_similar_words(const std::string_view& word,
                      std::uint8_t tolerance) const;
};
} // namespace spell_sweeper

#endif // !SPELL_SWEEPER_INCLUDE_BK_TREE_H

#ifndef SPELL_SWEEPER_INCLUDE_BK_TREE_H
#define SPELL_SWEEPER_INCLUDE_BK_TREE_H

#include <boost/serialization/map.hpp>
#include <boost/serialization/shared_ptr.hpp>
#include <cstdint>
#include <map>
#include <memory>
#include <string>
#include <vector>

namespace spell_sweeper {
class bk_tree {
public:
  class node {
  public:
    const std::string word;
    std::map<int8_t, std::shared_ptr<node>> next;

  private:
    friend class boost::serialization::access;

    template <typename Archive>
    void serialize(Archive& archive, const unsigned int version) {
      archive& const_cast<std::string&>(this->word);
      archive& this->next;
    }

  public:
    node() = default;
    node(const std::string_view& word);
  };
  std::shared_ptr<node> head;

private:
  int8_t add_node_from(std::shared_ptr<bk_tree::node> node,
                       std::shared_ptr<bk_tree::node> current);

private:
  friend class boost::serialization::access;

  template <typename Archive>
  void serialize(Archive& archive, const unsigned int version) {
    archive& this->head;
  }

public:
  bk_tree() = default;
  bk_tree(std::vector<std::string> words);
  int8_t add(const std::string_view& word);
  int8_t search(const std::string_view& word);
  int8_t remove(const std::string_view& word);
  std::vector<std::string_view> get_similar_words(const std::string_view& word,
                                                  std::uint8_t tolerance) const;
};
} // namespace spell_sweeper

#endif // !SPELL_SWEEPER_INCLUDE_BK_TREE_H

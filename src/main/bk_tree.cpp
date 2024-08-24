#include "include/bk_tree.h"

namespace spell_sweeper {
bk_tree::node::node(const std::string_view& word) { this->word = word; }
} // namespace spell_sweeper

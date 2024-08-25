#include "include/bk_tree.h"
#include "include/edit_distance.h"
#include <cstdint>
#include <memory>

namespace spell_sweeper {
bk_tree::node::node(const std::string_view& word) { this->word = word; }

int bk_tree::add(const std::string_view& word) {
    if (this->head == nullptr) {
        this->head = std::make_shared<bk_tree::node>(bk_tree::node(word));
        return 0;
    }

    std::shared_ptr<bk_tree::node> current_node = this->head;

    while (true) {
        if (current_node->word == word)
            return 0;
        std::uint8_t distance = edit_distance::get_damerau_levenshtein(
            current_node->word, word, 255);
        if (current_node->next.find(distance) == current_node->next.end()) {
            current_node->next[distance] =
                std::make_shared<bk_tree::node>(bk_tree::node(word));
            return 0;
        } else
            current_node = current_node->next[distance];
    }

    return -1;
}
} // namespace spell_sweeper

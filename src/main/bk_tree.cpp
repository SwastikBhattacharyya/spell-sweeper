#include "include/bk_tree.h"
#include "include/edit_distance.h"
#include <algorithm>
#include <stack>

namespace spell_sweeper {
bk_tree::node::node(const std::string_view& word) { this->word = word; }

int bk_tree::add_node_from(std::shared_ptr<bk_tree::node> node,
                           std::shared_ptr<bk_tree::node> current) {
    while (true) {
        std::uint8_t distance = edit_distance::get_damerau_levenshtein(
            node->word, current->word, 255);
        if (current->next.find(distance) == current->next.end()) {
            current->next[distance] = node;
            break;
        } else
            current = current->next[distance];
    }

    return 0;
}

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

int bk_tree::search(const std::string_view& word) {
    if (this->head == nullptr)
        return -1;

    std::shared_ptr<bk_tree::node> current_node = this->head;

    while (true) {
        std::uint8_t distance = edit_distance::get_damerau_levenshtein(
            word, current_node->word, 255);
        if (distance == 0)
            return 0;
        else if (current_node->next.find(distance) != current_node->next.end())
            current_node = current_node->next[distance];
        else
            return -1;
    }
}

int bk_tree::remove(const std::string_view& word) {
    if (this->head == nullptr)
        return -1;

    if (this->head->word == word) {
        std::shared_ptr<bk_tree::node> removed_head = this->head;
        this->head = nullptr;
        if (removed_head->next.empty())
            return 0;

        int first = removed_head->next.begin()->first;
        std::shared_ptr<bk_tree::node> first_node =
            removed_head->next.begin()->second;

        this->head = first_node;
        for (const std::pair<const int, std::shared_ptr<bk_tree::node>>& node :
             removed_head->next) {
            if (node.first == first)
                continue;

            this->add_node_from(node.second, this->head);
        }

        return 0;
    }

    std::shared_ptr<bk_tree::node> current_node = this->head;
    std::shared_ptr<bk_tree::node> parent_node;
    std::uint8_t index;

    while (true) {
        std::uint8_t distance = edit_distance::get_damerau_levenshtein(
            word, current_node->word, 255);
        if (distance == 0)
            break;
        else if (current_node->next.find(distance) !=
                 current_node->next.end()) {
            parent_node = current_node;
            index = distance;
            current_node = current_node->next[distance];
        } else
            return -1;
    }

    parent_node->next.erase(index);

    std::vector<std::shared_ptr<bk_tree::node>> children;
    for (const std::pair<const int, std::shared_ptr<bk_tree::node>>& node :
         current_node->next)
        children.push_back(node.second);

    for (const std::shared_ptr<bk_tree::node>& node : children)
        this->add_node_from(node, parent_node);

    return 0;
}

std::vector<std::string_view>
bk_tree::get_similar_words(const std::string_view& word,
                           std::uint8_t tolerance) const {
    std::vector<std::string_view> words;
    std::stack<std::shared_ptr<bk_tree::node>> stack;
    stack.push(this->head);

    while (!stack.empty()) {
        std::shared_ptr<bk_tree::node> current = stack.top();
        stack.pop();
        std::uint8_t distance =
            edit_distance::get_damerau_levenshtein(word, current->word, 255);

        if (distance <= tolerance && word != current->word)
            words.push_back(current->word);

        std::uint8_t tolerance_start = std::max(1, distance - tolerance);
        std::uint8_t tolerance_end = distance + tolerance;

        for (std::uint8_t i = tolerance_start; i <= tolerance_end; i++)
            if (current->next.find(i) != current->next.end())
                stack.push(current->next[i]);
    }

    return words;
}
} // namespace spell_sweeper

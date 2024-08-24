#include "include/bk_tree.h"
#include <gtest/gtest.h>
#include <memory>

TEST(bk_tree_test, node_create) {
    spell_sweeper::bk_tree::node node = spell_sweeper::bk_tree::node("Hello");
    ASSERT_EQ(node.word, "Hello");
    ASSERT_EQ(node.next.size(), 0);
}

TEST(bk_tree_test, node_link) {
    spell_sweeper::bk_tree::node first = spell_sweeper::bk_tree::node("Hello");
    spell_sweeper::bk_tree::node second = spell_sweeper::bk_tree::node("Hi");

    first.next[4] = std::make_shared<spell_sweeper::bk_tree::node>(second);

    ASSERT_EQ(first.word, "Hello");
    ASSERT_EQ(second.word, "Hi");
    ASSERT_EQ(first.next.size(), 1);
    ASSERT_EQ(second.next.size(), 0);
    ASSERT_EQ(first.next[4].use_count(), 1);
    ASSERT_EQ(first.next[4]->word, second.word);
    ASSERT_EQ(first.next[4]->next.size(), second.next.size());

    std::shared_ptr<spell_sweeper::bk_tree::node> ptr = first.next[4];
    ptr->word = "Hm";

    ASSERT_EQ(first.next[4]->word, "Hm");
    ASSERT_EQ(first.next[4].use_count(), 2);
}

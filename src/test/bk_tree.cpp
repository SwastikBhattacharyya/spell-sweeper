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

TEST(bk_tree_test, add) {
    spell_sweeper::bk_tree tree = spell_sweeper::bk_tree();
    ASSERT_EQ(tree.add("this"), 0);
    ASSERT_EQ(tree.add("thus"), 0);
    ASSERT_EQ(tree.add("these"), 0);
    ASSERT_EQ(tree.add("thin"), 0);
    ASSERT_EQ(tree.add("thud"), 0);

    EXPECT_EQ(tree.head->word, "this");
    EXPECT_EQ(tree.head->next[1]->word, "thus");
    EXPECT_EQ(tree.head->next[2]->word, "these");
    EXPECT_EQ(tree.head->next[1]->next[2]->word, "thin");
    EXPECT_EQ(tree.head->next[2]->next[3]->word, "thud");
}

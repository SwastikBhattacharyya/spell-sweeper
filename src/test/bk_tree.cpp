#include "include/bk_tree.h"
#include <algorithm>
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

TEST(bk_tree_test, search) {
    spell_sweeper::bk_tree tree = spell_sweeper::bk_tree();
    ASSERT_EQ(tree.add("this"), 0);
    ASSERT_EQ(tree.add("thus"), 0);
    ASSERT_EQ(tree.add("these"), 0);
    ASSERT_EQ(tree.add("thin"), 0);
    ASSERT_EQ(tree.add("thud"), 0);

    EXPECT_EQ(tree.search("this"), 0);
    EXPECT_EQ(tree.search("thus"), 0);
    EXPECT_EQ(tree.search("these"), 0);
    EXPECT_EQ(tree.search("thin"), 0);
    EXPECT_EQ(tree.search("thud"), 0);

    EXPECT_EQ(tree.search("should"), -1);
    EXPECT_EQ(tree.search("neck"), -1);
    EXPECT_EQ(tree.search("heart"), -1);
}

TEST(bk_tree_test, remove) {
    spell_sweeper::bk_tree tree = spell_sweeper::bk_tree();
    ASSERT_EQ(tree.add("this"), 0);
    ASSERT_EQ(tree.add("thus"), 0);
    ASSERT_EQ(tree.add("these"), 0);
    ASSERT_EQ(tree.add("thin"), 0);
    ASSERT_EQ(tree.add("thud"), 0);

    ASSERT_EQ(tree.remove("thus"), 0);

    EXPECT_EQ(tree.search("this"), 0);
    EXPECT_EQ(tree.search("these"), 0);
    EXPECT_EQ(tree.search("thin"), 0);
    EXPECT_EQ(tree.search("thud"), 0);
    EXPECT_EQ(tree.search("thus"), -1);
    EXPECT_EQ(tree.head->next.size(), 2);
    EXPECT_EQ(tree.head->next[1]->next.size(), 0);
    EXPECT_EQ(tree.head->next[2]->next.size(), 1);
    EXPECT_EQ(tree.head->next[2]->next[3]->next.size(), 0);

    ASSERT_EQ(tree.remove("these"), 0);
    EXPECT_EQ(tree.search("this"), 0);
    EXPECT_EQ(tree.search("these"), -1);
    EXPECT_EQ(tree.search("thin"), 0);
    EXPECT_EQ(tree.search("thud"), 0);
    EXPECT_EQ(tree.head->next.size(), 2);
    EXPECT_EQ(tree.head->next[1]->next.size(), 0);
    EXPECT_EQ(tree.head->next[2]->next.size(), 0);

    ASSERT_EQ(tree.remove("this"), -1);
}

TEST(bk_tree_test, get_similar_words) {
    spell_sweeper::bk_tree tree = spell_sweeper::bk_tree();

    ASSERT_EQ(tree.add("this"), 0);
    ASSERT_EQ(tree.add("thus"), 0);
    ASSERT_EQ(tree.add("these"), 0);
    ASSERT_EQ(tree.add("thin"), 0);
    ASSERT_EQ(tree.add("thud"), 0);

    std::vector<std::string_view> words = tree.get_similar_words("this", 1);
    EXPECT_EQ(words.size(), 2);
    EXPECT_NE(std::find(words.begin(), words.end(), "thus"), words.end());
    EXPECT_NE(std::find(words.begin(), words.end(), "thin"), words.end());
    EXPECT_EQ(std::find(words.begin(), words.end(), "these"), words.end());
}

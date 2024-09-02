#include "include/data.h"
#include <gtest/gtest.h>

TEST(data_test, get_dictionary) {
    spell_sweeper::data app_data;
    std::ifstream file("resources/words.txt");
    ASSERT_NO_THROW(app_data.read_dictionary(file));
    file.close();
}

TEST(data_test, init_bk_tree) {
    spell_sweeper::data app_data;
    std::ifstream file("resources/words.txt");
    std::vector<std::string> words = app_data.read_dictionary(file);
    file.close();

    ASSERT_NO_THROW(app_data.init_bk_tree(words));

    for (const auto& word : words)
        EXPECT_EQ(app_data.tree.search(word), 0);
}

TEST(data_test, init_bloom_filter) {
    spell_sweeper::data app_data;
    std::ifstream file("resources/words.txt");
    std::vector<std::string> words = app_data.read_dictionary(file);
    file.close();

    ASSERT_NO_THROW(app_data.init_bk_tree(words));
    ASSERT_NO_THROW(app_data.init_bloom_filter());

    for (const auto& word : words)
        EXPECT_NE(app_data.filter.lookup(word), false);
}

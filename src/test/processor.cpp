#include "include/processor.h"
#include <gtest/gtest.h>

TEST(processor_test, split_input) {
    std::string test = "'This is\"\" a '\n$%^";
    std::vector<std::array<std::string, 3>> split_test =
        spell_sweeper::processor::split_input(test);

    EXPECT_EQ(split_test[0][0], "'");
    EXPECT_EQ(split_test[0][1], "This");
    EXPECT_EQ(split_test[0][2], "");
    EXPECT_EQ(split_test[1][1], " ");
    EXPECT_EQ(split_test[2][1], "is");
    EXPECT_EQ(split_test[2][2], "\"\"");
    EXPECT_EQ(split_test[3][1], " ");
    EXPECT_EQ(split_test[4][1], "a");
    EXPECT_EQ(split_test[5][1], " ");
    EXPECT_EQ(split_test[6][0], "'");
    EXPECT_EQ(split_test[7][1], "\n");
    EXPECT_EQ(split_test[8][0], "$%^");
}

TEST(processor_test, get_words) {
    std::string test = "Hello World\nThis is a test";
    std::vector<std::string> words = spell_sweeper::processor::get_words(test);

    EXPECT_EQ(words[0], "Hello");
    EXPECT_EQ(words[1], " ");
    EXPECT_EQ(words[2], "World");
    EXPECT_EQ(words[3], "\n");
    EXPECT_EQ(words[4], "This");
    EXPECT_EQ(words[5], " ");
    EXPECT_EQ(words[6], "is");
    EXPECT_EQ(words[7], " ");
    EXPECT_EQ(words[8], "a");
    EXPECT_EQ(words[9], " ");
    EXPECT_EQ(words[10], "test");
}

TEST(processor_test, split_word) {
    std::string word1 = ".$%word.$'";
    std::array<std::string, 3> word1_split =
        spell_sweeper::processor::split_word(word1);
    EXPECT_EQ(word1_split[0], ".$%");
    EXPECT_EQ(word1_split[1], "word");
    EXPECT_EQ(word1_split[2], ".$'");

    std::string word2 = "\"'word'\"";
    std::array<std::string, 3> word2_split =
        spell_sweeper::processor::split_word(word2);

    EXPECT_EQ(word2_split[0], "\"'");
    EXPECT_EQ(word2_split[1], "word");
    EXPECT_EQ(word2_split[2], "'\"");

    std::string word3 = "word";
    std::array<std::string, 3> word3_split =
        spell_sweeper::processor::split_word(word3);

    EXPECT_EQ(word3_split[0], "");
    EXPECT_EQ(word3_split[1], "word");
    EXPECT_EQ(word3_split[2], "");
}

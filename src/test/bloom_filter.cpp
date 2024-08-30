#include "include/bloom_filter.h"
#include <algorithm>
#include <fstream>
#include <gtest/gtest.h>

TEST(bloom_filter_test, insert_test) {
    spell_sweeper::bloom_filter filter(5, 0.01);
    filter.insert("clear");
    filter.insert("this");
    filter.insert("these");
    filter.insert("that");
    filter.insert("those");

    EXPECT_FALSE(filter.lookup("htis"));
}

TEST(bloom_filter_test, file_test) {
    std::ifstream file("resources/words.txt");
    std::vector<std::string> words;
    std::string line;
    while (!file.eof()) {
        std::getline(file, line);
        std::transform(line.begin(), line.end(), line.begin(),
                       [](unsigned char c) { return std::tolower(c); });
        words.push_back(line);
    }
    file.close();

    spell_sweeper::bloom_filter filter(words.size(), 0.01);
    for (const auto& word : words)
        filter.insert(word);

    for (const auto& word : words)
        ASSERT_NE(filter.lookup(word), false);

    ASSERT_FALSE(filter.lookup("htis"));
    ASSERT_FALSE(filter.lookup("clesr"));
}

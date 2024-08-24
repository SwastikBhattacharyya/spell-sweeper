#include "include/edit_distance.h"
#include <gtest/gtest.h>

TEST(edit_distance_test, damerau_levenshtein) {
    EXPECT_EQ(
        spell_sweeper::edit_distance::get_damerau_levenshtein("Hi", "Hi", 255),
        0);
    EXPECT_EQ(
        spell_sweeper::edit_distance::get_damerau_levenshtein("Hi", "He", 255),
        1);
    EXPECT_EQ(spell_sweeper::edit_distance::get_damerau_levenshtein(
                  "Clear", "Clesr", 255),
              1);
    EXPECT_EQ(spell_sweeper::edit_distance::get_damerau_levenshtein(
                  "Hello", "Hekko", 255),
              2);
}

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

TEST(edit_distance_test, jaro) {
    EXPECT_GT(spell_sweeper::edit_distance::get_jaro("this", "htis"),
              spell_sweeper::edit_distance::get_jaro("thus", "this"));
    EXPECT_GT(spell_sweeper::edit_distance::get_jaro("pint", "piny"),
              spell_sweeper::edit_distance::get_jaro("pent", "piny"));
}

TEST(edit_distance_test, jaro_winkler) {
    EXPECT_GT(spell_sweeper::edit_distance::get_jaro_winkler("this", "thos"),
              spell_sweeper::edit_distance::get_jaro("this", "thos"));
    EXPECT_GT(spell_sweeper::edit_distance::get_jaro_winkler("neck", "necl"),
              spell_sweeper::edit_distance::get_jaro_winkler("peck", "necl"));
}

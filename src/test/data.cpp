#include "include/data.h"
#include <boost/archive/binary_iarchive.hpp>
#include <boost/archive/binary_oarchive.hpp>
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

TEST(data_test, serialization) {
  spell_sweeper::data app_data;
  std::ifstream file("resources/words.txt");
  std::vector<std::string> words = app_data.read_dictionary(file);
  file.close();

  ASSERT_NO_THROW(app_data.init_bk_tree(words));
  ASSERT_NO_THROW(app_data.init_bloom_filter());

  std::ofstream file_write("resources/data.bin");
  boost::archive::binary_oarchive write_archive{file_write};
  ASSERT_NO_THROW(write_archive << app_data;);
  file_write.close();

  spell_sweeper::data new_data;

  std::ifstream file_read("resources/data.bin");
  boost::archive::binary_iarchive read_archive{file_read};
  ASSERT_NO_THROW(read_archive >> new_data);
  file_read.close();

  for (const auto& word : words) {
    EXPECT_EQ(new_data.tree.search(word), 0);
    EXPECT_NE(new_data.filter.lookup(word), false);
  }
}

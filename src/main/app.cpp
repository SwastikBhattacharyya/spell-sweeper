#include "include/app.h"
#include <boost/archive/binary_iarchive.hpp>
#include <fstream>

namespace spell_sweeper {
void app::init() {
  std::ifstream file("resources/data.bin");
  if (file.fail()) {
    std::ifstream words_file("resources/words.txt");
    std::vector<std::string> words = app_data.read_dictionary(words_file);
    words_file.close();

    this->app_data.init_bk_tree(words);
    this->app_data.init_bloom_filter();
  }
  boost::archive::binary_iarchive read_archive{file};
  read_archive >> this->app_data;
  file.close();
}
} // namespace spell_sweeper

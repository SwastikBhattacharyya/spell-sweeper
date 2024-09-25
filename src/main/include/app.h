#ifndef SPELL_SWEEPER_INCLUDE_APP_H
#define SPELL_SWEEPER_INCLUDE_APP_H

#include "include/data.h"
#include <string>

namespace spell_sweeper {
class app {
public:
  std::string input_file;
  std::string output_file;
  data app_data;

public:
  app(const std::string& input_file, const std::string& output_file);
  int8_t init();
  int8_t run();
};
} // namespace spell_sweeper

#endif // !SPELL_SWEEPER_INCLUDE_APP_H

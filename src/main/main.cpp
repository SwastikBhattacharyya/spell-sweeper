#include "include/app.h"
#include <iostream>

#ifdef UNIT_TESTS
#define MAIN not_main
#else
#define MAIN main
#endif

int MAIN(int argc, char** argv) {
  if (argc != 3) {
    std::cout << "Usage: spell_sweeper input_file output_file" << '\n';
    return EXIT_FAILURE;
  }

  spell_sweeper::app app;
  app.init();

  return 0;
}

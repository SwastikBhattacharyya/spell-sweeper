#include "include/app.h"
#include <cstdlib>
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

  spell_sweeper::app app(argv[1], argv[2]);
  if (app.init() == -1) {
    std::cout << "Failed to initialize app" << '\n';
    return EXIT_FAILURE;
  }

  if (app.run() == -1) {
    std::cout << "Failed to run app" << '\n';
    return EXIT_FAILURE;
  }

  return EXIT_SUCCESS;
}

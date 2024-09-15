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

    std::cout << "Spell Sweeper" << '\n';
    return 0;
}

#include <iostream>

#ifdef UNIT_TESTS
#define MAIN not_main
#else
#define MAIN main
#endif

int MAIN(int argc, char** argv) {
    std::cout << "Spell Sweeper" << '\n';
    return 0;
}

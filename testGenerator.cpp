#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <chrono>
#include <random>

int main(int args, char const** argv) {
    if (args == 2 && !strcmp(argv[1], "-h")) {
        printf("usage %s <output file name>\n", argv[0]);
        printf("\nIf output file name is not given, \"test.s\" is used.\n");
        return EXIT_SUCCESS;
    }
    FILE* fp = nullptr;
    if (args == 2) {
        fp = fopen(argv[1], "w");
        if (!fp) {
            fprintf(stderr, "%s: %s\n", argv[1], strerror(errno));
            return EXIT_FAILURE;
        }
    }
    else {
        fp = fopen("test.s", "w");
        if (!fp) {
            fprintf(stderr, "%s: %s\n", "test.s", strerror(errno));
            return EXIT_FAILURE;
        }
    }
    unsigned seed = static_cast<unsigned>(std::chrono::system_clock::now().time_since_epoch().count());
    std::minstd_rand0 generator(seed);
    for (int i = 0; i < 200; ++i) {
        fprintf(fp, "lb $0, %u($0)\n", static_cast<unsigned>(generator()) % 1024);
    }
    fprintf(fp, "halt\n");
    fclose(fp);
    return 0;
}


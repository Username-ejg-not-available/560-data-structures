#include "Exec.h"

int main(int argc, char** argv) {
    Exec e((argc > 1) ? argv[1] : "data.txt");
}
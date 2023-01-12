#include <iostream>
#include <cstring>
#include "hauffman.h"

int main(int argc, char * argv []) {

    char * manual = "<compress/decompress> <input file> <output file>";

    Hauffman compressor = Hauffman();

    if (argc == 4 && !strcmp(argv[1], "compress")) {

        compressor.importFile(argv[2]);
        compressor.compress();
        std::cout << compressor.getHeader() << std::endl;
        compressor.exportFile(argv[3]);
        std::cout << "Compresion ratio: " << compressor.getCompresionRatio() << std::endl;
    } else if (argc == 4 && !strcmp(argv[1], "decompress")) {

        compressor.importFile(argv[2]);
        compressor.decompress();
        compressor.exportFile(argv[3]);

    } else { printf(manual); }

    return 0;
}

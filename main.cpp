#include <iostream>
#include <fstream>
#include <iomanip>

int main(int argc, char** argv) {
    if (argc < 3) {
        return EXIT_FAILURE;
    }

    std::string target = argv[1];

    std::fstream input(argv[2], std::ios::in | std::ios::binary);
    std::fstream source(target + ".cpp", std::ios::out);
    int byte = input.get();
    source << "#include <" << target << ".hpp>\n\nunsigned char " << target << "_data[] = {\n"
        << "0x" << std::hex << std::setfill('0') << std::setw(2) << byte;

    size_t count = 0;
    while (true) {
        byte = input.get();
        if (!input) {
            break;
        }
        ++count;
        source << ", 0x" << std::hex << std::setfill('0') << std::setw(2) << byte;
    }
    source << ", 0x" << std::hex << std::setfill('0') << std::setw(2) << 0 << "\n};\nsize_t " << target << "_size = " << std::dec << ++count << ";\n";

    std::fstream header(target + ".hpp", std::ios::out);
    header << "#pragma once\n\n#include <cstddef>\n\nextern unsigned char " << target << "_data[];\n"
        << "extern size_t " << target << "_size;\n";

    return EXIT_SUCCESS;
}

#include <iostream>
#include <fstream>
#include "CLexer.h"

int main(int argc, char* argv[])
{
    if (argc != 3)
    {
        std::cerr << "wrong arguments number\n";
        return 1;
    }

    std::ifstream fileInput(argv[1]);
    std::ofstream fileOutput(argv[2]);

    if (!fileInput.is_open())
    {
        std::cerr << "file can't be open\n";
        return 1;
    }

    CLexer lexer(fileInput, fileOutput);
    lexer.Run();
}
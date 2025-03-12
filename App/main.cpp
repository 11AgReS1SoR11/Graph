#include "Frontend.hpp"

int main(int argc, char* argv[])
{
    frontend::Frontend frontend;
    return frontend.exec(argc, argv);
}

#include "../include/perfectf.hh"

inline void line() { std::cout << '\n'; }

perfect_f::Perfect_F::Perfect_F()
{
    std::cout << "1";
    line();
}

perfect_f::Perfect_F::~Perfect_F()
{
    std::cout << "0";
    line();
}




//perfect forwarding tutorial
// # based on a YT video https://www.youtube.com/watch?v=cRjBj7-VjY4

int main()
{
    auto x = std::make_unique<perfect_f::Perfect_F>();
}
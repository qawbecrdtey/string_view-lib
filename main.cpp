#include <iostream>
#include <string_view>

#include "lib/concat.hpp"

using namespace std::literals;

int main() {
    constexpr auto const sv1 = "345"sv;
    auto const cc = lib::concat("012"sv, sv1);

    std::cout << "Hello, world!" << std::endl;
    
    std::cout << cc[3] << std::endl;

    std::cout << cc << std::endl;
}
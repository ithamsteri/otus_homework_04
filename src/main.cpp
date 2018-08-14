#include "../inc/print_ip.h"

using namespace ip;

int main(int, char *[]) {
    std::cout << "string:\t\t\t\t\t\t";
    print_ip(std::cout, std::string{"string"});
    std::cout << std::endl;

    std::cout << "char(-1):\t\t\t\t\t";
    print_ip(std::cout, char{-1});
    std::cout << std::endl;

    std::cout << "short(0):\t\t\t\t\t";
    print_ip(std::cout, short{0});
    std::cout << std::endl;

    std::cout << "int(2130706433):\t\t\t\t";
    print_ip(std::cout, int{2130706433});
    std::cout << std::endl;

    std::cout << "uint64_t(8875824491850138409):\t\t\t";
    print_ip(std::cout, uint64_t{8875824491850138409});
    std::cout << std::endl;

    std::cout << "vector(0x7b2d4359, 0x7b2d4359, 0x7b2d4359):\t";
    std::vector<long> v{0x7b2d4359, 0x7b2d4359, 0x7b2d4359};
    print_ip(std::cout, v);
    std::cout << std::endl;

    std::cout << "list(0x7b2d4359, 0x7b2d4359, 0x7b2d4359):\t";
    std::list<long> l{0x7b2d4359, 0x7b2d4359, 0x7b2d4359};
    print_ip(std::cout, l);
    std::cout << std::endl;

    std::cout << "tuple(0x7b, 0x7b2d, 0x7b2d4359, 0x7b2d4359):\t";
    std::tuple<char, short, int, long> tuple1 = std::make_tuple(0x7b, 0x7b2d, 0x7b2d4359, 0x7b2d4359);
    print_ip(std::cout, tuple1);
    std::cout << std::endl;
    return 0;
}
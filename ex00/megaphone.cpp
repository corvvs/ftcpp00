#include <iostream>
#include <cstddef>
#include <cctype>
#include <string>

const std::string kNoise = "* LOUD AND UNBEARABLE FEEDBACK NOISE *";

const std::string    ft_upcase(const std::string& str)
{
    std::string work(str);
    for (std::size_t i = 0; i < str.length(); i += 1) {
        if (islower(work[i])) {
            work[i] = toupper(work[i]);
        }
    }
    return work;
}

int main(int argc, char **argv)
{
    if (argc <= 1) {
        std::cout << kNoise;
    } else {
        for (int i = 1; i < argc; i += 1) {
            std::cout << ft_upcase(argv[i]);
        }
    }
    std::cout << std::endl;
    return (0);
}

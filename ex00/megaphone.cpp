#include <iostream>
#include <cstddef>
#include <string>

const std::string kNoise = "* LOUD AND UNBEARABLE FEEDBACK NOISE *";

void    ft_upcase(char *str)
{
    std::size_t i = 0;
    while (str[i]) {
        char c = str[i];
        if ('a' <= c && c <= 'z') {
            str[i] = c + ('A' - 'a');
        }
        i += 1;
    }
}

int main(int argc, char **argv)
{
    if (argc <= 1)
    {
        std::cout << MESSAGE_NOARG << std::endl;

        return (0);
    }
    for (int i = 1; i < argc; i += 1)
    {
        ft_upcase(argv[i]);
        std::cout << argv[i];
    }
    std::cout << std::endl;
    return (0);
}

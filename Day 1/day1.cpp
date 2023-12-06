#include <iostream>
#include <fstream>
#include <string>
#include <deque>
#include <regex>

int string_to_number(std::string x)
{
    if (x.length() == 1)
    {
        return x[0] - '0';
    }
    else
    {
        const char *numbers[] = {
            "one",
            "two",
            "three",
            "four",
            "five",
            "six",
            "seven",
            "eight",
            "nine"
        };
        for (int i = 0; i < 9; ++i)
        {
            if (x == numbers[i])
            {
                return i + 1;
            }
        }
    }

    return -1;
}

int main(int argc, char **argv)
{
    if (!argc)
    {
        return -1;
    }
    // Parse input.
    std::ifstream input_file(argv[1]);

    std::string line;
    int part_1 = 0;
    int part_2 = 0;
    std::regex r("(?=([0-9]|one|two|three|four|five|six|seven|eight|nine))");

    while (std::getline(input_file, line))
    {
        // Part 1
        std::deque<int> numbers;
        for (char &c : line)
        {
            if (c >= '0' && c <= '9')
            {
                numbers.push_back(c - '0');
            }
        }
        if (!numbers.empty())
        {
            part_1 += (numbers.front() * 10) + numbers.back();
        }

        // Part Two
        numbers.clear();
        std::smatch m;
        // They can overlap... so this has to handle that.
        while (std::regex_search(line, m, r))
        {
            numbers.push_back(string_to_number(m.str(1)));
            line = m.suffix().str().substr(1);
        }
        part_2 += (numbers.front() * 10) + numbers.back();
    }

    std::cout << "Part 1: " << part_1 << std::endl;
    std::cout << "Part 2: " << part_2 << std::endl;
    return 0;
}
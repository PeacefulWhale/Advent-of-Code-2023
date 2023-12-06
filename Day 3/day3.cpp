#include <iostream>
#include <fstream>
#include <deque>
#include <string>
#include <map>

struct part_number
{
    char c;
    std::deque<int> numbers;
};

bool is_part_number(const std::deque<std::string> &blueprint, int &y, int &x)
{
    // Check everything around this spot.
    for (int i = -1; i <= 1; ++i)
    {
        for (int j = -1; j <= 1; ++j)
        {
            // Don't go out of bounds.
            if (y + i >= 0 && y + i < blueprint.size())
            {
                if (x + j >= 0 && x + j < blueprint[y + i].size())
                {
                    // Is this square a symbol?
                    if (!isdigit(blueprint[y + i][x + j]) && blueprint[y + i][x + j] != '.')
                    {
                        y += i;
                        x += j;
                        return true;
                    }
                }
            }
        }
    }

    // The area is clear, this is not a part number!
    return false;
}

void parse_blueprint(const std::deque<std::string> &blueprint, std::map<std::pair<int, int>, part_number> &map)
{
    for (int y = 0; y < blueprint.size(); ++y)
    {
        for (int x = 0; x < blueprint[x].size(); ++x)
        {
            int num = 0;
            int i = 0;
            bool part_number = false;
            // These pos values are for if is_part_number updates them to the coordinates of the symbol.
            int pos_x = -1;
            int pos_y = -1;
            // Check to see if this is a digit.
            while (std::isdigit(blueprint[y][x + i]))
            {
                num *= 10;
                num += blueprint[y][x + i] - '0';
                int tmp_x = x + i;
                int tmp_y = y;
                if (is_part_number(blueprint, tmp_y, tmp_x))
                {
                    part_number = true;
                    pos_x = tmp_x;
                    pos_y = tmp_y;
                }
                i += 1;
            }
            // If it's a part number add it to the map.
            if (part_number)
            {
                map[std::make_pair(pos_y, pos_x)].c = blueprint[pos_y][pos_x];
                map[std::make_pair(pos_y, pos_x)].numbers.push_back(num);
            }
            // Update x with i (in case it was a number).
            x += i;
        }
    }
}

int main(int argc, char **argv)
{
    if (!argc)
    {
        return -1;
    }
    // Parse input.
    std::ifstream input_file(argv[1]);

    // Parse the input into a big thing of strings.
    std::string line;
    std::deque<std::string> blueprint;
    // The map is for all those symbols.
    std::map<std::pair<int, int>, part_number> map;
    while (std::getline(input_file, line))
    {
        blueprint.push_back(line);
    }
    // Parse the blueprint/input to the symbol mapping.
    parse_blueprint(blueprint, map);

    long part_1 = 0;
    long part_2 = 0;
    for (auto tmp : map)
    {
        // Part 1:
        for (int number : tmp.second.numbers)
        {
            part_1 += number;
        }
        // Part 2:
        if (tmp.second.c == '*' && tmp.second.numbers.size() == 2)
        {
            part_2 += tmp.second.numbers[0] * tmp.second.numbers[1];
        }
    }
    std::cout << "Part 1: " << part_1 << std::endl;
    std::cout << "Part 2: " << part_2 << std::endl;
    return 0;
}
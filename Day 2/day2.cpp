#include <iostream>
#include <fstream>


int max_num(int a, int b)
{
    return (a > b) ? a : b;
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
    int id = 0;
    while (std::getline(input_file, line))
    {
        // The IDs are always in order, so I don't need to parse that.
        id += 1;
        // Skip "Game X:"
        line = line.erase(0, line.find(':') + 2);
        int max[3] = { 0, 0, 0 };
        do {
            // Go through each round and update the max values.
            std::string round = line.substr(0, line.find(';'));
            line.erase(0, round.length() + 2);
            do {
                // Get the number.
                int dice = std::stoi(round.substr(0, round.find(' ')));
                round.erase(0, round.find(' ') + 1);
                // Set the max.
                int color;
                char c = round[0];
                if (c == 'r')
                {
                    color = 0;
                }
                else if (c == 'g') {
                    color = 1;
                }
                else {
                    color = 2;
                }
                max[color] = max_num(max[color], dice);
                // Erase the color (and comma if it exists)
                round.erase(0, round.find(' ') + 1);
            } while (round.find(' ') != round.npos);
        } while (!line.empty());

        // Part 1:
        // only 12 red cubes, 13 green cubes, and 14 blue cubes
        if (max[0] <= 12 && max[1] <= 13 && max[2] <= 14)
        {
            part_1 += id;
        }

        // Part 2:
        // How many would you need for each game to be possible?
        // Sum all the multiples together
        part_2 += max[0] * max[1] * max[2];
    }

    std::cout << "Part 1: " << part_1 << std::endl;
    std::cout << "Part 2: " << part_2 << std::endl;
    return 0;
}
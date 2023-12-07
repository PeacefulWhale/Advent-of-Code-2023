#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <deque>
#include <map>

int parse_card(std::string line)
{
    // Cut out the card name.
    line.erase(0, line.find(':') + 1);
    // Grab the winning numbers.
    std::stringstream wn_ss(line.substr(0, line.find('|')));
    std::map<int, int> winning_numbers;
    // Read the winning numbers into a map.
    int winning_number;
    while (wn_ss >> winning_number)
    {
        winning_numbers[winning_number] += 1;
    }

    // Grab the numbers and determine which entries have actually won.
    // Save the total count of winning numbers.
    int count = 0;
    std::stringstream n_ss(line.substr(line.find('|') + 1));
    int number;
    while (n_ss >> number)
    {
        if (winning_numbers.contains(number))
        {
            count += winning_numbers[number];
        }
    }
    return count;
}

int part_1(std::deque<int> &cards)
{
    int part_1 = 0;
    for (auto card : cards)
    {
        int score = 0;
        for (int i = 0; i < card; ++i)
        {
            if (score)
            {
                score *= 2;
            }
            else
            {
                score = 1;
            }
        }
        part_1 += score;
    }
    return part_1;
}


int part_2_recursion(std::deque<int> &cards, size_t card, int *cache)
{
    // Return the cached value if it exists.
    if (cache[card] != -1)
    {
        return cache[card];
    }

    // If there is no cache value, then recursively go down the card list.
    int return_val = 1;
    for (int i = 1; i <= cards[card]; ++i)
    {
        return_val += part_2_recursion(cards, card + i, cache);
    }

    cache[card] = return_val;
    return return_val;
}

int part_2_main(std::deque<int> &cards)
{
    int part_2 = 0;
    // I use a cache so this goes a little bit quicker.
    int cache[cards.size()];
    for (size_t i = 0; i < cards.size(); ++i)
    {
        cache[i] = -1;
    }

    for (size_t i = 0; i < cards.size(); ++i)
    {
        part_2 += part_2_recursion(cards, i, cache);
    }
    return part_2;
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

    std::deque<int> cards;
    while (std::getline(input_file, line))
    {
        cards.push_back(parse_card(line));
    }

    // Just go through and sum it all up.
    std::cout << "Part 1: " << part_1(cards) << std::endl;
    std::cout << "Part 2: " << part_2_main(cards) << std::endl;
    return 0;
}
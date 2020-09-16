#include <iostream>
#include <vector>
#include <map>
#include <random>
#include <algorithm>
#include <string>
#include <cmath>

static std::random_device kRandomDevice;
const int kLowerBound = 0;
const int kUpperBound = 9;
const int kSize = 8;
const std::map< char, int > kDictionary{ {'s', 7},
    { 'e', 6  },
    { 'n', 5  },
    { 'd', 4  },
    { 'm', 3  },
    { 'o', 2  },
    { 'r', 1  },
    { 'y', 0  } };

std::vector< int > lottery_generator(int);

void display_sequence(const std::vector< int >&);

int get_word_value(const std::string&, const std::vector< int >&);

int main()
{
  int tp = 100;

  std::vector< std::vector< int >> p;


  for (int i = 0; i < tp; ++i) {
    p.push_back(lottery_generator(kSize));
  }

  std::string a("send");
  std::string b("more");
  std::string c("money");

  auto it = p.cbegin();
  while (it != p.cend())
  {
    display_sequence(*it);

    int vA = get_word_value(a, *it);
    int vB = get_word_value(b, *it);
    int vC = get_word_value(c, *it);

    int fitness = abs(vC - (vA+vB));

    std::cout << fitness << std::endl;

    ++it;
  }
}

std::vector< int > lottery_generator(int size)
{
  std::mt19937 engine(kRandomDevice());
  std::uniform_int_distribution< int > distribution(kLowerBound, kUpperBound);
  std::vector< int > sequence;

  for (int i = 0; i < size;)
  {
    int numberDrawn = distribution(engine);

    auto it = std::find(sequence.cbegin(), sequence.cend(), numberDrawn);

    if (it != sequence.cend())
    {
      continue;
    }

    sequence.push_back(numberDrawn);
    ++i;
  }

  return sequence;
}

void display_sequence(const std::vector< int >& sequence)
{
  auto it = sequence.cbegin();
  while (it != sequence.cend())
  {
    std::cout << *it << "\t";
    ++it;
  }
  std::cout << std::endl;
}

int get_word_value(const std::string& word, const std::vector< int >& sequence)
{
  int result = 0;

  for (size_t i = 0; i < word.length(); ++i) {
    char c = word.at(i);

    int pos = kDictionary.find(c)->second;

    int value = sequence[pos];
    int exponent = (word.length() - 1) - i;

    result += (pow(10, exponent) * value);

    std::cout << exponent << "\tchar: " << c << "\tpos: " << pos << "\tvalue: " << value << std::endl << std::endl;
  }

  return result;
}

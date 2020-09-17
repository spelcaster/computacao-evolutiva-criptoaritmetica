#include <iostream>
#include <vector>
#include <map>
#include <random>
#include <algorithm>
#include <string>
#include <cmath>

static std::random_device kRandomDevice;
const int kChromosomeLowerBound = 0;
const int kChromosomeUpperBound = 9;
const int kChromosomeSize = 8;

const std::map< char, int > kDictionary{ {'s', 7},
    { 'e', 6  },
    { 'n', 5  },
    { 'd', 4  },
    { 'm', 3  },
    { 'o', 2  },
    { 'r', 1  },
    { 'y', 0  } };

std::vector< int > generate_chromosome(int);

void display(const std::vector< int >&);

int get_word_value(const std::string&, const std::vector< int >&);

std::vector< int > single_point_crossover(const int, const std::vector< int >&, const std::vector< int >&);

int get_single_point_crossover_mark(const int);

void mutate_chromosome(std::vector< int >&);

int main()
{
  int tp = 100;

  std::vector< std::vector< int >> p;

  std::vector< std::string > words{ { "send" },
    { "more" },
    { "money" } };

  for (int i = 0; i < tp; ++i) {
    p.push_back(generate_chromosome(kChromosomeSize));
  }

  double sumFitness = 0.0;

  std::vector< int > pFitness;
  auto it = p.cbegin();
  while (it != p.cend())
  {
    int vA = get_word_value(words.at(0), *it);
    int vB = get_word_value(words.at(1), *it);
    int vC = get_word_value(words.at(2), *it);

    int fitness = abs(vC - (vA+vB));

    pFitness.push_back(fitness);
    sumFitness += fitness;

    ++it;
  }

  for (size_t i = 0; i < pFitness.size(); ++i) {
    std::cout << (double) pFitness[i] / sumFitness << std::endl;
  }


  display(p[0]);

  mutate_chromosome(p[0]);
  display(p[0]);
}

std::vector< int > generate_chromosome(int size)
{
  std::mt19937 engine(kRandomDevice());
  std::uniform_int_distribution< int > distribution(kChromosomeLowerBound, kChromosomeUpperBound);
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

int get_single_point_crossover_mark(const int size)
{
  std::mt19937 engine(kRandomDevice());
  std::uniform_int_distribution< int > distribution(1, (size - 1));

  return distribution(engine);
}

void display(const std::vector< int >& sequence)
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

std::vector< int > single_point_crossover(int mark, const std::vector< int >& parentA, const std::vector< int >& parentB)
{
  auto aBegin = parentA.begin();
  auto aEnd = parentA.begin() + mark;

  auto bBegin = parentB.begin() + mark;
  auto bEnd = parentB.end();

  std::vector< int > offspring(aBegin, aEnd);
  offspring.insert(offspring.end(), bBegin, bEnd);

  return offspring;
}

void mutate_chromosome(std::vector< int >& chromosome)
{
  std::mt19937 engine(kRandomDevice());
  std::uniform_int_distribution< int > mutationDistribution(1, chromosome.size());
  std::uniform_int_distribution< int > positionDistribution(0, chromosome.size() - 1);
  std::uniform_int_distribution< int > distribution(kChromosomeLowerBound, kChromosomeUpperBound);

  std::vector< int > positionCache;

  int changes = mutationDistribution(engine);

  for (int i = 0; i < changes;)
  {
    int position = positionDistribution(engine);

    auto positionIt = std::find(positionCache.cbegin(), positionCache.cend(), position);

    if (positionIt != positionCache.cend())
    {
      continue;
    }

    int gene = distribution(engine);

    auto it = std::find(chromosome.cbegin(), chromosome.cend(), gene);

    if (it != chromosome.cend())
    {
      continue;
    }

    chromosome[position] = gene;
    ++i;
  }
}

#include "Generators.h"


Generators::Generators() : whichsimulation(0)
{
  std::cout << "Wygenerowanie ziaren : 1"<<std::endl<<"Odczytanie ziaren : 0"<<std::endl<<"(0/1):";
  bool whatseeds;
  std::cin >> whatseeds;
  if (whatseeds) GenerateSeeds();
  else ReadSeeds();
  std::cout << std::endl;
}

Generators::~Generators()
{
}

void Generators::GenerateSeeds()
{
  long long x = SEED;
  for (int i = 0; i < SIMULATION_NUMBER; ++i) 
  {
    for (int j = 0; j < GENERATOR_NUMBER; ++j) 
    {
      for (int k = 0; k < 100000; ++k) x = (x*MULTIPLY) % MODULO;
      seeds[i][j] = x;
    }
  }

  std::cout << "Ziarna wygenerowane, chcesz je zapisac do pliku? (0/1):";
  bool dosave;
  std::cin >> dosave;
  std::cout << std::endl;
  if (dosave) WriteSeeds();
  std::cout << std::endl;
}

void Generators::ReadSeeds()
{
  std::string seedline;
  std::ifstream readingseeds;
  readingseeds.open("Nasiona.txt");
  if (!readingseeds.good() || !readingseeds.is_open())
  {
    std::cout << "Blad odczytu z pliku" << std::endl;
    system("pause");
  }
  else
  {
    int countgenerator = 0;
    int  countsimulation = 0;
    while (readingseeds.good())
    {
      std::getline(readingseeds, seedline);
      if (seedline == "!!!")
      {
        countsimulation++;
        countgenerator = 0;
      }
      else
      {
        seeds[countsimulation][countgenerator] = std::stod(seedline);
        countgenerator++;
      }
      if (countsimulation >= SIMULATION_NUMBER) break;
    }
    std::cout << "Ziarna odczytane poprawnie." << std::endl;
  }
  readingseeds.close();
}

void Generators::WriteSeeds()
{
  std::ofstream writingseeds;
  writingseeds.open("Nasiona.txt", std::ios::app);
  if (!writingseeds.good() || !writingseeds.is_open())
  {
    std::cout << "Blad zapisu do pliku" << std::endl;
    system("pause");
  }
  else
  {
    for (int i = 0; i < SIMULATION_NUMBER; ++i)
    {
      for (int j = 0; j < GENERATOR_NUMBER; ++j)
      {
        writingseeds << seeds[i][j] << std::endl;        
      }
      writingseeds << "!!!" << std::endl;
    }
    std::cout << "Ziarna poprawnie zapisane." << std::endl;
  }
  writingseeds.close();
}

double Generators::Uniform(int type)
{
  seeds[whichsimulation][type] = (seeds[whichsimulation][type] * MULTIPLY) % MODULO;
  double tmp = static_cast<double>(seeds[whichsimulation][type]) / MODULO;
  return tmp;
}

double Generators::CGP(int whichsender)
{
  double tmp = -log(Uniform(2 + whichsender)) / L;
  tmp = floor(tmp * 10.0 + 0.5) / 10.0;
  return tmp;
}

int Generators::CTP(int whichsender)
{
  int tmp = (int)(Uniform(2 + 2 * whichsender) * 10 + 1);
  return tmp;
}

int Generators::CRP(int whichsender, int r)
{
  int range = (int)pow(2.0, r)-1;
  int tempCTP= (int)(Uniform(2 + 2 * whichsender) * 10 + 1);
  int tempR = (int)(Uniform(0) *range);
  int tmp = tempCTP*tempR;
  return tmp;
}

double Generators::PT()
{
  int tmp = (int)(Uniform(1) * 100);
  return tmp;
}

void Generators::NextSimulation()
{
  ++whichsimulation;
}

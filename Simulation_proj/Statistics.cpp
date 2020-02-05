#include "Statistics.h"

Statistics::Statistics() : 
  whichsimulation(0),
  packagecounter(0)
{
}

Statistics::~Statistics()
{
  for (unsigned int i = 0; i < allpackages.size(); ++i) delete allpackages.at(i);
  allpackages.clear();
}

void Statistics::NextSimulation()
{
  Package* spacepackage = new Package(whichsimulation, whichsimulation);
  spacepackage->PackageTransmitted(whichsimulation);
  spacepackage->PackageLeft(whichsimulation);
  allpackages.push_back(spacepackage);
  whichsimulation++;
  packagecounter = 0;
}

void Statistics::Save()
{
  std::cout << "Zapisuje wyniki."<< std::endl;

  std::fstream everypackage;
  everypackage.open("Wyniki.txt", std::ios::app);
  if (!everypackage.good() || !everypackage.is_open())
  {
    std::cout << "Blad zapisu do pliku" << std::endl;
    system("pause");
  }
  else
  { 
    everypackage << "ID" << "|"
      << "Czas wytworzenia" << "|"
      << "Czas opuszczenia bufora" << "|"
      << "Czas opuszczenia sieci" << "|"
      << "Ilosc retransmisji" << "|"
      << "Czy poprawnie przeslany"
      << std::endl;

    for (unsigned int i = 0; i < allpackages.size(); ++i)
    {
      everypackage << allpackages[i]->packageidsender<<"|"
        << allpackages[i]->GetPackageBorn() << "|"
        << allpackages[i]->GetPackageTransmitted() << "|"
        << allpackages[i]->GetPackageLeft() << "|"
        << allpackages[i]->GetR() << "|"
        << allpackages[i]->GetReceivedFlag()
        << std::endl;
    }
    std::cout << "Wyniki poprawnie zapisane." << std::endl;
  }
  everypackage.close();

}

void Statistics::PushDeadPackage(Package * deadpackage)
{
  packagecounter++;  
  if(packagecounter > START_PHASE) allpackages.push_back(deadpackage);
}

void Statistics::SaveErrors()
{
  std::cout << "Zapisuje bledy." << std::endl;
  std::fstream errorstream;
  errorstream.open("Bledy.txt", std::ios::app);
  if (!errorstream.good() || !errorstream.is_open())
  {
    std::cout << "Blad zapisu do pliku" << std::endl;
    system("pause");
  }
  else
  {
    for (unsigned int i = 0; i < errors.size(); ++i)
    {
      errorstream << errors[i] << std::endl;
    }
    std::cout << "Bledy poprawnie zapisane." << std::endl;
  }
  errorstream.close();
}

void Statistics::PushError(double error)
{
  errors.push_back(error);
}

void Statistics::SaveHistogram()
{
  std::cout << "Zapisuje dane histogramu." << std::endl;
  std::fstream histostream;
  //histostream.open("HistogramCGP.txt", std::ios::app);
  histostream.open("HistogramCTP.txt", std::ios::app);
  if (!histostream.good() || !histostream.is_open())
  {
    std::cout << "Blad zapisu do pliku" << std::endl;
    system("pause");
  }
  else
  {
    for (unsigned int i = 0; i < histogram.size(); ++i)
    {
      histostream << histogram[i] << std::endl;
    }
    std::cout << "Histogram poprawnie zapisany." << std::endl;
  }
  histostream.close();
}

void Statistics::PushHistogramData(double data)
{
  histogram.push_back(data);
}

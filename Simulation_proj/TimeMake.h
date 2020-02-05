#pragma once

#ifndef TimeMake_h_
#define TimeMake_h_

#include  <iostream>
#include "Generators.h"
#include "Network.h"

//klasa opisujπca zdarzenie czasowe - wygenerowanie pakietu, zaplanowanie wygenerowania kolejnego

class TimeMake
{
public:
  //konstruktor przyjmuje jako argumenty wskaüniki na sieÊ i generator
  TimeMake(Network* net, Generators* gen);
  ~TimeMake();
  //w execute wytwarzany jest nowy pakiet, dodawany do bufora i planowane jest generowanie kolejnego
  //w argumentach podawane jest ID nadajnika i obecny czas symulacji
  bool Execute(bool stepmode, int whichsender, double time);
  //funkcja podaje czas na wywo≥anie wydarzenia dla danego nadajnika
  double GiveTime(int whichsender);

private: //prywatne sπ wskaüniki na obiekty i czas na to wydarzenie
  Network* usednetwork;
  StationSender* usedsender;
  Generators* usedgenerator;
  Package* newpackage;
  //tablica przechowuje czas na wydarzenie dla kaødego nadajnika
  std::vector<double> timeforevent;
};

#endif //!TimeMake_h_
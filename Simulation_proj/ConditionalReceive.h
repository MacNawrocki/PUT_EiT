#pragma once

#ifndef ConditionalReceive_h_
#define ConditionalReceive_h_

#include <iostream>
#include "Generators.h"
#include "Network.h"

//Klasa opisuj¹ca zdarzenie warunkowe - wys³anie ACK z odbiornika je¿eli dotar³ pakiet bez kolizji
class ConditionalReceive
{
public:
  //konstruktor przyjmuje jako argumenty wskaŸniki na sieæ i generator
  ConditionalReceive(Network* net);
  ~ConditionalReceive();
  
  bool Execute(bool stepmode, int whichreceiver, double time);
  //funkcja podaje czas na wywo³anie wydarzenia
  double GiveTime(int whichreceiver);
  //funkcja nadaje wydarzeniu czas na wwo³anie
  void ChangeTime(int whichreceiver, double time);

private:
  Network* usednetwork;
  Channel *usedchannel;
  StationReceiver* usedreceiver;
  Package* receivedpackage;
  //tablica przechowuje czas na wydarzenie dla ka¿dego nadajnika
  std::vector<double> timeforevent;
};

#endif //!ConditionalReceive_h_

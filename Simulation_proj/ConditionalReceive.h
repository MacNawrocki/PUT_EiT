#pragma once

#ifndef ConditionalReceive_h_
#define ConditionalReceive_h_

#include <iostream>
#include "Generators.h"
#include "Network.h"

//Klasa opisuj�ca zdarzenie warunkowe - wys�anie ACK z odbiornika je�eli dotar� pakiet bez kolizji
class ConditionalReceive
{
public:
  //konstruktor przyjmuje jako argumenty wska�niki na sie� i generator
  ConditionalReceive(Network* net);
  ~ConditionalReceive();
  
  bool Execute(bool stepmode, int whichreceiver, double time);
  //funkcja podaje czas na wywo�anie wydarzenia
  double GiveTime(int whichreceiver);
  //funkcja nadaje wydarzeniu czas na wwo�anie
  void ChangeTime(int whichreceiver, double time);

private:
  Network* usednetwork;
  Channel *usedchannel;
  StationReceiver* usedreceiver;
  Package* receivedpackage;
  //tablica przechowuje czas na wydarzenie dla ka�dego nadajnika
  std::vector<double> timeforevent;
};

#endif //!ConditionalReceive_h_

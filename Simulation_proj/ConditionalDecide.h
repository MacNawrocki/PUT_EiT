#pragma once

#ifndef ConditionalDecide_h_
#define ConditionalDecide_h_

#include <iostream>
#include "Generators.h"
#include "Network.h"
#include "Statistics.h"

//Klasa opisuj�ca zdarzenie warunkowe - odebranie/retransmisja/odrzucenie pakietu
class ConditionalDecide
{
public:
  //konstruktor przyjmuje jako argumenty wska�niki na sie� i generator
  ConditionalDecide(Network* net, Generators* gen, Statistics* stat);
  ~ConditionalDecide();

  bool Execute(bool stepmode, int whichsender, double time);
  //funkcja podaje czas na wywo�anie wydarzenia
  double GiveTime(int whichsender);
  //funkcja nadaje wydarzeniu czas na wwo�anie
  void ChangeTime(int whichsender, double time);

private:
  Network* usednetwork;
  Generators* usedgenerator;
  Statistics* usedstatistics;
  Channel *usedchannel;
  StationSender *usedsender;
  Package* frontpackage;
  InfoACK* receivedinfo;
  //tablica przechowuje czas na wydarzenie dla ka�dego nadajnika
  std::vector<double> timeforevent;
};

#endif //!ConditionalDecide_h_


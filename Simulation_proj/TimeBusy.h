#pragma once

#ifndef TimeBusy_h_
#define TimeBusy_h_

#include<iostream>
#include "Generators.h"
#include "Network.h"

//klasa opisuj�ca zdarzenie czasowe - zamkni�cie kana�u
class TimeBusy
{
public:
  //konstruktor przyjmuje jako argumenty wska�nik na sie� 
  TimeBusy(Network* net);
  ~TimeBusy();
  //w argumentach podawane jest ID nadajnika i obecny czas symulacji
  bool Execute(bool stepmode, int whichsender, double time);
  //funkcja podaje czas na wywo�anie wydarzenia
  double GiveTime(int whichsender);
  //funkcja nadaje wydarzeniu czas na wwo�anie
  void ChangeTime(int whichsender, double time);

private:
  Network* usednetwork;
  StationSender *usedsender;
  Channel* usedchannel;
  //tablica przechowuje czas na wydarzenie dla ka�dego nadajnika
  std::vector<double> timeforevent;
};

#endif
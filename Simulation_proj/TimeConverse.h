#pragma once

#ifndef TimeConverse_h_
#define TimeConverse_h_

#include<iostream>
#include "Generators.h"
#include "Network.h"
#include "ConditionalDecide.h"
#include "ConditionalReceive.h"

//klasa opisuj�ca zdarzenie czasowe - komunikacja nadawca<->odbiornik
class TimeConverse
{
public:
  //konstruktor przyjmuje jako argumenty wska�niki na sie� i generator 
  TimeConverse(Network* net, Generators* gen);
  ~TimeConverse();
  //execute wysy�a pakiet i oczekuje 
  //w argumentach podawane jest ID nadajnika i obecny czas symulacji
  bool Execute(bool stepmode, int whichsender, double time);
  //funkcja podaje czas na wywo�anie wydarzenia
  double GiveTime(int whichsender);
  //funkcja nadaje wydarzeniu czas na wwo�anie
  void ChangeTime(int whichsender, double time);

private:
  Network* usednetwork;
  StationSender *usedsender;
  Generators* usedgenerator;
  Channel* usedchannel;
  Package* sendpackage;

  //tablica przechowuje czas na wydarzenie dla ka�dego nadajnika
  std::vector<double> timeforevent;
};

#endif
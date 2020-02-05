#pragma once

#ifndef ConditionalSend_h_
#define ConditionalSend_h_

#include<iostream>
#include "Generators.h"
#include "Network.h"
#include "TimeConverse.h"

//Klasa opisuj�ca zdarzenie warunkowe - wys�anie pakietu
class ConditionalSend
{
public:
  //konstruktor przyjmuje jako argumenty wska�niki na sie� i generator
  //r�wnie� wska�nik na wydarzenie TimeConverse
  ConditionalSend(Network* net, Generators* gen);
  ~ConditionalSend();                                 
  //Execute dzia�a w paru etapach kontrolowanych wewn�trznymi flagami
  //zajmuje si� sprawdzeniem kana�u, testu, i przekazaniem pakietu do nadania
  bool Execute(bool stepmode, int whichsender, double time);
  //funkcja podaje czas na wywo�anie wydarzenia
  double GiveTime(int whichsender);
  //funkcja nadaje wydarzeniu czas na wwo�anie
  void ChangeTime(int whichsender, double time);
  void ConnectEvents(TimeConverse* tevent);

private:
  Network* usednetwork;
  Generators* usedgenerator;
  StationSender *usedsender;
  Channel *usedchannel;
  TimeConverse  *converseevent;
  //tablica przechowuje czas na wydarzenie dla ka�dego nadajnika
  std::vector<double> timeforevent;
  //tablica przechowuje flag� dla execute dla ka�dego nadajnika
  int flag[SENDERS_NUMBER];
};


#endif
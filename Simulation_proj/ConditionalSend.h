#pragma once

#ifndef ConditionalSend_h_
#define ConditionalSend_h_

#include<iostream>
#include "Generators.h"
#include "Network.h"
#include "TimeConverse.h"

//Klasa opisuj¹ca zdarzenie warunkowe - wys³anie pakietu
class ConditionalSend
{
public:
  //konstruktor przyjmuje jako argumenty wskaŸniki na sieæ i generator
  //równie¿ wskaŸnik na wydarzenie TimeConverse
  ConditionalSend(Network* net, Generators* gen);
  ~ConditionalSend();                                 
  //Execute dzia³a w paru etapach kontrolowanych wewnêtrznymi flagami
  //zajmuje siê sprawdzeniem kana³u, testu, i przekazaniem pakietu do nadania
  bool Execute(bool stepmode, int whichsender, double time);
  //funkcja podaje czas na wywo³anie wydarzenia
  double GiveTime(int whichsender);
  //funkcja nadaje wydarzeniu czas na wwo³anie
  void ChangeTime(int whichsender, double time);
  void ConnectEvents(TimeConverse* tevent);

private:
  Network* usednetwork;
  Generators* usedgenerator;
  StationSender *usedsender;
  Channel *usedchannel;
  TimeConverse  *converseevent;
  //tablica przechowuje czas na wydarzenie dla ka¿dego nadajnika
  std::vector<double> timeforevent;
  //tablica przechowuje flagê dla execute dla ka¿dego nadajnika
  int flag[SENDERS_NUMBER];
};


#endif
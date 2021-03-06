#pragma once

#ifndef StationSender_h_
#define StationSender_h_

#include "Package.h"
#include <queue>

//Klasa opisująca stacje nadawczą

class StationSender
{
private:
  std::queue<Package*> buffer;
public:
  //konstruktor przyjmuje id jako argument
  StationSender(int id);
  ~StationSender();
  int senderidsender;

  //funkcje obsługujące bufor pakietów
  Package* GiveFront();
  void AddNew(Package * newpackage);
  void DeleteFront();
  bool IsBufferEmpty();

  //flagi ułatwiające poprawne wykonywanie symulacji
  double activatesend;
  double activatereceive;
  double activatedecide;
  double activatebusy;
};

#endif //!StationSender_h_
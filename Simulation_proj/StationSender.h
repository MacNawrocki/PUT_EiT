#pragma once

#ifndef StationSender_h_
#define StationSender_h_

#include "Package.h"
#include <queue>

//Klasa opisuj¹ca stacje nadawcz¹

class StationSender
{
private:
  std::queue<Package*> buffer;
public:
  //konstruktor przyjmuje id jako argument
  StationSender(int id);
  ~StationSender();
  int senderidsender;

  //funkcje obs³uguj¹ce bufor pakietów
  Package* GiveFront();
  void AddNew(Package * newpackage);
  void DeleteFront();
  bool IsBufferEmpty();

  //flagi u³atwiaj¹ce poprawne wykonywanie symulacji
  double activatesend;
  double activatereceive;
  double activatedecide;
  double activatebusy;
};

#endif //!StationSender_h_
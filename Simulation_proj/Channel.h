#pragma once

#ifndef Channel_h_
#define Channel_h_

#include <vector>
#include "Package.h"
#include "InfoACK.h"

//Klasa opisuj¹ca kana³ transmisyjny

class Channel
{
public:
  std::vector<Package*> packagesgoing;
  std::vector<InfoACK*> infogoing;
  bool isbusy;
  bool channelconflict;
  Channel();
  ~Channel();
};

#endif //!Channel_h_

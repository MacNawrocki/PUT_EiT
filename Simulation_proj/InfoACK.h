#pragma once
#ifndef InfoACK_h_
#define InfoACK_h_

//klasa opisuj�ca informacj� ACK
class InfoACK
{
public:
  InfoACK(int idsender, int idreceiver);
  ~InfoACK();
  //id stacji zwi�zanych z informacj� ACK
  int infoidsender;
  int infoidreceiver;
};

#endif //!InfoACK_h_

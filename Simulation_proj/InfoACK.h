#pragma once
#ifndef InfoACK_h_
#define InfoACK_h_

//klasa opisująca informację ACK
class InfoACK
{
public:
  InfoACK(int idsender, int idreceiver);
  ~InfoACK();
  //id stacji związanych z informacją ACK
  int infoidsender;
  int infoidreceiver;
};

#endif //!InfoACK_h_

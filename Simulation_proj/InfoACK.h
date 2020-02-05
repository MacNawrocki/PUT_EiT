#pragma once
#ifndef InfoACK_h_
#define InfoACK_h_

//klasa opisuj¹ca informacjê ACK
class InfoACK
{
public:
  InfoACK(int idsender, int idreceiver);
  ~InfoACK();
  //id stacji zwi¹zanych z informacj¹ ACK
  int infoidsender;
  int infoidreceiver;
};

#endif //!InfoACK_h_

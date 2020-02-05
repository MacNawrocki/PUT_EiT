#include "Channel.h"

Channel::Channel():
  isbusy(false),
  channelconflict(false)
{
}


Channel::~Channel()
{
  for (unsigned int i = 0; i < infogoing.size(); ++i) delete infogoing.at(i);
  packagesgoing.clear();
  infogoing.clear();
}

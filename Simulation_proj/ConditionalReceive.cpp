#include "ConditionalReceive.h"

ConditionalReceive::ConditionalReceive(Network* net) :
  usednetwork(net),
  usedchannel(net->channel),
  usedreceiver (nullptr),
  receivedpackage (nullptr)
{
  timeforevent.reserve(SENDERS_NUMBER);
  for (int i = 0; i < SENDERS_NUMBER; ++i) timeforevent.push_back(-1);
}

ConditionalReceive::~ConditionalReceive()
{
  timeforevent.clear();
  usednetwork = nullptr;

  usedchannel = nullptr;
  usedreceiver = nullptr;
  receivedpackage = nullptr;
}

bool ConditionalReceive::Execute(bool stepmode, int whichreceiver, double time)
{
  if (timeforevent[whichreceiver] == time)
   {
    usedreceiver = usednetwork->receivers[whichreceiver];
    int howmanypackages = usedchannel->packagesgoing.size();
    if (howmanypackages != 1)
    {
      usedchannel->channelconflict = true;
      Package* conflictedpackage;
      for (int i = 0; i < howmanypackages; i++)
      {
        conflictedpackage = usedchannel->packagesgoing.at(i);
        conflictedpackage->ChangeConflictFlag(true);
      }
    }
    else if (usedchannel->channelconflict) usedchannel->channelconflict = false;

    receivedpackage = usedchannel->packagesgoing.front();
    usedchannel->packagesgoing.erase(usedchannel->packagesgoing.begin());

    if (!receivedpackage->GetConflictFlag() && receivedpackage->packageidsender == whichreceiver)
    { 
      if (stepmode) std::cout << "W czasie: " << time << ", odbiornik: "<<whichreceiver<< " odebral pakiet i nadal ACK" <<std::endl;
      InfoACK* sendinfo = new InfoACK(whichreceiver, whichreceiver);
      usedchannel->infogoing.insert(usedchannel->infogoing.begin(),sendinfo);
    }
    else
    {
      if (stepmode) std::cout << "W czasie: " << time << ", odbiornik: " << whichreceiver << " nie odebral pakietu i nie nadal ACK" << std::endl;
    }
    timeforevent.at(whichreceiver) = -1;
    return true;
  }
  return false;
}

double ConditionalReceive::GiveTime(int whichreceiver)
{
  return timeforevent.at(whichreceiver);
}

void ConditionalReceive::ChangeTime(int whichreceiver, double time)
{
  timeforevent.at(whichreceiver) = time;
}

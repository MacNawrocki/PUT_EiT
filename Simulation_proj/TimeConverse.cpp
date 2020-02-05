#include "TimeConverse.h"

TimeConverse::TimeConverse(Network* net, Generators* gen) :
  usednetwork(net),
  usedgenerator(gen),
  sendpackage(nullptr)
{
  timeforevent.reserve(SENDERS_NUMBER);
  for (int i = 0; i < SENDERS_NUMBER; ++i) timeforevent.push_back(-1);
  usedchannel = usednetwork->channel;
}

TimeConverse::~TimeConverse()
{
  timeforevent.clear();
  usedgenerator = nullptr;
  usednetwork = nullptr;
  usedchannel = nullptr;
  sendpackage = nullptr;
}

bool TimeConverse::Execute(bool stepmode, int whichsender, double time)
{
  if (timeforevent.at(whichsender) == time) 
  {
    usedsender = usednetwork->senders[whichsender];
    Package* sendpackage = usedsender->GiveFront();
    //aktywowanie wydarzenia TimeBusy które z pewnym opóŸnieniem zamknie kana³
    usedsender->activatebusy = time + TIME_GAP;
    //pakiet z bufora jest przekazywany do kana³u, lecz nie zdejmmowany jeszcze z bufora
    if(sendpackage->GetPackageTransmitted() == 0) sendpackage->PackageTransmitted(time);
    usedchannel->packagesgoing.push_back(sendpackage);
    if (stepmode) std::cout << "W czasie: " << time << ", nadajnik: " << whichsender << " nadal pakiet" << std::endl;
    timeforevent[whichsender] = -1;
    double timefromgenerator = usedgenerator->CTP(whichsender);
    //aktywowanie wydarzenia ConditionalReceive które odbiera pakiet i wysy³a (lub nie) ACK
    usedsender->activatereceive = time + timefromgenerator;
    //aktywowanie wydarzenia ConditionalDecide które odbiera ACK i decyduje o dalszym procesie pakietu
    usedsender->activatedecide = time + timefromgenerator + 1.0;
    return true;
  }
  return false;
}

double TimeConverse::GiveTime(int whichsender)
{
  return timeforevent.at(whichsender);
}

void TimeConverse::ChangeTime(int whichsender, double time)
{
  timeforevent.at(whichsender) = time;
}

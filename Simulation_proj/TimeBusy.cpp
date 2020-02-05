#include "TimeBusy.h"

TimeBusy::TimeBusy(Network* net) :
  usednetwork(net)
{
  timeforevent.reserve(SENDERS_NUMBER);
  for (int i = 0; i < SENDERS_NUMBER; ++i) timeforevent.push_back(-1);
  usedchannel = usednetwork->channel;
}

TimeBusy::~TimeBusy()
{
  timeforevent.clear();
  usednetwork = nullptr;
  usedchannel = nullptr;
}

bool TimeBusy::Execute(bool stepmode, int whichsender, double time)
{
  if (timeforevent.at(whichsender) == time)
  {
    usedsender = usednetwork->senders[whichsender];
    if (!usedchannel->isbusy) 
    {
      usedchannel->isbusy = true;
      if (stepmode) std::cout << "W czasie: " << time << ", nadajnik: " << whichsender << " kanal zostal zamkniety"<< std::endl;
    }
    timeforevent.at(whichsender) = -1;
    return true;
  }
  return false;
}

double TimeBusy::GiveTime(int whichsender)
{
  return timeforevent.at(whichsender);
}

void TimeBusy::ChangeTime(int whichsender, double time)
{
  timeforevent.at(whichsender) = time;
}


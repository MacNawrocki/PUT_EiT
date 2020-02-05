#include "ConditionalSend.h"

ConditionalSend::ConditionalSend(Network* net, Generators* gen):
  usednetwork(net),
  usedgenerator(gen),
  usedsender(nullptr)
{
  timeforevent.reserve(SENDERS_NUMBER);
  for (int i = 0; i < SENDERS_NUMBER; ++i)
  {
    timeforevent.push_back(-1);
    flag[i] = 0;
  }
  usedchannel = usednetwork->channel;
}

void ConditionalSend::ConnectEvents(TimeConverse* tevent)
{
  converseevent = tevent;
}

ConditionalSend::~ConditionalSend()
{
  timeforevent.clear();
  usedgenerator = nullptr;
  usednetwork = nullptr;
  converseevent = nullptr;
  usedchannel = nullptr;
  usedsender = nullptr;
}

bool ConditionalSend::Execute(bool stepmode, int whichsender, double time)
{
  if (timeforevent[whichsender] == time) 
  {
    usedsender = usednetwork->senders[whichsender];
    if (stepmode) std::cout << "W czasie: " << time << ", nadajnik: " << whichsender << " probuje nadac pakiet" << std::endl;
    switch (flag[whichsender])
    {
    case 0:
    {
      if (usedchannel->isbusy)
      {
        if (stepmode) std::cout << "W czasie: " << time << ", nadajnik: " << whichsender << " kanal zajety, czeka 0.5 ms" << std::endl;
        timeforevent[whichsender] += 0.5;
        return true;
      }
      else flag[whichsender] = 2;
    }
    
    case 1:
    {
      if (usedchannel->isbusy)
      {
        if (stepmode) std::cout << "W czasie: " << time << ", nadajnik: " << whichsender << " kanal zajety, czeka 1 ms" << std::endl;
        timeforevent[whichsender] += 1;
        return true;
      }
      else flag[whichsender] = 2;
    }
    
    case 2:
    {
      if (usedgenerator->PT() > 60)
      {
        int abstime = (int)time;
        if (stepmode) std::cout << "W czasie: " << time << ", nadajnik: " << whichsender << " kanal wolny, test niezdany, czeka do kolejnej przerwy" << std::endl;
        if (abstime - time == 0) timeforevent[whichsender] += 1;
        else timeforevent[whichsender] = abstime + 1;
        flag[whichsender] = 1;
        return true;
      }
      else
      {
        if (stepmode) std::cout << "W czasie: " << time << ", nadajnik: " << whichsender << " kanal wolny, test zdany, rozpoczynam transmisje" << std::endl;
        converseevent->ChangeTime(whichsender, time);
        flag[whichsender] = 0;
        timeforevent[whichsender] = -1;
        return true;
      }
    }
    }
  }
  return false;
}

double ConditionalSend::GiveTime(int whichsender)
{
  return timeforevent.at(whichsender);
}

void ConditionalSend::ChangeTime(int whichsender, double time)
{
  timeforevent.at(whichsender) = time;
}

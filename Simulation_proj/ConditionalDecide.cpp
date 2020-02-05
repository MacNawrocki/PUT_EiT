#include "ConditionalDecide.h"

ConditionalDecide::ConditionalDecide(Network* net, Generators* gen, Statistics* stat) :
usednetwork(net),
usedgenerator(gen),
usedstatistics(stat),
usedchannel(net->channel),
usedsender(nullptr),
frontpackage(nullptr),
receivedinfo(nullptr)
{
  for (int i = 0; i < SENDERS_NUMBER; ++i) timeforevent.push_back(-1);
}

ConditionalDecide::~ConditionalDecide()
{
  timeforevent.clear();
  usedgenerator = nullptr;
  usednetwork = nullptr;
  usedstatistics = nullptr;

  usedsender = nullptr;
  usedchannel = nullptr;
  frontpackage = nullptr;
  receivedinfo = nullptr;
}

bool ConditionalDecide::Execute(bool stepmode, int whichsender, double time)
{
  if (timeforevent.at(whichsender) == time)
  {
    usedsender = usednetwork->senders[whichsender];
    frontpackage = usedsender->GiveFront();
    
    if (!usedchannel->infogoing.empty()) 
    {
      receivedinfo = usedchannel->infogoing.front();
      usedchannel->infogoing.erase(usedchannel->infogoing.begin());
    }
    if(!usedchannel->channelconflict) usedchannel->isbusy = false;
    if (receivedinfo == nullptr || receivedinfo->infoidsender!=whichsender)
    {
      if (frontpackage->GetR() < RETRANSMISSIONS)
      {
        frontpackage->IncreaseR();
        frontpackage->ChangeConflictFlag(false);
        if (stepmode) std::cout << "W czasie: " << time << ", nadajnik: "<< whichsender <<" pakiet z bufora bedzie retransmitowany po raz " << frontpackage->GetR() << std::endl;
        //aktywowanie wydarzenia ConditionalSend które rozpocznie procedurê retransmisji pakietu
        usedsender->activatesend = time + usedgenerator->CRP(whichsender,frontpackage->GetR());
      }
      else
      {
        if (stepmode) std::cout<< "W czasie: " << time << ", nadajnik: " << whichsender << " pakiet z bufora zostaje odrzucony"<< std::endl;
        usedsender->DeleteFront();
        frontpackage->PackageLeft(time);
        frontpackage->ChangeReceivedFlag(false);
        usedstatistics->PushDeadPackage(frontpackage);
        usednetwork->PackageRemoved();
        //aktywowanie wydarzenia ConditionalSend które rozpocznie procedurê wysy³ania kolejnego pakietu
        if (!usedsender->IsBufferEmpty()) usedsender->activatesend = time;
      }
    }
    else
    {
      if (stepmode) std::cout << "W czasie: " << time << ", nadajnik: " << whichsender << " pakiet z bufora zostal poprawnie przeslany"<< std::endl;
      usedsender->DeleteFront();
      frontpackage->PackageLeft(time);
      frontpackage->ChangeReceivedFlag(true);
      usedstatistics->PushDeadPackage(frontpackage);
      usednetwork->PackageHasLeft();
      //aktywowanie wydarzenia ConditionalSend które rozpocznie procedurê wysy³ania kolejnego pakietu
      if (!usedsender->IsBufferEmpty()) usedsender->activatesend = time;
    }
    timeforevent.at(whichsender) = -1;
    receivedinfo = nullptr;
    return true;
  }
  return false;
}

double ConditionalDecide::GiveTime(int whichsender)
{
  return timeforevent.at(whichsender);
}

void ConditionalDecide::ChangeTime(int whichsender, double time)
{
  timeforevent.at(whichsender) = time;
  //std::cout << "Stacja nadawcza " << whichsender<< " oczekuje ACK o " << time << std::endl;
}

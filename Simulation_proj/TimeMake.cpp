#include "TimeMake.h"

TimeMake::TimeMake(Network* net, Generators* gen) : 
  usednetwork(net),
  usedgenerator(gen),
  newpackage(nullptr),
  usedsender(nullptr)
{
  timeforevent.reserve(SENDERS_NUMBER);
  for (int i = 0; i < SENDERS_NUMBER; ++i) timeforevent.push_back(usedgenerator->CGP(i));
}

TimeMake::~TimeMake()
{
  timeforevent.clear();
  usedgenerator = nullptr;
  usednetwork = nullptr;
  usedsender = nullptr;
  newpackage = nullptr;
}

bool TimeMake::Execute(bool stepmode, int whichsender, double time)
{
  if (timeforevent.at(whichsender) == time) {
    usedsender = usednetwork->senders[whichsender];
    newpackage = new Package(whichsender, time);
    usednetwork->PackageMade();
    //je¿eli dodawany jest pierwszy element do bufora to aktywowane jest wysy³anie pakietu
    if (usedsender->IsBufferEmpty()) usedsender->activatesend = time;
    usedsender->AddNew(newpackage);
    if(stepmode) std:: cout << "W czasie: " << time << ", nadajnik: "<< whichsender <<" wytworzyl pakiet" << std::endl;
    timeforevent.at(whichsender) += usedgenerator->CGP(whichsender);
    if (stepmode) std::cout << "W czasie: " << time << " , nadajnik: " << whichsender
      << " planuje wytworzenie kolejnego pakietu o " << timeforevent[whichsender] << std::endl;
    return true;
  }
return false;
}

double TimeMake::GiveTime(int whichsender)
{
  return timeforevent.at(whichsender);
}

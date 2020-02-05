#include "Simulation.h"


Simulation::Simulation(bool steps, Generators *gen, Statistics *stat):
  stepmode(steps),
  generator(gen),
  statistics(stat)
{
  network = new Network();
  // Zdarzenia czasowe
  makeevent = new TimeMake(network, generator);
  converseevent = new TimeConverse(network, generator);
  busyevent = new TimeBusy(network);
  // Zdarzenia warunkowe
  sendevent = new ConditionalSend(network, generator);
  sendevent->ConnectEvents(converseevent);
  receiveevent = new ConditionalReceive(network);
  decideevent = new ConditionalDecide(network, generator, statistics);
}

Simulation::~Simulation()
{
  generator=nullptr;
  statistics = nullptr;
  delete network;
  delete makeevent;
  delete converseevent;
  delete busyevent;
  delete sendevent;
  delete receiveevent;
  delete decideevent;
}

// Glowna petla symulacyjna
void Simulation::mainloop() {
  bool flag = true;
  bool endmainloop = false;
  int counter = 1;
  while (!endmainloop) 
  {
    counter++;
    //Aktualizowanie czasu symulacji flag¹ ustawian¹ przez execute wydarzeñ
    if (flag) 
    {
    //Najpierw flagi z stacji nadawczej zamieniane sa na aktywowane wydarzenia
     for (int i = 0; i < SENDERS_NUMBER; ++i)
     {
       if (network->senders[i]->activatesend > 0)
       {
         sendevent->ChangeTime(i, network->senders[i]->activatesend);
         network->senders[i]->activatesend = 0;
       }
       if (network->senders[i]->activatereceive > 0)
       {
         receiveevent->ChangeTime(i, network->senders[i]->activatereceive);
         network->senders[i]->activatereceive = 0;
       }
       if (network->senders[i]->activatedecide > 0)
       {
         decideevent->ChangeTime(i, network->senders[i]->activatedecide);
         network->senders[i]->activatedecide = 0;
       }
       if (network->senders[i]->activatebusy > 0)
       {
         busyevent->ChangeTime(i, network->senders[i]->activatebusy);
         network->senders[i]->activatebusy = 0;
       }
     }
     //Wybranie aktualnego czasu symulacji
     time = makeevent->GiveTime(0);
      for (int i = 0; i < SENDERS_NUMBER; ++i)
      {
        if (makeevent->GiveTime(i) < time && makeevent->GiveTime(i) >= 0) time = makeevent->GiveTime(i);
        if (converseevent->GiveTime(i) < time && converseevent->GiveTime(i) >= 0) time = converseevent->GiveTime(i);
        if (sendevent->GiveTime(i) < time && sendevent->GiveTime(i) >= 0) time = sendevent->GiveTime(i);
        if (receiveevent->GiveTime(i) < time && receiveevent->GiveTime(i) >= 0) time = receiveevent->GiveTime(i);
        if (decideevent->GiveTime(i) < time && decideevent->GiveTime(i) >= 0) time = decideevent->GiveTime(i);
        if (busyevent->GiveTime(i) < time && busyevent->GiveTime(i) >= 0) time = busyevent->GiveTime(i);
      }
      flag = false;
    }
    //Wybieranie zdarzen na które nadszedl czas
    for (int i = 0; i < SENDERS_NUMBER; ++i)
    {
      if (makeevent->Execute(stepmode, i, time)) flag = true;
      if (sendevent->Execute(stepmode, i, time)) flag = true;
      if (receiveevent->Execute(stepmode, i, time)) flag = true;
      if (decideevent->Execute(stepmode, i, time)) flag = true;
      if (converseevent->Execute(stepmode, i, time)) flag = true;
      if (busyevent->Execute(stepmode, i, time)) flag = true;
    }
   
    //Warunek konca petli symulacyjnej / podsumowanie petli symulacyjnej
    if (network->HowManyPackagesLeft()>=500)
    {
      std::cout << "Symulacja zakonczona z czasem systemowym: " << time << std::endl;
      std::cout << "Wytworzonych pakietow: "<< network->HowManyPackagesMade() << std::endl;
      std::cout << "Poprawnie odebrnych pakietow: " << network->HowManyPackagesLeft() << std::endl;
      std::cout << "Odrzuconych pakietow: " << network->HowManyPackagesRemoved() << std::endl;
      std::cout << "Pakietowa stopa bledu: " << network->PackageError() << std::endl << std::endl;
      statistics->PushError(network->PackageError());
      endmainloop = true;
    }
    if (stepmode) std::system("pause");
  }
  if (stepmode) std::system("pause");
}
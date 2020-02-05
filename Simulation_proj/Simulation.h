#pragma once

#ifndef Simulation_h_
#define Simulation_h_

#include<iostream>
#include "Network.h"
#include "Generators.h"
#include "Statistics.h"
#include "TimeMake.h"
#include "TimeConverse.h"
#include "TimeBusy.h"
#include "ConditionalSend.h"
#include "ConditionalReceive.h"
#include "ConditionalDecide.h"

class Simulation
{
public:
  Simulation(bool steps, Generators *gen, Statistics *stat);
  ~Simulation();
  void mainloop();
private:
  double time;
  bool stepmode;
  Generators* generator;
  Statistics *statistics;
  Network* network;
  TimeMake* makeevent;
  TimeConverse* converseevent;
  TimeBusy* busyevent;
  ConditionalSend* sendevent;
  ConditionalReceive* receiveevent;
  ConditionalDecide* decideevent;
};

#endif //Simulation_h_
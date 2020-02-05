#pragma once

#ifndef Statistics_h_
#define Statistics_h_

#include <iostream>
#include <fstream>
#include <vector>
#include "Package.h"
#include "GLOBALS.h"

class Statistics
{
public:
  Statistics();
  ~Statistics();
  void NextSimulation();
  void Save();
  void PushDeadPackage(Package* deadpackage);
  void SaveErrors();
  void PushError(double error);
  void SaveHistogram();
  void PushHistogramData(double data);

private:
  std::vector <Package*> allpackages;
  std::vector <double> errors;
  std::vector <double> histogram;
  int whichsimulation;
  int packagecounter;
};

#endif // !Statistics_h_
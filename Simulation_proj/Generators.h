#pragma once

#ifndef Generators_h_
#define Generators_h_

#include <random>
#include <iostream>
#include <conio.h>
#include <math.h>
#include <fstream>
#include <string>
#include "GLOBALS.h"


//Klasa zawiera generatory
class Generators
{
public:
  //double L;
  Generators();
  ~Generators();
  void GenerateSeeds();
  void ReadSeeds();
  void WriteSeeds();
  double L;
  //CPG = czas wygenerowania pakietu
  //CPG: rozk³ad wyk³adniczy o intensywnoœci L
  double CGP(int whichsender);
  //CTP = czas transmisji wiadomoœci
  //CTP: rozk³ad jednostajny w przedziale {1,2,3,...,10}
  int CTP(int whichsender);
  //CRP = czas oczekiwania w retrasmisji
  //CRP: R*CTP, R: rozk³ad jednostajny w przedziale <0,(2^r - 1)>
  int CRP(int whatsender,int r);
  //PT = prawdopodobieñstwo rozpoczêcia transmisji
  //PT: rozk³ad jednostajny w przedziale <0,100>
  double PT();

  void NextSimulation();

private:
  double Uniform(int type);
  //tablica ziaren
  long long seeds[SIMULATION_NUMBER][GENERATOR_NUMBER];
  // Numer aktualnej symulacji
  int whichsimulation;
};

#endif // !Generators_h_
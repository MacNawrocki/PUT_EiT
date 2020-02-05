#include<iostream>
#include<queue>
#include<vector>

#include "Simulation.h"
#include "Network.h"
#include "Statistics.h"
#include "Generators.h"

using namespace std;


int main()
{
  cout << "Symulacja cyfrowa sieci bezprzewodowej." << endl;
  cout << "Symulacja uruchomiona z nastepujacymi parametrami:" << endl;
  cout << "Liczba nadajnikow: " << SENDERS_NUMBER << endl;
  cout << "Ilosc retransmisji po ktorej pakiet jest odrzucany: " << RETRANSMISSIONS << endl;
  cout << "Po nadaniu pakietu, czas po ktorym kanal sie zamyka: " << TIME_GAP << endl;
  cout << "Faza pocz¹tkowa: " << START_PHASE << endl;
  cout << "Liczba symulacji: " << SIMULATION_NUMBER << endl;
  cout << endl<<"Wybierz tryb pracy: "<< endl;
  cout << "Praca krokowa : 1 "<<endl<<"Praca automatyczna: 0"<<endl<<"(0/1): ";
  bool steps;
  cin >> steps;
  cout << endl;

  Statistics *statistics = new Statistics();
  cout << "Przygotowuje generator: "<<endl;
  Generators *generator = new Generators();
  cout << "Podaj lambde do tej symulacji:";
  cin>> generator->L;
  //generator->L = 0.0089;
  cout << endl;
  for (int i = 0; i < SIMULATION_NUMBER; ++i) 
  {
    cout << "---------------------------------" << endl;
    cout << "Uruchamiam symulacje nr: " << i + 1 << endl;
    Simulation *simulation = new Simulation(steps, generator, statistics);
    simulation->mainloop();
    delete simulation;
    generator->NextSimulation();
    statistics->NextSimulation();
  }
  cout << "Koniec symulacji" << endl;
  
  cout << "Chcesz zapisac wyniki? (0/1): ";
  bool save;
  cin >> save;
  cout << endl;
  if(save) statistics->Save();
  cout << "Chcesz zapisac bledy? (0/1): ";
  cin >> save;
  cout << endl;
  if (save) statistics->SaveErrors();
  
  delete generator;
  delete statistics;
  system("pause");  
  return 0;
}
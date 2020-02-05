#pragma once
#ifndef Package_h_
#define Package_h_

//klasa opisuj¹ca pakiet
class Package
{
private:
  //r to liczba retransmisji
  int r;
  //informacje o czasie powstania, opuszczenia bufora oraz opuszczenia sieci
  double packagetimeborn;
  double packagetimestart;
  double packagetimeleave;
  //czy pakiet opuœci³ sieæ jako poprawnie odebrany czy odrzucony
  bool packagereceived;
  //czy wyst¹pi³ konflikt
  bool packageconflict;

public:
  Package(int idsender, double time);
  ~Package();

  //id stacji obs³uguj¹cych pakiet
  int packageidsender;

  //funcje obs³uguj¹ce liczbe retransmisji
  int GetR();
  void IncreaseR();
  
  //funkcje obs³uguj¹ce informacje o ¿yciu pakietu
  void PackageTransmitted(double time);
  void PackageLeft(double time);
  double GetPackageBorn();
  double GetPackageTransmitted();
  double GetPackageLeft();
  
  //funkcje ob³suguj¹ce flagi
  void ChangeConflictFlag(bool state);
  void ChangeReceivedFlag(bool state);
  bool GetConflictFlag();
  bool GetReceivedFlag();  
};

#endif //Package_h_
#include "Package.h"

Package::Package(int idsender, double time): 
  packageidsender(idsender), 
  packagetimeborn(time),
  r(0),
  packageconflict(false),
  packagereceived(false),
  packagetimeleave(0),
  packagetimestart(0)  
{
}

Package::~Package()
{
}

int Package::GetR()
{
  return r;
}

void Package::IncreaseR()
{
  r++;
}

void Package::PackageTransmitted(double time)
{
  packagetimestart = time;
}

void Package::PackageLeft(double time)
{
  packagetimeleave = time;
}

double Package::GetPackageBorn()
{
  return packagetimeborn;
}

double Package::GetPackageTransmitted()
{
  return packagetimestart;
}

double Package::GetPackageLeft()
{
  return packagetimeleave;
}

void Package::ChangeConflictFlag(bool state)
{
  packageconflict = state;
}

void Package::ChangeReceivedFlag(bool state)
{
  packagereceived = state;
}

bool Package::GetConflictFlag()
{
  return packageconflict;
}

bool Package::GetReceivedFlag()
{
  return packagereceived;
}

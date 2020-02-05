#pragma once

#ifndef Network_h_
#define Network_h_

#include "StationSender.h"
#include "StationReceiver.h"
#include "Channel.h"
#include "GLOBALS.h"
#include <vector>

class Network
{
private:
  int packagesleft;
  int packagesremoved;
  int packagesmade;
public:
  std::vector<StationSender*> senders;
  std::vector<StationReceiver*> receivers;
  Channel *channel;
  Network();
  ~Network();
  void PackageHasLeft();
  int HowManyPackagesLeft();

  void PackageRemoved();
  int HowManyPackagesRemoved();

  void PackageMade();
  int HowManyPackagesMade();
  double PackageError();
};

#endif //!Network_h_
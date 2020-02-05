#include "Network.h"

Network::Network():
  packagesleft(0),
  packagesremoved(0),
  packagesmade(0)
{
  for (int i = 0; i < SENDERS_NUMBER; ++i)
  {
    StationSender* newsender = new StationSender(i);
    StationReceiver* newreceiver = new StationReceiver(i);
    senders.push_back(newsender);
    receivers.push_back(newreceiver);
  }
  channel = new Channel();
}

Network::~Network()
{
  for (int i = 0; i < SENDERS_NUMBER; ++i)
  {
    delete senders.at(i);
    delete receivers.at(i);
  }
  senders.clear();
  receivers.clear();
  delete channel;
}

void Network::PackageHasLeft()
{
  packagesleft++;
}

int Network::HowManyPackagesLeft()
{
  return packagesleft;
}

void Network::PackageRemoved()
{
  packagesremoved++;
}

int Network::HowManyPackagesRemoved()
{
  return packagesremoved;
}

void Network::PackageMade()
{
  packagesmade++;
}

int Network::HowManyPackagesMade()
{
  return packagesmade;
}

double Network::PackageError()
{
  int allpackages = packagesleft + packagesremoved - START_PHASE;
  double error = (double) packagesremoved / (double) allpackages;
  return error;
}

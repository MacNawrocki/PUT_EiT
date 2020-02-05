#include "StationSender.h"

StationSender::StationSender(int id):senderidsender(id), activatesend(0), activatedecide(0), activatereceive(0)
{
}

StationSender::~StationSender()
{
  int originsize=buffer.size();
  for (int i = 0; i < originsize; ++i) 
  {
    delete buffer.front();
    buffer.pop();
  }
}

Package * StationSender::GiveFront()
{
  return buffer.front();
}

void StationSender::AddNew(Package * newpackage) 
{
  buffer.push(newpackage);
}

void StationSender::DeleteFront()
{
  buffer.pop();
}

bool StationSender::IsBufferEmpty()
{
  return buffer.empty();
}
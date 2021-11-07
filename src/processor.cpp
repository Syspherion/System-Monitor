#include "processor.h"

#include <iostream>
#include <string>
#include <vector>

#include "linux_parser.h"

using std::string;
using std::vector;

// TODO: Return the aggregate CPU utilization
float Processor::Utilization() {
  vector<string> dataVector = LinuxParser::CpuUtilization();

  unsigned long long int user = std::stoi(dataVector[0]);
  unsigned long long int nice = std::stoi(dataVector[1]);
  unsigned long long int system = std::stoi(dataVector[2]);
  unsigned long long int idle = std::stoi(dataVector[3]);
  unsigned long long int ioWait = std::stoi(dataVector[4]);
  unsigned long long int irq = std::stoi(dataVector[5]);
  unsigned long long int softIrq = std::stoi(dataVector[6]);
  unsigned long long int steal = std::stoi(dataVector[7]);
  unsigned long long int guest = std::stoi(dataVector[8]);
  unsigned long long int guestNice = std::stoi(dataVector[9]);

  unsigned long long int idleAll = idle + ioWait;
  unsigned long long int systemAllTime = system + irq + softIrq;
  unsigned long long int virtallTime = guest + guestNice;
  unsigned long long int nonIdle = user + nice + systemAllTime + steal + virtallTime;
  unsigned long long int total = idleAll + nonIdle;

  // # differentiate: actual value minus the previous one
  float totald = total - prevTotal;
  float idled = idleAll - prevIdleAll;

  float cpuPercentage = (totald - idled) / totald;

  prevTotal = total;
  prevIdleAll = idleAll;

  return cpuPercentage;
}
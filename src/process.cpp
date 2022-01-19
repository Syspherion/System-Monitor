#include <unistd.h>
#include <cctype>
#include <sstream>
#include <string>
#include <vector>

#include "process.h"
#include "linux_parser.h"

using namespace std;

Process::Process(int pid) : pid(pid) {
  string ramString = LinuxParser::Ram(pid);
  if (ramString.size() > 0) {
    ram = std::stof(ramString);
  } else {
    ram = 0;
  }
}

// DONE: Return this process's ID
int Process::Pid() { return pid; }

// DONE: Return this process's CPU utilization
float Process::CpuUtilization() { return LinuxParser::Cpu(pid); }

// DONE: Return the command that generated this process
string Process::Command() {
  string fullCommand = LinuxParser::Command(pid);

 //Added some substring handling to cleanup the format.
  if (fullCommand.length() > 40) {
    return fullCommand.substr(0, 40) + "...";
  } else {
    return fullCommand;
  }
}

// DONE: Return this process's memory utilization
string Process::Ram() { return LinuxParser::Ram(pid); }

// DONE: Return the user (name) that generated this process
string Process::User() { return LinuxParser::User(pid); }

// DONE: Return the age of this process (in seconds)
long int Process::UpTime() { return LinuxParser::UpTime(pid);}

// DONE: Overload the "less than" comparison operator for Process objects
bool Process::operator<(Process const& a) const { return a.ram < this->ram; }
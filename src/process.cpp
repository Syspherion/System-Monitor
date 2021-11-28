#include <unistd.h>
#include <cctype>
#include <sstream>
#include <string>
#include <vector>

#include "process.h"
#include "linux_parser.h"

using std::string;
using std::to_string;
using std::vector;

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

// TODO: Return this process's CPU utilization
float Process::CpuUtilization() { return 0; }

// DONE: Return the command that generated this process
string Process::Command() { return LinuxParser::Command(pid); }

// DONE: Return this process's memory utilization
string Process::Ram() { return LinuxParser::Ram(pid); }

// DONE: Return the user (name) that generated this process
string Process::User() { return LinuxParser::User(pid); }

// TODO: Return the age of this process (in seconds)
long int Process::UpTime() { return 0; }

// TODO: Overload the "less than" comparison operator for Process objects
bool Process::operator<(Process const& a) const { return a.ram < this->ram; }
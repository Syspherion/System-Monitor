#include "linux_parser.h"

#include <dirent.h>
#include <unistd.h>

#include <iostream>
#include <sstream>
#include <string>
#include <vector>

using std::stof;
using std::string;
using std::to_string;
using std::vector;

// DONE: An example of how to read data from the filesystem
string LinuxParser::OperatingSystem() {
  return LinuxParser::getValueFromFile("PRETTY_NAME", kOSPath, true);
}

string LinuxParser::getValueFromFile(std::string searchValue,
                                     std::string filePath,
                                     bool doReplacements) {
  string line;
  string key;
  string value;
  std::ifstream filestream(filePath);
  if (filestream.is_open()) {
    while (std::getline(filestream, line)) {
      if (doReplacements) {
        std::replace(line.begin(), line.end(), ' ', '_');
        std::replace(line.begin(), line.end(), '=', ' ');
        std::replace(line.begin(), line.end(), '"', ' ');
      }
      std::istringstream linestream(line);
      while (linestream >> key >> value) {
        if (key == searchValue) {
          if (doReplacements) {
            std::replace(value.begin(), value.end(), '_', ' ');
          }
          return value;
        }
      }
    }
  }
  return value;
}

// DONE: An example of how to read data from the filesystem
string LinuxParser::Kernel() {
  string os, kernel, version;
  string line;
  std::ifstream stream(kProcDirectory + kVersionFilename);
  if (stream.is_open()) {
    std::getline(stream, line);
    std::istringstream linestream(line);
    linestream >> os >> version >> kernel;
  }
  return kernel;
}

// BONUS: Update this to use std::filesystem
vector<int> LinuxParser::Pids() {
  vector<int> pids;
  DIR* directory = opendir(kProcDirectory.c_str());
  struct dirent* file;
  while ((file = readdir(directory)) != nullptr) {
    // Is this a directory?
    if (file->d_type == DT_DIR) {
      // Is every character of the name a digit?
      string filename(file->d_name);
      if (std::all_of(filename.begin(), filename.end(), isdigit)) {
        int pid = stoi(filename);
        pids.push_back(pid);
      }
    }
  }
  closedir(directory);
  return pids;
}

// DONE: Read and return the system memory utilization
float LinuxParser::MemoryUtilization() {
  std::string memTotal = LinuxParser::getValueFromFile(
      "MemTotal:", kProcDirectory + kMeminfoFilename, false);
  std::string memFree = LinuxParser::getValueFromFile(
      "MemFree:", kProcDirectory + kMeminfoFilename, false);

  int memTotalInt = std::stoi(memTotal);
  int memFreeInt = std::stoi(memFree);

  float result = 100.00 / memTotalInt * (memTotalInt - memFreeInt);

  return result / 100;
}

// DONE: Read and return the system uptime
long LinuxParser::UpTime() {
  string uptime;
  string line;
  std::ifstream stream(kProcDirectory + kUptimeFilename);
  if (stream.is_open()) {
    std::getline(stream, line);
    std::istringstream linestream(line);
    linestream >> uptime;
  }
  std::string::size_type sz;
  return std::stol(uptime, &sz);
}

// TODO: Read and return the number of jiffies for the system
long LinuxParser::Jiffies() { return 0; }

// TODO: Read and return the number of active jiffies for a PID
// REMOVE: [[maybe_unused]] once you define the function
long LinuxParser::ActiveJiffies(int pid [[maybe_unused]]) { return 0; }

// TODO: Read and return the number of active jiffies for the system
long LinuxParser::ActiveJiffies() { return 0; }

// TODO: Read and return the number of idle jiffies for the system
long LinuxParser::IdleJiffies() { return 0; }

// DONE: Read and return CPU utilization
vector<string> LinuxParser::CpuUtilization() {
  string line;
  string data;
  std::vector<std::string> dataVector;

  std::ifstream filestream(kProcDirectory + kStatFilename);
  std::getline(filestream, line);

  std::istringstream linestream(line);
  
  bool isFirst = true;

  while (linestream >> data) {
    if(!isFirst){
    dataVector.push_back(data);
    }else{
      isFirst = false;
    }
  }

 return dataVector;
}

// DONE: Read and return the total number of processes
int LinuxParser::TotalProcesses() {
  std::string procsRunning = LinuxParser::getValueFromFile(
      "processes", kProcDirectory + kStatFilename, false);

  return std::stoi(procsRunning);
}

// DONE: Read and return the number of running processes
int LinuxParser::RunningProcesses() {
  std::string procsRunning = LinuxParser::getValueFromFile(
      "procs_running", kProcDirectory + kStatFilename, false);

  return std::stoi(procsRunning);
}

// DONE: Read and return the command associated with a process
string LinuxParser::Command(int pid) {
  string line = "";
  std::ifstream stream(kProcDirectory + std::to_string(pid) + kCmdlineFilename);
  if (stream.is_open()) {
    std::getline(stream, line);
  }
  return line;
}

// DONE: Read and return the memory used by a process
string LinuxParser::Ram(int pid) {
  
  string ramMB = "";

  string ramKB = getValueFromFile(
      "VmSize:", kProcDirectory + std::to_string(pid) + kStatusFilename, false);

      ramMB = std::to_string(std::stof(ramKB) / 1024);

return ramMB.length()<6?ramMB:ramMB.substr(0,6);

}

// DONE: Read and return the user ID associated with a process
string LinuxParser::Uid(int pid ) {
  
    std::string uid = LinuxParser::getValueFromFile(
      "Uid:", kProcDirectory + std::to_string(pid) + kStatusFilename, false);

   return uid; 
   }

   // TODO: Read and return the user associated with a process
   // REMOVE: [[maybe_unused]] once you define the function
   string LinuxParser::User(int pid) {
     string line;
     string user;
     string something;
     string searchValue;
     std::ifstream filestream(kPasswordPath);
     if (filestream.is_open()) {
       while (std::getline(filestream, line)) {
         std::replace(line.begin(), line.end(), ':', ' ');

         std::istringstream linestream(line);
         while (linestream >> user >> something >> searchValue) {
           if (searchValue == Uid(pid)) {
       
             return user;
           }
         }
       }
     }

     return "";
   }

// TODO: Read and return the uptime of a process
// REMOVE: [[maybe_unused]] once you define the function
long LinuxParser::UpTime(int pid [[maybe_unused]]) { return 0; }

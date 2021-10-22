#include "format.h"

#include <iostream>
#include <string>

using std::string;
using std::to_string;
using namespace std;

// TODO: Complete this helper function
// INPUT: Long int measuring seconds
// OUTPUT: HH:MM:SS
// REMOVE: [[maybe_unused]] once you define the function
string Format::ElapsedTime(long seconds) {
  long timeLeft = seconds % 3600;
  long hours = (seconds - timeLeft) / 3600;
  cout << "hours:" <<hours<<"\n";

  string hoursString = (hours < 10 ? "0" : "") + to_string(hours);

  
  long minutes = (timeLeft - timeLeft % 60) / 60;
  timeLeft = timeLeft % 60;

  string minutesString = (minutes < 10 ? "0" : "") + to_string(minutes);

  string secondsString = (timeLeft < 10 ? "0" : "") + to_string(timeLeft);

  return hoursString + ":" + minutesString + ":" + secondsString;
}
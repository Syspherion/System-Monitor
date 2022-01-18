#include "format.h"

#include <iostream>
#include <string>

using std::string;
using std::to_string;
using namespace std;

// INPUT: Long int measuring seconds
// OUTPUT: HH:MM:SS
string Format::ElapsedTime(long seconds) {
  long timeLeft = seconds % 3600;
  long hours = (seconds - timeLeft) / 3600;
  string hoursString = (hours < 10 ? "0" : "") + to_string(hours);

  long minutesLeft = timeLeft % 60;
  long minutes = (timeLeft - minutesLeft) / 60;
  timeLeft = minutesLeft;

  string minutesString = (minutes < 10 ? "0" : "") + to_string(minutes);

  string secondsString = (timeLeft < 10 ? "0" : "") + to_string(timeLeft);

  return hoursString + ":" + minutesString + ":" + secondsString;
}
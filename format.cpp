#include <string>
#include <sstream>
#include "format.h"

using std::string;

// TODO: Complete this helper function
// INPUT: Long int measuring seconds
// OUTPUT: HH:MM:SS
// REMOVE: [[maybe_unused]] once you define the function
string Format::ElapsedTime(long seconds) {

  int hours = seconds/3600;
  seconds -= hours*3600;
  int minutes = seconds/60;
  seconds -= minutes * 60;

  std::ostringstream time_final;
  time_final << hours << ":" << minutes << ":" << seconds;
  return time_final.str();
}

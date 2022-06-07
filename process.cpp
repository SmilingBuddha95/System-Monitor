#include <unistd.h>
#include <cctype>
#include <sstream>
#include <string>
#include <fstream>

#include "process.h"
#include "linux_parser.h"
#include "format.h"
#include "system.h"

using std::string;
using std::to_string;
using std::vector;
using std::stol;

// TODO: Return this process's ID
int Process::Pid() { return pid_; }

// TODO: Return this process's CPU utilization
float Process::CpuUtilization() {
  string pidNum = to_string(Process::Pid());
  string line, value;
  float uptime = LinuxParser::UpTime();
  float utime, stime, cutime, cstime, starttime;
  float cpu_usage;

  std::ifstream proc_Cpu_File(LinuxParser::kProcDirectory + pidNum + LinuxParser::kStatFilename);
  if(proc_Cpu_File.is_open())
  {
    std::getline(proc_Cpu_File,line);
    std::istringstream linestream(line);

    for(int i = 0; i < 22; i++)
    {
        linestream >> value;

        switch (i) {
          case 13:
            utime = stol(value);
            break;
          case 14:
            stime = stol(value);
            break;
          case 15:
            cutime = stol(value);
            break;
          case 16:
            cstime = stol(value);
            break;
          case 21:
            starttime = stol(value);
            break;
        }
    }
    float total_time = utime + stime;
    total_time = total_time + cutime + cstime;
    float seconds = uptime - (starttime / sysconf(_SC_CLK_TCK));
    cpu_usage = (total_time / sysconf(_SC_CLK_TCK)) / seconds;
  }
  return cpu_usage;
}

// TODO: Return the command that generated this process
string Process::Command() {
  int pid = Process::Pid();
  return LinuxParser::Command(pid);
}

// TODO: Return this process's memory utilization
string Process::Ram() {
  int pid = Process::Pid();
  return LinuxParser::Ram(pid);
}

// TODO: Return the user (name) that generated this process
string Process::User() {
  int pid = Process::Pid();
  return LinuxParser::User(pid);
}

// TODO: Return the age of this process (in seconds)
long int Process::UpTime() {
  int pid = Process::Pid();
  long uptime = LinuxParser::UpTime(pid);
  return uptime;
}

// TODO: Overload the "less than" comparison operator for Process objects
// REMOVE: [[maybe_unused]] once you define the function
bool Process::operator<(Process const& a[[maybe_unused]]) const { return true; }

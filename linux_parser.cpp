#include <dirent.h>
#include <unistd.h>
#include <sstream>
#include <string>
#include <vector>

#include "linux_parser.h"

using std::stof;
using std::string;
using std::to_string;
using std::vector;

// DONE: An example of how to read data from the filesystem
string LinuxParser::OperatingSystem() {
  string line;
  string key;
  string value;
  std::ifstream filestream(kOSPath);
  if (filestream.is_open()) {
    while (std::getline(filestream, line)) {
      std::replace(line.begin(), line.end(), ' ', '_'); //REFERENCE: replace(start,end,old,new);
      std::replace(line.begin(), line.end(), '=', ' ');
      std::replace(line.begin(), line.end(), '"', ' ');
      std::istringstream linestream(line);
      while (linestream >> key >> value) {
        if (key == "PRETTY_NAME") {
          std::replace(value.begin(), value.end(), '_', ' ');
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

// TODO: Read and return the system memory utilization
float LinuxParser::MemoryUtilization() {
  string line, label;
  float val, totalMem, freeMem;
  std::ifstream memFile(kProcDirectory + kMeminfoFilename);
  if (memFile.is_open()){
    while(std::getline(memFile, line)){
      std::istringstream linestream(line);
      while(linestream >> label >> val){
        if(label == "MemTotal:"){
          totalMem = val;
        }
        if(label == "MemFree:"){
          freeMem = val;
          return (totalMem-freeMem)/totalMem;
        }
      }
    }
  }

  return 0.0;
}

// TODO: Read and return the system uptime
long LinuxParser::UpTime() {

    string line;
    string uptime_idle, uptime_all;
    std::ifstream timeFile(kProcDirectory + kUptimeFilename);
    if(timeFile.is_open()){
      std::getline(timeFile,line);
      std::istringstream linestream(line);
      linestream >> uptime_all >> uptime_idle;
    }
    return std::stol(uptime_all);
}

// TODO: Read and return the number of jiffies for the system
long LinuxParser::Jiffies() { return 0; }

// TODO: Read and return the number of active jiffies for a PID
// REMOVE: [[maybe_unused]] once you define the function
long LinuxParser::ActiveJiffies(int pid[[maybe_unused]]) { return 0; }

// TODO: Read and return the number of active jiffies for the system
long LinuxParser::ActiveJiffies() { return 0; }

// TODO: Read and return the number of idle jiffies for the system
long LinuxParser::IdleJiffies() { return 0; }

// TODO: Read and return CPU utilization
vector<string> LinuxParser::CpuUtilization()
{
  string line;
  string cpu_label, data_label;
  std:: vector<string> cpu_stat{};

  std::ifstream cpuFile("/proc/stat");
  if(cpuFile.is_open()){
    std::getline(cpuFile,line);
    std::istringstream linestream(line);
    linestream >> cpu_label;

    while(linestream >> data_label)
    {
      cpu_stat.push_back(data_label);
    }
    return cpu_stat;
  }
  return {};

}

// TODO: Read and return the total number of processes
int LinuxParser::TotalProcesses() {
  string line;
  string stat_label, value;
  std::ifstream procFile(kProcDirectory + kStatFilename);
  if(procFile.is_open())
  {
    while(std::getline(procFile, line))
    {
      std::istringstream linestream(line);
      while(linestream >> stat_label >> value)
      {
        if(stat_label == "processes")
        {
          return std::stoi(value);
        }
      }
    }
  }
  return 0;
}

// TODO: Read and return the number of running processes
int LinuxParser::RunningProcesses() {
  string line;
  string stat_label, value;
  std::ifstream procFile(kProcDirectory + kStatFilename);
  if(procFile.is_open())
  {
    while(std::getline(procFile, line))
    {
      std::istringstream linestream(line);
      while(linestream >> stat_label >> value)
      {
        if(stat_label == "procs_running")
        {
          return std::stoi(value);
        }
      }
    }
  }
  return 0;
}

// TODO: Read and return the command associated with a process
// REMOVE: [[maybe_unused]] once you define the function
string LinuxParser::Command(int pid[[maybe_unused]]) { return string(); }

// TODO: Read and return the memory used by a process
// REMOVE: [[maybe_unused]] once you define the function
string LinuxParser::Ram(int pid[[maybe_unused]]) { return string(); }

// TODO: Read and return the user ID associated with a process
// REMOVE: [[maybe_unused]] once you define the function
string LinuxParser::Uid(int pid[[maybe_unused]]) { return string(); }

// TODO: Read and return the user associated with a process
// REMOVE: [[maybe_unused]] once you define the function
string LinuxParser::User(int pid[[maybe_unused]]) { return string(); }

// TODO: Read and return the uptime of a process
// REMOVE: [[maybe_unused]] once you define the function
long LinuxParser::UpTime(int pid[[maybe_unused]]) { return 0; }

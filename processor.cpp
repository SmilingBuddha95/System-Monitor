#include "processor.h"
#include "linux_parser.h"
#include <string>

using std::stol;

// enum CPUStates {
//   kUser_ = 0,
//   kNice_,
//   kSystem_,
//   kIdle_,
//   kIOwait_,
//   kIRQ_,
//   kSoftIRQ_,
//   kSteal_,
//   kGuest_,
//   kGuestNice_
// };

// TODO: Return the aggregate CPU utilization

float Processor::Utilization() {
  std::vector<std::string> cpu_stat = LinuxParser::CpuUtilization();

  if(!cpu_stat.empty())
  {
    float PrevIdle = prev_stats[LinuxParser::kIdle_] + prev_stats[LinuxParser::kIOwait_];
    float Idle = stol(cpu_stat[LinuxParser::kIdle_]) + stol(cpu_stat[LinuxParser::kIOwait_]);

    float PrevNonIdle = prev_stats[LinuxParser::kUser_] + prev_stats[LinuxParser::kNice_] + prev_stats[LinuxParser::kSystem_] + prev_stats[LinuxParser::kIRQ_] + prev_stats[LinuxParser::kSoftIRQ_] + prev_stats[LinuxParser::kSteal_];

    float NonIdle = stol(cpu_stat[LinuxParser::kUser_]) + stol(cpu_stat[LinuxParser::kNice_]) + stol(cpu_stat[LinuxParser::kSystem_]) + stol(cpu_stat[LinuxParser::kIRQ_]) + stol(cpu_stat[LinuxParser::kSoftIRQ_]) + stol(cpu_stat[LinuxParser::kSteal_]);

    float PrevTotal = PrevIdle + PrevNonIdle;
    float Total = Idle + NonIdle;

    float totald = Total - PrevTotal;
    float idled = Idle - PrevIdle;

    float CPU_Percentage = (totald - idled)/totald;

    for(int i = 0; i < LinuxParser::kGuestNice_; i++)
    {
      prev_stats[i] = stol(cpu_stat[i]);
    }

    return CPU_Percentage;

  }

  return 0.0;
}

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

Process::Process(int pid){
  pid_ = pid;
  command_ = LinuxParser::Command(pid);
  if (command_.size() > 40){
    command_ = command_.substr(0, 40) + "...";
  }
  ram_ = LinuxParser::Ram(pid);
  user_ = LinuxParser::User(pid);
  uptime_ = LinuxParser::UpTime(pid);
  cpuutil_ = LinuxParser::ActiveJiffies(pid);
}

int Process::Pid() { return pid_;
}


float Process::CpuUtilization() const {
  	return cpuutil_;
  }


string Process::Command() { return command_; }


string Process::Ram() { return ram_; }


string Process::User() { return user_; }


long int Process::UpTime() { return uptime_; }


bool Process::operator<(Process const& a) const { return a.CpuUtilization() > CpuUtilization(); }
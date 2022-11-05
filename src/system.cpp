#include <unistd.h>
#include <cstddef>
#include <set>
#include <string>
#include <vector>
#include <algorithm>

#include "process.h"
#include "processor.h"
#include "system.h"
#include "linux_parser.h"

using std::set;
using std::size_t;
using std::string;
using std::vector;
using std::sort;


Processor& System::Cpu() { return cpu_; }


vector<Process>& System::Processes() {
  const vector<int> &pids = LinuxParser::Pids();
  for (const int & pid: pids){
    processes_.push_back(pid);
  }
//   sort(processes_.begin(), processes_.end());
  return processes_; }


std::string System::Kernel() { return LinuxParser::Kernel(); }


float System::MemoryUtilization() { return LinuxParser::MemoryUtilization(); }


std::string System::OperatingSystem() { return LinuxParser::OperatingSystem(); }


int System::RunningProcesses() { return LinuxParser::RunningProcesses(); }


int System::TotalProcesses() { return LinuxParser::TotalProcesses(); }


long int System::UpTime() { return LinuxParser::UpTime(); }

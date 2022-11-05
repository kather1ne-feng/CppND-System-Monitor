#ifndef SYSTEM_PARSER_H
#define SYSTEM_PARSER_H

#include <fstream>
#include <regex>
#include <string>

namespace LinuxParser {
    
// Paths
const std::string kProcDirectory{"/proc/"};
const std::string kCmdlineFilename{"/cmdline"};
const std::string kCpuinfoFilename{"/cpuinfo"};
const std::string kStatusFilename{"/status"};
const std::string kStatFilename{"/stat"};
const std::string kUptimeFilename{"/uptime"};
const std::string kMeminfoFilename{"/meminfo"};
const std::string kVersionFilename{"/version"};
const std::string kOSPath{"/etc/os-release"};
const std::string kPasswordPath{"/etc/passwd"};
  
const std::string kMemTotalKey{"MemTotal:"};
const std::string kMemFreeKey{"MemFree:"};
const std::string kVmSizeKey{"VmSize:"};  
const std::string kVmRSSKey{"VmRSS:"};
const std::string kUidKey{"Uid:"};
const std::string kPrettyNameKey{"PRETTY_NAME"};
const std::string kProcessNumKey{"processes"};
const std::string kProcsRunningKey{"procs_running"};
  
  
// System
float MemoryUtilization();
long UpTime();
std::vector<int> Pids();
int TotalProcesses();
int RunningProcesses();
std::string OperatingSystem();
std::string Kernel();

// CPU
enum CPUStates {
  kUser_ = 0,
  kNice_ = 1,
  kSystem_ = 2,
  kIdle_ = 3,
  kIOwait_ = 4,
  kIRQ_ = 5,
  kSoftIRQ_ = 6,
  kSteal_ = 7,
  kGuest_ = 8,
  kGuestNice_ = 9
};
  
float CpuUtilization();
long ActiveJiffies(int pid);


// Processes
std::string Command(int pid);
std::string Ram(int pid);
std::string Uid(int pid);
std::string User(int pid);
long int UpTime(int pid);
  
    template <typename T> T findValueByKey(std::string const &keyFilter, std::string const &filename) {
  std::string line, key;
    T value;
  std::ifstream stream(kProcDirectory + filename);
    if (stream.is_open()){
      while (std::getline(stream, line)) {
        std::istringstream linestream(line);
        while(linestream >> key >> value) {
          if (key == keyFilter) {
            return value;
          }
        }
      }
    }
      return value;
}
  
      template <typename T> T getValueofFile(std::string const &filename) {
  std::string line;
    T value;
  std::ifstream stream(kProcDirectory + filename);
    if (stream.is_open()){
      while (std::getline(stream, line)) {
        std::istringstream linestream(line);
        linestream >> value;
      }
    }
      return value;
}
  
        template <typename T> std::vector<T> getVectorfromLine(std::string const &filename) {
  std::string line;
    T value;
          std::vector<T> values;
  std::ifstream stream(kProcDirectory + filename);
    if (stream.is_open()){
      while (std::getline(stream, line)) {
        std::istringstream linestream(line);
        while(linestream >> value){
          values.emplace_back(value);
        }
      }
    }
      return values;
}
  
};  // namespace LinuxParser

#endif
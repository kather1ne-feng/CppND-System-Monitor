#include <dirent.h>
#include <unistd.h>
#include <sstream>
#include <string>
#include <vector>
#include <iostream>
#include <cmath>

#include "linux_parser.h"
#include "format.h"

using std::stof;
using std::stol;
using std::string;
using std::to_string;
using std::vector;
using std::trunc;



string LinuxParser::OperatingSystem() {
  string line;
  string key;
  string value;
  std::ifstream filestream(kOSPath);
  if (filestream.is_open()) {
    while (std::getline(filestream, line)) {
      std::replace(line.begin(), line.end(), ' ', '_');
      std::replace(line.begin(), line.end(), '=', ' ');
      std::replace(line.begin(), line.end(), '"', ' ');
      std::istringstream linestream(line);
      while (linestream >> key >> value) {
        if (key == kPrettyNameKey) {
          std::replace(value.begin(), value.end(), '_', ' ');
          return value;
        }
      }
    }
  }
  return value;
}


string LinuxParser::Kernel() {
  vector<string> data = getVectorfromLine<string>(kVersionFilename);

  return data[2];
}


vector<int> LinuxParser::Pids() {
  vector<int> pids;
  DIR* directory = opendir(kProcDirectory.c_str());
  struct dirent* file;
  while ((file = readdir(directory)) != nullptr) {
    if (file->d_type == DT_DIR) {
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


float LinuxParser::MemoryUtilization() {
  float memtotal, memfree;
  memtotal = findValueByKey<float>(kMemTotalKey, kMeminfoFilename);
  memfree = findValueByKey<float>(kMemFreeKey, kMeminfoFilename);
  return (memtotal-memfree)/memtotal;
}


long LinuxParser::UpTime() {
  return getValueofFile<long>(kUptimeFilename);
}


long LinuxParser::ActiveJiffies(int pid) {
  vector<string> cputil = getVectorfromLine<string>(to_string(pid) + kStatFilename);

  long totaljiffies = stol(cputil[13]) + stol(cputil[14]) + stol(cputil[15]) + stol(cputil[16]);
  long usage = totaljiffies/sysconf(_SC_CLK_TCK);
  long uptime = UpTime(pid);
  if (uptime != 0){
    return usage/uptime;
  }
 else {
   return 100;
 }
  
}


float LinuxParser::CpuUtilization() {
  vector<string> cputil = getVectorfromLine<string>(kStatFilename);

  float user, nice, system, idle, iowait, irq, softirq, steal;
  user = stof(cputil[kUser_ + 1]);
  nice = stof(cputil[kNice_ + 1]);
  system = stof(cputil[kSystem_ + 1]);
  irq = stof(cputil[kIRQ_ + 1]);
  softirq = stof(cputil[kSoftIRQ_ + 1]);
  steal = stof(cputil[kSteal_ + 1]);
  idle = stof(cputil[kIdle_ + 1]);
  iowait = stof(cputil[kIOwait_ + 1]);
  
  float activejiffies = user + nice + system + irq + softirq + steal;
  float idlejiffies = idle + iowait;
  float util = activejiffies/(activejiffies + idlejiffies);
  return util;
  
}


int LinuxParser::TotalProcesses() { 
  return findValueByKey<int>(kProcessNumKey, kStatFilename);
}

int LinuxParser::RunningProcesses() {
    return findValueByKey<int>(kProcsRunningKey, kStatFilename);
}

string LinuxParser::Command(int pid) {
  return getValueofFile<string>(to_string(pid) + kCmdlineFilename);
}

string LinuxParser::Ram(int pid) { 
  float value;
  value = findValueByKey<float>(kVmSizeKey, to_string(pid) + kStatusFilename);
//   value = findValueByKey<long>(kVmRSSKey, std::to_string(pid) + kStatusFilename);
//   use "VmRSS" if you want memory used from physical ram
	value = value/1024.0;
  	value = round(value * 100)/100;
  

  return to_string(value).substr(0, 7);

	
}



string LinuxParser::Uid(int pid) {
    return findValueByKey<string>(kUidKey, to_string(pid) + kStatusFilename);
}


string LinuxParser::User(int pid) {
    string line, key, value, user;
  string uid = Uid(pid);
  std::ifstream stream(kPasswordPath);
  if (stream.is_open()){
    while (std::getline(stream, line)) {
       std::replace(line.begin(), line.end(), ':', ' ');

      std::istringstream linestream(line);
      linestream >> key;
      while (linestream >> value){
        if (value == uid){
          user = key;
        }
      }
    }
  }
  return user;
}


long LinuxParser::UpTime(int pid) { 
 vector<string> values = getVectorfromLine<string>(to_string(pid) + kStatFilename);

  long time = stol(values[21]);
  return UpTime() - (time/sysconf(_SC_CLK_TCK));
}

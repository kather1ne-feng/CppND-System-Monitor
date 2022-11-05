#ifndef PROCESS_H
#define PROCESS_H

#include <string>
 

class Process {
 public:
  Process(int pid);
  int Pid();                               
  std::string User();                      
  std::string Command();                   
  float CpuUtilization() const;                
  std::string Ram();                       
  long int UpTime();                       
  bool operator<(Process const& a) const;  


 private:
  	int pid_;
    float cpuutil_;
  std::string command_;
  std::string ram_;
  std:: string user_;
  long int uptime_;
};

#endif
#include <vector>
#include <string>
#include <unistd.h>
#include <iostream>
#include <sstream>

#include "processor.h"
#include "linux_parser.h"

using std::vector;
using std::string;
using std::stof;


float Processor::Utilization() {
    return LinuxParser::CpuUtilization();
}
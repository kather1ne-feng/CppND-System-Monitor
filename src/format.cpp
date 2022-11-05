#include <string>

#include "format.h"

using std::string;


string Format::ElapsedTime(long times) {
  string sec, min, hr;
  int hours = (int) (times / 3600);
  int minutes = (int) ((times - (hours * 3600)) / 60);
  int seconds = (int) (times - (hours * 3600 + minutes * 60));
  if (seconds < 10) {
    sec = "0" + std::to_string(seconds);
  }
  else
    sec = std::to_string(seconds);
  if (minutes < 10) {
    min = "0" + std::to_string(minutes);
  }
  else
    min = std::to_string(minutes);
  if (hours < 10) {
    hr = "0" + std::to_string(hours);
  }
  else
    hr = std::to_string(hours);
  
  return hr + ":" + min + ":" + sec;
}
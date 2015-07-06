/*
 * error.cpp
 *
 *  Created on: 03.10.2013
 *      Author: scn
 */

#include "errors/error.h"

#include <fstream>
#include <iostream>
#include <sstream>
#include <time.h>


namespace core {

  error::error(std::string const& what) {
    log_error(what);
  }


  void error::log_error(std::string const& what) {
    std::ofstream error_log("logs/error.log", std::ios::out | std::ios::app);
    if (error_log.is_open()) {
      time_t now;
      time(&now);
      auto ts = gmtime(&now);
      char time_buffer[20];
      strftime(time_buffer, 20, "%Y %m", ts);
      int year, month;
      std::istringstream (time_buffer) >> year >> month;
      strftime(time_buffer, 20, "-%d %H:%M:%S", ts);
      error_log << year << '-';
      if (month < 10)
        error_log << '0';
      error_log << month << time_buffer << "# " << what << std::endl;
      error_log.flush();
      error_log.close();
    }
  }

}


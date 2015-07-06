/*
 * error.h
 *
 *  Created on: 03.10.2013
 *      Author: scn
 */

#ifndef ERROR_H_
#define ERROR_H_

#include <exception>
#include <string>


namespace core {

  class error : public std::exception {
    public:


    error(std::string const& what);
    error() {
      log_error("");
    }

    void log_error(std::string const& what);
  };

}

#endif /* ERROR_H_ */


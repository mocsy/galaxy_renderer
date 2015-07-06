/*
 * shader_error.h
 *
 *  Created on: 03.10.2013
 *      Author: scn
 */

#ifndef SHADER_ERROR_H_
#define SHADER_ERROR_H_

#include "error.h"


namespace core {

  namespace errors {

    class shader_error : public error {
      public:


      shader_error(std::string const& what) : error(what) {}
    };

  }

}

#endif /* SHADER_ERROR_H_ */


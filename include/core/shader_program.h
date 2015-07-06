/*
 * shader_program.h
 *
 *  Created on: 05.10.2013
 *      Author: scn
 */

#ifndef SHADER_PROGRAM_H_
#define SHADER_PROGRAM_H_


#include <string>


namespace core {
  class shader_program {
    public:


    explicit shader_program(std::string const& name) : m_name(name), m_handle(0) {}
    ~shader_program() {
      shutdown();
    }

    void init();
    void shutdown();

    unsigned int get_handle() const { return m_handle; };
    void activate();
    int get_uniform_location(std::string const& name);


    protected:


    void check_for_error(int result);


    std::string m_name;
    unsigned int m_handle;
  };
}

#endif /* SHADER_PROGRAM_H_ */


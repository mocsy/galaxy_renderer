/*
 * shader.h
 *
 *  Created on: 03.10.2013
 *      Author: scn
 */

#ifndef SHADER_H_
#define SHADER_H_


#include <string>


namespace core {

  class shader {
    public:


    shader(std::string const& name, unsigned int type) : m_name(name), m_type(type), m_handle(0), m_result(1) {}
    shader(shader&)  = delete;
    shader(shader&& right) {
      m_name   = std::move(right.m_name);
      m_type   = right.m_type;
      m_handle = right.m_handle;
      m_result = right.m_result;
    }
    ~shader() {
      shutdown();
    }


    void init();
    void shutdown();

    void check_for_error(int result);

    unsigned int get_handle() { return m_handle; };
    std::string file_path_name();

    int get_result() const { return m_result; };


    protected:


    std::string m_name;
    unsigned int m_type;
    unsigned int m_handle;
    int m_result;
  };
}

#endif /* SHADER_H_ */


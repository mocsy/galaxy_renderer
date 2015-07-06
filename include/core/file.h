/*
 * file.h
 *
 *  Created on: 03.10.2013
 *      Author: scn
 */

#ifndef FILE_H_
#define FILE_H_

#include <string>
#include <vector>
#include <system_error>


namespace core {

  class file {
    public:


    file(std::string const & name) : m_name(name) {}
    file(std::string&& name) {
      m_name = std::move(name);
    }
    file(file&) = delete;
    file(file&& right) {
      m_name = std::move(right.m_name);
    }


    static std::string content(std::string const & file_name);
    static std::vector<std::string> get_lines(std::string const& file_name);
    static void put_contents(std::string const& file_name, std::string const& contents);


    protected:


    std::string m_name;
  };

}

#endif /* FILE_H_ */


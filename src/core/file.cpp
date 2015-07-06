/*
 * file.cpp
 *
 *  Created on: 03.10.2013
 *      Author: scn
 */

#include "core/file.h"

#include <fstream>
#include <system_error>
#include <iostream>
#include <cstring>
#include <cstdio>


namespace core {

  std::string file::content(std::string const & file_name) {
    //FILE *file_handle = fopen(file_name.c_str(), "rb");
    std::ifstream file_handle(file_name.c_str(), std::ios::in | std::ios::binary);

    if(file_handle == NULL)
      throw std::system_error(ENOENT, std::system_category(), file_name.c_str());

    return std::string((std::istreambuf_iterator<char>(file_handle) ), (std::istreambuf_iterator<char>() ));
  }


  std::vector<std::string> file::get_lines(std::string const& file_name) {
    std::ifstream file_handle(file_name);

    if (!file_handle.is_open()) {
      throw std::system_error(ENOENT, std::system_category(), file_name.c_str());
    }

    std::vector<std::string> result;
    const int buffer_size = 1024;
    char buffer[buffer_size];
    while (file_handle.good()) {
      file_handle.getline(buffer, buffer_size);

      result.push_back(std::string(buffer));
    }
    file_handle.close();

    return result;
  }


  void file::put_contents(std::string const& file_name, std::string const& data) {
    std::ofstream file_handle(file_name);

    if (!file_handle.is_open()) {
      throw std::system_error(ENOENT, std::system_category(), file_name.c_str());
    }

    file_handle.write(data.c_str(), data.size());
    file_handle.close();
  }

}


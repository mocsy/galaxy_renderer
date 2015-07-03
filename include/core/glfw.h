/*
 * glfw.h
 *
 *  Created on: 16.08.2013
 *      Author: scn
 */

#ifndef GLFW_H_
#define GLFW_H_


namespace core {

  class glfw {
    public:


    glfw() = default;
    ~glfw() {
      this->shutdown();
    }
    glfw(glfw&)  = default;
    glfw(glfw&&) = default;


    void init();
    void shutdown();

  };

}

#endif /* GLFW_H_ */


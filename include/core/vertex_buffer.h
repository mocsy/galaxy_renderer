/*
 * vertex_buffer.h
 *
 *  Created on: 20.10.2013
 *      Author: scn
 */

#ifndef VERTEX_BUFFER_H_
#define VERTEX_BUFFER_H_


#include <vector>

#include <GL/glew.h>


namespace core {

  class vertex_buffer {
    public:


    vertex_buffer() : m_id(0) {}
    ~vertex_buffer() {
      shutdown();
    }


    void init() {
      glGenBuffers(1, &m_id);
    }

    void shutdown() {
      glDeleteBuffers(1, &m_id);
    }

    void activate() {
      glBindBuffer(GL_ARRAY_BUFFER, m_id);
    }
    void deactivate() {};


    template <class T>
    void set_data(std::vector<T> const& data);
    template <class T>
    void set_data(T const& data, unsigned int vector_size, unsigned int vertex_size);


    protected:


    unsigned int m_id;
  };

}

#endif /* VERTEX_BUFFER_H_ */


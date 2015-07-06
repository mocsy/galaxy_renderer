/*
 * vertex_array.h
 *
 *  Created on: 20.10.2013
 *      Author: scn
 */

#ifndef VERTEX_ARRAY_H_
#define VERTEX_ARRAY_H_


namespace core {

  class vertex_array {
    public:


    explicit vertex_array(unsigned int count = 1) : m_count(count), m_handle(0) {};
    ~vertex_array() {
      shutdown();
    }


    void init();
    void shutdown();


    void activate();
    void deactivate();


    protected:


    unsigned int m_count, m_handle;
  };

}

#endif /* VERTEX_ARRAY_H_ */


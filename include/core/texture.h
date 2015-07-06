/*
 * texture.h
 *
 *  Created on: 20.09.2014
 *      Author: scn
 */

#ifndef TEXTURE_H_
#define TEXTURE_H_


namespace core {

  class texture {
    public:


    explicit texture(int unit_id) : m_id(unit_id), m_handle(0) {}
    ~texture() {
      shutdown();
    }


    void init();
    void shutdown();

    void activate();
    int get_unit_id() const { return m_id; };


    protected:


    int m_id;
    unsigned int m_handle;
  };

}


#endif /* TEXTURE_H_ */


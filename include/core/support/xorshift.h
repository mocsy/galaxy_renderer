/*
 * xorshift.h
 *
 *  Created on: 13.10.2013
 *      Author: scn
 */

#ifndef XORSHIFT_H_
#define XORSHIFT_H_


#include <limits>

namespace core {

  namespace support {

    template <class T>
    class xorshift {
      public:

      typedef T result_type;

      static constexpr T default_seed = 88172645463325252ull;


      explicit xorshift(T const& seed = default_seed) : m_current(seed) {}
      xorshift(xorshift const& right) {
        m_current = right.m_current;
      }
      xorshift(xorshift & right) {
        m_current = right.m_current;
      }


      result_type operator()() {
        m_current ^= m_current << 13;
        m_current ^= m_current >> 7;
        m_current ^= m_current << 17;
        return m_current;
      }


      void seed(result_type seed = default_seed) {
        m_current = seed;
      }


      static constexpr result_type min() { return std::numeric_limits<T>::min(); }
      static constexpr result_type max() { return std::numeric_limits<T>::max(); }


      void discard(result_type __z) {
        for (; __z != result_type(0); --__z)
          (*this)();
      }


      protected:


      T m_current;
    };

  }

}
template <class T> constexpr T core::support::xorshift<T>::default_seed;


#endif /* XORSHIFT_H_ */


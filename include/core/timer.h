/*
 * timer.h
 *
 *  Created on: 11.01.2015
 *      Author: scn
 */

#ifndef TIMER_H_
#define TIMER_H_


namespace core {
  class timer {
    public:


    timer() : m_start_time(0.0) {};
    ~timer() {
      shutdown();
    };


    void init();
    void reset() { init(); };
    void shutdown();

    double elapsed_time() const;


    protected:


    double m_start_time;
  };

}

#endif /* TIMER_H_ */


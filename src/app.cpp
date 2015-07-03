/*
 * app.cpp
 *
 *  Created on: 03.07.2015
 *      Author: scones
 */


#include "app.h"


app::app(std::uint64_t const number_of_stars)
  :
    m_number_of_stars(number_of_stars),
    m_glfw(core::glfw()),
    m_window(core::window(800, 600, "galaxy simulation by density wave"))
{
}


void app::init() {

}


void app::run() {

}


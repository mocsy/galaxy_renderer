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
  m_glfw.init();
  m_window.init();

  m_galaxy.Reset(13000,    // radius of the galaxy
    4000,     // radius of the core
    0.0004,   // angluar offset of the density wave per parsec of radius
    0.9,      // excentricity at the edge of the core
    0.9,      // excentricity at the edge of the disk
    0.5,
    200,      // orbital velocity at the edge of the core
    300,      // orbital velovity at the edge of the disk
    30000);   // total number of stars

}


void app::run() {

}


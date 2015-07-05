/*
 * File:   main.cpp
 * Author: beltoforion, scones
 *
 * Created on 5. Juli 2009, 22:15
 * Updated on 2015.07.03
 */

#include <cstdlib>
#include <iostream>


#ifdef __MINGW64__
#include <windows.h>
#endif


#include "app.h"


#ifdef __MINGW64__
int WINAPI WinMain (HINSTANCE hInst, HINSTANCE hPrev, char* lpCmdLine, int nCmdShow) {
#else
int main (int argc, char** argv) {
#endif
  try {
    app galaxy_renderer(4000);
    galaxy_renderer.init();

    galaxy_renderer.run();
  } catch(std::exception & exc) {
    std::cout << "Fatal error: " << exc.what() << std::endl;
  } catch(...) {
    std::cout << "Fatal error: unexpected exception" << std::endl;
  }

  return 0;
}


/*
 * File:   main.cpp
 * Author: beltoforion, scones
 *
 * Created on 5. Juli 2009, 22:15
 * Updated on 2015.07.03
 */

#include <cstdlib>
#include <iostream>


#include "NBodyWnd.h"


int main(int argc, char** argv) {
  try {
    NBodyWnd wndMain(800, "Density wave simulation");

    // Define simulation size
    wndMain.Init(4000);
    wndMain.MainLoop();
  } catch(std::exception & exc) {
    std::cout << "Fatal error: " << exc.what() << std::endl;
  } catch(...) {
    std::cout << "Fatal error: unexpected exception" << std::endl;
  }

  return 0;
}


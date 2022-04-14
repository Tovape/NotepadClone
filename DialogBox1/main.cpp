#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <winuser.h>
#include <tchar.h>
#include <windows.h>

// Including Files

#include "header.h"
#include "functions.cpp"

using namespace std;

// C++ Boxes

int main() {

  cout << "Dialog Boxes\n";

  cout << "Dialog 1 - MessageBox\n";
  cout << box1() << "\n";

  return 0;
}

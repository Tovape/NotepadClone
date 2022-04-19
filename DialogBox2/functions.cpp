#include <iostream>
#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <tchar.h>
#include "wtypes.h"
#include <string.h>

using namespace std;

void menuItem1() {

  // Creates Window Box
  int menuItemBox1 = MessageBoxW(
    NULL,
    L"Toni Valverde\nVersion 1.0",
    L"Information",
    MB_ICONINFORMATION | MB_OK
  );

}

void menuItem2() {

  // Opens Link
  string openWebpage = string("start ").append("https://tovape.github.io");
  system(openWebpage.c_str());

}

// login

int GeneralLogin(char username[30], char password[30]) {
  if (strcmp(username, "Tovape") == 0 && strcmp(password, "123") == 0) {
    return 0;
  } else {
    return 1;
  }

}



// Getting Desktop Resolution - Inoperative

/*
int* GetDesktopResolution(int returnValues[]) {
  RECT desktop;
  const HWND hDesktop = GetDesktopWindow();
  GetWindowRect(hDesktop, &desktop);
  int horizontal = 0;
  int vertical = 0;
  horizontal = desktop.right;
  vertical = desktop.bottom;
  returnValues[0] = horizontal;
  returnValues[1] = vertical;
  return returnValues;
}
*/

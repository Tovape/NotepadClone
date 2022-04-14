#include <iostream>
#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <tchar.h>
#include "wtypes.h"

#define FILE_MENU_NEW 3
#define FILE_MENU_OPEN 4
#define FILE_MENU_EXIT 5

// Including Files

#include "header.h"
#include "functions.cpp"

using namespace std;

// C++ Boxes

LRESULT CALLBACK WindowProcedure(HWND, UINT, WPARAM, LPARAM);

void AddMenus(HWND hWnd);

HMENU hMenu;

int WINAPI WinMain(HINSTANCE box2, HINSTANCE hPrevInst, LPSTR args, int ncmdshow) {
  WNDCLASSW wc = {0};
  wc.hbrBackground = (HBRUSH)COLOR_WINDOW;
  wc.hCursor = LoadCursor(NULL, IDC_CROSS);
  wc.hInstance = box2;
  wc.lpszClassName = L"box2";
  wc.lpfnWndProc = WindowProcedure;

  if (!RegisterClassW(&wc)) {
    return 1;
  }

  // Getting Screen Resolution to place Screen in the center

  int p[1];
  int *desktopResolution = GetDesktopResolution(p);
  cout << "Screen Resolution: " << desktopResolution[0] << "x" << desktopResolution[1] << "\n";

  // Window Creation
  CreateWindowW(L"box2", L"My Window", WS_OVERLAPPEDWINDOW | WS_VISIBLE,0,100,desktopResolution[0]/2,desktopResolution[1]/2,NULL,NULL,NULL,NULL);

  MSG msg = {0};

  while(GetMessage(&msg,NULL,NULL,NULL)) {
    TranslateMessage(&msg);
    DispatchMessage(&msg);
  }

  sleep(2);
  return 0;
}

// Handling Window Properties (Being Open/Closed/Sized etc)

LRESULT CALLBACK WindowProcedure(HWND hWnd, UINT msg, WPARAM wp, LPARAM lp) {
  switch (msg) {
    // Closed
    case WM_DESTROY:
      PostQuitMessage(0);
      cout << "Window Closed\n";
      break;
    // Being Moved
    case WM_MOVING:
      //cout << "Moving Window\n";
      break;
    // Being Created
    case WM_NCCREATE:
      // We can now create the menus for our program in functions.cpp
      AddMenus(hWnd);
      cout << "Window Created\n";
      break;
    // Being Sized
    case WM_SIZING:
      cout << "Sizing\n";
      break;
    // Being Acive
    case WM_NCACTIVATE:
      cout << "Active\n";
      break;

    // Menu Items Behaviour
    case WM_COMMAND:
      cout << "Menu Item Selected\n";

      switch(wp) {
        // Handling Menu Buttons
        case 1:
          menuItem1();
          cout << "Menu Item 1 - Active\n";
          break;
        case 2:
          MessageBeep(MB_OK); // Message Sound Effect
          menuItem2();
          cout << "Menu Item 2 - Active\n";
          break;
        // Handling Context Menu
        case FILE_MENU_NEW:
        case FILE_MENU_OPEN:
        case FILE_MENU_EXIT:
          cout << "Menu Item 3 (Exit) - Active\n";
          DestroyWindow(hWnd);
          break;

      }

    default:
      return DefWindowProcW(hWnd,msg,wp,lp);
  }
}

// Creating Menu Bars

void AddMenus(HWND hWnd) {
  hMenu = CreateMenu();

  HMENU hSubmenu = CreateMenu();
    AppendMenu(hSubmenu, MF_STRING, 7, "asd");

  // File Menu
  HMENU hFileMenu = CreateMenu();
  // Adding Context Menu to the option File
  AppendMenu(hFileMenu, MF_STRING, FILE_MENU_NEW, "New");
  AppendMenu(hFileMenu, MF_POPUP, (UINT_PTR)hSubmenu, "Open");
  //Adding Separator
  AppendMenu(hFileMenu, MF_SEPARATOR,NULL,NULL);
  AppendMenu(hFileMenu, MF_STRING, FILE_MENU_EXIT, "Exit");

  AppendMenu(hMenu, MF_POPUP, (UINT_PTR)hFileMenu, "File");
  AppendMenu(hMenu, MF_STRING, 2, "Info");
  AppendMenu(hMenu, MF_STRING, 3, "Help");

  SetMenu(hWnd,hMenu);
}

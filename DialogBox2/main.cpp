#include <iostream>
#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <tchar.h>
#include <wtypes.h>

#define FILE_MENU_NEW 4
#define FILE_MENU_OPEN 5
#define FILE_MENU_EXIT 6

// Including Files

#include "header.h"
#include "functions.cpp"

using namespace std;

// C++ Boxes

LRESULT CALLBACK WindowProcedure(HWND, UINT, WPARAM, LPARAM);

void AddMenus(HWND hWnd);
void AddControl(HWND hWnd);

HICON hIcon1;
HMENU hMenu;

// Background Window Colors
COLORREF color = RGB(0x00, 0x00, 0x00);
HBRUSH backgroundColor = ::CreateSolidBrush(color);

COLORREF color2 = RGB(0xFF, 0x00, 0x00);
HBRUSH backgroundColor2 = ::CreateSolidBrush(color2);

int WINAPI WinMain(HINSTANCE box2, HINSTANCE hPrevInst, LPSTR args, int ncmdshow) {
  SetConsoleTitleA("Debugger");

  WNDCLASSW wc = {0};
  wc.hbrBackground = (HBRUSH)backgroundColor;
  wc.hCursor = LoadCursor(NULL, IDC_CROSS);
  wc.hInstance = box2;
  wc.lpszClassName = L"box2";
  wc.lpfnWndProc = WindowProcedure;
  if (!RegisterClassW(&wc)) {
    return 1;
  }

  WNDCLASSW wcs = {0};
  wcs.hbrBackground = (HBRUSH)backgroundColor2;
  wcs.hInstance = box2;
  wcs.lpszClassName = L"static";
  wcs.lpfnWndProc = WindowProcedure;
  if (!RegisterClassW(&wcs)) {
    return 1;
  }

  // Getting Screen Resolution to place Screen in the center

  int screenWidth = GetSystemMetrics(SM_CXSCREEN);
  int screenHeight = GetSystemMetrics(SM_CYSCREEN);
  cout << "Screen resolution: " << screenWidth << "x" << screenHeight << "\n";

  // Window Creation
  //CreateWindowExW(WS_EX_CLIENTEDGE | WS_HSCROLL | WS_EX_ACCEPTFILES, L"box2", L"badox2", WS_OVERLAPPEDWINDOW | WS_VISIBLE,(screenWidth-500)/2,(screenHeight-500)/2,500,500,NULL,NULL,NULL,NULL);
  CreateWindowW(L"box2", L"Null", WS_OVERLAPPEDWINDOW | WS_VISIBLE,(screenWidth-500)/2,(screenHeight-500)/2,500,500,NULL,NULL,NULL,NULL);

  MSG msg = {0};

  while(GetMessage(&msg,NULL,NULL,NULL)) {
    TranslateMessage(&msg);
    DispatchMessage(&msg);
  }

  return 0;
}

// Handling Window Properties (Being Open/Closed/Sized etc)

LRESULT CALLBACK WindowProcedure(HWND hWnd, UINT msg, WPARAM wp, LPARAM lp) {
  switch (msg) {
    // Default
    default:
      return DefWindowProcW(hWnd,msg,wp,lp);
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
      AddControl(hWnd);
      // Set Window Title
      SetWindowTextW(hWnd, L"My Program");
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
        case 3:
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
          cout << "Menu Item 3 (New) - Active\n";
          break;
        case FILE_MENU_OPEN:
          cout << "Menu Item 4 (Open) - Active\n";
          break;
        case FILE_MENU_EXIT:
          cout << "Menu Item 5 (Exit) - Active\n";
          DestroyWindow(hWnd);
          break;
      }
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

// Adding Controls

void AddControl(HWND hWnd) {
  CreateWindowW(L"static", L"Username:", WS_VISIBLE | WS_CHILD, 250, 250, 250, 100, hWnd, NULL, NULL, NULL);
}

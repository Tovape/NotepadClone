#include <iostream>
#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <tchar.h>
#include <wtypes.h>
#include <string.h>

#define FILE_MENU_INFO 2
#define FILE_MENU_HELP 3
#define FILE_MENU_NEW 4
#define FILE_MENU_OPEN 5
#define FILE_MENU_EXIT 6
#define GENERAL_LOGIN 8

// Including Files

#include "header.h"
#include "functions.cpp"

using namespace std;

// C++ Boxes

LRESULT CALLBACK WindowProcedure(HWND, UINT, WPARAM, LPARAM);

void AddMenus(HWND hWnd);
void AddContent(HWND hWnd);
void loadImages();

HMENU hMenu;
HWND hUsername;
HWND hPassword;
HWND hLoginstatus;
HWND hLogo;
HBITMAP hLogoImage, hButtonImage;

// Background Window Colors
COLORREF color = RGB(0xFF, 0xFF, 0xFF);
HBRUSH backgroundColor = ::CreateSolidBrush(color);

COLORREF color2 = RGB(0xFF, 0x00, 0x00);
HBRUSH backgroundColor2 = ::CreateSolidBrush(color2);

// Gradient

// Main
int WINAPI WinMain(HINSTANCE box2, HINSTANCE hPrevInst, LPSTR args, int ncmdshow) {
  SetConsoleTitleA("Debugger");

  WNDCLASSW wc = {0};
  wc.hbrBackground = (HBRUSH)backgroundColor2;
  wc.hCursor = LoadCursor(NULL, IDC_CROSS);
  wc.hInstance = box2;
  wc.lpszClassName = L"box2";
  wc.lpfnWndProc = WindowProcedure;
  if (!RegisterClassW(&wc)) {
    return 1;
  }

  /* Adds backgroundColor to button
  WNDCLASSW wsc = {0};
  wsc.hbrBackground = (HBRUSH)backgroundColor2;
  wsc.hCursor = LoadCursor(NULL, IDC_CROSS);
  wsc.hInstance = box2;
  wsc.lpszClassName = L"Button";
  wsc.lpfnWndProc = WindowProcedure;
  if (!RegisterClassW(&wsc)) {
    return 1;
  }
  */

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
      // Load Images
      loadImages();
      // We can now create the menus for our program in functions.cpp
      AddMenus(hWnd);
      // Adding Content
      AddContent(hWnd);
      // Set Window Title
      SetWindowTextW(hWnd, L"My Program");
      break;
    // Being Sized
    //case WM_SIZING:
      //cout << "Sizing\n";
      //break;
    // Being Acive
    case WM_NCACTIVATE:
      cout << "Active\n";
      break;
    // Menu Items Behaviour
    case WM_COMMAND:
      switch(wp) {
        // Login function
        case GENERAL_LOGIN:
          char username[30], password[30];
          GetWindowText(hUsername,username,30);
          GetWindowText(hPassword,password,30);
          cout << "Logging...\n";
          if (GeneralLogin(username, password) == 0) {
            cout << "Login Accepted.\n";
            SetWindowText(hLoginstatus, "Login Accepted");
          } else if (GeneralLogin(username, password) == 1) {
            cout << "Incorrect Login.\n";
            SetWindowText(hLoginstatus, "Incorrect Login");
          } else {
            cout << "There's been an Error.\n";
            SetWindowText(hLoginstatus, "There's been an Error");
          }
          break;
        // Handling Menu Buttons
        case FILE_MENU_INFO:
          menuItem1();
          cout << "Menu Item 1 (Info) - Active\n";
          break;
        case FILE_MENU_HELP:
          MessageBeep(MB_OK); // Message Sound Effect
          menuItem2();
          cout << "Menu Item 2 (Help) - Active\n";
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
    AppendMenu(hSubmenu, MF_STRING, 7, "Submenu");

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

// Adding Content

void AddContent(HWND hWnd) {
  // Username Field
  CreateWindowW(L"static", L"Username:", WS_VISIBLE | WS_CHILD | SS_CENTER, 150, 50, 100, 20, hWnd, NULL, NULL, NULL);
  hUsername = CreateWindowW(L"Edit", L"", WS_VISIBLE | WS_CHILD | WS_BORDER | ES_MULTILINE | ES_AUTOVSCROLL, 250, 50, 98, 20, hWnd, NULL, NULL, NULL);

  // Password Field
  CreateWindowW(L"static", L"Password:", WS_VISIBLE | WS_CHILD | SS_CENTER, 150, 90, 100, 20, hWnd, NULL, NULL, NULL);
  hPassword = CreateWindowW(L"Edit", L"", WS_VISIBLE | WS_CHILD | WS_BORDER, 250, 90, 98, 20, hWnd, NULL, NULL, NULL);

  // Login Button
  // CreateWindowW(L"Button", L"Login", WS_VISIBLE | WS_CHILD | WS_BORDER | SS_CENTER, 150, 120, 198, 30, hWnd, (HMENU)GENERAL_LOGIN, NULL, NULL);

  // With Image
  //HWND hBut = CreateWindowW(L"Button", L"Login", WS_VISIBLE | WS_CHILD | SS_CENTER | BS_BITMAP, 150, 120, 198, 30, hWnd, (HMENU)GENERAL_LOGIN, NULL, NULL);
  //SendMessageW(hBut, BM_SETIMAGE, IMAGE_BITMAP, (LPARAM) hButtonImage);

  CreateWindowW(L"Button", L"Login", WS_VISIBLE | WS_CHILD | WS_BORDER | SS_CENTER | BS_OWNERDRAW, 150, 120, 198, 30, hWnd, (HMENU)GENERAL_LOGIN, NULL, NULL);

  // Show Login Status
  hLoginstatus = CreateWindowW(L"Edit", L"", WS_VISIBLE | WS_CHILD | WS_BORDER, 150, 160, 198, 20, hWnd, NULL, NULL, NULL);

  // Load logo
  hLogo = CreateWindowW(L"static", NULL, WS_VISIBLE | WS_CHILD | SS_BITMAP, 100, 100, 100, 100, hWnd, NULL, NULL, NULL);
  SendMessageW(hLogo, STM_SETIMAGE, IMAGE_BITMAP, (LPARAM) hLogoImage);
}

// Load Images and Icons

void loadImages() {
  hLogoImage = (HBITMAP)LoadImageW(NULL, L"logo.bmp", IMAGE_BITMAP, 20, 20, LR_LOADFROMFILE);
  hButtonImage = (HBITMAP)LoadImageW(NULL, L"logo.bmp", IMAGE_BITMAP, 198, 30, LR_LOADFROMFILE);
}

#include <iostream>
#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <tchar.h>
#include <wtypes.h>
#include <string.h>

// Prototypes
LRESULT CALLBACK DialogFontProcedure(HWND hWnd, UINT msg, WPARAM wp, LPARAM lp);

// Creating Menu Bars
void AddMenu(HWND hWnd, HMENU hMenu) {

  // Menus
  hMenu = CreateMenu();
  HMENU hFileMenu = CreateMenu();
  HMENU hEditionMenu = CreateMenu();
  HMENU hFormatMenu = CreateMenu();
  HMENU hViewMenu = CreateMenu();
  HMENU hHelpMenu = CreateMenu();

  // Appending Menu Content

  // File
  AppendMenu(hMenu, MF_POPUP, (UINT_PTR)hFileMenu, "File");
  AppendMenu(hFileMenu, MF_STRING | MF_ENABLED, FILE_MENU_NEW, "&New\tCtrl+N");
  AppendMenu(hFileMenu, MF_STRING | MF_ENABLED, FILE_MENU_NEWINDOW, "&New Window\tCtrl+S");
  AppendMenu(hFileMenu, MF_STRING | MF_ENABLED, FILE_MENU_OPEN, "&Open\tCtrl+May+N");
  AppendMenu(hFileMenu, MF_STRING | MF_ENABLED, FILE_MENU_SAVE, "&Save\tCtrl+G");
  AppendMenu(hFileMenu, MF_STRING | MF_ENABLED, FILE_MENU_SAVEAS, "&Save As\tCtrl+May+S");
  AppendMenu(hFileMenu, MF_SEPARATOR,NULL,NULL);
  AppendMenu(hFileMenu, MF_STRING, FILE_MENU_CONFIGPAGE, "Configure Page");
  AppendMenu(hFileMenu, MF_STRING | MF_ENABLED, FILE_MENU_PRINT, "&Print\tCtrl+P");
  AppendMenu(hFileMenu, MF_SEPARATOR,NULL,NULL);
  AppendMenu(hFileMenu, MF_STRING, FILE_MENU_EXIT, "Exit");

  // Edition
  AppendMenu(hMenu, MF_POPUP, (UINT_PTR)hEditionMenu, "Edition");
  AppendMenu(hEditionMenu, MF_STRING | MF_ENABLED, EDITION_UNDO, "&Undo\tCtrl+Z");
  AppendMenu(hEditionMenu, MF_SEPARATOR,NULL,NULL);
  AppendMenu(hEditionMenu, MF_STRING | MF_ENABLED, EDITION_CUT, "&Cut\tCtrl+X");
  AppendMenu(hEditionMenu, MF_STRING | MF_ENABLED, EDITION_COPY, "&Copy\tCtrl+C");
  AppendMenu(hEditionMenu, MF_STRING | MF_ENABLED, EDITION_PASTE, "&Paste\tCtrl+P");
  AppendMenu(hEditionMenu, MF_STRING | MF_ENABLED, EDITION_DELETE, "&Delete\tSupr");
  AppendMenu(hEditionMenu, MF_SEPARATOR,NULL,NULL);
  AppendMenu(hEditionMenu, MF_STRING | MF_ENABLED, EDITION_SEARCHBING, "&Search with Bing\tCtrl+F");
  AppendMenu(hEditionMenu, MF_STRING | MF_ENABLED, EDITION_SEARCH, "&Search\tCtrl+B");
  AppendMenu(hEditionMenu, MF_STRING | MF_ENABLED, EDITION_SEARCHNEXT, "&Search Next\tF3");
  AppendMenu(hEditionMenu, MF_STRING | MF_ENABLED, EDITION_SEARCHPREV, "&Search Previous\tMay+F3");
  AppendMenu(hEditionMenu, MF_STRING | MF_ENABLED, EDITION_REPLACE, "&Replace\tCtrl+R");
  AppendMenu(hEditionMenu, MF_STRING | MF_ENABLED, EDITION_GOTO, "&Go To\tCtrl+T");
  AppendMenu(hEditionMenu, MF_SEPARATOR,NULL,NULL);
  AppendMenu(hEditionMenu, MF_STRING | MF_ENABLED, EDITION_SELECTALL, "&Select All\tCtrl+E");
  AppendMenu(hEditionMenu, MF_STRING | MF_ENABLED, EDITION_TIMEDATE, "&Time & Date\tF5");

  // Format
  AppendMenu(hMenu, MF_POPUP, (UINT_PTR)hFormatMenu, "Format");
  AppendMenu(hFormatMenu, MF_STRING, FORMAT_LINESETTING, "Line Settings");
  AppendMenu(hFormatMenu, MF_STRING, FORMAT_FONT, "Font");

  // View

  AppendMenu(hMenu, MF_POPUP, (UINT_PTR)hViewMenu, "View");

  HMENU hViewSubmenu = CreateMenu();
  AppendMenu(hViewSubmenu, MF_STRING | MF_ENABLED, VIEW_ZOOMIN, "&Zoom In\tCtrl++");
  AppendMenu(hViewSubmenu, MF_STRING | MF_ENABLED, VIEW_ZOOMOUT, "&Zoom Out\tCtrl+-");
  AppendMenu(hViewSubmenu, MF_STRING | MF_ENABLED, VIEW_ZOOMDEF, "&Restore Zoom\tCtrl+0");
  AppendMenu(hViewMenu, MF_STRING, (UINT_PTR)hViewSubmenu, "Zoom");
  AppendMenu(hViewMenu, MF_STRING, VIEW_STATUS, "Status Bar");

  // Help
  AppendMenu(hMenu, MF_POPUP, (UINT_PTR)hHelpMenu, "Help");
  AppendMenu(hHelpMenu, MF_STRING, HELP_VIEW, "View Help");
  AppendMenu(hHelpMenu, MF_STRING, HELP_SUGGESTION, "Send Suggestion");
  AppendMenu(hHelpMenu, MF_SEPARATOR,NULL,NULL);
  AppendMenu(hHelpMenu, MF_STRING, HELP_ABOUT, "About Notepad-Clone");

  SetMenu(hWnd,hMenu);
}

// Adding Items - Inoperative
/*
void AddContent(HWND hWnd, HWND hEditor) {
  // Scroll Bar width is 17
  //hEditor = CreateWindowW(L"Edit", L"", WS_VISIBLE | WS_CHILD | ES_MULTILINE | WS_VSCROLL | WS_HSCROLL | ES_AUTOHSCROLL | ES_AUTOVSCROLL, 0, 0, 683, 440, hWnd, NULL, NULL, NULL);
}
*/

// Font Dialog Box
void ClassDialogFont(HINSTANCE mainWindow) {

  WNDCLASSW fontClass = {0};
  fontClass.hbrBackground = (HBRUSH)COLOR_WINDOW;
  fontClass.hCursor = LoadCursor(NULL, IDC_ARROW);
  fontClass.hInstance = mainWindow;
  fontClass.lpszClassName = L"fontDialog";
  fontClass.lpfnWndProc = DialogFontProcedure;

  RegisterClassW(&fontClass);

}

void CreateDialogFont(HWND hWnd, int screenWidth, int screenHeight, HFONT hSecundaryFont, HWND hApplyFont, HWND hFontList) {

  typedef struct {
      TCHAR fontName[64];
      int fontId;
  } Fonts;

  Fonts fontList[] =
  {
      {TEXT("Consolas"), 1 },
      {TEXT("Courier"), 2 }
  };


  HWND hfontDialog = CreateWindowW(L"fontDialog", L"", WS_VISIBLE | WS_OVERLAPPEDWINDOW, (screenWidth-500)/2, (screenHeight-500)/2, 400, 500, hWnd, NULL, NULL, NULL);
  SetWindowLong(hfontDialog, GWL_STYLE,GetWindowLong(hfontDialog, GWL_STYLE) & ~WS_MINIMIZEBOX & ~WS_MAXIMIZEBOX);

  // Adding Content
  hApplyFont = CreateWindowW(L"static", L"Font:", WS_VISIBLE | WS_CHILD, 10, 10, 180, 20, hfontDialog, NULL, NULL, NULL);
  CreateWindowW(L"edit", L"", WS_VISIBLE | WS_CHILD | WS_BORDER, 10, 34, 180, 20, hfontDialog, NULL, NULL, NULL);
  hFontList = CreateWindowW(L"listbox", NULL, WS_VISIBLE | WS_CHILD | WS_VSCROLL | ES_AUTOVSCROLL, 10, 64, 180, 100, hfontDialog, NULL, NULL, NULL);

  CreateWindowW(L"Button", L"Login", WS_VISIBLE | WS_CHILD | WS_BORDER | SS_CENTER, 150, 120, 198, 30, hfontDialog, (HMENU)FORMAT_FONT_LIST, NULL, NULL);


  int fontListArray = sizeof(fontList)/sizeof(fontList[0]);

  // Adding Items in the Font List
  for (int i = 0; i < fontListArray; i++) {
    int pos = (int)SendMessage(hFontList, LB_ADDSTRING, 0, (LPARAM) fontList[i].fontName);
    SendMessage(hFontList, LB_SETITEMDATA, pos, (LPARAM) i);
  }

  SetFocus(hFontList);

  //CreateWindowW(L"combobox", L"Dropdown?", WS_VISIBLE | WS_CHILD, 20, 20, 198, 20, hfontDialog, NULL, NULL, NULL);

  // Setting Font
  SendMessage(hApplyFont, WM_SETFONT, (WPARAM)hSecundaryFont, TRUE);

  EnableWindow(hWnd, false);
}

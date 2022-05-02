#include <iostream>
#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <tchar.h>
#include <wtypes.h>
#include <string.h>
#include <chrono>
#include <ctime>

// Prototypes
LRESULT CALLBACK DialogFontProcedure(HWND hWnd, UINT msg, WPARAM wp, LPARAM lp);
LRESULT CALLBACK DialogAboutProcedure(HWND hWnd, UINT msg, WPARAM wp, LPARAM lp);

// Variables
string globalPathWindow = "";
string globalPath = "";
HWND globalStatus;

// Creating Menu Bars
void AddMenu(HWND hWnd, HMENU hMenu, HMENU hViewMenu) {

  // Menus
  hMenu = CreateMenu();
  HMENU hFileMenu = CreateMenu();
  HMENU hEditionMenu = CreateMenu();
  HMENU hFormatMenu = CreateMenu();
  hViewMenu = CreateMenu();
  HMENU hHelpMenu = CreateMenu();

  // Appending Menu Content

  // File
  AppendMenu(hMenu, MF_POPUP, (UINT_PTR)hFileMenu, "File");
  AppendMenu(hFileMenu, MF_STRING | MF_ENABLED, FILE_MENU_NEW, "&New\tCtrl+N");
  AppendMenu(hFileMenu, MF_STRING | MF_ENABLED, FILE_MENU_NEWINDOW, "&New Window\tCtrl+May+N");
  AppendMenu(hFileMenu, MF_STRING | MF_ENABLED, FILE_MENU_OPEN, "&Open\tCtrl+A");
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
  AppendMenu(hViewMenu, MF_STRING | MF_BYCOMMAND | MF_CHECKED, VIEW_STATUS, "Status Bar"); // FIX TODO

  // Help
  AppendMenu(hMenu, MF_POPUP, (UINT_PTR)hHelpMenu, "Help");
  AppendMenu(hHelpMenu, MF_STRING, HELP_VIEW, "View Help");
  AppendMenu(hHelpMenu, MF_STRING, HELP_SUGGESTION, "Send Suggestion");
  AppendMenu(hHelpMenu, MF_SEPARATOR,NULL,NULL);
  AppendMenu(hHelpMenu, MF_STRING, HELP_ABOUT, "About Notepad-Clone");

  SetMenu(hWnd,hMenu);
}

// Status Bar
HWND CreateStatusBar(HWND hWnd, int idStatus, HINSTANCE hinst, int cParts, int height) {
    HWND hStatusBar;
    RECT rcClient;
    HLOCAL hloc;
    PINT paParts;
    int i, nWidth;

    // Creation
    hStatusBar = CreateWindowEx(0, STATUSCLASSNAME, NULL, WS_CHILD | WS_VISIBLE, 17, 17, 0, 0, hWnd, (HMENU) idStatus, hinst, NULL);
    // Get the coordinates of the parent window's client area.
    GetClientRect(hWnd, &rcClient);
    // Allocate an array for holding the right edge coordinates.
    hloc = LocalAlloc(LHND, sizeof(int) * cParts);
    paParts = (PINT) LocalLock(hloc);
    // Calculate the right edge coordinate for each part, and copy the coordinates to the array.
    nWidth = rcClient.right / cParts;
    int rightEdge = nWidth;
    for (i = 0; i < cParts; i++) {
       paParts[i] = rightEdge;
       rightEdge += nWidth;
    }
    // Tell the status bar to create the window parts.
    SendMessage(hStatusBar, SB_SETPARTS, (WPARAM) cParts, (LPARAM) paParts);
    // Set Text
    SendMessage(hStatusBar, SB_SETTEXT, SBT_NOBORDERS | 2, (LPARAM)"Windows");
    //SendMessage(hStatusBar, SB_SETBKCOLOR , 0, (LPARAM)RGB(219,227,250)); To set Color
    globalStatus = hStatusBar;
    // Free the array, and return.
    LocalUnlock(hloc);
    LocalFree(hloc);
    return hStatusBar;
}

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

// About Dialog Box
void ClassDialogAbout(HINSTANCE mainWindow) {

  WNDCLASSW aboutClass = {0};
  aboutClass.hbrBackground = (HBRUSH)COLOR_WINDOW;
  aboutClass.hCursor = LoadCursor(NULL, IDC_ARROW);
  aboutClass.hInstance = mainWindow;
  aboutClass.lpszClassName = L"aboutDialog";
  aboutClass.lpfnWndProc = DialogAboutProcedure;

  RegisterClassW(&aboutClass);

}

struct FontsStruct {
    TCHAR fontName[64];
};

FontsStruct fontList[] =
{
    {TEXT("Consolas")},
    {TEXT("Courier")},
    {TEXT("Verdana")}
};

struct StyleStruct {
    TCHAR fontStyle[64];
};

StyleStruct styleList[] =
{
    {TEXT("Normal")},
    {TEXT("Cursive")},
    {TEXT("Bold")},
    {TEXT("Italic")}
};

struct SizesStruct {
    TCHAR fontSize[64];
};

SizesStruct sizesList[] =
{
    {TEXT("8")},
    {TEXT("10")},
    {TEXT("12")}
};

// About Dialog
void CreateDialogAbout(HWND hWnd, int screenWidth, int screenHeight, HBITMAP bWindowsImage, HBITMAP bNotepadImage, HWND hWindowsImage, HWND hNotepadImage) {
  bWindowsImage = (HBITMAP)LoadImageW(NULL, L"windows.bmp", IMAGE_BITMAP, 200, 60, LR_LOADFROMFILE);
  bNotepadImage = (HBITMAP)LoadImageW(NULL, L"notepad.bmp", IMAGE_BITMAP, 40, 40, LR_LOADFROMFILE);

  HWND haboutDialog = CreateWindowW(L"aboutDialog", L"", WS_VISIBLE | WS_OVERLAPPED | WS_SYSMENU, (screenWidth-500)/2, (screenHeight-500)/2, 500, 300, hWnd, NULL, NULL, NULL);

  hWindowsImage = CreateWindowW(L"static", NULL, WS_VISIBLE | WS_CHILD | SS_BITMAP, 150, 10, 200, 60, haboutDialog, NULL, NULL, NULL);
  SendMessageW(hWindowsImage, STM_SETIMAGE, IMAGE_BITMAP, (LPARAM) bWindowsImage);
  hNotepadImage = CreateWindowW(L"static", NULL, WS_VISIBLE | WS_CHILD | SS_BITMAP, 20, 80, 50, 50, haboutDialog, NULL, NULL, NULL);
  SendMessageW(hNotepadImage, STM_SETIMAGE, IMAGE_BITMAP, (LPARAM) bNotepadImage);
  CreateWindowW(L"static", L"Microsoft Windows 2022 (R)\nNotepad Clone by Toni Valverde\ntovape.github.io", WS_VISIBLE | WS_CHILD, 100, 80, 380, 100, haboutDialog, NULL, NULL, NULL);

  CreateWindowW(L"Button", L"Accept", WS_VISIBLE | WS_CHILD | SS_CENTER | BS_DEFPUSHBUTTON | BS_FLAT, 410, 236, 80, 30, haboutDialog, (HMENU)HELP_ABOUT_ACCEPT, NULL, NULL);

  EnableWindow(hWnd, false);
}

// Font Dialog
void CreateDialogFont(HWND hWnd, int screenWidth, int screenHeight, HFONT hSecundaryFont, HWND hFontList, HWND hFontStyle, HWND hFontSize) {

  HWND hfontDialog = CreateWindowW(L"fontDialog", L"", WS_VISIBLE | WS_OVERLAPPED | WS_SYSMENU, (screenWidth-500)/2, (screenHeight-500)/2, 400, 500, hWnd, NULL, NULL, NULL);
  SetWindowLong(hfontDialog, GWL_STYLE,GetWindowLong(hfontDialog, GWL_STYLE) & ~WS_MINIMIZEBOX & ~WS_MAXIMIZEBOX);

  // Adding Content
  CreateWindowW(L"static", L"Font:", WS_VISIBLE | WS_CHILD, 10, 10, 160, 20, hfontDialog, NULL, NULL, NULL);
  CreateWindowW(L"edit", L"", WS_VISIBLE | WS_CHILD | WS_BORDER, 10, 34, 160, 20, hfontDialog, NULL, NULL, NULL);
  hFontList = CreateWindowW(L"listbox", NULL, WS_VISIBLE | WS_CHILD | WS_VSCROLL | ES_AUTOVSCROLL | LBS_STANDARD | LBS_NOTIFY, 10, 64, 160, 100, hfontDialog, (HMENU)FORMAT_FONT_LIST, NULL, NULL);

  CreateWindowW(L"static", L"Style:", WS_VISIBLE | WS_CHILD, 180, 10, 120, 20, hfontDialog, NULL, NULL, NULL);
  CreateWindowW(L"edit", L"", WS_VISIBLE | WS_CHILD | WS_BORDER, 180, 34, 120, 20, hfontDialog, NULL, NULL, NULL);
  hFontStyle = CreateWindowW(L"listbox", NULL, WS_VISIBLE | WS_CHILD | WS_VSCROLL | ES_AUTOVSCROLL | LBS_STANDARD | LBS_NOTIFY, 180, 64, 120, 100, hfontDialog, (HMENU)FORMAT_FONT_STYLE, NULL, NULL);

  CreateWindowW(L"static", L"Size:", WS_VISIBLE | WS_CHILD, 310, 10, 70, 20, hfontDialog, NULL, NULL, NULL);
  CreateWindowW(L"edit", L"", WS_VISIBLE | WS_CHILD | WS_BORDER, 310, 34, 70, 20, hfontDialog, NULL, NULL, NULL);
  hFontSize = CreateWindowW(L"listbox", NULL, WS_VISIBLE | WS_CHILD | WS_VSCROLL | ES_AUTOVSCROLL | LBS_STANDARD | LBS_NOTIFY, 310, 64, 70, 100, hfontDialog, (HMENU)FORMAT_FONT_SIZE, NULL, NULL);

  CreateWindowW(L"Button", L"Accept", WS_VISIBLE | WS_CHILD | SS_CENTER | BS_DEFPUSHBUTTON | BS_FLAT, 210, 430, 80, 30, hfontDialog, (HMENU)FORMAT_FONT_APPLY, NULL, NULL);
  CreateWindowW(L"Button", L"Cancel", WS_VISIBLE | WS_CHILD | SS_CENTER | BS_FLAT, 300, 430, 80, 30, hfontDialog, (HMENU)FORMAT_FONT_CANCEL, NULL, NULL);

  // Adding Items in the Font List
  int fontListArray = sizeof(fontList)/sizeof(fontList[0]);
  cout << fontListArray << " Fonts Added\n";
  for (int i = 0; i < fontListArray; i++) {
    int pos = (int)SendMessage(hFontList, LB_ADDSTRING, 0, (LPARAM) fontList[i].fontName);
    SendMessage(hFontList, LB_SETITEMDATA, pos, (LPARAM) i);
  }

  // Adding Items in the Style List
  int fontStyleArray = sizeof(fontList)/sizeof(styleList[0]);
  cout << fontStyleArray << " Styles Added\n";
  for (int i = 0; i < fontStyleArray; i++) {
    int pos = (int)SendMessage(hFontStyle, LB_ADDSTRING, 0, (LPARAM) styleList[i].fontStyle);
    SendMessage(hFontStyle, LB_SETITEMDATA, pos, (LPARAM) i);
  }

  // Adding Items in the Size List
  int fontSizeArray = sizeof(fontList)/sizeof(sizesList[0]);
  cout << fontSizeArray << " Sizes Added\n";
  for (int i = 0; i < fontSizeArray; i++) {
    int pos = (int)SendMessage(hFontSize, LB_ADDSTRING, 0, (LPARAM) sizesList[i].fontSize);
    SendMessage(hFontSize, LB_SETITEMDATA, pos, (LPARAM) i);
  }

  SetFocus(hFontList);
  SetFocus(hFontStyle);
  SetFocus(hFontSize);

  //CreateWindowW(L"combobox", L"Dropdown?", WS_VISIBLE | WS_CHILD, 20, 20, 198, 20, hfontDialog, NULL, NULL, NULL);

  // Setting Font
  //SendMessage(hApplyFont, WM_SETFONT, (WPARAM)hSecundaryFont, TRUE);

  EnableWindow(hWnd, false);
}

// Display File
void DisplayFile(char* path, HWND hEditor) {
  FILE *file;
  file = fopen(path,"r");
  fseek(file,0,SEEK_END);
  int filesize = ftell(file);
  rewind(file);
  char *data = new char[filesize+1];
  fread(data,filesize,1,file);
  data[filesize] = '\0';

  SetWindowText(hEditor,data);

  fclose(file);
}

// Open File
void OpenFile(HWND hWnd, HWND hEditor) {
  cout << "Open File\n";

  char filename[100];
  filename[0] = 0;

  OPENFILENAME ofn;
  ZeroMemory(&ofn,sizeof(OPENFILENAME));
  ofn.lStructSize = sizeof(OPENFILENAME);
  ofn.hwndOwner = hWnd;
  ofn.lpstrFile = filename;
  ofn.lpstrFile[0] = '\0';
  ofn.nMaxFile = 100;
  // This will filter the files in the explorer (Open extensions)
  ofn.lpstrFilter = "All Files\0*.*\0Text Files\0*.txt\0";
  ofn.nFilterIndex = 1;

  GetOpenFileName(&ofn);

  // In case User closes window
  if (filename[0] != 0) {
    // Path of the file
    cout << ofn.lpstrFile << "\n";
    globalPath = ofn.lpstrFile;
    globalPathWindow = ofn.lpstrFile;

    // Set Status
    char statusChar[1024];
    string statusString = globalPathWindow.substr(globalPathWindow.length() - 3) + " - File";
    strcpy(statusChar, statusString.c_str());
    SendMessageW(globalStatus, SB_SETTEXT, SBT_NOBORDERS | 3, (LPARAM) TEXT(statusChar));

    // Setting New Window Name
    globalPathWindow = "Notepad - " + globalPathWindow;

    wstring globalPathWide = wstring(globalPathWindow.begin(), globalPathWindow.end());
    const wchar_t* globalPathTide = globalPathWide.c_str();

    SetWindowTextW(hWnd, TEXT(globalPathTide));

    DisplayFile(ofn.lpstrFile, hEditor);
  } else {
    cout << "Window Closed\n";
  }

}

// Write File
void WriteFile(char* path, HWND hEditor) {
  FILE *file;
  file = fopen(path,"w");

  int filesize = GetWindowTextLength(hEditor);
  char *data = new char[filesize+1];
  GetWindowText(hEditor,data,filesize+1);

  fwrite(data,filesize+1,1,file);
  fclose(file);
}

// Save As File
void SaveAsFile(HWND hWnd, HWND hEditor) {
  cout << "Saving File\n";

  char filename[100];

  OPENFILENAME ofn;
  ZeroMemory(&ofn,sizeof(OPENFILENAME));

  ofn.lStructSize = sizeof(OPENFILENAME);
  ofn.hwndOwner = hWnd;
  ofn.lpstrFile = filename;
  ofn.lpstrFile[0] = '\0';
  ofn.nMaxFile = 100;
  // This will filter the files in the explorer (Open extensions)
  ofn.lpstrFilter = "All Files\0*.*\0Text Files\0*.txt\0";
  ofn.nFilterIndex = 1;

  GetSaveFileName(&ofn);

  // Path of the file
  cout << ofn.lpstrFile << "\n";

  WriteFile(ofn.lpstrFile, hEditor);
}

// Save File
void SaveFile(HWND hWnd, HWND hEditor) {
  OPENFILENAME ofn;

  int globalPathSize = globalPath.length();
  char filename[globalPathSize + 1];
  strcpy(filename, globalPath.c_str());
  ofn.lpstrFile = filename;
  ofn.hwndOwner = hWnd;
  cout << ofn.lpstrFile << "\n";

  if (globalPathSize == 0) {
    SaveAsFile(hWnd, hEditor);
  } else {
    WriteFile(ofn.lpstrFile, hEditor);
  }

}

// New
void NewFile(HWND hWnd) {
  globalPathWindow = "";
  globalPath = "";
  // Setting New Window Name
  globalPathWindow = "Notepad";
  wstring globalPathWide = wstring(globalPathWindow.begin(), globalPathWindow.end());
  const wchar_t* globalPathTide = globalPathWide.c_str();

  SetWindowTextW(hWnd, TEXT(globalPathTide));
}

// New Window
void NewWindow(HWND hWnd, int screenWidth, int screenHeight) {
  CreateWindowW(L"mainWindow", L"Null", WS_OVERLAPPEDWINDOW | WS_VISIBLE,(screenWidth-500)/2,(screenHeight-500)/2,700,500,NULL,NULL,NULL,NULL);
}

// Timestamp
void Timestamp(HWND hWnd, HWND hEditor) {

  // Get Time format HH:MM DD/MM/YYYY
  time_t t = time(0);
  tm* now = localtime(&t);
  string timestamp = to_string(now->tm_hour) + ":" + to_string(now->tm_min) + " " + to_string(now->tm_mday) + "/" + to_string(now->tm_mon + 1) + "/" + to_string(now->tm_year + 1900);

  cout << timestamp << "\n";

  int index = GetWindowTextLength(hEditor);
  SetFocus(hEditor);
  SendMessageA(hEditor, EM_SETSEL, (WPARAM)index, (LPARAM)index);
  SendMessageA(hEditor, EM_REPLACESEL, 0, (LPARAM)timestamp.c_str());
}

// Register Hotkeys - https://docs.microsoft.com/es-es/windows/win32/inputdev/virtual-key-codes
void RegisterHotkey(HWND hWnd) {
  RegisterHotKey(hWnd, MACRO_MENU_NEW, MOD_CONTROL, 0x4E);
  RegisterHotKey(hWnd, MACRO_MENU_NEWINDOW, MOD_CONTROL | MOD_SHIFT, 0x4E);
  RegisterHotKey(hWnd, MACRO_MENU_OPEN, MOD_CONTROL, 0x41);
  RegisterHotKey(hWnd, MACRO_MENU_SAVE, MOD_CONTROL, 0x47);
  RegisterHotKey(hWnd, MACRO_MENU_SAVEAS, MOD_CONTROL | MOD_SHIFT, 0x53);
}

// Search with bing
void SearchBing(HWND hWnd, HWND hEditor, unsigned int selStart, unsigned int selEnd) {

  int selectBuf = selEnd - selStart + 1;
  int selectSize = GetWindowTextLength(hEditor);
  char data[selectSize+1];
  GetWindowTextA(hEditor, data, selectSize+1);
  string selectText;

  for(int i = selStart; i < selEnd; i++) {
    selectText.push_back(data[i]);
  }

  cout << "Selecting Text from " << selStart << " to " << selEnd << "\n";

  if (selStart != 0 && selEnd != 0) {
    string openWebpage = string("start ").append("https://www.google.com/search?q=" + selectText);
    system(openWebpage.c_str());
  }

}

// View Help
void SearchHelp() {
  string openWebpage = string("start ").append("https://support.microsoft.com/en-us/windows/help-in-notepad-4d68c388-2ff2-0e7f-b706-35fb2ab88a8c");
  system(openWebpage.c_str());
}

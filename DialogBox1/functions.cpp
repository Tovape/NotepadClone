#include <iostream>
#include <windows.h>
#include <stdio.h>
#include <String>
#include <tchar.h>

#ifndef NOMINMAX
#define NOMINMAX
#endif

// Box 1

string box1() {

  /* Icons

  MB_ICONHAND
  MB_ICONSTOP
  MB_ICONERROR
  MB_ICONQUESTION
  MB_ICONEXCLAMATION
  MB_ICONWARNING
  MB_ICONASTERISK
  MB_ICONINFORMATION

  */

  /* Functionality

  MB_ABORTRETRYIGNORE
  MB_CANCELTRYCONTINUE
  MB_YESNO
  MB_HELP
  MB_OK
  MB_OKCANCEL
  MB_RETRYCANCEL
  MB_YESNOCANCEL

  */

  int msgbox1ID = MessageBoxW(
    NULL,
    L"Exclamation",
    L"Dialog Box 1",
    MB_ICONINFORMATION | MB_YESNO
  );

  if (msgbox1ID == IDYES) {
    return "YES";
  } else if (msgbox1ID == IDNO) {
    return "NOT";
  } else {
    return "Null";
  }

}

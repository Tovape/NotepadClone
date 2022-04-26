#include <iostream>
#include <windows.h>
#include <stdio.h>
#include <string.h>
using namespace std;

string fontlistselected (char* bufferFontList, string fontSelected) {
  if (_tcscmp(bufferFontList, "Verdana") == 0) {
    fontSelected = "Verdana";
  } else if (_tcscmp(bufferFontList, "Impact") == 0) {
    fontSelected = "Impact";
  } else {
    cout << "Font Name Not Applied\n";
    fontSelected = "Consolas";
  }
  return fontSelected;
}

int fontweightselected (char* bufferFontStyle, int fontWeight) {
  if (_tcscmp(bufferFontStyle, "Bold") == 0) {
    fontWeight = 700;
  } else if (_tcscmp(bufferFontStyle, "Normal") == 0) {
    fontWeight = 400;
  } else {
    cout << "Font Style Not Applied\n";
    fontWeight = 400;
  }
  return fontWeight;
}

boolean fontitalicselected (char* bufferFontStyle, boolean fontItalic) {
  if (_tcscmp(bufferFontStyle, "Italic") == 0) {
    fontItalic = TRUE;
  } else if (_tcscmp(bufferFontStyle, "Italic") != 0) {
    fontItalic = FALSE;
  } else {
    cout << "Font Italic Not Applied\n";
    fontItalic = FALSE;
  }
  return fontItalic;
}

int fontsizeselected (char* bufferFontSize, int fontSize) {
  if (_tcscmp(bufferFontSize, "8") == 0) {
    fontSize = 8;
  } else if (_tcscmp(bufferFontSize, "10") == 0) {
    fontSize = 10;
  } else if (_tcscmp(bufferFontSize, "12") == 0) {
    fontSize = 12;
  } else {
    fontSize = 0;
  }
  return fontSize;
}

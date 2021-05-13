#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#ifndef BASIC_INI_FILE
#define BASIC_INI_FILE
int BIFGetPrivateProfileInt(const char * section, const char * name, int defaultValue, const char * filename);
int BIFGetPrivateProfileString(const char * section, const char * name, const char * defaultValue, char * returnedString, int nSize, const char * filename);
#endif

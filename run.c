#include "BasicIniFile.h"

#define LENGTH 1024

int main(int argc, char *argv[])
{
    printf("Sample Basic Ini File linux v0.1\n");
    int b = BIFGetPrivateProfileInt("sectionB", "keyB", -1, "iniFiles/sample0.ini");
    printf("keyB in sectionB has a value of %d\n", b);

    char currentValueStrA[LENGTH];
    int a = BIFGetPrivateProfileString("sectionB", "keyString4", "defaultValue", currentValueStrA, LENGTH, "iniFiles/sample0.ini");
    printf("keyString4 in sectionB has a value of '%s' %d chars where copied\n", currentValueStrA, a);
}

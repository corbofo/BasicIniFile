#include <windows.h>

#include "BasicIniFile.h"

#define MAX_LENGTH 1024

#define ASSERT_INT(a, b) assertInt(a, b, __LINE__)
#define ASSERT_STR(a, b, s) assertStr(a, b, s, __LINE__)

int tests = 0;
int failed = 0;

int assertInt(int a, int b, int line)
{
    tests++;
    if (a != b)
    {
        printf("Assertion failed (line %d) : %d != %d\n", line, a, b);
        failed++;
    }
}

int assertStr(const char * a, const char * b, int size, int line)
{
    tests++;
    if (strncmp(a, b, size) != 0)
    {
        printf("Assertion failed (line %d) : '%s' != '%s'\n", line, a, b);
        failed++;
    }
}

int run()
{
    int b = BIFGetPrivateProfileInt("sectionB", "keyB", -1, "iniFiles/sample0.ini");
    int b2 = GetPrivateProfileInt("sectionB", "keyB", -1, "iniFiles/sample0.ini");
    ASSERT_INT(b, b2);

    int a = BIFGetPrivateProfileInt("sectionA", "keyA", -1, "iniFiles/sample0.ini");
    int a2 = GetPrivateProfileInt("sectionA", "keyA", -1, "iniFiles/sample0.ini");
    ASSERT_INT(a, a2);

    int c = BIFGetPrivateProfileInt("sectionC", "keyC", -1, "iniFiles/sample0.ini");
    int c2 = GetPrivateProfileInt("sectionC", "keyC", -1, "iniFiles/sample0.ini");
    ASSERT_INT(c, c2);

    int d = BIFGetPrivateProfileInt("sectionC", "keyD", -2, "iniFiles/sample0.ini");
    int d2 = GetPrivateProfileInt("sectionC", "keyD", -2, "iniFiles/sample0.ini");
    ASSERT_INT(d, d2);

    char currentValueStrA[MAX_LENGTH];
    char currentValueStrA2[MAX_LENGTH];
    a = BIFGetPrivateProfileString("sectionB", "keyString", "defaultValue", currentValueStrA, MAX_LENGTH, "iniFiles/sample0.ini");
    a2 = GetPrivateProfileString("sectionB", "keyString", "defaultValue", currentValueStrA2, MAX_LENGTH, "iniFiles/sample0.ini");
    ASSERT_STR(currentValueStrA, currentValueStrA2, MAX_LENGTH);
    ASSERT_INT(a, a2);

    a = BIFGetPrivateProfileString("sectionB", "keyString2", "defaultValue", currentValueStrA, MAX_LENGTH, "iniFiles/sample0.ini");
    a2 = GetPrivateProfileString("sectionB", "keyString2", "defaultValue", currentValueStrA2, MAX_LENGTH, "iniFiles/sample0.ini");
    ASSERT_STR(currentValueStrA, currentValueStrA2, MAX_LENGTH);
    ASSERT_INT(a, a2);

    a = BIFGetPrivateProfileString("sectionB", "keyString3", "defaultValue", currentValueStrA, MAX_LENGTH, "iniFiles/sample0.ini");
    a2 = GetPrivateProfileString("sectionB", "keyString3", "defaultValue", currentValueStrA2, MAX_LENGTH, "iniFiles/sample0.ini");
    ASSERT_STR(currentValueStrA, currentValueStrA2, MAX_LENGTH);
    ASSERT_INT(a, a2);
    
    a = BIFGetPrivateProfileString("sectionB", "keyString4", "defaultValue", currentValueStrA, MAX_LENGTH, "iniFiles/sample0.ini");
    a2 = GetPrivateProfileString("sectionB", "keyString4", "defaultValue", currentValueStrA2, MAX_LENGTH, "iniFiles/sample0.ini");
    ASSERT_STR(currentValueStrA, currentValueStrA2, MAX_LENGTH);
    ASSERT_INT(a, a2);
    
    a = BIFGetPrivateProfileString("sectionB", "keyString5", "defaultValue", currentValueStrA, MAX_LENGTH, "iniFiles/sample0.ini");
    a2 = GetPrivateProfileString("sectionB", "keyString5", "defaultValue", currentValueStrA2, MAX_LENGTH, "iniFiles/sample0.ini");
    ASSERT_STR(currentValueStrA, currentValueStrA2, MAX_LENGTH);
    ASSERT_INT(a, a2);
    
    a = BIFGetPrivateProfileString("sectionB", "keyString6", "defaultValue", currentValueStrA, MAX_LENGTH, "iniFiles/sample0.ini");
    a2 = GetPrivateProfileString("sectionB", "keyString6", "defaultValue", currentValueStrA2, MAX_LENGTH, "iniFiles/sample0.ini");
    ASSERT_STR(currentValueStrA, currentValueStrA2, MAX_LENGTH);
    ASSERT_INT(a, a2);
    
    
    // The following test failed cause limitations and not good tricks at the moment see README.md Limitations
    a = BIFGetPrivateProfileString("sectionB", "keyString", "defaultValue", currentValueStrA, 3, "iniFiles/sample0.ini");
    a2 = GetPrivateProfileString("sectionB", "keyString", "defaultValue", currentValueStrA2, 3, "iniFiles/sample0.ini");
    ASSERT_STR(currentValueStrA, currentValueStrA2, MAX_LENGTH);
    ASSERT_INT(a, a2);
    // Assertion failed (line 87) : '""ringValue"' != 'st'
    // Assertion failed (line 88) : -1 != 2

    a = BIFGetPrivateProfileString("sectionB", "none", "defaultValue", currentValueStrA, 3, "iniFiles/sample0.ini");
    a2 = GetPrivateProfileString("sectionB", "none", "defaultValue", currentValueStrA2, 3, "iniFiles/sample0.ini");
    ASSERT_STR(currentValueStrA, currentValueStrA2, MAX_LENGTH);
    ASSERT_INT(a, a2);

    a = BIFGetPrivateProfileString("sectionB", "none", "defaultValue", currentValueStrA, MAX_LENGTH, "iniFiles/sample0.ini");
    a2 = GetPrivateProfileString("sectionB", "none", "defaultValue", currentValueStrA2, MAX_LENGTH, "iniFiles/sample0.ini");
    ASSERT_STR(currentValueStrA, currentValueStrA2, MAX_LENGTH);
    ASSERT_INT(a, a2);

    a = BIFGetPrivateProfileString("sectionB", "none", "defaultValue", currentValueStrA, 3, "iniFiles/nofile.ini");
    a2 = GetPrivateProfileString("sectionB", "none", "defaultValue", currentValueStrA2, 3, "iniFiles/nofile.ini");
    ASSERT_STR(currentValueStrA, currentValueStrA2, MAX_LENGTH);
    ASSERT_INT(a, a2);

    a = BIFGetPrivateProfileString("sectionB", "none", "defaultValue", currentValueStrA, MAX_LENGTH, "iniFiles/nofile.ini");
    a2 = GetPrivateProfileString("sectionB", "none", "defaultValue", currentValueStrA2, MAX_LENGTH, "iniFiles/nofile.ini");
    ASSERT_STR(currentValueStrA, currentValueStrA2, MAX_LENGTH);
    ASSERT_INT(a, a2);

}


int WINAPI WinMain(HINSTANCE hInstance,	HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow){
    printf("test BasicIniFile v0.1 (Windows)\n");
    printf("next\n");

    run();

    if(failed == 0) {
        printf("%d Tests succeeded\n", tests);
    } else {
        printf("%d / %d Tests FAILED\n", failed, tests);
    }
    return 0;
}



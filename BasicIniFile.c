#include "BasicIniFile.h"
#define MAX_LENGTH 256

enum INI_STATE{
    NONE,
    SECTION,
    NAME,
    VALUE,
    COMMENT
};

int BIFGetPrivateProfileInt(const char * section, const char * name, int defaultValue, const char * filename) {
    char currentValueStr[MAX_LENGTH];
    char defaultValueStr[MAX_LENGTH];
    snprintf(defaultValueStr, MAX_LENGTH, "%d", defaultValue);
    BIFGetPrivateProfileString(section, name, defaultValueStr, currentValueStr, MAX_LENGTH, filename);
    return atoi(currentValueStr);
}

int BIFGetPrivateProfileString(const char * section, const char * name, const char * defaultValue, char * returnedString, int nSize, const char * filename) {
    char currentSection[MAX_LENGTH];
    char currentName[MAX_LENGTH];
    FILE *fp = NULL;
    fp = fopen(filename, "rb");
    if (!fp) {
        perror("error");
        fprintf (stderr, "error: couldn't open \"%s\"!\n", filename);
        strncpy(returnedString, defaultValue, nSize);
        returnedString[nSize - 1] = '\0';
        return strnlen(returnedString, nSize - 1);
    }
    enum INI_STATE state = NONE;
    enum INI_STATE newState = NONE;

    int valueStartWithDoubleQuote = 0;
    int valueEndWithDoubleQuote = 0;
    char currentChar;
    int position = 0;
    while(!feof(fp)){
        size_t readed = fread(&currentChar, 1, 1, fp);
        if (readed == 1) {
            switch (currentChar)
            {
            case '[':
                if (state == NONE) {
                    newState = SECTION;
                }
                break;
            case ']':
                if (state == SECTION) {
                    newState = NONE;
                }
                break;
            case ';':
                newState = COMMENT;
                break;
            case '\r':
            case '\n':
                newState = NONE;
                break;
            case '=':
                if (state == NAME) {
                    newState = VALUE;
                }
                break;
            default:
                switch (state)
                {
                case SECTION:
                    currentSection[position++] = currentChar;
                    break;
                case NAME:
                    currentName[position++] = currentChar;
                    break;
                case VALUE:
                    if (position == 0 && currentChar == '"') {
                        valueStartWithDoubleQuote = 1;
                    }
                    returnedString[position++] = currentChar;
                    break;
                case NONE:
                    position = 0;
                    state = NAME;
                    newState = NAME;
                    currentName[position++] = currentChar;
                    break;

                default:
                    break;
                }
                switch (state)
                {
                case VALUE:
                    if (position > nSize - 2) {
                        position = nSize - 2;
                    }
                    break;
                
                default:
                    if (position > MAX_LENGTH - 2) {
                        position = MAX_LENGTH - 2;
                    }
                    break;
                }
                break;
            }
        }
        if (newState != state) {
            switch (state)
            {
            case SECTION:
                currentSection[position++] = '\0';
                break;
            case NAME:
                currentName[position++] = '\0';
                break;
            case VALUE:
                if (position > 0 && returnedString[position - 1] == '"') {
                    valueEndWithDoubleQuote = 1;
                    if (valueStartWithDoubleQuote != 0) {
                        position--;
                        for (int copy = 0; copy < position - 1; copy++)
                        {
                            returnedString[copy] = returnedString[copy + 1];
                        }
                        position--;
                    }
                }
                returnedString[position++] = '\0';

                if(strncmp(currentSection, section, MAX_LENGTH) == 0) {
                    if(strncmp(currentName, name, MAX_LENGTH) == 0) {
                        fclose(fp);
                        return position - 1;
                    }
                }

                break;
            default:
                break;
            }
            position = 0;
            valueStartWithDoubleQuote = 0;
            valueEndWithDoubleQuote = 0;

            state = newState;
        }
    }
    fclose(fp);
    strncpy(returnedString, defaultValue, nSize);
    returnedString[nSize - 1] = '\0';
    return strnlen(returnedString, nSize - 1);
}

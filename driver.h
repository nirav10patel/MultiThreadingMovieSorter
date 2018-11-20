#ifndef driver_h
#define driver_h


typedef struct Collection
{
    Row *group;
    char *header;
}Collection;

typedef struct Row
{
    char *modRow;
    char *value;
    char *ogRow;
}Row;

char *delWhiteSpace(char* input);
int sortFile(char* inFile, char* inFileName, char *name, char *endDir, int hasEnd);
int isColValid(char* inCol);
int isValidCSV(char* headerRow);
int findNum(char* inCol);
int getRows(char* inFile);
#endif

#ifndef scannerCSVsorter_h
#define scannerCSVsorter_h

typedef struct Row
{
    char *row;
    char *OGrow;
    char *value;
    int inum;
    float fnum;
    int isEmpty;
}Row;

char *delWhiteSpace(char* input);
int sortFile(char* inFile, char* inFileName, char *name, char *endDir, int hasEnd);
int isColValid(char* inCol);
int isValidCSV(char* headerRow);
int checkifDirorFile(char* dir);
int checkDir(char* dir);
char* checkPath(char* destination, char* workFile);
char* changeOutFileName(char* workFile, char* colName);
int ScannerDriver(char* path, char* name, char* endDir, int hasEnd, char* input);
char* getparentPath(char* inFile, char* inFileName);
#endif

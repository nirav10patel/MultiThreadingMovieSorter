#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <dirent.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include "scannerCSVsorter.h"
#include "mergesort.c"

int procCount = 1;

char *delWhiteSpace(char* input){
        char *trail;
        while( isspace((unsigned char)*input) )
        {
                input++;
        }
        if(*input == 0)
        {
                return input;
        }

        trail = input + strlen(input) - 1;
        while(trail > input && isspace((unsigned char)*trail) )
        {
                trail--;
        }
        trail[1] = '\0';
        return input;
}

int isColValid(char* inCol){
    if( strcmp(inCol, "color") == 0){                             return 1;
    }else if( strcmp(inCol, "director_name") == 0){               return 1;
    }else if( strcmp(inCol, "num_critic_for_reviews") == 0){      return 1;
    }else if( strcmp(inCol, "duration") == 0){                    return 1;
    }else if( strcmp(inCol, "director_facebook_likes") == 0){     return 1;
    }else if( strcmp(inCol, "actor_3_facebook_likes") == 0){      return 1;
    }else if( strcmp(inCol, "actor_2_name") == 0){                return 1;
    }else if( strcmp(inCol, "actor_1_facebook_likes") == 0){      return 1;
    }else if( strcmp(inCol, "gross") == 0){                       return 1;
    }else if( strcmp(inCol, "genres") == 0){                      return 1;
    }else if( strcmp(inCol, "actor_1_name") == 0){                return 1;
    }else if( strcmp(inCol, "movie_title") == 0){                 return 1;
    }else if( strcmp(inCol, "num_voted_users") == 0){             return 1;
    }else if( strcmp(inCol, "cast_total_facebook_likes") == 0){   return 1;
    }else if( strcmp(inCol, "actor_3_name") == 0){                return 1;
    }else if( strcmp(inCol, "facenumber_in_poster") == 0){        return 1;
    }else if( strcmp(inCol, "plot_keywords") == 0){               return 1;
    }else if( strcmp(inCol, "movie_imdb_link") == 0){             return 1;
    }else if( strcmp(inCol, "num_user_for_reviews") == 0){        return 1;
    }else if( strcmp(inCol, "language") == 0){                    return 1;
    }else if( strcmp(inCol, "country") == 0){                     return 1;
    }else if( strcmp(inCol, "content_rating") == 0){              return 1;
    }else if( strcmp(inCol, "budget") == 0){                      return 1;
    }else if( strcmp(inCol, "title_year") == 0){                  return 1;
    }else if( strcmp(inCol, "actor_2_facebook_likes") == 0){      return 1;
    }else if( strcmp(inCol, "imdb_score") == 0){                  return 1;
    }else if( strcmp(inCol, "aspect_ratio") == 0){                return 1;
    }else if( strcmp(inCol, "movie_facebook_likes") == 0){        return 1;
    }else{
      return 0;
    }
}

int isValidCSV(char* headerRow){
    char *colToken = strtok(headerRow, ",");
    int colCounter = 0;
    int found = 0;

    while(colToken != NULL)
    {
        colCounter++;
        colToken = delWhiteSpace(colToken);
        found = isColValid(colToken);
        if(found == 0){
            return -1;
        }
        colToken = strtok(NULL, ",");
    }
    return 1;
}

int findNum(char* inCol){
    if( strcmp(inCol, "color") == 0){                             return 0;
    }else if( strcmp(inCol, "director_name") == 0){               return 1;
    }else if( strcmp(inCol, "num_critic_for_reviews") == 0){      return 2;
    }else if( strcmp(inCol, "duration") == 0){                    return 3;
    }else if( strcmp(inCol, "director_facebook_likes") == 0){     return 4;
    }else if( strcmp(inCol, "actor_3_facebook_likes") == 0){      return 5;
    }else if( strcmp(inCol, "actor_2_name") == 0){                return 6;
    }else if( strcmp(inCol, "actor_1_facebook_likes") == 0){      return 7;
    }else if( strcmp(inCol, "gross") == 0){                       return 8;
    }else if( strcmp(inCol, "genres") == 0){                      return 9;
    }else if( strcmp(inCol, "actor_1_name") == 0){                return 10;
    }else if( strcmp(inCol, "movie_title") == 0){                 return 11;
    }else if( strcmp(inCol, "num_voted_users") == 0){             return 12;
    }else if( strcmp(inCol, "cast_total_facebook_likes") == 0){   return 13;
    }else if( strcmp(inCol, "actor_3_name") == 0){                return 14;
    }else if( strcmp(inCol, "facenumber_in_poster") == 0){        return 15;
    }else if( strcmp(inCol, "plot_keywords") == 0){               return 16;
    }else if( strcmp(inCol, "movie_imdb_link") == 0){             return 17;
    }else if( strcmp(inCol, "num_user_for_reviews") == 0){        return 18;
    }else if( strcmp(inCol, "language") == 0){                    return 19;
    }else if( strcmp(inCol, "country") == 0){                     return 20;
    }else if( strcmp(inCol, "content_rating") == 0){              return 21;
    }else if( strcmp(inCol, "budget") == 0){                      return 22;
    }else if( strcmp(inCol, "title_year") == 0){                  return 23;
    }else if( strcmp(inCol, "actor_2_facebook_likes") == 0){      return 24;
    }else if( strcmp(inCol, "imdb_score") == 0){                  return 25;
    }else if( strcmp(inCol, "aspect_ratio") == 0){                return 26;
    }else if( strcmp(inCol, "movie_facebook_likes") == 0){        return 27;
    }else{
      return 0;
    }
}


int main(int argc, char **argv)
{
    if( (argc != 3) && (argc != 5) && (argc != 7)){
        fprintf(stderr, "You have entered the incorrect number of arguments. The correct format is one of the following:\n");
        fprintf(stderr, "For no specifications: ./scannerCSVsorter -c someSortingItem\n");
        fprintf(stderr, "For input directory specification: ./scannerCSVsorter -c someSortingItem -d inDirectoryPath\n");
        fprintf(stderr, "For input directory specification: ./scannerCSVsorter -c someSortingItem -d inDirectoryPath -o outDirectoryPath\n");
        return -1;
    }

    int hasName = 0;
    int hasStart = 0;
    int hasEnd = 0;
    int nameAt = 0;
    int startAt = 0;
    int endAt = 0;


    if(argc == 3){
        if(strcmp(argv[1], "-c")){
            fprintf(stderr, "You must enter the -c flag and the column name\n");
            return -1;
        }
        nameAt = 2;
        hasName = 1;
    }

    if(argc == 5){
        if(!strcmp(argv[1],"-c")){
            hasName = 1;
            nameAt = 2;
        }
        if(!strcmp(argv[3],"-c")){
            if(hasName)
            {
                fprintf(stderr, "TOO MANY C FLAGS\n");
                return -1;
            }
            hasName = 1;
            nameAt = 4;
        }
        if(!strcmp(argv[1],"-d")){
            hasStart = 1;
            startAt = 2;
        }
        if(!strcmp(argv[3],"-d")){
            if(hasStart)
            {
                fprintf(stderr, "TOO MANY D FLAGS\n");
                return -1;
            }
            hasStart = 1;
            startAt = 4;
        }
        if(!strcmp(argv[1],"-o")){
            hasEnd = 1;
            endAt = 2;
        }
        if(!strcmp(argv[3],"-o")){
            if(hasEnd)
            {
                fprintf(stderr, "TOO MANY O FLAGS\n");
                return -1;
            }
            hasEnd = 1;
            endAt = 4;
        }
    }

    if(argc == 7){
        if(!strcmp(argv[1],"-c")){
            hasName = 1;
            nameAt = 2;
        }
        if(!strcmp(argv[3],"-c")){
            if(hasName)
            {
                fprintf(stderr, "TOO MANY C FLAGS\n");
                return -1;
            }
            hasName = 1;
            nameAt = 4;
        }
        if(!strcmp(argv[5],"-c")){
            if(hasName)
            {
                fprintf(stderr, "TOO MANY C FLAGS\n");
                return -1;
            }
            hasName = 1;
            nameAt = 6;
        }

        if(!strcmp(argv[1],"-d")){
            hasStart = 1;
            startAt = 2;
        }
        if(!strcmp(argv[3],"-d")){
            if(hasStart)
            {
                fprintf(stderr, "TOO MANY D FLAGS\n");
                return -1;
            }
            hasStart = 1;
            startAt = 4;
        }
        if(!strcmp(argv[5],"-d")){
            if(hasStart)
            {
                fprintf(stderr, "TOO MANY D FLAGS\n");
                return -1;
            }
            hasStart = 1;
            startAt = 6;
        }

        if(!strcmp(argv[1],"-o")){
            hasEnd = 1;
            endAt = 2;
        }
        if(!strcmp(argv[3],"-o")){
            if(hasEnd)
            {
                fprintf(stderr, "TOO MANY O FLAGS\n");
                return -1;
            }
            hasEnd = 1;
            endAt = 4;
        }
        if(!strcmp(argv[5],"-o")){
            if(hasEnd)
            {
                fprintf(stderr, "TOO MANY O FLAGS\n");
                return -1;
            }
            hasEnd = 1;
            endAt = 6;
        }
    }

    char *name = (argv[nameAt]);
    int i;
    for(i = 0; name[i]; i++){
        name[i] = tolower(name[i]);
    }
    int isColAns = isColValid(name);
    if(isColAns == 0){
        fprintf(stderr, "The sorting-by column you entered is not a valid one for a movie_metadata file\n");
        return -1;
    }
    //Checks if input col name exists

    char *startDir = malloc(100*sizeof(char));
    startDir[0] = '\0';
    if (hasStart){
        startDir = strcat(startDir, argv[startAt]);
        //Check if directory actually exists;
        int checkStatus = checkDir(startDir);
        if (checkStatus)
        {
            //chdir(startDir);
        }
        else
        {
            fprintf(stderr, "The given start directory does not exist\n");
            return -1;
        }}
    else{
      startDir = strcat(startDir, "./");
    }
    //Checks if start dir exists

    char *endDir = malloc(100*sizeof(char));
    endDir[0] = '\0';
    if(hasEnd){
        endDir = strcat(endDir, argv[endAt]);
        if(!checkDir(endDir))
        {
            fprintf(stderr, "The given output directory does not exist\n");
            return -1;
        }
    }
    //Checks if end dir exists

    char *inputFile = malloc(1000*sizeof(char));
    inputFile[0] = '\0';
    pid_t firstPID = getpid();
    printf("Initial PID: %d\n", firstPID);
    printf("PIDS of all child processes: ");
    fflush(stdout);
    int ans = ScannerDriver(startDir, name, endDir, hasEnd, inputFile);
    //Runs the main file

    if(firstPID == getpid())
    {
      printf("\nTotal number of processes: %d\n", procCount);
    }

    free(inputFile);
    free(endDir);
    free(startDir);

    if(ans == 0)
    {
        return -1;    //Failue
    }
    else
    {
	    return 0;    //Success
    }
}

int sortFile(char* inFile, char* inFileName, char *name, char *endDir, int hasEnd){
    int i = 0;
    char *str = malloc(1000*sizeof(char));
    char **list = malloc(100000*sizeof(char*));
    int counter = 0;
	FILE *fp = fopen(inFile, "r");

	if(!fp){
		fprintf(stderr, "File could not be opened\n");
		return -1;
	}

	size_t strSize;
    while ( (getline(&str, &strSize, fp)) != -1)
    {
        list[counter] = (malloc(1000*sizeof(char)));
        strcpy(list[counter],str);
        counter++;
    }
    //THE ABOVE IS THAT BIG BOI INITIALIZER

    if (counter == 0)
    {
        return -1;
    }

    char *colNames = malloc(1000*sizeof(char));
    strcpy(colNames,list[0]);

    colNames = delWhiteSpace(colNames);

    char *token = strtok(colNames, ",");
    int iterator = 0;
    int found = 0;

    while(token != NULL)
    {
        if ((strcmp(token,name)) == 0)
        {
            found = 1;
            break;
        }
        token = strtok(NULL, ",");
        iterator++;
    }

    if (found == 0)
    {
        fprintf(stderr,"Error column not found\n");
        return -1;
    }

    strcpy(colNames, list[0]);
    colNames = delWhiteSpace(colNames);

    char *colCounterToken = strtok(colNames, ",");
    int numColumns = 0;
    while(colCounterToken != NULL)
    {
        numColumns++;
        colCounterToken = strtok(NULL, ",");
    }
    //Gets num of columns in numColumns

    strcpy(colNames, list[0]);
    colNames = delWhiteSpace(colNames);

    char *sequenceToken = strtok(colNames, ",");
    int seqCounter = 0;
    int sequence[numColumns];

    while(sequenceToken != NULL)
    {
        int numInSeq = findNum(delWhiteSpace(sequenceToken));
        sequence[seqCounter] = numInSeq;
        //printf("String is: %s", sequenceToken);
        //printf("    Number is: %d\n", numInSeq);
        seqCounter++;
        sequenceToken = strtok(NULL, ",");
    }
    //Gets sequence of header

    printf("The sequence is: ");
    for (i = 0; i < numColumns; i++)
    {
        printf("%d,",sequence[i]);
    }
    printf("\n");
    //Prints the sequence

    Row *master = malloc((counter+1)*sizeof(Row));
    int dCount;
    for(dCount = 1; dCount < counter; dCount++)
    {
        master[dCount].row = malloc(1000*sizeof(char));
        master[dCount].OGrow = malloc(1000*sizeof(char));
        strcpy(master[dCount].OGrow,list[dCount]);
        master[dCount].OGrow = delWhiteSpace(master[dCount].OGrow);

        char *temp = malloc(1000*sizeof(char));
        int length = strlen(list[dCount]);

        if((list[dCount])[0] == ',')
        {
            char d = '!';
            char str1[2];
            str1[0] = d;
            str1[1] = '\0';
            strcat(temp,str1);
        }
        int isQuote = 0;
        for(i = 0; i < length; i++) {
            if (isQuote == 0)
            {
                if((list[dCount])[i] != '\"')
                {
                    if((list[dCount])[i] == ',')
                    {
                        //printf("start 123123");
                        strcat(temp,",");
                        if((i+1) < length)
                        {
                            if((list[dCount])[i+1] == ',')
                            {
                                strcat(temp,"!");//NEED TO ADD SUBSTRING
                            }
                        }
                    }
                    else
                    {
                        char c = (list[dCount])[i];
                        char str[2];
                        str[0] = c;
                        str[1] = '\0';
                        strcat(temp,str);
                    }
                }
                else
                {
                    isQuote = 1;
                    strcat(temp,"\"");
                }
            }
            else
            {
                if((list[dCount])[i] != '\"')
                {
                    if((list[dCount])[i] == ',')
                    {
                        strcat(temp,"~");
                    }
                    else
                    {
                        char v = (list[dCount])[i];
                        char strv[2];
                        strv[0] = v;
                        strv[1] = '\0';
                        strcat(temp,strv);
                    }
                }
                else
                {
                    isQuote = 0;
                    strcat(temp,"\"");
                }
            }
        }

        temp = delWhiteSpace(temp);
        strcpy(master[dCount].row,temp);

    }
    //"Run, Hide, Die "
    //"Run~ Hide~ Die "
    //Now to get rid of the "" and ~ in the movie

    //MAKE SURE U DO THE "" MY GUY
    int eCount;
    for (eCount = 1; eCount < counter; eCount++)
    {
        char *tempY = malloc(1000*sizeof(char));
        strcpy(tempY,master[eCount].row);

        char *toke = strtok(tempY, ",");
        int go = 0;

        while(toke != NULL && go <= iterator)
        {
            if (iterator == go)
            {
                master[eCount].value = malloc(500*sizeof(char));
                toke = delWhiteSpace(toke);
                strcpy(master[eCount].value,toke);
                break;
            }
            toke = strtok(NULL, ",");
            go++;
        }
    }
    //Tokenizes and fills in row properly


    /////////////////////////////////
    printf("Counter is: %d\n", counter);
    for(i = 1; i < counter; i++)
    {
        char *rawRow = malloc(1000*sizeof(char));
        strcpy(rawRow, master[i].row);
        printf("copied rawROw\n");

        char *placingToken = strtok(rawRow,",");
        int colCounterTest = 0;
        //int error = 0;
        char listof28[28][100];
        printf("We made the list\n");
        int j;
        for(j = 0; j < 27; j++ )
        {
            strcpy(listof28[j], ",\0");
        }
        strcpy(listof28[27], "\0");

        while(placingToken != NULL)
        {
            if (colCounterTest > numColumns - 1)
            {
                //error = 1;
                printf("THERE ARE TOO MANY COLUMNS IN THE BODY\n");
                return -1;
            }
            int indexSeq = sequence[colCounterTest];
            printf("The index is: %d ", indexSeq);
            char *inputinList = malloc(100*sizeof(char));
            strcpy(inputinList, placingToken);
            printf("The inputinList is: %s ", inputinList);
            inputinList = strcat(inputinList,listof28[indexSeq]);
            strcpy(listof28[indexSeq],inputinList);
            printf("The inputted string is: %s ", listof28[indexSeq]);
            printf("\n");

            colCounterTest++;
            placingToken = strtok(NULL, ",");
        }
        char *ProperRowOrder = malloc(1000*sizeof(char));
        for(j = 0; j < 28; j++)
        {
            ProperRowOrder = strcat(ProperRowOrder,listof28[j]);
        }
        printf("The ENTIRE STRING is: %s ", ProperRowOrder);
        strcpy(master[i].OGrow, ProperRowOrder);
    }
    ////////////////////////////////


    






    for(i = 1; i < counter; i++)
    {
        char *tmpval = malloc(500*sizeof(char));
        int length1 = strlen(master[i].value);
        int j = 0;
        for(j = 0; j < length1; j++)
        {
            if((master[i].value)[j] == '~')
            {
                strcat(tmpval,",");
            }
            else if((master[i].value)[j] != '\"')
            {
                char h = (master[i].value)[j];
                char strh[2];
                strh[0] = h;
                strh[1] = '\0';
                strcat(tmpval,strh);
            }
        }
        strcpy(master[i].value,tmpval);
    }
    //Replaces the ~ to ""

    int j;
    for(j = 1; j < counter - 1; j++)
    {
        char *tempnum = malloc(500*sizeof(char));
        strcpy(tempnum,master[j].value);
        if(!strcmp(tempnum,"!"))
        {
            master[j].fnum = -9999999999;
        }
        else
        {
            float val;
            val = atof(tempnum);
            master[j].fnum = val;
        }
    }

    int typeofitem = 1;

    if (strcmp(name,"color") == 0)
    {
        typeofitem = 0;
    }
    else if (strcmp(name,"director_name") == 0)
    {
        typeofitem = 0;
    }
    else if (strcmp(name,"actor_2_name") == 0)
    {
        typeofitem = 0;
    }
    else if (strcmp(name,"genres") == 0)
    {
        typeofitem = 0;
    }
    else if (strcmp(name,"actor_1_name") == 0)
    {
        typeofitem = 0;
    }
    else if (strcmp(name,"movie_title") == 0)
    {
        typeofitem = 0;
    }
    else if (strcmp(name,"actor_3_name") == 0)
    {
        typeofitem = 0;
    }
    else if (strcmp(name,"plot_keywords") == 0)
    {
        typeofitem = 0;
    }
    else if (strcmp(name,"movie_imdb_link") == 0)
    {
        typeofitem = 0;
    }
    else if (strcmp(name,"language") == 0)
    {
        typeofitem = 0;
    }
    else if (strcmp(name,"country") == 0)
    {
        typeofitem = 0;
    }
    else if (strcmp(name,"content_rating") == 0)
    {
        typeofitem = 0;
    }
    else
    {
        typeofitem = 1;
    }
    //Check if name is correct

    mergeSort(master, 1, counter - 1, typeofitem);
    char *workFile = malloc(1000*sizeof(char));
    workFile[0] = '\0';
    workFile = strcat(workFile, inFileName);
    //Set current csv file to workFile

    char *newFile = changeOutFileName(workFile, name);
    //Change the input file name to sorted file name

    char *destination = malloc(1000*sizeof(char));
    destination[0] = '\0';
    destination = strcat(destination, getparentPath(inFile, inFileName));
    //CHANGE DESTINATION TO CURRENT DIRECTORY

    char *newPath = malloc(1000*sizeof(char));
    if (hasEnd)
    {
        newPath = checkPath(endDir, newFile);
    }
    else
    {
        newPath = checkPath(destination, newFile);
    }

    //Set destination given in stdin to destination

    FILE *output;
    output = fopen(newPath,"w");
    fprintf(output, delWhiteSpace(list[0]));
    fprintf(output, "\n");
    for(i = 1; i < counter; i++)
    {
        fprintf(output, master[i].OGrow);
        fprintf(output, "\n");
    }
    fclose(output);

    //Print to out file
    free(str);
    free(list);
    //free(tempColNames);
    free(colNames);
    free(master);
    free(workFile);
    free(newFile);
    free(destination);
    free(newPath);

    return 0;
}


char* getparentPath(char* inFile, char* inFileName)
{
    //printf("The inFile is %s and the inFileName is %s\n", inFile, inFileName);
    char *token = strtok(inFile, "/");
    char *newFile = malloc(1000*sizeof(char));
    newFile[0] = '\0';
    while(token != NULL)
    {
        if ((strcmp(token,inFileName)) != 0)
        {
            newFile = strcat(newFile,token);
            newFile = strcat(newFile, "/");
            token = strtok(NULL, "/");
        }
        else
        {
            break;
        }

    }
    //printf("The newFile is %s\n", newFile);
    return newFile;
}

int checkifDirorFile(char* dir)
{
    struct stat statbuf;
////////////////////////    printf("The dir inside this method is %s\n", dir);
    if (stat(dir, &statbuf) != 0)
    {
        return 0;
    }
   return S_ISDIR(statbuf.st_mode);
}

int checkDir(char* dir)
{
    struct stat buffer;
    int status;
    status = stat(dir, &buffer);
    if (status == 0)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}
char* checkPath(char* destination, char* workFile)
{
    struct stat buffer;
    int status;
    status = stat(destination, &buffer);

    char *newDest = malloc((strlen(destination)+strlen(workFile)+2)*sizeof(char));
    char *newFile = malloc((strlen(workFile)+2)*sizeof(char));
    strcpy(newDest, destination);
    strcpy(newFile, workFile);
////////////////////    printf("The status is %d\n" , status);

    if(status == 0)
    {
        if(newDest[strlen(newDest)-1] != '/')
        {
            newDest = strcat(newDest, "/");
        }
        return strcat(newDest, newFile);
    }
    else
    {
        fprintf(stderr, "The input destination is not a valid path\n");
    }
    return destination;
}

char* changeOutFileName(char* workFile, char* colName)
{
    int i = 0;
    int length = strlen(workFile);
    if(strstr(workFile, ".csv"))
    {
        length = length - 4;
    }
    //char *extension = "-sorted-movie_title.csv";
    char *extension = malloc((strlen(colName)+100)*sizeof(char));
    extension[0] = '\0';
    extension = strcat(extension, "-sorted-");
    extension = strcat(extension, colName);
    extension = strcat(extension, ".csv");
    //printf("THE EXTENSION IS NAMED: %s\n", extension);
    int lenExt = strlen(extension);
    char *begin = malloc((length+lenExt+1)*sizeof(char));

    while (i < length)
    {
        begin[i] = workFile[i];
        i++;
    }

    begin[i] = '\0';
    return strcat(begin,extension);
}

int ScannerDriver(char* path, char* name, char* endDir, int hasEnd, char* input)
{
    //chdir(path);
    struct dirent *de;
    DIR *dr = opendir(path);
    if (dr == NULL)
    {
        fprintf(stderr, "Could not open current directory: %s\n", path);
        return 0;
    }

    char **listDir = malloc(100*sizeof(char*));
    //char **listFiles = malloc(100*sizeof(char*));
    int i = 0;
    //int j = 0;
    int r = 0;
    pid_t fPID;
    int status = 0;
    while ((de = readdir(dr)) != NULL)
    {
        char* usePath = (char*)malloc(sizeof(char)*1000);
        memcpy(usePath, path, sizeof(char)*strlen(path));
        int pathLen = strlen(path);
        usePath[pathLen] = '\0';
        if(usePath[strlen(usePath) - 1] != '/')
        {
          usePath = strcat(usePath, "/");
        }
        usePath = strcat(usePath, de->d_name);
        if(strcmp(de->d_name, ".") && strcmp(de->d_name, "..") && !strstr(de->d_name, "-sorted-"))
        {
            if(checkifDirorFile(usePath))
            {
                ///////////////////////////////printf("Directory is %s\n\n", de->d_name);
                //listDir[i] = de->d_name;
                listDir[i] = (char*)malloc(1000*sizeof(char));
                strcpy(listDir[i], usePath);
                i++;
                //ScannerDriver(de->d_name, name, endDir, hasEnd, input);
            }
            else
            {
              /*char *inFile = malloc(100*sizeof(char));
              inFile[0] = '\0';
              inFile = strcat(inFile, de->d_name);
              */
              FILE *fp = fopen(usePath, "r");
            //////////////////////////    printf("OPENED FILE\n");
              if(!fp){
                    //printf("maybe\n");
                fprintf(stderr, "File could not be opened\n");
                return -1;
              }
            //////////////////////////////    printf("File exists\n");
                //Open input file

              size_t strSize;
              char *str = malloc(1000*sizeof(char));
              char * tempColNames = malloc(1000*sizeof(char));
                if( (getline(&str, &strSize, fp)) == -1)
                {
                    //printf("over here1?\n");
                    return -1;
                }
                /*char **list = malloc(2*sizeof(char*));
                list[0] = malloc(1000*sizeof(char));
                list[1] = malloc(1000*sizeof(char));
                strcpy(list[0], str);
                strcpy(tempColNames, list[0]);
                */
                strcpy(tempColNames, str);
                int CSVisGood = isValidCSV(tempColNames);
                int check = 0;
                if(CSVisGood == -1){
                     //printf("over here2? usePath is: %s\n", usePath);
                     check = -1;
                }
                free(str);
                free(tempColNames);
                if (check != -1)
                {
                  //chdir(path);
                  fPID = fork();
                  if(fPID == 0){  //childProcess
                        pid_t childPID = getpid();
                        printf("%d, ", childPID);
                        fflush(stdout);
                        /////////////////////////printf("File is %s\n", de->d_name);
                        char *inputFile = malloc(100*sizeof(char));
                        inputFile[0] = '\0';
                        inputFile = strcat(inputFile, de->d_name);
                        //////////////////////////printf("The input is: %s\nThe name is: %s\nThe endDir is: %s\n", inputFile, name, endDir);
                        /////////////////////////printf("Usepath is: %s\n", usePath);
                        int ans = sortFile(usePath, inputFile, name, endDir, hasEnd);
                        if(ans == -1){
                            exit(0);
                        }
                        /////////////////////////printf("The ans is %d\n\n" , ans);
                        exit(1);
                  }else{
                      waitpid(fPID, &status, 0);
                      procCount = procCount + WEXITSTATUS(status);
                  }
                }
            }
        }
        /////////////////////////printf("We are on %d iteration\n\n", r);
        r++;
    }
    closedir(dr);
    int j = 0;
    if (i > j)
    {
        //////////////////////////printf("WE HERE\n");
        for(j = 0; j < i; j++)
        {
            fPID = fork();
            if(fPID == 0)   //child PRocess
            {
                pid_t childPID = getpid();
                printf("%d, ", childPID);
                fflush(stdout);
                char *temp = malloc(1000*sizeof(char));
                temp[0] = '\0';
                //////////////////////////printf("The content of listDir is: %s\n", listDir[j]);
                procCount = 1;
                strcat(temp, listDir[j]);
                ///////////////////////////printf("The directory to go into is: %s\n", temp);
                ScannerDriver(temp, name, endDir, hasEnd, input);
                exit(procCount);
            }else{
                waitpid(fPID, &status, 0);
                procCount = procCount + WEXITSTATUS(status);
            }
        }
        free(listDir);
        return 1;
    }
    else
    {
        free(listDir);
        return 1;
    }
}

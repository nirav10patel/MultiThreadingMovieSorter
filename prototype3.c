#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <dirent.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include "driver.h"
//#include "mergesort.c"


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
    char *inFile = argv[1];
    int ans = getRows(inFile);
    return int;
}

int getRows(char *inFile)
{
    char *str = malloc(1000*sizeof(char));
    File *fp = fopen(inFile, "r");
    if(!fp)
    {
        fprintf(stderr, "File could not be opened\n");
        return -1;
    }

    size_t strSize;
    int counter = 0;
    int first = 0;
    Collection master = malloc(sizeof(Collection));
    while((getline(&str, &strSize, fp)) != -1)
    {
        if (first == 0)
        {
            strcpy(master.header,str);
            first = 1;
        }
        Row temp = malloc(sizeof(Row));
        strcpy(temp.ogRow,str);
        memcpy(master.group[counter],temp);
    }
    //The above fills in row by row into master

    if(counter == 0)
    {
        return -1;
    }
    //Returns -1 if no rows found

    int i;
    for(i = 0; i < counter, i++)
    {
        printf("%s\n", master.group[i]);
    }
}

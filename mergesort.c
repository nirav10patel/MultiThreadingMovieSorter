#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

void merge(Row *bigMaster, int low, int mid, int high, int type)
{
        static int mergenum = 0;
        mergenum++;
        //printf("merge is: %d\n", mergenum);
       int listSize = high - low + 1;
       int lside = low;
       Row *tempList = (Row*)(malloc(listSize*sizeof(Row)));
       int rside = mid + 1;
       int i = 0;
       for(; (lside <= mid) && (rside <= high); i++)
       {
               if( type == 1 )
               {
                   if( (bigMaster[lside].fnum) <= (bigMaster[rside].fnum) )
                   {
                       tempList[i] = bigMaster[lside];
                       lside = lside+1;
                    }else
                    {
                       tempList[i] = bigMaster[rside];
                       rside = rside+1;
                    }
               }else
               {
                       if( (strcmp(bigMaster[lside].value, bigMaster[rside].value)) <= 0)
                       {
                           /*printf("IN FOR1: 1\n");
                           printf("     LSIDE IS: %d\n", lside);
                           printf("     RSIDE IS: %d\n", rside);
                           printf("     I IS: %d LISTSIZE IS: %d\n", i,listSize);
                           printf("     HIGH is %d LOW is %d MID is %d\n", high,low,mid); */
                           tempList[i] = bigMaster[lside];
                           //printf("GOTTEM BOYS\n");
                           lside = lside+1;
                       }else
                       {
                          /* printf("IN FOR2: 1\n");
                           printf("     LSIDE IS: %d\n", lside);
                           printf("     RSIDE IS: %d\n", rside);
                           printf("     I IS: %d LISTSIZE IS: %d\n", i,listSize);
                           printf("     HIGH is %d LOW is %d MID is %d\n", high,low,mid); */
                           tempList[i] = bigMaster[rside];
                          // printf("GOTTEM BOYS\n");
                           rside = rside+1;
                       }
                       /* LSIDE IS: 234
                       RSIDE IS: 236
                       I IS: 234 LISTSIZE IS: 4
                       HIGH is 237 LOW is 234 MID is 235 */
               }
       }
       //printf("END OF FOR\n");
       while(lside <= mid)
       {
           tempList[i] = bigMaster[lside];
           lside = lside+1;
           i = i+1;
       }
      // printf("END OF WHILE1\n");
       while(rside <= high)
       {
           tempList[i] = bigMaster[rside];
           rside = rside+1;
           i = i+1;
       }
       //printf("END OF WHILE2\n");
       for(i = 0; i < listSize; ++i)
       {
           bigMaster[i+low] = tempList[i];
       }
       free(tempList);
       //printf("END OF MERGE\n");
}

void mergeSort(Row *bigMaster, int low, int high, int type)
{
       int mid = 0;
       static int counter = 1;
       if(low<high)
       {
           mid = (low+high)/2;
           mergeSort(bigMaster, low, mid, type);
           mergeSort(bigMaster, mid+1, high, type);
           merge(bigMaster, low, mid, high, type);
           //printf("got here %d\n", counter);
           counter++;
       }else
       {
               return;
       }
}

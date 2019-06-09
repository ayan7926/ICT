#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<time.h>
#define CW_LEN 20
#define IP_LEN 16
#define NO_CW 1048576
#define NO_VALID_CW 65536

char CW_TAB[NO_CW][CW_LEN+1];
static long int c = 0;
char A[CW_LEN+1];

void binary(int n)
{

    if(n < 1)
    {
        strcpy(CW_TAB[c], A);
        c++;
    }
    else
    {
        A[n-1] = '0';
        binary(n-1);
        A[n-1] = '1';
        binary(n-1);

    }

}

int count_1(char s[])
{
    int t=0,i=0;
    while(s[i] != '\0')
    {
        if(s[i] == '1')
        {
            t++;
        }
    
        i++;
    }

    return t;
}

int Hamming_Dist(char a[], char b[])
{
    int x,y,i;

    x = count_1(a);
    y = count_1(b);

    i = ((x-y) > 0) ? (x-y) : (y-x);

    return i;
}

void main()
{
    int i,j,r,p,flag=0,used[NO_CW];
    char CW_SET[NO_VALID_CW][CW_LEN+1];
    char msg[CW_LEN+1], org_msg[CW_LEN+1];
    binary(CW_LEN);
    srand(time(NULL));

    
    for(i=0; i<NO_CW; i++)
    {
        used[i] = 0;
    }

    /*
        Generate 2^16 valid codewords from the codeword
        table
    */

    for(i=0; i<NO_VALID_CW; i++)
    {
         r = rand() % NO_CW;
         
         if(used[r] != 0)
         {
            i--;
            continue;
         }

         strcpy(CW_SET[i], CW_TAB[r]);
         // printf("%s \n", CW_SET[i]);
         used[r] = 1;
     }

     r = rand() % NO_VALID_CW;
     strcpy(msg, CW_SET[r]);
     strcpy(org_msg, msg);
     printf("Sent message : %s \n", msg);

     /*
        CHANNEL
        BSC with p = 0.15
        Flip bits with 0.15 probability
     */
    for(i=0; i<CW_LEN; i++)
    { 
        p = rand() % 100;
        if(p<0.15)
        {
            if(msg[i] == '0')
                msg[i] = '1';
            else if(msg[i] == '1')
                msg[i] = '0';
        }
    }

    /*
        Receiver's End : 
        To Find the codewords within Hamming distance = 3;
        Since, mean probability of error = np = 3
        
        If more than 1, decode to the one having minimum
        Hamming distance(Maximum Likelihood decoding)
        
        If more than 1 with same Hamming distance, decode to 
        any one of them.
    */

    printf("Received message : %s %d\n", msg, count_1(msg));

    char within_HD_3[NO_VALID_CW][CW_LEN+1];
    char within_HD_1[NO_VALID_CW][CW_LEN+1];
    int HD,c=0,closest=0;

    for(i=0; i<NO_VALID_CW; i++)
    {
        HD = Hamming_Dist(msg, CW_SET[i]);
        if(HD <= 3)
        {
            strcpy(within_HD_3[c], CW_SET[i]);
            //printf("%s\n", within_HD_3[c]);
            c++;
        }
        if(HD <= 1)
        {
            strcpy(within_HD_1[closest], CW_SET[i]);
            closest++;
        }
    }

    printf("No. of codewords within radius 3 = %d\n", c);
    printf("No. of codewords within radius 1 = %d", closest);
}

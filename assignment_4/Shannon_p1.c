#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<string.h>
#define pe 10


char codewords[8][3] = {"000","001","010","011","100","101","110","111"};
char valid_cw[2][3]	= {"000","111"};

int no_of_zeroes(char c[])
{
	int i,j=0,k;

	for(i=0; i<strlen(c) ; i++)
	{
		if(c[i] == '0')
			j++;
	}

	return j;
}

int main()
{
	srand(time(0));

	char msg;
	char enc_msg[4];
	char dis_msg[4];
	char dec_msg[4];
	int i,j,temp,z,error=0;

	for(j=0; j<10000; j++)
	{	
		//SOURCE
		for(i=0;i<100;i++)
		{
			msg = rand() % 2;

			if(msg == 0)
			{
				strcpy(enc_msg,"000");
			}
			else if(msg == 1)
			{
				strcpy(enc_msg,"111");
			}
		}

		printf("Encoded msg : %s", enc_msg);

		strcpy(dis_msg, enc_msg);

		//CHANNEL
		for(i=0; i<3; i++)
		{
			temp = rand() % 100;
			
			if(temp < pe)
			{
				if(dis_msg[i] == '0')
					dis_msg[i] = '1';
				else if(dis_msg[i] == '1')
					dis_msg[i] = '0';	
			}
		}

		printf(" Distorted msg : %s", dis_msg);

		//DECODING
		z = no_of_zeroes(dis_msg);

		printf(" z= %d", z);	

		if(z >= 2)
		{
			strcpy(dec_msg,"000");
		}
		else if(z <= 1)
		{
			strcpy(dec_msg,"111");
		}

		printf(" Decoded msg : %s \n", dec_msg);		
	
		if(strcmp(enc_msg, dec_msg) == 0)
			error++;
	}

	printf("Probability of error = %f", (10000-error)/(10000.0));

}


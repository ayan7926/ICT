#include<stdio.h>
#include<time.h>
#include<stdlib.h>
#define p 0.1
#define q 0.2
#define M 10000

//2 state source :- 0,1
//const float p = 0.2;
//const float q = 0.4;

// 4 state source :- 00,01,10,11
float p_00_00 = 1-p;
float p_01_00 = p;
float p_10_00 = 0;
float p_11_00 = 0;
float p_00_01 = 0;
float p_01_01 = 0;
float p_10_01 = q;
float p_11_01 = 1-q;
float p_00_10 = 1-p;
float p_01_10 = p;
float p_10_10 = 0;
float p_11_10 = 0;
float p_00_11 = 0;
float p_01_11 = 0;
float p_10_11 = q;
float p_11_11 = 1-q;



int main()
{
	srand(time(0));
	FILE *fp;

	fp = fopen("data_3.csv","w");

	int prev_initial_sym = rand() % 2;
	int initial_sym = rand()%2;
	int prev_curr_sym = prev_initial_sym;
	int curr_sym = initial_sym;
	//int prev_curr_sym = 0;
	//int curr_sym = 0;
	int x = 0, cnt_00=0, cnt_01=0, cnt_10=0, cnt_11=0;
	int i,j,k;
	float prob, temp;

	while(x<=M)
	{
		temp = rand() % 100;

		if((prev_curr_sym == 0) && (curr_sym == 0))
		{
			if(temp <= (100*p_00_00))
			{
				prev_curr_sym = curr_sym;
				curr_sym = 0;
				cnt_00++;
			}
			
			else 
			{
				prev_curr_sym = curr_sym;
				curr_sym = 1;
				cnt_01++;
			}
		}

		else if((prev_curr_sym == 0) && (curr_sym == 1))
		{
			if(temp <= (100*p_10_01))
			{
				prev_curr_sym = curr_sym;
				curr_sym = 0;
				cnt_10++;
			}
			else 
			{
				prev_curr_sym = curr_sym;
				curr_sym = 1;
				cnt_11++;
			}
		}

		else if((prev_curr_sym == 1) && (curr_sym == 0))
		{
			
			if(temp <= (100*p_01_10))
			{
				prev_curr_sym = curr_sym;
				curr_sym = 1;
				cnt_01++;
			}
			else 
			{
				prev_curr_sym = curr_sym;
				curr_sym = 0;
				cnt_00++;
			}
		}

		else if((prev_curr_sym == 1) && (curr_sym == 1))
		{
			
			if(temp <= (100*p_10_11))
			{
				prev_curr_sym = curr_sym;
				curr_sym = 0;
				cnt_10++;
			}
			else 
			{
				prev_curr_sym = curr_sym;
				curr_sym = 1;
				cnt_11++;
			}
		}
		
		fprintf(fp, "%f,%f,%f,%f\n",(float)cnt_00/x, (float)cnt_01/x, (float)cnt_10/x, (float)cnt_11/x);
		x++;
	}

	printf("c_00 = %d, c_01 = %d, c_10 = %d, c_11 = %d",cnt_00, cnt_01, cnt_10, cnt_11);


		
	return 0;
}

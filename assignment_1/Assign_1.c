#include<stdio.h>
#include<stdlib.h>
#include<time.h>

float p = 0.2;
float q = 0.4;
FILE *fp;


int main()
{
	srand(time(0));

	int initial_sym = rand()%2;
	int seq_len = 5000;
	int x = 0, cnt_0 = 0, cnt_1 = 0;
	int cnt_0_l, cnt_1_l;
	int curr_sym = initial_sym;
	int i,j,k;
	float p_local, q_local, prob, temp;

	fp = fopen("data_1.csv","w");

	while(x<=50000)
	{
		cnt_1_l = 0;
		cnt_0_l = 0;
		for(i=0;i<100;i++)
		{
			if(curr_sym == 0)
			{
				temp = rand() % 100;

				if(temp <= (100*p))
				{
					curr_sym = 1;
					cnt_1++;
					cnt_1_l++;
					//printf("%d",curr_sym);
				}
				else
				{
					curr_sym = 0;
					cnt_0++;
					cnt_0_l++;
					//printf("%d",curr_sym);
				}
			}
		
			else if(curr_sym == 1)
			{
				temp = rand() % 100;

				if(temp <= (100*q))
				{
					curr_sym = 0;
					cnt_0++;
					cnt_0_l++;
					//printf("%d", curr_sym);
				}
				else
				{	
					curr_sym = 1;
					cnt_1++;
					cnt_1_l++;
					//printf("%d", curr_sym);
				}
			}
		}
		
		x++;
		printf("P(0) = %f, P(1) = %f\n", cnt_0/(100.0*x), cnt_1/(100.0*x));
		fprintf(fp, "\n%f,%f", cnt_0/(100.0*x), cnt_1/(100.0*x));
		
	}

	printf("\nTheoritical P(0) = %f, Theroritical P(1) = %f", q/(p+q), p/(p+q));

}
#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<string.h>
#define IP_LEN 4
#define OP_LEN 7
#define MAX 100

/*
	Linear Block Code with Parameters :
	(7,4) one error correcting code
	Input block length 	= 4 bits
	Output block length = 7 bits	 
*/

/*
	input and output lengths
*/
int ip_length = 4;
int op_length = 7;

/*Generator Matrix*/
int G[IP_LEN][OP_LEN] = { {1,0,0,0,1,0,1},
			  			  {0,1,0,0,1,1,1},
			  			  {0,0,1,0,1,1,0},
			  			  {0,0,0,1,0,1,1}
			  			};

/*Transpose of Parity Check Matrix*/
int H_T[OP_LEN][OP_LEN - IP_LEN] = { {1,0,1},
									 {1,1,1},
									 {1,1,0},
								     {0,1,1},
									 {1,0,0},
									 {0,1,0},
									 {0,0,1}
								 	};
/*
	Error vs Syndrome table
*/
struct err_syn_table
{
	int err[OP_LEN];
	int syn[OP_LEN - IP_LEN];
} ES[OP_LEN + 1];

/*
	Displaying a vector
	c --> The array storing the vector
	n --> size of the vector
*/
void disp_vector(int *c, int n)
{
	int i;
	
	for(i=0; i<n; i++)
	{
		printf("%d ", c[i]);
	}

	printf("\n");
}

/*
	Vector Matrix Multiplication
	for compatible multiplication
	length of vector = no. of rows of matrix
	i.e n = r
*/
int *vector_matrix_mul(int n, int r, int c, int a[], int m[][c])
{
	int *temp = (int*)malloc(c*sizeof(int));
	int i,j,sum;

	for(i=0; i<c; i++)
	{
		sum = 0;

		for(j=0; j<r; j++)
		{
			sum = (sum + a[j]*m[j][i]); 
			//printf("a[%d]*m[%d][%d] = %d*%d = %d\n",j,j,i,a[j],m[j][i],sum);
		}	

		temp[i] = sum % 2;
	}

	return temp;
}

int *single_channel_error(int a[], int n)
{	
	int *temp = (int*)malloc(n*sizeof(int));
	int i,sum,r;

	r = rand() % n;

	for(i=0;i<n;i++)
	{
		temp[i] = a[i];
	}

	/*
		Introduce single bit error in channel by 
		flipping a random bit
	*/
	if(a[r] == 0)
		temp[r] = 1;
	else
		temp[r] = 0;

	return temp;
}		

/*
	Function to Construct the Error vs Syndrome table
	syn = err.H_T
*/
void syndrome_table_cons()
{
	int temp[OP_LEN] = {0,0,0,0,0,0,0};
	int synd[OP_LEN - IP_LEN] = {0,0,0};
	int *t = (int*)malloc((OP_LEN - IP_LEN)*sizeof(int));
	int i,j;

	memcpy(temp, ES[0].err, OP_LEN*sizeof(int));
	memcpy(synd, ES[0].syn, (OP_LEN - IP_LEN)*sizeof(int));

	for(i=0; i<OP_LEN; i++)
	{
		for(j=0; j<OP_LEN; j++)
		{
			if(i == j)
				temp[j] = 1;
			else
				temp[j] = 0;
		
			ES[i+1].err[j] = temp[j];
		}
				
		t = vector_matrix_mul(OP_LEN, OP_LEN, (OP_LEN- IP_LEN), temp, H_T);
		
		for(j=0; j<(OP_LEN - IP_LEN); j++)
		{
			ES[i+1].syn[j] = t[j];
		}
	}

	/*Display the error vs syndrome table*/
	for(i=0; i<(OP_LEN + 1); i++)
	{
		disp_vector(ES[i].err, OP_LEN);
		printf("--->");
		disp_vector(ES[i].syn, OP_LEN - IP_LEN);
	}
}

/*
	Function for error detection : 
	-> To input the received vector after passing through channel 
	-> and the Parity check matrix
	-> syn = recv.(H_T)
*/
int *error_detection(int n, int r, int c, int m[r][c], int a[n])
{
	int *temp = (int*)malloc(c*sizeof(int));
	int i,j=0;

	temp = vector_matrix_mul(n,r,c,a,m);

	for(i=0; i<c; i++)
	{
		if(temp[i]!=0)
		{
			j=1;
			break;
		}

	}

	printf("Syndrome is : ");
	disp_vector(temp,c);

	if(j==0)
		printf("No error detected in received code\n");
	else if(j==1)
		printf("Error in Received code\n");

	return temp;
}

int* error_correction(int s[], int n, int m)
{	
	int i,j,flag,pos;

	for(i=0; i < (OP_LEN+1) ;i++)
	{
		flag = 0;

		for(j=0; j<n; j++)
		{
			if(ES[i].syn[j] != s[j])
			{
				flag = 1;
				break;
			}
		}
	
		if(flag == 0)
		{
			pos = i;	
			break;
		}
	}

	if(flag !=0)
	{
		printf("More than one error possibly, cannot be corrected\n");
		return ES[0].err;
	}
	

	return ES[pos].err;
}

int* remove_error(int m, int a[m], int b[m])
{
	int *temp = (int*)malloc(m*sizeof(int));
	int i;

	for(i=0; i<m;i++)
	{
		temp[i] = (a[i]+b[i])%2;
	}

	return temp;
}

void main()
{
	/*
		SOURCE
	*/
	int ip_block[IP_LEN] = {1,0,1,1};
	int *op_block = (int*)malloc(OP_LEN*sizeof(int));
	op_block = vector_matrix_mul(IP_LEN, IP_LEN, OP_LEN, ip_block, G);
	disp_vector(op_block, OP_LEN);

	/*
		CHANNEL
	*/
	srand(time(NULL));
	op_block = single_channel_error(op_block, OP_LEN);
	disp_vector(op_block, OP_LEN);

	/*
		DESTINATION
	*/
	syndrome_table_cons();
	int *syndrome = (int*)malloc((OP_LEN - IP_LEN)*sizeof(int));
	int *err_vector = (int*)malloc((OP_LEN)*sizeof(int));
	
	/*
		syndrome calculation
	*/
	syndrome = error_detection(OP_LEN, OP_LEN, (OP_LEN-IP_LEN), H_T, op_block);
	disp_vector(syndrome, (OP_LEN - IP_LEN));
	
	/*
		finding error by table lookup
	*/
	err_vector = error_correction(syndrome, (OP_LEN - IP_LEN), OP_LEN);
	disp_vector(err_vector, OP_LEN);
	
	/*
		removing the error
	*/
	op_block = remove_error(OP_LEN, err_vector, op_block);
	disp_vector(op_block, OP_LEN);
}





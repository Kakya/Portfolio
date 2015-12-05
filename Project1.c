#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define max(a,b) \
({ int (a) _a = (a); \
int (b) _b = (b); \
_a > _b ? _a : _b; })
#define min(a,b) \
({ int (a) _a = (a); \
int (b) _b = (b); \
_a < _b ? _a : _b; })
int checkboard(int b[], int n);
int displayboard(int b[], int n);
void randperm(int b[], int n);
void InitializeArray(int emptyArray[], int maxNum);
void StatisticsCounting(double StatsArray[], int arraySuccess[], int sizeofBoard, int sizeofArray);
int main()
{
	//Initializing variables to be used in the main function.
	srandom(7304);
	int boardSize = 4;
	int ctr;
	int Array[20] = {0};
	int i;
	int displayed=0;
	int Actr = 0;
	int timeToSuccess[10];
	double StatsArray[6] = {0};
	while(boardSize<=20){
		//loop ten times through each boardsize to find ten solutions.
		for (ctr=0; ctr < 10; ctr++)
		{
			//initialize the counter to check how many boards to find solution
			Actr=0;
			while(1)
			{
				//keeps generating random boards until a solution is found. Board number is incremented. First solution found is printed.
				InitializeArray(Array, boardSize);
				randperm(Array, boardSize);
				Actr++;
				if(checkboard(Array, boardSize))
				{
					//add how many boards you went through to an array keeping the time.
					timeToSuccess[ctr]=Actr;
					//print first board found.
					if(displayed==0)
					{
						displayed++;
						displayboard(Array, boardSize);
					}
					break;
				}
			}
		}
		//Compute max, min, mean, etc.
		StatisticsCounting(StatsArray, timeToSuccess, boardSize, 10);
		//print out the statistics for each board.
		printf("Size\t    min\t    \tmax\t    \tmean\t    \tsize**size\t    \tsize!\n");
		for(i=0; i<6; i++)
		{
			printf("%f  ", *(StatsArray+i));
		}
		printf("\n");
		boardSize++;
		displayed=0;
	}
}

void randperm(int b[], int n)
{
	int i;
	int k;
	int j;
	//Shuffle a board using the Yates Shuffle
	for(i=n-1; i >= 1; i--)
	{
		j = random()%(i + 1);
		k = *(b+j);
		*(b+j) = *(b+i);
		*(b+i) = k;
	}
}
void InitializeArray(int emptyArray[], int maxNum)
{
	//Initialize an array with elements (0...n-1)
	int i;
	int numAdd = 0;
	for (i=0; i<maxNum; i++)
	{
 		*(emptyArray+i)=numAdd;
		numAdd++;
	}
}
int checkboard(int b[], int n)
{
	//Checks for a solution using the slope formula: (Y1-Y2)/(X1-X2)=1, if 1 is the answer the board is not a solution and returns 0
	int i;
	for (i=0; i < n; i++)
	{
		int j;
		for(j=0; j < n; j++)
		{
			if(j!=i)
			{
				if(abs(*(b+j)-*(b+i))==abs(j-i))
					return 0;
			}
		}
	}
	//returns 1 if it is a solution
	return 1;
}
int displayboard(int b[], int n)
{
	int i;
	int j=0;
	int ctr;
	printf("[ ");
	for(i=0; i< n; i++)
	{
		printf("%d ",*(b+i));
	}
	printf("]\n");
	for(i=0; i<n; i++)
	{
		ctr=0;
		j=0;
		while(j!=*(b+i))
		{
			printf("- ");
			ctr++;
			j++;
		}	
		printf("* ");
		while(ctr<n-1)
		{
			printf("- ");
			ctr++;
		}
		printf("\n");
	}
	return 0;
}
void StatisticsCounting(double StatsArray[], int arraySuccess[], int sizeofBoard, int sizeofArray)
{
	//General mathematical functions to compute a variety of statistics.
	double min = arraySuccess[0]/1.0;
	double max = arraySuccess[0]/1.0;
	double sum = 0;
	double mean;
	double sizeToTheSize=sizeofBoard;
	double facCtr = sizeofBoard-1;
	double facSum = sizeofBoard;
	int ctr;
	StatsArray[0]=sizeofBoard;
	int i;
	for(i=0; i<sizeofArray; i++)
	{
		if(arraySuccess[i]<min)
			min = arraySuccess[i];
	}
	StatsArray[1]=min;
	for(i = 0; i<sizeofArray; i++)
	{
		if(arraySuccess[i]>max)
			max = arraySuccess[i];
	}
	StatsArray[2] = max;
	for(i = 0; i<sizeofArray; i++)
	{
		sum+=arraySuccess[i];
	}
	mean = sum/sizeofArray;
	StatsArray[3] = mean;
	for(ctr=0; ctr<sizeofBoard-1; ctr++)
		sizeToTheSize=sizeToTheSize*sizeofBoard;
	StatsArray[4] = sizeToTheSize;
	while(facCtr>0)
	{
		facSum=facSum*(facCtr);
		facCtr--;
	}
	StatsArray[5] = facSum;
}
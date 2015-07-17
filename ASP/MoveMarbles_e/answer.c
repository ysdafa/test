// In Practice, You should use the statndard input/output
// in order to receive a score properly.
// Do not use file input and output. Please be very careful. 

#include <stdio.h>

int main(void)
{
	int tc, T;
	
	// The freopen function below opens input.txt file in read only mode, and afterward,
	// the program will read from input.txt file instead of standard(keyboard) input.
	// To test your program, you may save input data in input.txt file,
	// and use freopen function to read from the file when using scanf function.
	// You may remove the comment symbols(//) in the below statement and use it.
	// But before submission, you must remove the freopen function or rewrite comment symbols(//).
	
	// freopen("input.txt", "r", stdin);

	// If you remove the statement below, your program's output may not be rocorded
	// when your program is terminated after the time limit.
	// For safety, please use setbuf(stdout, NULL); statement.

    int numPockets = 0, np = 0; 
    int sumMarbles = 0; 
    int iter, totalMovementReq, equalMarbleQuantity, move; 
    int MarblesArr[32005]; 

	scanf("%d", &T); 
    for(tc = 0; tc < T; tc++) 
    { 
    for(iter = 0; iter < 32005; iter++) 
    { 
        MarblesArr[iter] = 0; 
    } 
    int sumMarbles = 0; 
    scanf("%d", &numPockets); 
    //printf("numPockets = %d\n", numPockets); 
    for(np = 0; np < numPockets; np++) 
    { 
        scanf("%d", &MarblesArr[np]); 
        //printf("%d\n", MarblesArr[np]); 
        // Sum of total marbles 
        sumMarbles += MarblesArr[np]; 
        //printf("sumMarbles = %d\n", sumMarbles ); 
    } 
 
    if( (sumMarbles % numPockets) ) 
    { 
        //printf("Not possible to equally distribute for TC number %d\n", tc); 
        return -1; 
        } 
        equalMarbleQuantity = sumMarbles / numPockets; 
        totalMovementReq = 0; 
        for ( np = 0; np < numPockets; np++ ) 
        { 
            move = ( MarblesArr[np] - equalMarbleQuantity ); 
            if( move > 0 ) 
            { 
                totalMovementReq += move; 
            } 

            /*if( MarblesArr[np] < equalMarbleQuantity ) 
            { 
                totalMovementReq += equalMarbleQuantity - MarblesArr[np]; 
            }*/ 
        } 
        //printf(" Total Movement required for TC %d is %d\n", tc, totalMovementReq); 
        printf("%d\n", totalMovementReq); 
    }


	return 0;//Your program should return 0 on normal termination.
}


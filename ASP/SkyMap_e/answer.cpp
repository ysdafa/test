/*

In Practice, You should use the statndard input/output
in order to receive a score properly.
Do not use file input and output. Please be very careful. 

*/

#include <stdio.h>
#include <iostream>

using namespace std;

int N;
int data[26][26];

int main(int argc, char** argv)
{
	int test_case;
	int T;
	/*
	   The freopen function below opens input.txt file in read only mode, and afterward,
	   the program will read from input.txt file instead of standard(keyboard) input.
	   To test your program, you may save input data in input.txt file,
	   and use freopen function to read from the file when using cin function.
	   You may remove the comment symbols(//) in the below statement and use it.
	   Use #include<cstdio> or #include<stdio.h> to use the function in your program.
	   But before submission, you must remove the freopen function or rewrite comment symbols(//).
	*/	
	// freopen("input.txt", "r", stdin);

	cin >> T;
	for(test_case = 0; test_case < T; test_case++)
	{
		int i,j;
		int S,C;
		cin >> N;
		
		for(i=1; i<=N; i++) {
			for(j=1; j<=N; j++) {
				cin >> data[i][j];
			}
		}
		
		/**********************************
		 * Implement your algorithm here. *
		 **********************************/
		
		S = 0;
		C = 0;
		
		// Print the answer to standard output(screen).
		cout << S << " " << C << endl;
	}

	return 0;//Your program should return 0 on normal termination.
}


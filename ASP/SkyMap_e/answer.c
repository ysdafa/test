/*

Practice는 표준 입출력을 사용합니다. 
파일 입출력을 사용하지 않음에 주의하세요.
In Practice, You should use the statndard input/output
in order to receive a score properly.
Do not use file input and output. Please be very careful. 

*/

#include <stdio.h>

int N;
int data[26][26];

int main(void)
{
	int test_case;
	int T;
	/*
	   The freopen function below opens input.txt file in read only mode, and afterward,
	   the program will read from input.txt file instead of standard(keyboard) input.
	   To test your program, you may save input data in input.txt file,
	   and use freopen function to read from the file when using scanf function.
	   You may remove the comment symbols(//) in the below statement and use it.
	   But before submission, you must remove the freopen function or rewrite comment symbols(//).
	 */
	// freopen("input.txt", "r", stdin);

	/*
	   If you remove the statement below, your program's output may not be rocorded
	   when your program is terminated after the time limit.
	   For safety, please use setbuf(stdout, NULL); statement.
	 */
	setbuf(stdout, NULL);

	scanf("%d", &T);
	for(test_case = 0; test_case < T; test_case++)
	{
		int i,j;
		int S,C;
		scanf("%d", &N);
		
		for(i=1; i<=N; i++) {
			for(j=1; j<=N; j++) {
				scanf("%d", &data[i][j]);
			}
		}

		/**********************************
		 * Implement your algorithm here. *
		 **********************************/
		
		S = 0;
		C = 0;
		
		// Print the answer to standard output(screen).
		printf("%d %d\n", S, C);
		
	}

	return 0;//Your program should return 0 on normal termination.
}

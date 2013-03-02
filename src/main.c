#include <stdio.h>
#include <stdlib.h>

#include "quiz.h"

int main(int argc, char *argv[])
{
	if( argc != 2 )
	{
		printf("Usage: quiz [questionfile]\n");
		exit(1);
	}
	Questiondata questions;
	read_file(argv[1], &questions);
		
	return 0;
}

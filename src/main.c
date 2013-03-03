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
	
	ask_questions(&questions);
	
	destroy_questiondata(&questions);
		
	return 0;
}

void destroy_questiondata(Questiondata *questions)
{
	free(questions->question_answers);
	free(questions->not_asked);
	
	int freecount;
	for(freecount=0; freecount<questions->numquestions; freecount++)
	{
		free(questions->question_text[freecount]);
	}
	
	free(questions->question_text);
}

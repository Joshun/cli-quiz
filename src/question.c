#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "quiz.h"

#define UNIX_RAND_SEED "/dev/urandom"

int get_random(const int min, const int max)
{
	FILE *random_source = fopen(UNIX_RAND_SEED, "r");
	/* Seed the current time if random file doesn't exist */
	if( random_source == NULL)
		srand(time(NULL));
	else
	{
		srand((int)fgetc(random_source));
		fclose(random_source);
	}

	return ( min + ((int)((double)rand() / ((double)RAND_MAX + 1) * (max))) );

}

float get_percentage(const int num, const int tot)
{
	return( (( float)num / (float)tot) * 100);
}


int question_not_asked(int question_number, Questiondata *questions)
{
	return questions->not_asked[question_number];
}

void ask_questions(Questiondata *questions)
{
	questions->not_asked = malloc(questions->numquestions * sizeof(char));
	/* Questions haven't been asked yet - set to true*/
	int i; for(i=0; i<questions->numquestions; i++)
	{
		questions->not_asked[i] = 1;
	}
	int question_no, answer, question_count = 0;
	int question_correct = 0;
	question_no = get_random(0, questions->numquestions);
	//printf("%d %d", question_no, question_not_asked(question_no, questions));
	while(question_count < questions->numquestions)
	{
		while( ! question_not_asked(question_no, questions) ) question_no = get_random(0, questions->numquestions);
		printf("Question %d: %s\n", question_count + 1, questions->question_text[question_no]);
		#if DEBUG > 0
		printf("Answer: %d\n", questions->question_answers[question_no]);
		#endif
		fscanf(stdin, "%d", &answer);
		if( questions->question_answers[question_no] == answer )
		{
			printf("Correct!\n");
			question_correct++;
		}
		else
			printf("Wrong answer.\n");

		questions->not_asked[question_no] = 0;
		question_count++;
	}
	printf("You scored %d out of %d: %.1f%%\n", question_correct, questions->numquestions, get_percentage(question_correct, questions->numquestions));


}

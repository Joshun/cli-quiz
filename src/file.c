#define fileerr1 { printf("Error: incorrect file header\n"); exit(1); }

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>

#include "quiz.h"

//#define MAX_LINE_LENGTH 3000


void add_newline(const char *filename)
{
	FILE *append_file = fopen(filename, "a");
	if( append_file == NULL)
	{
		perror(filename);
		exit(1);
	}
	fputc('\n', append_file);
	fclose(append_file);
}

void check_newline(FILE *datafile, const char *filename, char *datastore, long *file_size)
{

	if( datastore[*file_size - 1] != '\n' )
	{
		printf("File does not end with a newline, as required by the parser.\n");
		printf("Add it now? y/n\n");

		char choice = 0;
		scanf("%c", &choice);

		switch(choice)
		{
			case 'Y':
			case 'y':
				fclose(datafile);
				add_newline(filename);
				printf("Please re-run the program\n");
				exit(0);
				break;
			case 'N':
			case 'n':
				exit(1);
		}		
	}
	else
	{
		fclose(datafile);
	}
}

int get_max_length(const char *data, const int numlines)
{
	int i, index = 0, count;
	int lastlength = 0;
	
	for(i=0; i<(numlines + 1); i++)
	{
		count=0;
		while(data[index] != '\n')
		{
			count++;
			index++;
			//printf("%c", data[index]);
		}
		index++;
		
		if( count > lastlength )
			lastlength = count;
	}
	return lastlength;
}

void read_file(const char *filename, Questiondata *questions)
{
	FILE *datafile = fopen(filename, "r");
	char *datastore;

	if( datafile == NULL)
	{
		perror(filename);
		exit(1);
	}


	struct stat st;
	stat(filename, &st);
	long file_size = st.st_size;
	#if DEBUG > 0
	printf("File is %ld bytes long.", file_size);
	#endif
	datastore = malloc(file_size + 1);
	fread(datastore, 1, file_size, datafile);
	datastore[file_size] = '\0';
	check_newline(datafile, filename, datastore, &file_size);
	
	int first_line_count = 0;
	char currentchar = 0;
	
	while(currentchar != '\n')
	{
		currentchar = datastore[first_line_count];
		first_line_count++;
	}
	int start = first_line_count;
	char formatdata[first_line_count];
	
	int i;
	for(i=0; i<first_line_count; i++)
		formatdata[i] = datastore[i];
	formatdata[first_line_count] = 0;

	char checkstr[7];
	
	if( sscanf(formatdata, "%6s%d", checkstr, &questions->numquestions) < 2 )
	{
		fileerr1;
	}
	else
	{
		if(strcmp(checkstr, "total:") != 0)
			fileerr1;
	}
	
	questions->question_text = malloc(questions->numquestions);
	questions->question_answers = malloc( (questions->numquestions * sizeof(int)) );
	
	int index = start;
	int current_line = 0;
	int arraypos;
	
	int MAX_LINE_LENGTH = ( get_max_length(datastore, questions->numquestions) + 1 );
	
	#if DEBUG > 0
	printf("Max line length: %d", MAX_LINE_LENGTH);
	#endif

	char answer_read[MAX_LINE_LENGTH];
	printf("Loading quiz of %d question(s)...\n", questions->numquestions);
	
	while(current_line < questions->numquestions)
	{
		questions->question_text[current_line] = malloc(MAX_LINE_LENGTH);
		if( datastore[index] == '\n' ) index++;
		for(arraypos = 0; datastore[index] != ':'; index++)
		{
			questions->question_text[current_line][arraypos] = datastore[index];
			arraypos++;
		}
		/* Null terminate string */
		questions->question_text[current_line][arraypos] = '\0';
		index++;
		
		int init;
		for(init=0; init<MAX_LINE_LENGTH; init++) answer_read[init]=0;
		for(arraypos = 0; datastore[index] != '\n' && datastore[index] != '\0'; index++)
		{
			//printf("'%c'", datastore[index]);
			answer_read[arraypos] = datastore[index];
			arraypos++;
		}
		/* answer_read doesn't need terminating since it was initialised */
		#if DEBUG > 0
		printf("Question: %s\n", questions->question_text[current_line]);
		#endif
		questions->question_answers[current_line] = atoi(answer_read);
		#if DEBUG > 0
		printf("Answer: %s\n", answer_read);
		#endif
		current_line++;


	}
	
	ask_questions(questions);

	free(questions->question_answers);
	free(questions->not_asked);
	
	int freecount;
	for(freecount=0; freecount<questions->numquestions; freecount++)
	{
		free(questions->question_text[freecount]);
	}
	
	free(questions->question_text);
}

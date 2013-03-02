#define DEBUG 0

typedef struct
{
	int numquestions;
	int *question_answers;
	char **question_text;
	char *not_asked;
} Questiondata;

/* File I/O functions */
void add_newline(const char *filename);
void check_newline(FILE *datafile, const char *filename, char *datastore, long *file_size);
void read_file(const char *filename, Questiondata *questions);
int get_max_length(const char *data, const int numlines);

void ask_questions(Questiondata *questions);
int question_not_asked(int question_number, Questiondata *questions);
int get_random(const int min, const int max);
float get_percentage(const int num, const int tot);

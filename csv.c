#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "llist.h"

struct csv {
	int rowcount;
	int colcount;
	char** cols;
	char*** rows;
};

enum parsestate {
	STARTFL,
	STARTLN,
	QUOTE,
	TEXT,
	WHITESPACE,
	COMMA,
	ENDLN,
	ENDFL
};

struct csv_parse_results
{
	struct strarrllist* rows;
	int rowcount;
	int colcount;
	int endindex;
};

void csv_print(struct csv* file);
void print_strarr (char** arr, int size);
struct csv_parse_results* csv_parse (char* filestr, int start, int rowsToFetch);

int main(int argc, char const *argv[])
{
	// Read the file

	FILE *fp = fopen( "test.csv", "r" );

	int i = 0, c;

	char buffer[1024];

	while ( i < 1024 && (c = fgetc(fp)) != EOF )
	{
		buffer[i++] = (char)c;
	}

	if ( i < 1024 && ! feof(fp) )
	{
		fprintf( stderr, "Error reading.\n" );
	}
       
	fclose(fp);

	int filestrsize = i;

	char* filestr = (char*)malloc(sizeof(char) * filestrsize + 1);

	strcpy(filestr, buffer);

	// Parse it
	int hasHeaders = 1;

	char** headers;

	struct csv_parse_results* results = csv_parse(filestr, 0, -1);

	struct csv* file = (struct csv*)malloc(sizeof(struct csv));

	if ( hasHeaders == 1 )
	{
		headers = strarrllist_pop(results->rows);

		results->rowcount--;

		file->cols = headers;
	}

	file->rowcount = results->rowcount;
	file->colcount = results->colcount;
	
	file->rows = strarrllist_to_array(results->rows, results->rowcount);

	csv_print(file);

	if (hasHeaders == 1)
	{
		free(headers);
	}

	strarrllist_del(results->rows);
	free(results);
	free(file);
	free(filestr);

	return 0;
}

struct csv_parse_results* csv_parse (char* filestr, int start, int rowsToFetch)
{
	int beginindex = start, endindex = start;

	int collectCell = 0, collectRow = 0, rowcount = 0,
	quoted = 0, eof = 0, eol = 0, endingindex = 0;

	int colcount = -1;

	enum parsestate currstate = STARTFL;

	struct strarrllist* rows = strarrllist_create();
	struct strllist* currrow = strllist_create();

	char c;

	for ( int i = start; eof == 0; i++ )
	{
		c = filestr[i];

		if (c == ',' && quoted == 0)
		{
			if (currstate == TEXT)
			{
				endindex = i - 1;
			}

			collectCell = 1;
			currstate = COMMA;
		}
		else if (c == '\n' && quoted == 0)
		{
			if (currstate == TEXT)
			{
				endindex = i - 1;
			}

			eol = 1;

			collectCell = 1;
			collectRow = 1;
		}
		else if (c == '\0')
		{
			if (currstate == TEXT)
			{
				endindex = i - 1;
				collectCell = collectRow = 1;
			}

			eof = 1;
		}
		else if (c == '"')
		{
			if (quoted == 0)
			{
				beginindex = i+1;
				quoted = 1;
				currstate = TEXT;
			}
			else
			{
				endindex = i-1;
				quoted = 0;
				currstate = WHITESPACE;
			}
		}
		else if (currstate != WHITESPACE)
		{
			currstate = TEXT;
		} 

		if (collectCell == 1)
		{
			int size = (endindex - beginindex + 1);
			char* cell = (char*) malloc(sizeof(char) * size + 1);
			for ( int j = 0; j < size; j++ )
			{
				cell[j] = filestr[beginindex + j];
			}
			cell[size] = '\0';
			strllist_add(currrow, cell);

			collectCell = 0;

			endindex = beginindex = i + 1;		
		}

		if (collectRow == 1)
		{
			if (colcount == -1)
			{
				colcount = strllist_count(currrow);
			}

			char** row = strllist_to_array(currrow, colcount);
			strarrllist_add(rows, row);
			rowcount++;
			collectRow = 0;

			if (eof == 0)
			{
				currrow = strllist_create();
			}

			if (rowcount == rowsToFetch)
			{
				endingindex = i + 1;
				break;
			}
		}
	}

	struct csv_parse_results* results = (struct csv_parse_results*)malloc(sizeof(struct csv_parse_results));

	results->rows = rows;
	results->rowcount = rowcount;
	results->colcount = colcount;
	results->endindex = endingindex;

	return results;
}

void csv_print(struct csv* file)
{
	puts("Here is the csv.\nHeaders:");

	print_strarr(file->cols, file->colcount);

	puts("\nBody:");

	for (int i = 0; i < file->rowcount; i++)
	{
		print_strarr(file->rows[i], file->colcount);

		if ((i+1) < file->rowcount)
			puts("");
	}

	puts("\nEnd of csv.");
}

void print_strarr (char** arr, int size)
{
	for (int i = 0; i < size; i++)
	{
		printf("%s ", arr[i]);
	}
}
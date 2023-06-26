
#include <stdio.h>
#include "comic.h"
#include <stdlib.h>
#include <string.h>

int main( int argc, char* argv[] )
{

	//Creates and initializes comicList & buyList
	struct Comic_List comicList;
	initialize(&comicList);
	struct Comic_List buyList;
	initialize(&buyList);

	if ( argc != 3 )
	{
		fprintf(stderr, "Usage: project1 <input-command-file> <output-file>\n");
		exit(1);
	}
	
	FILE* command_file; //command file pointer

	command_file = fopen(argv[1], "r"); //opening file for reading
	if (command_file == NULL) 
	{
		printf("Sorry, can't read this file: %s", argv[1]); 
	}

    FILE* output_file; //output file pointer

	output_file = fopen(argv[2], "w");//opening file for writing
	if (output_file == NULL) 
	{
		printf("Sorry, can't read this file: %s", argv[2]); 
	}
    
	//Creates strings to hold command, data file, and csv file names
	char command[20]; 
	char data_file_name[100]; 
	FILE* new_csv;
	char csv_name[100];

    fscanf(command_file, "%s", command);
    while( !feof(command_file) ) //loops through command file and executes necessary functiosn
	{
		if (strcmp( "load", command ) == 0 )
		{
			fscanf(command_file, " %s\n", data_file_name);
			load(data_file_name, &comicList, output_file);
		}
		else if(strcmp( "buy", command ) == 0)
		{
			char buy_position[100];
			fscanf( command_file, "%[^\n]", buy_position);
			buy(buy_position, &comicList, &buyList, output_file);
		}
		else if(strcmp( "display", command) == 0)
		{
			display(&comicList, output_file);
		}
		else if(strcmp( "checkout", command) == 0)
		{
			fscanf(command_file, "%s", command);
			checkout(&buyList, output_file);
		}
		else if(strcmp( "save", command) == 0)
		{
			fscanf( command_file, " %[^\n]\n", csv_name);
			new_csv = fopen(csv_name, "w");
			save(&comicList, new_csv, output_file, csv_name);
			fclose(new_csv);
		}
		else if(strcmp("find", command ) == 0)
		{
			char find_position[100];
			fscanf( command_file, "%[^\n]", find_position);
			find(&comicList, find_position, output_file);
		}
		else if(strcmp("clear", command) == 0)
		{
			fgetc(command_file);
			clear(&comicList, output_file);
		}
		else if(strcmp("remove", command) == 0)
		{
			char remove_position[100];
			fscanf( command_file, " %[^\n]", remove_position);
			removeAt(&comicList, remove_position, output_file);
		}
		fscanf(command_file, "%s", command );
		
	}
	fclose(command_file);
	
	//Clears buyList & comicList
	clear(&buyList, output_file);
	clear(&comicList, output_file);
	fclose(output_file);
	//Frees comics in buyList and comicList
	free(buyList.comics);
	free(comicList.comics);
	return 0;
}

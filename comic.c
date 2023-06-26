/**
“As a Hokie, I will conduct myself with honor and integrity at all times. 
I will not lie, cheat, or steal, nor will I accept the actions of those who do.”*/
//Pranav Poodari

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include "comic.h"
#include <string.h>

// Initializes Comic_List with size 10 and count 0
void initialize( struct Comic_List* comicList )
{
    comicList->size = 10;
    comicList->comics = malloc(comicList->size * sizeof(struct Comic));
    comicList->count = 0;
}

//Initializes comic with individual fields
void initialize_comic(struct Comic* comic, char* date, char* code, char* publisher, char* title, char* cost)
{
    comic->date = calloc(strlen(date) + 1, sizeof(char));
    strcpy(comic->date, date);
    comic->code = calloc(strlen(code) + 1, sizeof(char));
    strcpy(comic->code, code);
    comic->publisher = calloc(strlen(publisher) + 1, sizeof(char));
    strcpy(comic->publisher, publisher);
    comic->title = calloc(strlen(title) + 1, sizeof(char));
    strcpy(comic->title, title);
    comic->cost = calloc(strlen(cost) + 1, sizeof(char));
    strcpy(comic->cost, cost);
}

//Doubles the size of a Comic_List 
void double_size(struct Comic_List* comicList)
{
    comicList->size = comicList->size * 2;
    comicList->comics = realloc(comicList->comics, comicList->size * sizeof(struct Comic));
}

//Reads in a data file and stores the data in comics which will then go into a Comic_List
void load(char* data_file_name, struct Comic_List* comicList, FILE* output_file)
{
    //Creating buffers
    fprintf(output_file, "Command: load %s\n", data_file_name);
    char date[1000] = {'\0'};
    char code[1000] = {'\0'};
    char publisher[1000] = {'\0'};
    char title[1000] = {'\0'};
    char cost[1000] = {'\0'};
    FILE* data_file; //data file pointer to store the data file from the command file 
    int small_count = 0;

    data_file = fopen(data_file_name, "r"); 

    //Checks if data file is null
	if (data_file == NULL) 
	{
	    printf("Sorry, can't read this file: %s\n", data_file_name); 
        return;
	}
    while ( !feof(data_file)) 
    {
        //Reads in each line
        date[0] = code[0] = publisher[0] = title[0] = cost[0] = '\0';
        fscanf(data_file, "%[^,],%[^,],%[^,],%[^,],%[^\n]", date, code, publisher, title, cost);
        fgetc(data_file);
        if ((strcmp(date, "DATE") != 0) && (strlen(date) > 1))
        {
            //Creates and initializes comic
            struct Comic comic;
            initialize_comic(&comic, date, code, publisher, title, cost);

            //Checks if comicList is full
            if (comicList->size == comicList->count)
            {
                double_size(comicList);
            }
            //Adds comic to Comic_List and updates count
            comicList->comics[comicList->count] = comic;
            comicList->count++;
            small_count++;

        }

    }
    fprintf(output_file, "\tNumber of comics: %d\n", small_count);
    small_count = 0;
	fclose(data_file);
}

void buy(char* buy_position, struct Comic_List* comicList, struct Comic_List* buyList, FILE* output_file)
{   
    fprintf(output_file, "Command: buy%s\n", buy_position);
    //Converts buy_position string to integer
    int buy_int;
    sscanf(buy_position, "%d", &buy_int);
    //Checks if buy_int is invalid
    if ((comicList->count - 1 < buy_int) || (buy_int < 0))
    {
        fprintf(output_file, "Buy: This index does not exist\n");
    }
    else
    {
        //Creates and initializes comic
        struct Comic comic;
        initialize_comic(&comic, comicList->comics[buy_int].date, 
            comicList->comics[buy_int].code, comicList->comics[buy_int].publisher,
            comicList->comics[buy_int].title, comicList->comics[buy_int].cost);
        
        //Checks if buyList is full
        if (buyList->count == buyList->size)
        {
            double_size(buyList);
        }
        //Adds comic to buyList and updates count
        buyList->comics[buyList->count] = comic;
        buyList->count++;
        fprintf(output_file, "Comic #%s added to purchase list\n", buy_position);

    }
}

//Displays comicList
void display(struct Comic_List* comicList, FILE* output_file)
{
    fprintf(output_file, "Command: display\n");
    //Checks if comicList is empty
    if (comicList->count == 0)
    {
        fprintf(output_file, "This list is currently empty\n");
    }
    else
    {
        //for loop to print each comic in comicList
        for(int i = 0; i < comicList->count; i++)
        {
            fprintf(output_file, "Comic Number: %d\n", i + 1);
            fprintf(output_file, "\tDate: %s\n", comicList->comics[i].date);
            fprintf(output_file, "\tCode: %s\n", comicList->comics[i].code);
            fprintf(output_file, "\tPublisher: %s\n", comicList->comics[i].publisher);
            fprintf(output_file, "\tTitle: %s\n", comicList->comics[i].title);
            fprintf(output_file, "\tCost: %s\n", comicList->comics[i].cost);
        }
    }
}

//Purchases every comic in buyList
void checkout(struct Comic_List* buyList, FILE* output_file)
{
    fprintf(output_file, "Command: checkout\n");
    fprintf(output_file, "Comics in Purchase List\n");
    //Initializes a double to store the price
    double price = 0.0;
    for(int i = 0; i < buyList->count; i++)
    {
        //Checks if comic has a price of AR
        if (strcmp( "AR", buyList->comics[i].cost) != 0)
        {
            //Adds price of individual comic to total
            double individual = 0.0;
            sscanf(buyList->comics[i].cost, "$%lf", &individual);
            price = price + individual;
        }        
        //Prints information
        fprintf(output_file, "Comic Number: %d\n", i + 1);
        fprintf(output_file, "\tDate: %s\n", buyList->comics[i].date);
        fprintf(output_file, "\tCode: %s\n", buyList->comics[i].code);
        fprintf(output_file, "\tPublisher: %s\n", buyList->comics[i].publisher);
        fprintf(output_file, "\tTitle: %s\n", buyList->comics[i].title);
        fprintf(output_file, "\tCost: %s\n", buyList->comics[i].cost);
    }
    //Prints subtotal, tax, and total
    fprintf(output_file, "Subtotal: $%.2lf\n", price);
    double tax = 0.05 * price;
    double total = 1.05 * price;
    fprintf(output_file, "Tax: $%.2lf\n", tax);
    fprintf(output_file, "Total: $%.2lf\n", total);
    //Clears buyList
    clear(buyList, output_file);
}

void save(struct Comic_List* comicList, FILE* output_file, FILE* other_output, char* csv_name)
{
    fprintf(other_output, "Command: save %s\n", csv_name);
    fprintf(output_file, "DATE,CODE,PUBLISHER,TITLE,PRICE\n");
    //Loops through comicList and prints data 
    for(int i = 0; i < comicList->count-1; i++)
    {
        fprintf(output_file, "%s,%s,%s,%s,%s\n", comicList->comics[i].date, comicList->comics[i].code,
        comicList->comics[i].publisher, comicList->comics[i].title, comicList->comics[i].cost);
        fflush(output_file);
    }
}

void find(struct Comic_List* comicList, char* find_position, FILE* output_file)
{
    fprintf(output_file, "Command: find%s\n", find_position);
    //Creates find_int and assigns it to value from find_position
    int find_int;
    sscanf(find_position, "%d", &find_int);
    //Checks if find_int is valid
    if ((comicList->count < find_int) || (find_int < 0))
    {
        fprintf(output_file, "There is no comic at index #%s in the list.\n", find_position);
    }
    else
    {
        fprintf(output_file, "\tDate: %s\n", comicList->comics[find_int].date);
        fprintf(output_file, "\tCode: %s\n", comicList->comics[find_int].code);
        fprintf(output_file, "\tPublisher: %s\n", comicList->comics[find_int].publisher);
        fprintf(output_file, "\tTitle: %s\n", comicList->comics[find_int].title);
        fprintf(output_file, "\tCost: %s\n", comicList->comics[find_int].cost);
    }
}

void removeAt(struct Comic_List* comicList, char* remove_position, FILE* output_file)
{
    fprintf(output_file, "Command: remove %s\n", remove_position);
    //Creates remove_int
    int remove_int;
    sscanf(remove_position, "%d", &remove_int);
    //Checks if remove_int is valid
    if (!(remove_int < 1))
    {
        remove_int = remove_int - 1;
    }
    if ((remove_int < 0) || (remove_int > comicList->count))
    {
        fprintf(output_file, "Comic at index %s was not removed\n", remove_position);
    }
    else
    {
        //Frees fields associated with comic to be removed
        free(comicList->comics[remove_int].date);
        free(comicList->comics[remove_int].code);
        free(comicList->comics[remove_int].publisher);
        free(comicList->comics[remove_int].title);
        free(comicList->comics[remove_int].cost);

        //Loops through comicList and shifts comics
        for (int i = remove_int; i < comicList->size - 1; i++) 
        {
            comicList->comics[i] = comicList->comics[i + 1];
        }
        //Updates count
        comicList->count--;
        fprintf(output_file, "Comic at index %s successfully removed\n", remove_position);
    }
}

void clear(struct Comic_List* comicList, FILE* output_file)
{
    fprintf(output_file, "Command: clear\n");
    //Loops through comicList and frees fields associated with each comic
    for (int i = 0; i < comicList->count; i++)
    {
        free(comicList->comics[i].date);
        free(comicList->comics[i].code);
        free(comicList->comics[i].publisher);
        free(comicList->comics[i].title);
        free(comicList->comics[i].cost);
    }
    //Resets count to 0
    comicList->count = 0;
}

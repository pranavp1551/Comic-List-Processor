/**
“As a Hokie, I will conduct myself with honor and integrity at all times. 
I will not lie, cheat, or steal, nor will I accept the actions of those who do.”*/
//Pranav Poodari

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

struct Comic_List
{
	struct Comic* comics;
	int size;
	int count;
};

struct Comic
{
    char* date;
    char* code;
    char* publisher;
    char* title;
    char *cost;
};

void initialize( struct Comic_List* comicList );


void load(char* data_file_name, struct Comic_List* comicList, FILE* output_file);

void buy(char* buy_position, struct Comic_List* comicList, struct Comic_List* buyList, FILE* output_file);

void double_size(struct Comic_List* comicList);

void display(struct Comic_List* comicList, FILE* output_file);

void checkout(struct Comic_List* buyList, FILE* output_file);

void save(struct Comic_List* comicList, FILE* output_file, FILE* other_output, char* csv_name);

void find(struct Comic_List* comicList, char* find_position, FILE* output_file);

void removeAt(struct Comic_List* comicList, char* remove_position, FILE* output_file);

void clear(struct Comic_List* comicList, FILE* output_file);

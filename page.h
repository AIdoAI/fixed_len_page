#ifndef __PAGE_H_INCLUDED__
#define __PAGE_H_INCLUDED__

#include <stdlib.h>
#include <iostream>
#include <stdio.h>
#include <vector>
#include <string.h>
#include <vector>
#include "serialization.h"

#define OFFSET_SIZE sizeof(int)
#define NUM_ATTRS 100 // number of attributes
#define ATTR_LEN  10 //  lenght of each attribute
#define SLOT_SIZE NUM_ATTRS * ATTR_LEN

typedef std::vector<char> FlagArray;

typedef struct Page{
    std::vector<Record> *data;
    int page_size;
    int slot_size;
    FlagArray* slots_flags;
} Page;

typedef struct Slot{
    char used_flag = '0';  //0 if not occupied
	char record[NUM_ATTRS * ATTR_LEN];
} Slot;

/**
 * Initializes a page using the given slot size
 */
void init_fixed_len_page(Page* page, int page_size, int slot_size);
 
/**
 * Calculates the maximal number of records that fit in a page
 */
int fixed_len_page_capacity(Page* page);
 
/**
 * Calculate the free space (number of free slots) in the page
 */
int fixed_len_page_freeslots(Page *page);
 
/**
 * Add a record to the page
 * Returns:
 *   record slot offset if successful,
 *   -1 if unsuccessful (page full)
 */
int add_fixed_len_page(Page *page, Record *r);
 
/**
 * Write a record into a given slot.
 */
void write_fixed_len_page(Page *page, int slot, Record *r);
 
/**
 * Read a record from the page from a given slot.
 */
void read_fixed_len_page(Page *page, int slot, Record *r);


#endif
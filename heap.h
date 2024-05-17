#ifndef __HEAP_H_INCLUDED__
#define __HEAP_H_INCLUDED__

#include <stdlib.h>
#include <iostream>
#include <stdio.h>
#include <vector>
#include <string.h>
#include <vector>
#include "serialization.h"
#include "page.h"

#define MAXLINE   1500
#define OFFSET_LEN     8 // bytes of page_offset
#define FREESPACE_LEN  4 // bytes of freespace
#define TOTAL_LEN 12

typedef struct Heapfile{
    FILE *file_ptr;
    int page_size;
    int number_of_page;
} Heapfile;

/*
 * Allocate another page in the heapfile.  This grows the file by a page.
 * Every page p has an entry in the heap directory of (page_offset, freespace).
 *  The page ID of p can be the index of its entry in the directory. 
 * We call this: ID(p).
 */

typedef struct Page_Entry{
	unsigned long page_offset; 
	int freespace;  
} Page_Entry;


typedef int PageID;
 
typedef struct {
    int page_id;
    int slot;
} RecordID;

int read_check(void *ptr, int size, int count, FILE *file);
int read_offset(FILE *file);
int read_offset(FILE *file);

/**
 * Initalize a heapfile to use the file and page size given.
 */
void init_heapfile(Heapfile *heapfile, int page_size, FILE *file);
/**
 * Allocate another page in the heapfile.  This grows the file by a page.
 */
PageID alloc_page(Heapfile *heapfile);
/**
 * Read a page into memory
 */
void read_page(Heapfile *heapfile, PageID pid, Page *page);
/**
 * Write a page from memory to disk
 */
void write_page(Page *page, Heapfile *heapfile, PageID pid);

int fixed_dir_page_capacity(Heapfile *heapfile);

/*
The central functionality of a heap file is enumeration of records.
Implement the record iterator class.
*/
class RecordIterator {
    private:
    Heapfile *heapfile;
    Page *curPage;
    public:
    RecordIterator(Heapfile *heapfile);
    Record next();
    bool hasNext();
};




#endif

#include "heap.h"


int read_check(void *ptr, int size, int count, FILE *file) {
    int result;
    if ((result = fread(ptr, size, count, file)) != 1) {
        fputs("Read error\n",stderr); 
    }
    return result;
}

int write_check(const void *ptr, size_t size, size_t count, FILE *file) {
    int result;
    if ((result = fwrite(ptr, size, count, file)) != 1) {
        fputs("Write error\n",stderr); 
    }
    return result;
}

int read_offset(FILE *file) {
    int *buffer = (int *) malloc(sizeof(int));
    if (buffer == NULL) {
        fputs("Memory error\n", stderr); 
        exit(-1);
    }

    if (read_check(buffer, sizeof(int), 1, file) != 1) {
        free(buffer);
        return 0;
    }

    int result = *buffer;
    free(buffer);

    return result;
}


/**
 * Initalize a heapfile to use the file and page size given.
 */
void init_heapfile(Heapfile *heapfile, int page_size, FILE *file){
    heapfile->number_of_page = 0;
    heapfile->page_size = page_size;
    Page* page = (Page*)malloc(sizeof(Page));
    init_fixed_len_page(page, heapfile->page_size,sizeof(Slot));
    fwrite(heapfile, sizeof(Heapfile), 1, file);
    fwrite(page, sizeof(Page), 1, file);
    fwrite(page->data, page_size, 1, file);

    free(page->data);

    heapfile->file_ptr = file;
}

int fixed_dir_page_capacity(Heapfile *heapfile){
     return heapfile->page_size / (OFFSET_LEN + FREESPACE_LEN);
}



/*
int fseek(FILE *fp, long int offset, int whence)
SEEK_SET	SEEK_SET – It moves file pointer position to the beginning of the file.
SEEK_CUR	SEEK_CUR – It moves file pointer position to given location.
SEEK_END	SEEK_END – It moves file pointer position to the end of file.
*/
int alloc_new_dir_page(FILE* file, int page_size, bool dir_flag){
//int ftell(FILE *stream) returns the current file position of the given stream
   int current = ftell(file);
   fseek(file, 0, SEEK_END);
   int offset = ftell(file);
   Page* page = (Page*)malloc(sizeof(Page));
   init_fixed_len_page(page, page_size, sizeof(int));
   if(dir_flag){
    fwrite(page, sizeof(Page), 1, file);
    fwrite(page->data, page_size, 1, file);

   }else{
    


   }



    return 0;

}

/*
We are to implement a directory based heap file
 in which we have directory pages (organized as a linked list), 
 and data pages that store records.
*/
/**
 * Allocate another page in the heapfile.
 * This grows the file by a page.
 * When added a new page: 
 * read a directory page from heapfile (use a linked list to store the directory.)
 * 1. if directory page has freespace:
 * there is free slot, assign a page entry and update
 * 2. if directory page is full:
 * create a new directory page in the linked list to heapfile
 * 
 */


PageID alloc_page(Heapfile *heapfile){

    //Page_Entry *dir_page_entry, *data_page_entry;
    int page_size = heapfile->page_size;
    PageID page_id = heapfile->number_of_page;
    FILE* file = heapfile->file_ptr;
    //capacity of the directory (number of pages stored)
    int dir_page_cap = fixed_dir_page_capacity(heapfile);
    //directory order in linkedlist
    int dir_order = page_id/dir_page_cap;
    //page order in each directory
    int page_order = page_id % dir_page_cap;

    fseek(file, sizeof(Heapfile), SEEK_SET);
    for(int i = 0; i < dir_page_cap; ++i){
        fseek(file, sizeof(Page), SEEK_CUR);
        int position = ftell(file);
        int offset = read_offset(file);



    }

    


}
/**
 * Read a page into memory
 */
void read_page(Heapfile *heapfile, PageID pid, Page *page){
    fseek(heapfile->file_ptr, pid * heapfile->page_size, SEEK_SET);
	fread(page->data, 1, heapfile->page_size, heapfile->file_ptr);
	fseek(heapfile->file_ptr, 0, SEEK_SET);

}
/**
 * Write a page from memory to disk
 */
void write_page(Page *page, Heapfile *heapfile, PageID pid){
    fseek(heapfile->file_ptr, pid * heapfile->page_size, SEEK_SET);

	fwrite(page->data, 1, heapfile->page_size, heapfile->file_ptr);
	fflush(heapfile->file_ptr);
	fseek(heapfile->file_ptr, 0, SEEK_SET);


}
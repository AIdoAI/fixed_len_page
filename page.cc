#include "page.h"
/**
 * Initializes a page using the given slot size
 */
void init_fixed_len_page(Page *page, int page_size, int slot_size){
    page->page_size = page_size;
    page->slot_size = slot_size;
    std::vector<Record> *data = new std::vector<Record>();
    page->slots_flags = new FlagArray;
    for(int i = 0; i < fixed_len_page_capacity(page); ++i){
        Record* r = new Record();
        page->data->push_back(*r);
        page->slots_flags->push_back('0');
        delete r;
    }
}
 

/**
 * Calculates the maximal number of records that fit in a page
 */
int fixed_len_page_capacity(Page *page){
     return page->page_size / page->slot_size;
}
 
/**
 * Calculate the free space (number of free slots) in the page
 */
int fixed_len_page_freeslots(Page *page){
    int num = 0;
    Slot* slot_pointer;
    for(int i = 0; i < fixed_len_page_capacity(page); ++i){
        slot_pointer = (Slot*)((char*)page->data+i*page->slot_size);
        if(slot_pointer->used_flag == '0') num++;
    }
    return num;
}
 
/**
 * Add a record to the page
 * Returns:
 *   record slot offset if successful,
 *   -1 if unsuccessful (page full)
 */
int add_fixed_len_page(Page *page, Record *r){
    if(fixed_len_page_freeslots(page) == 0) return -1;
    Slot* slot_pointer;
    for(int i = 0; i < fixed_len_page_capacity(page); ++i){
        slot_pointer = (Slot*)((char*)page->data+i*page->slot_size);
        if(slot_pointer->used_flag == '0'){
            slot_pointer->used_flag = '1';
            fixed_len_write(r, slot_pointer->record);
            return i;
        }
    }
    return -1;

}
 
/**
 * Write a record into a given slot.
 */
void write_fixed_len_page(Page *page, int slot, Record *r){
    if(slot < 0 || slot >= fixed_len_page_capacity(page)){
        printf("Slot is out of range.\n");
    }
    Slot* slot_pointer = (Slot*)((char*) page->data+slot*page->slot_size);
    slot_pointer->used_flag = '1';
    fixed_len_write(r, slot_pointer->record);
}
 
/**
 * Read a record from the page from a given slot.
 */
void read_fixed_len_page(Page *page, int slot, Record *r){
    *r = page->data->at(slot);
}
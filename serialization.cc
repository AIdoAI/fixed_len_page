#include "serialization.h"
int fixed_len_sizeof(Record *record){
       int size = 0;
    for (auto i = record->begin(); i != record->end(); ++i) {
        size += strlen(*i);
    }
    return size;
}

/**
 * Serialize the record to a byte array to be stored in buf.
 */
void fixed_len_write(Record *record, char *buf){
    for (auto i = record->begin(); i != record->end(); ++i) {
        strcat(buf, *i);
    }
}

/**
 * Deserializes `size` bytes from the buffer, `buf`, and
 * stores the record in `record`.
 */
void fixed_len_read(char *buf, int size, Record *record){
    char* store = (char*) buf;
    for(int i = 0; i < size; i+=10){
        char* temp = (char*)malloc(11);
        strncpy(temp, store+i, 10);
        record->push_back(temp);

    }
}



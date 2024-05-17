#ifndef __SERIALIZATION_H_INCLUDED__
#define __SERIALIZATION_H_INCLUDED__

#include <stdlib.h>
#include <iostream>
#include <stdio.h>
#include <vector>
#include <string.h>

#include <vector>
typedef const char* V;
typedef std::vector<V> Record;

const int record_size = 1000;


/**
 * Compute the number of bytes required to serialize record
 */
int fixed_len_sizeof(Record *record);

/**
 * Serialize the record to a byte array to be stored in buf.
 * void: generic 
 */
void fixed_len_write(Record *record, char *buf);

/**
 * Deserializes `size` bytes from the buffer, `buf`, and
 * stores the record in `record`.
 */
void fixed_len_read(char *buf, int size, Record *record);

#endif
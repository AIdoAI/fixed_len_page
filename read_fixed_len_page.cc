#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/timeb.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <sys/timeb.h>
#include "serialization.h"
#include "page.h"
using namespace std;


/*
Write another program to load the page_file, and print out all records in the page in CSV format.

$ read_fixed_len_page <page_file> <page_size>
*/
int main(int argc, char* argv[]){
    if(argc != 3){
        cerr << "Standard Input: read_fixed_len_page <page_file> <page_size>\n";
        exit(-1);
    }
    std::string page_file(argv[1]);
    fstream file (page_file, ios::in);
    
    int page_size = stoi(argv[2]);
    if(page_size <= 0){
        cerr << "Page size should be an integer bigger than 0.\n";
        exit(-1);
    }

    Page page;
    char count[page_size];
    while(file.read(count, page_size)){
         init_fixed_len_page(&page, page_size, record_size);
         for(int i = 0; i < fixed_len_page_capacity(&page); ++i){
            Record* record = new Record;
            fixed_len_read(count+(i*record_size), record_size, record);
            write_fixed_len_page(&page, i, record);

            for(Record::iterator i = record->begin(); i != record->end(); ++i){
                  if (i + 1 == record->end()) {
                        std::cout << *i;
                } else {
                        std::cout << *i << ",";
                    }
                }
                std::cout << "\n";

            }

         }
         file.close();
         return 0;
    }
    
  

    

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
Load as many records from a comma separated file to fill up a page, 
and append the page to a file. 
Repeat until all the records in the CSV files are written to the page file.
 Your program should follow the following syntax, 
 and produce the output containing record count, page count, and time took, 
 similar to as follows:
 $ write_fixed_len_pages <csv_file> <page_file> <page_size>

NUMBER OF RECORDS: 1000
NUMBER OF PAGES: 32
TIME: 43 milliseconds
*/
int main(int argc, char* argv[]){
    if(argc != 4){
        cerr << "Standard Input: write_fixed_len_pages <csv_file> <page_file> <page_size>\n";
        exit(-1);
    }
    /*
    FILE* csv_file = fopen(argv[1], "r");
    if(csv_file == NULL){
        cerr << "No such csv file exists.\n";
        exit(-1);
    }

    FILE* page_file = fopen(argv[2], "w");
      if(page_file == NULL){
        cerr << "No such page file exists.\n";
        exit(-1);
    }
    */
    std::string csv_file(argv[1]);
    std::string page_file(argv[2]);
    int page_size = stoi(argv[3]);
    if(page_size <= 0){
        cerr << "Page size should be an integer bigger than 0.\n";
        exit(-1);
    }
    
    Page page;
    Slot* slot_pointer;
    fstream file (csv_file, ios::in);
    std::string line, word;
    int new_page_flag = 1;

    std::ofstream write_file;
    write_file.open(page_file, std::ios::out | std::ios::binary);


    int records_num = 0;
    int pages_num = 0;
    struct timeb t_start, t_end;
    ftime(&t_start);
    unsigned long start_ms = t_start.time * 1000 + t_start.millitm;

        while(std::getline(file, line)){
            std::stringstream str(line);
            Record record;
            while(getline(str, word, ',')){
                char *temp = (char *) malloc(11);
                std::strncpy(temp, word.c_str(), 11);
                record.push_back(temp);   
            }
        if(new_page_flag == 1){
            init_fixed_len_page(&page, page_size, fixed_len_sizeof(&record));
            pages_num += 1;
        }
        if(add_fixed_len_page(&page, &record) == -1){ //already full, need to add new page
            new_page_flag = 1;
            }
            else{
                new_page_flag = 0;
                }
            records_num += 1;
        if(new_page_flag == 1){
                write_file.write((const char *)page.data, page.page_size);
                init_fixed_len_page(&page, page_size, fixed_len_sizeof(&record));
                add_fixed_len_page(&page, &record);
                new_page_flag = 0;
                pages_num += 1;

        }
        }

    if(new_page_flag != 1){
        write_file.write((const char *)page.data, page.page_size);

    }
        
    write_file.close();
   
    
    ftime(&t_end);
    unsigned long end_ms = t_end.time * 1000 + t_end.millitm;


    std::cout << "NUMBER OF RECORDS: " << records_num << "\n";
    std::cout << "NUMBER OF PAGES: " << pages_num << "\n";
    std::cout << "TIME: " << end_ms - start_ms << " milliseconds\n";



    return 0;
}

//
//  main.cpp
//  CSVReader
//
//  Created by Fizi Yadav on 11/3/15.
//  Copyright © 2015 Fizi Yadav. All rights reserved.
//

#include <algorithm>                              // for std::find
#include <iostream>                               // for std::cout
#include <sys/mman.h>
#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>
#include <assert.h>


size_t getFilesize(const char* filename) {
    /**
     * get the size of the file, Needed before calling mmap
     * @param filename a const char pointer.
     * @return file size in size_t
     */
    struct stat st;
    stat(filename, &st);
    return st.st_size;
}

size_t read(const char* filename){
    /**
     * read a file using mmap
     * @param filename a const char pointer.
     * @return file size read in size_t
     */
    // get file size.
    size_t filesize = getFilesize(filename);
    // open file
    int fd = open(filename, O_RDONLY, 0);
    if(fd == -1){
        std::cout<<"There was an opening the file\n";
        return 1;
    }
    // execute mmap
    void* mmappedData = mmap(NULL, filesize, PROT_READ, MAP_PRIVATE, fd, 0);
    if(mmappedData == NULL){
        std::cout<<"There was an error reading the file\n";
        return 1;
    }
    // write the mmapped data to stdout (= FD #1)
    write(1, mmappedData, filesize);
    // cleanup
    int rc = munmap(mmappedData, filesize);
    if(rc != 0){
        std::cout<<"There was an error removing the file mapping\n";
        return 1;
    }
    close(fd);
    return filesize;
    
}

int write(const char* filename){
    /**
     * write to a file
     * @param filename a const char pointer.
     * @return 0 or 1 to signify success or failure
     */
    
    int filedesc = open(filename, O_WRONLY | O_APPEND);
    if(filedesc < 0){
        std::cout<<"There was an opening the file\n";
        return 1;
    }
    
    if(write(filedesc,"This will be output to testfile.txt\n", 36) != 36)
    {
        std::cout<<"There was an error writing to testfile.txt\n";
        return 1;
    }
    
    return 0;
    
}

int main(int argc, const char * argv[]) {
    read("test.csv");
    return 0;
    
}



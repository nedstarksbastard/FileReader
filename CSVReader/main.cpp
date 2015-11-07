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
    struct stat st;
    stat(filename, &st);
    return st.st_size;
}

int main(int argc, const char * argv[]) {
    // insert code here...
    size_t filesize = getFilesize("Users/fizi/Documents/XCode/CSVReader/CSVReader/test.csv");
    //Open file
    int fd = open("Users/fizi/Documents/XCode/CSVReader/CSVReader/test.csv", O_RDONLY, 0);
    assert(fd != -1);
    //Execute mmap
    void* mmappedData = mmap(NULL, filesize, PROT_READ, MAP_PRIVATE, fd, 0);
    assert(mmappedData != NULL);
    //Write the mmapped data to stdout (= FD #1)
    write(1, mmappedData, filesize);
    //Cleanup
    int rc = munmap(mmappedData, filesize);
    assert(rc == 0);
    close(fd);
}

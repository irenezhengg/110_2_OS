#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>

using namespace std;

int main(int argc, char* argv[]){
    unsigned int address, pageNumber, offset;
    unsigned int pageSize = pow(2, 12);

    if(argc != 2) {
        cout << "Please enter the virtual address." << endl;
        return 1;
    }

    address = atoi(argv[1]);

    cout << "The address " << address << " contains:" << endl;

    pageNumber = address / pageSize;
    offset = address % pageSize;

    cout << "page number: " << pageNumber << endl;
    cout << "offset: " << offset << endl;

    return 0;
}

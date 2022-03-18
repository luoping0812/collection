#include <iostream>

#include <stdlib.h>
#include <unistd.h>

using namespace std;

void * getmemory(int size)
{
    return ::malloc(size);
}

int main(int argc, char const *argv[])
{
    {
        void *p = getmemory(1024 * 1024); 
    }

    {
        char p[10];
        cout << *p << endl;
    }

    {
        char *p = new char;
        free(p);
    }
 
    {
        char *p = new char;
        delete p;
    }

    {
        char *p = new char;
        delete p;
        cout << *p << endl;
    }
 
    return 0;
}

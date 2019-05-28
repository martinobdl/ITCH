#include <stdio.h>
#include <iostream>
#include <netinet/in.h>

int main()
{
    const char a[2] = {'\x09','\x64'};
    unsigned b = *((unsigned int *)a);
    std::cout << b << std::endl;
    std::cout << ntohs(b);
    
}

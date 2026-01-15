#include <stdio.h>
#include <string.h>

struct Box {
    char buffer[8];         
    int secret_code;     
};

int main()
{
    struct Box b;
    b.secret_code = 0;
    printf("%X\n",b.secret_code);
    strcpy(b.buffer, "12345678ABCD");
    printf("%X\n",b.secret_code);

    return 0;
}
/*
The value of secret code was initalized right after buffer in the stack
That means that when strcopy writes charcters and goes over the 8 bytes 
alocated it will overflow and write over the secret code we assigned
*/
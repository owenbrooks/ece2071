#include <stdio.h>
#include <unistd.h>

#define BUFLEN 5

void readMyData()
{
    char mybuff[BUFLEN];
    while (1)
    {
        int r = read(0, mybuff, BUFLEN);
        if (r <= 0)
            return;
        mybuff[r] = 0;
        printf("You entered: %s\n\n", mybuff);
        return;
    }
}

int main()
{
    readMyData();

    return 0;
}

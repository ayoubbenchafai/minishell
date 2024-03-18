#include <signal.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

void ft_handle(int sig)
{

    exit(0);
}
void ctrl_d(int sig)
{
    printf("ctrl + d\n");
    exit(0);
}

//  SIGINT ==>ctrl + c
int main()
{
    signal(SIGQUIT, ctrl_d);
    while (1)
    {
        printf("-->\n");
        sleep(1);
    }
    return (0);
}
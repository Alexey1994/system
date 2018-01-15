#include <windows.h>
#include "thread.h"


procedure a()
{
    for(;;)
    {
        printf("a");
        sleep_thread(1);
    }
}


procedure b()
{
    for(;;)
    {
        printf("b");
        sleep_thread(1);
    }
}


int main()
{
    printf("\nthread ID %d\n", run_thread(a, 0));
    printf("\nthread ID %d\n", run_thread(b, 0));
    run_thread(a, 0);

    for(;;);
        return 0;
}

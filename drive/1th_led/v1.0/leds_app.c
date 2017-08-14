#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>

#define msleep(x) usleep(x*1000)

int main(int argc, char **argv)
{
    int fd[4];
    int val = 0;
    int i = 0;
    //const char *dev[] = {"/dev/ti_led0", "/dev/ti_led1", "/dev/ti_led2", "/dev/ti_led3"};
    const char *dev[] = {"/dev/ti_led2", "/dev/ti_led0", "/dev/ti_led3", "/dev/ti_led1"};

    for(i=0; i<4; i++)
    {
        fd[i] = open(dev[i], O_RDWR);
        if (fd[i] < 0)
        {
            printf("can't open %s\n", *dev[i]);
            return 0;
        }
    }

    //leds off all.
    for(i=0; i<4; i++)
    {
        write(fd[i], &val, 4);
    }	

    //flicker leds.
    while(1)
    {
        val = !val;
        for(i=0; i<4; i++)
        {
            write(fd[i], &val, 4);
            msleep(300);
        }	
    }
}






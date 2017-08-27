#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

#define msleep(x) usleep(x*1000)

/*
 * ./rtc_app w 2017 08 25 18 36 20
 * ./rtc_app r [times]
*/
struct rtc_struct {
	int year;
	int month;
	//int week;
	int day;
	int hour;
	int minute;
	int second;
};
struct rtc_struct set_time, rtc_time;

int main(int argc, char **argv)
{
    int fd;
    int i;
  
    fd = open("/dev/ti_rts0", O_RDWR);
    if (fd < 0)
    {
        printf("can't open /dev/ti_rts0.\n");
        return 0;
    }

    if(strcmp(argv[1], "w") == 0 && argc == 8)
    {
        set_time.year   = atoi(argv[2]);
        set_time.month  = atoi(argv[3]);
        set_time.day    = atoi(argv[4]);
        set_time.hour   = atoi(argv[5]);
        set_time.minute = atoi(argv[6]);
        set_time.second = atoi(argv[7]);
        
        write(fd, &set_time, sizeof(set_time));  
        printf("write ok\n");
    }
    else if(strcmp(argv[1], "r") == 0)
    {
        if(argv[2] == NULL) 
            i = 999;
        else 
            i = atoi(argv[2]);
        
        do{
            read(fd, &rtc_time, sizeof(rtc_time));
            printf("\n\rcurrent_time is:\n\r\%d-%d-%d %d:%d:%d\n\r",\
            rtc_time.year+2000,rtc_time.month,rtc_time.day,rtc_time.hour,rtc_time.minute,rtc_time.second);
            printf("read ok\n");
            msleep(1000);  
            i--;
        }
        while(i);
    }
    
    close(fd);
    
    return 0;
}






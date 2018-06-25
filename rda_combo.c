#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/ioctl.h>

#define RDA_BT_IOCTL_MAGIC 'u'
#define RDA_WIFI_STA_MODE_IOCTL                _IO(RDA_BT_IOCTL_MAGIC ,0x20)
#define RDA_WIFI_SOFTAP_MODE_IOCTL             _IO(RDA_BT_IOCTL_MAGIC ,0x21)

void main(int argc, char *argv[])
{
	int fd = open("/dev/rdacombo", O_RDWR);
	ioctl(fd, RDA_WIFI_SOFTAP_MODE_IOCTL);
	printf("hello world\n");
	close(fd);
}

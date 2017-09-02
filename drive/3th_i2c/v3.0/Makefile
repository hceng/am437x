KERN_DIR = /home/hceng/ti-processor-sdk-linux-am437x-evm-01.00.00.03/board-support/linux-3.14.43+gitAUTOINC+875c69b2c3-g875c69b

all:
	make ARCH=arm CROSS_COMPILE=arm-linux-gnueabihf- -C $(KERN_DIR) M=`pwd` modules 

clean:
	make ARCH=arm CROSS_COMPILE=arm-linux-gnueabihf- -C $(KERN_DIR) M=`pwd` modules clean
	rm -rf modules.order

obj-m	+= at24cxx_drv.o

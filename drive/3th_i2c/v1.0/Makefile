KERN_DIR = /home/hceng/ti-processor-sdk-linux-am437x-evm-01.00.00.03/board-support/linux-3.14.43+gitAUTOINC+875c69b2c3-g875c69b

OUT_FILE_NAME = at24cxx

all:
	make ARCH=arm CROSS_COMPILE=arm-linux-gnueabihf- -C $(KERN_DIR) M=`pwd` modules 

clean:
	make ARCH=arm CROSS_COMPILE=arm-linux-gnueabihf- -C $(KERN_DIR) M=`pwd` modules clean
	rm -rf modules.order 

obj-m	+= $(OUT_FILE_NAME)_drv.o $(OUT_FILE_NAME)_dev.o

app:
	arm-linux-gnueabihf-gcc  -o app_$(OUT_FILE_NAME) app_$(OUT_FILE_NAME).c 
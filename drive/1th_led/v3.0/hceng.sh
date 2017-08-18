#!/bin/bash

myPath="/media/hceng/rootfs/" 
RED_COLOR='\E[1;31m'         #红
GREEN_COLOR='\E[1;32m'       #绿
YELOW_COLOR='\E[1;33m'       #黄
BLUE_COLOR='\E[1;34m'        #蓝
PINK='\E[1;35m'              #粉红
RES='\E[0m'                  #END


function diff_time()
{
    local current_time=`date +%s` 
    local file_time=`stat -c %Y /media/hceng/rootfs/boot/devicetree-zImage-am437x-sk-evm.dtb`
    local diff_time=$(($current_time-$file_time))
    
    echo "current_time:" `date -d "1970-01-01 UTC $current_time seconds" "+%F %T"`
    echo "file_time:   " `date -d "1970-01-01 UTC $file_time seconds" "+%F %T"`

    if [ $diff_time -gt 4 ];then  
       echo -e "${RED_COLOR}======DTB time ERROR!======${RES}"  
    else
       echo -e "${GREEN_COLOR}======DTB time OK!======${RES}" 
    fi  
}

#生成DTB
function creat_dtb()
{
    sudo rm /home/hceng/ti-processor-sdk-linux-am437x-evm-01.00.00.03/board-support/linux-3.14.43+gitAUTOINC+875c69b2c3-g875c69b/arch/arm/boot/dts/*.dtb
    sudo rm /media/hceng/rootfs/boot/devicetree-zImage-am437x-sk-evm.dtb
    cd /home/hceng/ti-processor-sdk-linux-am437x-evm-01.00.00.03/ &&make linux-dtbs && cd -  
    sudo cp  /home/hceng/ti-processor-sdk-linux-am437x-evm-01.00.00.03/board-support/linux-3.14.43+gitAUTOINC+875c69b2c3-g875c69b/arch/arm/boot/dts/am437x-sk-evm.dtb /media/hceng/rootfs/boot/devicetree-zImage-am437x-sk-evm.dtb
    echo -e "${YELOW_COLOR}-------------------------------------------------${RES}"
	sync
}

#判断U盘路径是否存在；
#存在则生成DTB、拷贝，不存在则提示报错

if [ ! -d "$myPath" ];then  
  echo -e  "${RED_COLOR}======Check USB Disk!======${RES}"	
else
	creat_dtb
    diff_time    
fi  
sync
exit

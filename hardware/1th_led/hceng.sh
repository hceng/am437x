#!/bin/bash

#170722�������ж�U��
#170724������echo�����ɫ

myPath="/mnt/hgfs/windows/"  #���������"�ļ�����"WindowsU�̵�·��
RED_COLOR='\E[1;31m'         #��
GREEN_COLOR='\E[1;32m'       #��
YELOW_COLOR='\E[1;33m'       #��
BLUE_COLOR='\E[1;34m'        #��
PINK='\E[1;35m'              #�ۺ�
RES='\E[0m'                  #END

#����MLO
function creat_MLO()
{
	rm -f /mnt/hgfs/windows/MLO
	make clean 
	make
	gcc  ./image_tool/tiimage.c  -o  tiimage.out
	./tiimage.out   0x40300000    MMCSD    am437x_hardware.bin   /mnt/hgfs/windows/MLO  
	rm   -f *.dis  *.bin  *.o  *_elf tiimage.out
	ls /mnt/hgfs/windows/MLO -l && echo -e  "${GREEN_COLOR}======MLO OK!======${RES}" || echo -e  "${RED_COLOR}======MLO ERROR!======${RES}"
	sync
}

#�ж�U��·���Ƿ���ڣ�
#����������MLO������������������ʾ����
if [ ! -d "$myPath" ];then  
  echo -e  "${RED_COLOR}======Check USB Disk!======${RES}"	
else
	creat_MLO	 
fi  
sync
exit

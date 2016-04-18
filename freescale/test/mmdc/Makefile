CC = /home/wangqiang/work/yocto/fsl-release-bsp/build-fb/tmp/sysroots/x86_64-linux/usr/bin/cortexa9hf-vfp-neon-poky-linux-gnueabi/arm-poky-linux-gnueabi-gcc
CFLAGS = \
-I/home/wangqiang/work/yocto/fsl-release-bsp/build-fb/tmp/sysroots/imx6qsabresd/usr/include      \
-I/home/wangqiang/work/yocto/fsl-release-bsp/build-fb/tmp/work/imx6qsabresd-poky-linux-gnueabi/imx-test/1_3.10.53-1.1.0-r0/imx-test-3.10.53-1.1.0/include  \
-I/home/wangqiang/work/yocto/fsl-release-bsp/build-fb/tmp/sysroots/imx6qsabresd/usr/src/kernel/include/uapi     \
-I/home/wangqiang/work/yocto/fsl-release-bsp/build-fb/tmp/sysroots/imx6qsabresd/usr/src/kernel/include        \
-I/home/wangqiang/work/yocto/fsl-release-bsp/build-fb/tmp/sysroots/imx6qsabresd/usr/src/kernel/arch/arm/include       \
-I/home/wangqiang/work/yocto/fsl-release-bsp/build-fb/tmp/sysroots/imx6qsabresd/usr/src/kernel/drivers/mxc/security/rng/include   \
-I/home/wangqiang/work/yocto/fsl-release-bsp/build-fb/tmp/sysroots/imx6qsabresd/usr/src/kernel/drivers/mxc/security/sahara2/include
SRCS =  mmdc.c 
OBJS = $(SRCS:.c=.o)
EXECUTABLE =  mmdc.out

all:
	$(CC) $(CFLAGS) -o $(EXECUTABLE) $(SRCS) 
clean:
	rm -f $(OBJS) $(EXECUTABLE) 

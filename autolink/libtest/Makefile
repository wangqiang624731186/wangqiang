OBJS_PATH=obj
SRCS_PATH=src
TEST_PATH=test
CONF_PATH=conf

CONF_FILES = \
$(CONF_PATH)/*

QEMU_ARM_SRCS = \
$(SRCS_PATH)/qemu_arm.c

QEMU_MCU_SRCS = \
$(SRCS_PATH)/qemu_mcu.c

QEMU_ARM = \
$(addprefix $(OBJS_PATH)/, $(addsuffix ,$(notdir $(basename $(QEMU_ARM_SRCS)))))

QEMU_MCU = \
$(addprefix $(OBJS_PATH)/, $(addsuffix ,$(notdir $(basename $(QEMU_MCU_SRCS)))))



DEPEND= \
-lpthread \
-lautolink_base \
-lautolink_mcu \

all:
	$(CC)  $(QEMU_ARM_SRCS) $(OBJS) -o $(QEMU_ARM) $(CFLAGS) ${DEPEND}
	$(CC)  $(QEMU_MCU_SRCS) $(OBJS) -o $(QEMU_MCU) $(CFLAGS) ${DEPEND}

tests:


installed:
	cp $(QEMU_ARM) ../images/usr/bin/
	cp $(QEMU_MCU) ../images/usr/bin/
	cp $(CONF_FILES) ../images/usr/bin/

clean:
	rm -rf $(LIBS) $(OBJS) $(QEMU_ARM) $(QEMU_MCU)

ifeq ($(KERNELRELEASE),)
	KERNELDIR ?= /usr/src/linux
	PWD := $(shell pwd)
modules:
	$(MAKE) -C $(KERNELDIR) M=$(PWD) modules
modules_install:
	$(MAKE) -C $(KERNELDIR) M=$(PWD) modules_install
else
	obj-m := eldd_cmos.o
endif

clean:
	rm -f *.ko *.o *.order *.symvers *.Mod.c *.mod.c

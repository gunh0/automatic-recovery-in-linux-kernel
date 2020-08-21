obj-m += result_lkm.o
result_lkm-objs := main.o

KDIR := /lib/modules/$(shell uname -r)/build
PWD := $(shell pwd)

KBUILD_EXTRA_SYMBOLS += $(PWD)/Module.symvers

all:
	$(MAKE) -C $(KDIR) M=$(PWD) modules
	mkdir -p \/home
	mkdir -p \/home\/backup_dir

clean:
	$(MAKE) -C $(KDIR) M=$(PWD) clean

test:
	sudo insmod result_lkm.ko
	
	# Display the kernel log
	dmesg

remove:
	sudo rm -rf /home/backup_dir
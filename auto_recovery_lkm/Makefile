obj-m += result_lkm.o
result_lkm-objs := main.o filename_extension_check.o

KDIR := /lib/modules/$(shell uname -r)/build
PWD := $(shell pwd)

KBUILD_EXTRA_SYMBOLS += $(PWD)/Module.symvers

all:
	$(MAKE) -C $(KDIR) M=$(PWD) modules
	sudo mkdir -p \/backup_dir
        sudo mkdir -p \/target_dir

clean:
	$(MAKE) -C $(KDIR) M=$(PWD) clean
	
start:
	sudo insmod result_lkm.ko
	
	# Display the kernel log
	dmesg

remove:
	sudo rm -rf /backup_dir
	sudo rmmod result_lkm.ko

restart:
	sudo rm -rf /backup_dir
	sudo rmmod result_lkm.ko
	$(MAKE) -C $(KDIR) M=$(PWD) clean
	$(MAKE) -C $(KDIR) M=$(PWD) modules
	sudo mkdir -p \/backup_dir
	sudo insmod result_lkm.ko
	
	# Display the kernel log
	dmesg

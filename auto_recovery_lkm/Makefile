obj-m += result_lkm.o
result_lkm-objs := main.o flag_handle.o filename_extension_check.o file_handle.o 

KDIR := /lib/modules/$(shell uname -r)/build
PWD := $(shell pwd)

KBUILD_EXTRA_SYMBOLS += $(PWD)/Module.symvers

all:
	$(MAKE) -C $(KDIR) M=$(PWD) modules
	sudo mkdir -p \/backup_dir
	sudo mkdir -p \/target_dir

auth:
	sudo chmod -R 777 /backup_dir
	sudo chmod -R 777 /target_dir
	# sudo chmod -R 777 /backup_copy

copy:
	cp -r /backup_dir /backup_copy

clean:
	$(MAKE) -C $(KDIR) M=$(PWD) clean
	
start:
	sudo insmod result_lkm.ko
	
	# Display the kernel log
	dmesg

rmmod:
	sudo rmmod result_lkm.ko

remove:
	sudo rm -rf /backup_dir
	sudo rm -rf /backup_copy
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

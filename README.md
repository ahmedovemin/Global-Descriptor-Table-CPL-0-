# Global descriptor table is stored in kernel memory and may be accessed through kernel modules or system call via store_gdt function. The GDT(Global Descriptor Table) entries can be obtained by using the this kernel module.


Python debugging:

	/*
	python compatible :  long(gdt[10:20] & 0xffffff00,16) ;byte checking
	*/


@drmint80

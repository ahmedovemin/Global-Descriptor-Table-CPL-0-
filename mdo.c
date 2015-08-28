#include <linux/init.h>         
#include <linux/smp.h>  
#include <linux/module.h>       
#include <asm/processor.h>   
#include <linux/kernel.h>           
#include <asm/system.h>
#include <asm/desc_defs.h>
#include <asm/desc.h>
#include <asm/ptrace.h>
#include <asm/asm-offsets.h>
#include <asm/current.h>
#include <linux/percpu.h>
#include <linux/thread_info.h>
#include <linux/sched.h>

#define currentt get_current()
struct LIST_ENTRY{ //windows compatible :)
	int next,prev;
};

MODULE_LICENSE("GPL"); //for cpu_gdt_table

static int __init root_init(void){
	
	int gdt_size,ecx;
	long unsigned long cr4;
	struct task_struct *task = current; // current process
	struct desc_struct *gdt = get_cpu_gdt_table(smp_processor_id());
		
	struct desc_ptr gdt_p;
	struct LIST_ENTRY gdt_addr;
	struct LIST_ENTRY *root;
	store_gdt(&gdt_p);
	
	root = (struct LIST_ENTRY*) gdt_p.address;
	gdt_size=gdt_p.size+1;
	printk(KERN_INFO "%d",task->pid);
	//printk(KERN_INFO "owned %lx",gdt_p.addre);
	for(ecx=0; ecx<gdt_size; ecx++){
		gdt_addr=*(root+ecx);
		printk(KERN_INFO "GDT %.8x = %.8x",gdt_addr.next,gdt_addr.prev);
	}
	
	printk(KERN_INFO "%lx",(unsigned long)gdt & 0xffffff00000);

	/*
	python compatible : 0xffffffff00 = long(gdt & 0xfffffffffff00,16)
	*/


	cr4 = native_read_cr4_safe();
	//printk(KERN_INFO "cr4 %lx",address);
	return 0;
}

static void __exit root_exit(void){
	printk(KERN_INFO "");
}

module_init(root_init);
module_exit(root_exit);


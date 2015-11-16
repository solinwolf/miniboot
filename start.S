
.text
.global _start
/******************1. set exception vectors*******************/
_start:
       b    reset
       ldr  pc, _undefined_instructions
       ldr  pc, _software_interrupt
       ldr  pc, _prefetch_abort
       ldr  pc, _data_abort
       ldr  pc, _not_used
       ldr  pc, _irq
       ldr  pc, _fiq


_undefined_instructions: .word undefined_instructions
_software_interrupt:     .word software_interrupt
_prefetch_abort:         .word prefetch_abort
_data_abort:             .word data_abort
_not_used:               .word not_used
_irq:                    .word irq
_fiq:                    .word fiq    

undefined_instructions:
        nop

software_interrupt:
        nop

prefetch_abort:
        nop

data_abort:
        nop
      
not_used:
        nop

irq:
        nop

fiq:
        nop

/*************************************/
/*********start code on reset*********/
/*************************************/

reset:
     bl set_cpu_mode  /****** 2. set to svc32 mode ******/
     bl turn_off_watchdog  /*******3. turn off watchdog********/
     bl mask_irqs          /*********4. mask all irqs**********/
     bl set_clock          /********5. set clock*******/     
     bl disable_id_caches    /*******6. disable I/Dcaches and mmu ****/
     bl init_memory         /*****7. initialize memory controler***/
   //  bl copy_to_ram         /****8. copy datas to sdram *****/
     bl init_stack          /*****9. initialize stack*****8/
     bl clean_bss           /******10. clear bss section*******/
     bl nand_init
     bl nand_to_ram 
     ldr pc, =arm_main      /****11. jump to c coding function******/
   @  bl light_led         /********lighting led*********/



set_cpu_mode:      
     /****** set to svc32 mode ******/
      mrs r0, cpsr
      bic r0, r0, #0x1f
      orr r0, r0, #0xd3
      msr cpsr, r0
      mov pc, lr


turn_off_watchdog:
     /*******turn off watchdog********/  
#define WTCON 0x53000000
      ldr r0, =WTCON
      mov r1, #0x0
      str r1, [r0]
      mov pc, lr


mask_irqs:
     /*********mask all irqs**********/
      mvn r0, #0
      ldr r1, =0x4a000008
      str r0, [r1]
      mov pc,lr
      

#define CLKDIVN 0x4c000014
#define MPLLCON 0x4C000004
#define MPLL_405M ((0x7f<<12)|(2<<4)|(1<<0))
set_clock:
     /*****FCLK:HCLK:PCLK = 1:4:8*********/
      ldr r0, =CLKDIVN
      mov r1, #0x5
      str r1, [r0]
      mrc p15, 0, r0,c1,c0,0
      orr r0,r0,#0xc0000000
      mcr p15,0,r0,c1,c0,0
     /*******FCLK = 405MHZ************/
      ldr r0, =MPLLCON
      ldr r1, =MPLL_405M
      str r1, [r0]
      mov pc, lr

disable_id_caches:
      /*******flush I/Dcaches and mmu*****/
      mcr p15, 0, r0, c7, c7,0
      mrc p15, 0, r0, c1, c0,0
      bic r0, r0,#0x00000007 
      mcr p15, 0, r0, c1,c0, 0
      mov pc, lr
 
init_memory:
      /*******initialize memory controler********/
      ldr r0, =0X48000000
      add r3, r0, #4*13
      adrl r1, mem_data
      
      
0:
      ldr r2, [r1],#4
      str r2, [r0],#4
      cmp r0, r3
      bne 0b
      mov pc, lr
mem_data:
          .long 0x22000000
          .long 0x00000700
          .long 0x00000700
          .long 0x00000700
          .long 0x00000700
          .long 0x00000700
          .long 0x00000700
          .long 0x00018001
          .long 0x00018001
          .long 0x008c04f5
          .long 0x000000b1
          .long 0x00000030
          .long 0x00000030




copy_to_ram:
      /*******copy datas to sdram from stepping stone*****/
      ldr r0, =0
      ldr r1, =0x30008000
      add r3, r0, #1024*4
              
1:
      ldr r2, [r0],#4
      str r2, [r1],#4
      cmp r0, r3
      bne 1b
      mov pc, lr

init_stack:
      /********initializing stack*********/
      ldr sp, =0x34000000
      mov pc, lr

clean_bss:
      /********clearing bss section**********/
      clean_bss:
	ldr r0, =bss_start
	ldr r1, =bss_end
	cmp r0, r1
	moveq pc, lr

clean_loop:
	mov r2, #0
	str r2, [r0], #4
	cmp r0, r1
	bne clean_loop
	mov pc, lr


#define GPBCON 0x56000010
#define GPBDAT 0x56000014
#define all_output ((0x1<<10)|(0x1<<12)|(0x1<<14)|(0x1<<16))
#define led_1_3_on (0b1010<<5)
light_led:
    /*******lighting led to see whether the initilization before is ok or not*******/
       ldr r0, =GPBCON
       ldr r1, =all_output
       str r1, [r0]
       ldr r2, =GPBDAT
       ldr r3, =led_1_3_on
       str r3, [r2]
       mov pc,lr




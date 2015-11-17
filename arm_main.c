

int arm_main()
{
    int cmm_num = 0;
    led_init();
    irqs_init();
    uart_init();
    
    while(1)
    {
    	display_menul(); 
    	scanf("%d",&cmm_num);
    	switch(cmm_num)
    	{
    	    case 1:
                led_on();
    	        printf("\nyou chose selection: %d\n\r",cmm_num);
                break;    		
    	    case 2:
    	      //  boot_linux_from_ram();
    	        led_off();
    	        printf("\nyou chose selection: %d\n\r",cmm_num);
    	        break;
    	       
    	    case 3:
    	     //   boot_linux_from_nand();
    	        printf("\nyou chose selection: %d\n\r",cmm_num);
    	        break;    	  
    	    default:
    	        printf("\nIlleagal selection!\n\r");
    	        break;  	
    	}
    }
    return 0;
}



const unsigned char gImage_dog1[153608];

int arm_main()
{
    int cmm_num = 0;
    led_init();
    irqs_init();
    uart_init();
   // dma_init();
  //  dma_on();  
    lcd_init(); 
    ts_init();
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
    	        clearsrc(0x0000ff);
    	        printf("\nyou chose selection: %d\n\r",cmm_num);
    	        break;
    	       
    	    case 3:
    	     //   boot_linux_from_nand();
    	        Draw_picture(0,0,320,240,gImage_dog1);
    	        printf("\nyou chose selection: %d\n\r",cmm_num);
    	        break;    	  
    	    default:
    	        printf("\nIlleagal selection!\n\r");
    	        break;  	
    	}
    }
    return 0;
}


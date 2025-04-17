final : stm32_blink.elf

main.o : main.c
	arm-none-eabi-gcc -c -mcpu=cortex-m4 -mthumb -std=gnu11 main.c -o main.o
	
stm32f446_startup.o : stm32f446_startup.c
	arm-none-eabi-gcc -c -mcpu=cortex-m4 -mthumb -std=gnu11 stm32f446_startup.c -o stm32f446_startup.o
	
stm32_blink.elf : main.o stm32f446_startup.o
	arm-none-eabi-gcc -nostdlib -T stm32_ls.ld *.o -o stm32_blink.elf -Wl,-Map=stm32_blink.map

load :
	openocd -f board/st_nucleo_f4.cfg
clean:
	del	-f *.o *.elf *.map
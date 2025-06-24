CC=arm-none-eabi-gcc
MACH=cortex-m4
CFLAGS= -c -mcpu=$(MACH) -mthumb -mfloat-abi=soft -std=gnu11 -Wall -o0

#Below commented linker flags are for without semihosting. Final elf file generated is final.elf
#LDFLAGS= -mcpu=$(MACH) -mthumb -mfloat-abi=soft --specs=nano.specs -T stm32_ls.ld -Wl,-Map=final.map

#Below commented linker flags are for with semihosting. Final elf file generated is final_sh.elf
LDFLAGS_SH= -mcpu=$(MACH) -mthumb -mfloat-abi=soft --specs=rdimon.specs -T stm32_ls.ld -Wl,-Map=final.map

#Give below command for project compilation without semihosting
all:main.o syscalls.c stm32f4xx_gpio_driver.o stm32f4xx_i2c_driver.o STM32_startup.o stm32f4xx_spi_driver.o final.elf

#Give below command for project compilation with semihosting, syscalls are not used in semihosting as library itself provide it.
semi:main.o stm32f4xx_gpio_driver.o stm32f4xx_i2c_driver.o STM32_startup.o stm32f4xx_spi_driver.o final_sh.elf

main.o:main.c
	$(CC) $(CFLAGS) -o $@ $^
	
stm32f4xx_gpio_driver.o:stm32f4xx_gpio_driver.c
	$(CC) $(CFLAGS) -o $@ $^
	
stm32f4xx_i2c_driver.o:stm32f4xx_i2c_driver.c
	$(CC) $(CFLAGS) -o $@ $^
	
stm32f4xx_spi_driver.o:stm32f4xx_spi_driver.c
	$(CC) $(CFLAGS) -o $@ $^
	
STM32_startup.o:STM32_startup.c
	$(CC) $(CFLAGS) -o $@ $^
	
syscalls.o:syscalls.c
	$(CC) $(CFLAGS) -o $@ $^
	
final.elf: main.o syscalls.o stm32f4xx_gpio_driver.o stm32f4xx_i2c_driver.o stm32f4xx_spi_driver.o STM32_startup.o
	$(CC) $(LDFLAGS) -o $@ $^
	
final_sh.elf: main.o stm32f4xx_gpio_driver.o stm32f4xx_i2c_driver.o stm32f4xx_spi_driver.o STM32_startup.o
	$(CC) $(LDFLAGS_SH) -o $@ $^
	
clean:
	del /Q *.o *.elf
	
load:
	openocd -f interface/stlink.cfg -f target/stm32f4x.cfg
	
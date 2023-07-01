# CORTEX-M3 makefile created by : Adham Ehab 
CC= arm-none-eabi-
CFLAGS= -mcpu=cortex-m4 -gdwarf-2 -g  
INCS= -I 
LIBS= 
SRC= $(wildcard *.c)
OBJ= $(SRC:.c=.o)
AS= $(wildcard *.s)
ASOBJ= $(AS:.s=.o)

all: Cortex-M4-Lab.bin
	@echo "===build is done==="
	
startup.o: startup.c 
	$(CC)gcc.exe $(CFLAGS)  -c $< -o $@
	
%.o: %.c 
	$(CC)gcc.exe $(CFLAGS)  -c $< -o $@

Cortex-M4-Lab.elf: $(OBJ) $(ASOBJ)
	$(CC)ld.exe -T linker_script.ld $(LIBS) $(OBJ) $(ASOBJ) -o $@ -Map=Map_file.map
	cp Cortex-M4-Lab.elf Cortex-M4-Lab.axf
	 
	
Cortex-M4-Lab.bin: Cortex-M4-Lab.elf 
	$(CC)objcopy.exe -O binary $< $@
	
clean: 
	rm -rf *.o *~ *.elf *.hex
	@echo "everything is clean"	
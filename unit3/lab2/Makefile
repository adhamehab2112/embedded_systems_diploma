# CORTEX-M3 makefile created by : Adham Ehab 
CC= arm-none-eabi-
CFLAGS= -mcpu=cortex-m3 -gdwarf-2 
INCS= -I 
LIBS= 
SRC= $(wildcard *.c)
OBJ= $(SRC:.c=.o)
AS= $(wildcard *.s)
ASOBJ= $(AS:.s=.o)

all: Cortex-M3-Lab.bin
	@echo "===build is done==="
	
startup.o: startup.s 
	$(CC)as.exe $(CFLAGS) $< -o $@
	
%.o: %.c 
	$(CC)gcc.exe $(CFLAGS)  -c $< -o $@

Cortex-M3-Lab.elf: $(OBJ) $(ASOBJ)
	$(CC)ld.exe -T linker_script.ld $(LIBS) $(OBJ) $(ASOBJ) -o $@ -Map=Map_file.map
	
Cortex-M3-Lab.bin: Cortex-M3-Lab.elf 
	$(CC)objcopy.exe -O binary $< $@
	
clean: 
	rm -rf *.o *~ *.elf *.hex
	@echo "everything is clean"	
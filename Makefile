CC=arm-none-eabi-gcc
OBJCOPY=arm-none-eabi-objcopy

# The standard peripheral library root directory
STDPERIPH=/home/shams/W/Embedded/ARM/Libraries/en.stsw-stm32054/STM32F10x_StdPeriph_Lib_V3.5.0

DEVICE=$(STDPERIPH)/Libraries/CMSIS/CM3/DeviceSupport/ST/STM32F10x
CORE=$(STDPERIPH)/Libraries/CMSIS/CM3/CoreSupport
PERIPH=$(STDPERIPH)/Libraries/STM32F10x_StdPeriph_Driver

# Paths to libraries .c source files
vpath %.c $(CORE)
vpath %.c $(PERIPH)/src
vpath %.c $(DEVICE)

vpath %.c src
vpath %.s src

CFLAGS=-ggdb -nostdlib -DSTM32F10X_MD_VL -DUSE_STDPERIPH_DRIVER -mthumb -mcpu=cortex-m3

SRC=src
BUILD=build

# OBJS is the list of object target files to compile
OBJS=startup.o main.o stm32f10x_gpio.o stm32f10x_rcc.o

# Add library paths for compiler
CFLAGS+= -I$(DEVICE) -I$(CORE) -I$(PERIPH)/inc -Isrc/

_ := $(shell mkdir -p $(BUILD))

flash: main.bin
	st-flash --reset write main.bin 0x08000000

main.bin: main.elf
	$(OBJCOPY) -O binary -j .text -j .data main.elf main.bin

main.elf: $(OBJS)
	$(CC) $(CFLAGS) -Tlinker.ld -o main.elf $(BUILD)/*

%.o: %.c
	$(CC) -c $(CFLAGS) $< -o $(BUILD)/$@

%.o: %.s
	$(CC) -c $(CFLAGS) $< -o $(BUILD)/$@

clean:
	rm -f main.elf *.o build/*
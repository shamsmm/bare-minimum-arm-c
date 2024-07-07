PROJECTNAME = EasyLibrary

TOOLCHAIN=arm-none-eabi
CC=$(TOOLCHAIN)-gcc

INCDIR = inc $(wildcard modules/*/inc)
SRCDIR = src $(wildcard modules/*/src)

INCLUDES = $(addprefix -I, $(INCDIR))

SRC = $(wildcard modules/*/src/*.c)
SRC += $(wildcard src/*.c)
SRC += $(wildcard src/*.s)

OBJ = $(SRC:.c=.o)

vpath %.c $(SRCDIR)
vpath %.s $(SRCDIR)
vpath %.h $(INCDIR)

BINDIR = build

TARGET = $(BINDIR)/main.elf

CFLAGS=-ggdb -mthumb -mcpu=cortex-m3 -O0 $(INCLUDES)
ASMFLAGS=-ggdb -mthumb -mcpu=cortex-m3

all: $(TARGET)

flash: $(TARGET)
	openocd -f stlink.cfg -c "program main.elf verify reset exit"

$(TARGET): clean $(OBJ)
	$(CC) $(CFLAGS) -TSTM32F103.ld -o $(TARGET) $(addprefix $(BINDIR)/, $(OBJ))

%.o: %.c
	@mkdir -p $(dir $(BINDIR)/$@)
	$(CC) -c $(CFLAGS) $< -o $(BINDIR)/$@

%.o: %.s
	@mkdir -p $(dir $(BINDIR)/$@)
	$(CC) -c $(ASMFLAGS) $< -o $(BINDIR)/$@

clean:
	rm -rf $(BINDIR)

.PHONY: all clean flash
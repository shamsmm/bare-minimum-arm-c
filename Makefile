PROJECTNAME = EasyLibrary

TOOLCHAIN=arm-none-eabi
CC=$(TOOLCHAIN)-gcc

INCDIR = src src/inc modules/
SRCDIR = src $(wildcard modules/*/src) $(wildcard modules/*)

INCLUDES = $(addprefix -I, $(INCDIR))

SRC = $(wildcard modules/*/*.c)
SRC += $(wildcard modules/*/*.s)
SRC += $(wildcard modules/*/src/*.c)
SRC += $(wildcard src/*.c)
SRC += $(wildcard src/*.s)

OBJ = $(SRC:.c=.o)
OBJ := $(OBJ:.s=.o)

BINDIR = build

TARGET = $(BINDIR)/main.elf

CFLAGS=-ggdb -mthumb -mcpu=cortex-m3 -O0 -ffreestanding $(INCLUDES)
ASMFLAGS=-ggdb -mthumb -mcpu=cortex-m3

all: $(TARGET)

flash: $(TARGET)
	openocd -f stlink.cfg -c "program $(TARGET) verify reset exit"

$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) -nostartfiles -Tstm32f103.ld -o $(TARGET) $(addprefix $(BINDIR)/, $(OBJ))

%.o: %.c
	@mkdir -p $(dir $(BINDIR)/$@)
	$(CC) -c $(CFLAGS) $< -o $(BINDIR)/$@

%.o: %.s
	@mkdir -p $(dir $(BINDIR)/$@)
	$(CC) -c $(ASMFLAGS) $< -o $(BINDIR)/$@

clean:
	rm -rf $(BINDIR)

.PHONY: all clean flash
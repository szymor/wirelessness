.PHONY: all flash fuses reset clean

PROJNAME = wlndongle
PARTNAME = atmega8
F_CPU = 12000000ul
DEBUG ?= 0

OUT_HEX = $(PROJNAME).hex
OUT_ELF = $(PROJNAME).elf
OUT_BIN = $(PROJNAME).bin
CC = avr-gcc
LD = avr-gcc
OBJCOPY = avr-objcopy
OBJDUMP = avr-objdump
SIZE = avr-size

CFLAGS = -g -O2 -Wall -std=c99 -mmcu=$(PARTNAME) -DF_CPU=$(F_CPU) -Iinc
ifneq ($(DEBUG), 0)
CFLAGS += -DDEBUG=$(DEBUG)
endif

LFLAGS = -mmcu=$(PARTNAME)

SRCDIR = src
OBJDIR = obj
OBJ = main.o NRF24L01.o spisw.o
OBJS = $(addprefix $(OBJDIR)/,$(OBJ))

all: $(OUT_HEX)

$(OUT_HEX): $(OUT_ELF)
	@$(OBJCOPY) -S -I elf32-avr -O ihex $< $@

$(OUT_BIN): $(OUT_ELF)
	@$(OBJCOPY) -S -I elf32-avr -O binary $< $@

$(OUT_ELF): $(OBJS)
	@$(CC) $(LFLAGS) -o $@ $(OBJS)
	@$(SIZE) -C --mcu=$(PARTNAME) $@

$(OBJS): $(OBJDIR)/%.o : $(SRCDIR)/%.c | $(OBJDIR)
	@$(CC) $(CFLAGS) -c -o $@ $<

$(OBJDIR):
	@mkdir $(OBJDIR)

flash:
	@avrdude -c usbasp -p $(PARTNAME) -U flash:w:$(OUT_HEX):i

fuses:
	@avrdude -c usbasp -p $(PARTNAME) -U lfuse:w:0xfd:m -U hfuse:w:0xd9:m

reset:
	@avrdude -c usbasp -p $(PARTNAME)
	
clean:
	@-rm -rf $(OBJS) $(OUT_HEX) $(OUT_ELF) $(OUT_BIN)

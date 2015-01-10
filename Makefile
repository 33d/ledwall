PROJECT	       = ledwall

PRG            = $(PROJECT)
OBJECTS        = 
AVR_OBJECTS    = Adafruit_NeoPixel pattern matrix snake scroll plasma main
TEST_OBJECTS   = 

CLEAN          = *.o *.avro $(PRG).elf *.eps *.png *.pdf *.bak \
	*.lst *.map *.a $(EXTRA_CLEAN_FILES)

ARDUINO_HOME  ?= /opt/arduino-1.0.5

PROGRAMMER    ?= arduino
UPLOAD_PORT   ?= /dev/ttyUSB0
# 57600 for Duemilianove, 19200 for Decimilia, 115200 for Bus Pirate
UPLOAD_SPEED  ?= 57600

MCU_TARGET     = atmega328p
OPTIMIZE       = -Os

DEFS           = -DF_CPU=16000000L -DARDUINO=105
LIBS           =
TEST_LIBS       = -lcunit

CPPFLAGS      += -g

# You should not have to change anything below here.

AVRCC          = avr-gcc
AVRCPP         = avr-g++

# Override is only needed by avr-lib build system.

CALLFLAGS      = -g -Wall $(OPTIMIZE) -mmcu=$(MCU_TARGET) \
	-ffunction-sections -fdata-sections -Wall -Werror \
	$(DEFS)
	#-funsigned-char -funsigned-bitfields -fpack-struct -short-enums 
override AVRCFLAGS        = -I. $(CALLFLAGS) -std=gnu99  
override AVRCPPFLAGS      = -I. $(CALLFLAGS)
override AVRLDFLAGS       = -Wl,-Map,$(PRG).map

AVROBJCOPY      = avr-objcopy
OBJDUMP         = avr-objdump

ARDUINO_CORE = $(ARDUINO_HOME)/hardware/arduino/cores/arduino
ARDUINO_VARIANT = $(ARDUINO_HOME)/hardware/arduino/variants/standard/
INCLUDES = -I$(ARDUINO_CORE) -I$(ARDUINO_VARIANT)

BUILD_DIR	= build
TEST_DIR	= test
BUILD_OBJS	= $(foreach OBJ,$(OBJECTS) $(AVR_OBJECTS),$(OBJ).avro)
TEST_OBJS	= $(foreach OBJ,$(OBJECTS) $(TEST_OBJECTS),$(OBJ).o) test.o
CLEAN_FIND	= $(foreach F,$(CLEAN),-o -name '$(F)')

.PHONY: reset_arduino clean

export CFLAGS CPPFLAGS F_CPU LDFLAGS ARDUINO_HOME CC CPP INCLUDES ARDUINO_CORE \
	ARDUINO_VARIANT AVRCC AVRCPP F_CPU AVRCFLAGS AVRCPPFLAGS AVRLDFLAGS

all: test $(PRG).elf lst text eeprom

$(PRG).elf: $(BUILD_OBJS) libarduino/libarduino.a
	$(AVRCPP) $(AVRCPPFLAGS) $(AVRLDFLAGS) -o $@ $^ $(LIBS)

%.avro : %.c 
	$(AVRCC) $(AVRCFLAGS) $(INCLUDES) -c -o $@ $<

%.avro : %.cpp
	$(AVRCPP) $(AVRCPPFLAGS) $(INCLUDES) -c -o $@ $<

%.avro : %.S
	$(AVRCPP) $(AVRCPPFLAGS) $(INCLUDES) -c -o $@ $<

test:
#test: test-prg
#	./test
#
#test-prg: $(TEST_OBJS)
#	$(CXX) $(CPPFLAGS) $(LDFLAGS) -o test $^ $(TEST_LIBS)

libarduino/libarduino.a:
	$(MAKE) -C libarduino

# Depend on "Makefile", so we don't accidentally delete files in the wrong 
# place if invoked with -f
clean: Makefile
# $(CLEAN_FIND) starts with -o, so the -false is a no-op to accept this
	-find . -false $(CLEAN_FIND) | xargs rm -fv

lst:  $(PRG).lst

%.lst: %.elf
	$(OBJDUMP) -h -S $< > $@

# Rules for building the .text rom images

text: hex bin srec

hex:  $(PRG).hex
bin:  $(PRG).bin
srec: $(PRG).srec

%.hex: %.elf
	$(AVROBJCOPY) -j .text -j .data -O ihex $< $@

%.srec: %.elf
	$(AVROBJCOPY) -j .text -j .data -O srec $< $@

%.bin: %.elf
	$(AVROBJCOPY) -j .text -j .data -O binary $< $@

# Rules for building the .eeprom rom images

eeprom: ehex ebin esrec

ehex:  $(PRG)_eeprom.hex
ebin:  $(PRG)_eeprom.bin
esrec: $(PRG)_eeprom.srec

%_eeprom.hex: %.elf
	$(AVROBJCOPY) -j .eeprom --change-section-lma .eeprom=0 -O ihex $< $@ \
	|| { echo empty $@ not generated; exit 0; }

%_eeprom.srec: %.elf
	$(AVROBJCOPY) -j .eeprom --change-section-lma .eeprom=0 -O srec $< $@ \
	|| { echo empty $@ not generated; exit 0; }

%_eeprom.bin: %.elf
	$(AVROBJCOPY) -j .eeprom --change-section-lma .eeprom=0 -O binary $< $@ \
	|| { echo empty $@ not generated; exit 0; }

# Every thing below here is used by avr-libc's build system and can be ignored
# by the casual user.

FIG2DEV                 = fig2dev
EXTRA_CLEAN_FILES       = *.hex *.bin *.srec

ifeq ($(PROGRAMMER),arduino)
AVRDUDE = $(ARDUINO_HOME)/hardware/tools/avrdude \
		-C$(ARDUINO_HOME)/hardware/tools/avrdude.conf \
		-p$(MCU_TARGET) -cstk500v1 -P$(UPLOAD_PORT) \
		-b$(UPLOAD_SPEED)

reset_arduino:
	# Reset the Arduino first to activate the bootloader
	stty $(UPLOAD_SPPED) raw ignbrk hup < $(UPLOAD_PORT)

else
AVRDUDE = avrdude \
		-p$(MCU_TARGET) -c$(PROGRAMMER) -P$(UPLOAD_PORT) \
		-b$(UPLOAD_SPEED)

reset_arduino:

endif
	
upload: $(PRG).hex reset_arduino
	$(AVRDUDE) -Uflash:w:$<:i

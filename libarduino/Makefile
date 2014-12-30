OBJECTS = $(addsuffix .o,$(notdir $(basename $(wildcard $(ARDUINO_CORE)/*.c*))))
AVRALLFLAGS += -w -fno-exceptions -ffunction-sections -fdata-sections -DARDUINO=22
AVRCFLAGS += $(AVRALLFLAGS)
AVRCPPFLAGS += $(AVRALLFLAGS)

libarduino.a: $(OBJECTS)
	avr-ar rcs libarduino.a $(OBJECTS)

%.o : $(ARDUINO_CORE)/%.c
	$(AVRCC) -c $(AVRCFLAGS) $(INCLUDES) -o $@ $^
 
%.o : $(ARDUINO_CORE)/%.cpp
	$(AVRCPP) -c $(AVRCPPFLAGS) $(INCLUDES) -o $@ $^
 
clean:
	-rm *.o

.PHONY: clean


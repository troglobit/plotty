# Leveraging implicit rules in GNU make
LIB     = libplotty.a(plotty.o)

EXEC    = demo
OBJS    = demo.o term.o

all: $(LIB) $(EXEC)

$(EXEC): $(OBJS) $(LIB)

clean:
	$(RM) *.o *.a $(EXEC)

distclean: clean
	$(RM) *~

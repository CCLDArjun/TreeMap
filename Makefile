CFLAGS   = -O0 -g 
OBJFILES = TreeMap.o main.o
TARGET   = main
export CFLAGS

all: $(TARGET)

$(TARGET): $(OBJFILES)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJFILES) $(LDFLAGS)

clean:
	rm -r $(OBJFILES) $(TARGET)


override CFLAGS  += -O0 -g 
OBJFILES = TreeMap.o main.o
TARGET   = main
CC       = /usr/local/opt/llvm/bin/clang
export CFLAGS

all: $(TARGET)

san: CFLAGS += -fsanitize=address
san: $(TARGET)

$(TARGET): $(OBJFILES)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJFILES) $(LDFLAGS)

clean:
	rm -r $(OBJFILES) $(TARGET)


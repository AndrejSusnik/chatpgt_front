# Compiler
CC = gcc

# Target executable
TARGET = chatgpt_native

# Source files
SRC = main.c

PREFIX ?= /usr/local
BINDIR = $(PREFIX)/bin

# GTK and Webkit flags
CFLAGS = `pkg-config --cflags gtk+-3.0 webkit2gtk-4.0`
LDFLAGS = `pkg-config --libs gtk+-3.0 webkit2gtk-4.0`

# Build rule
all: $(TARGET)

$(TARGET): $(SRC)
	$(CC) -o $(TARGET) $(SRC) $(CFLAGS) $(LDFLAGS)

install: $(TARGET)	
	install -d $(BINDIR)
	install -m 755 $(TARGET) $(BINDIR)
	install -m 644 chatgpt-desktop.desktop /usr/share/applications

# Clean rule
clean:
	rm -f $(TARGET)


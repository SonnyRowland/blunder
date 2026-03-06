TARGET = blunder

SRCS = src/main.c src/fen.c src/display.c

all: $(TARGET)

$(TARGET): $(SRCS)
	cc -o $(TARGET) $(SRCS)
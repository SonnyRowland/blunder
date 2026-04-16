TARGET = blunder

SRCS = src/main.c src/fen.c src/display.c src/move.c src/board.c src/movegen.c

all: $(TARGET)

$(TARGET): $(SRCS)
	cc -o $(TARGET) $(SRCS)

UNITY = unity/unity.c
TEST_SRCS = src/fen.c src/display.c src/move.c src/board.c src/movegen.c

.PHONY: test
test:
	@for f in tests/test_*.c; do \
		bin=$$(basename $$f .c); \
		cc -Isrc -Iunity -o tests/$$bin $$f $(TEST_SRCS) $(UNITY) && \
		./tests/$$bin; \
	done

.PHONY: format
format:
	clang-format --style=WebKit -i $(SRCS)
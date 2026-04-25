TARGET = blunder

SRCS = src/main.c src/fen.c src/display.c src/move.c src/board.c src/movegen.c src/eval.c src/movesearch.c

all: $(TARGET)

$(TARGET): $(SRCS)
	cc -o $(TARGET) $(SRCS)

UNITY = unity/unity.c
TEST_SRCS = src/fen.c src/display.c src/move.c src/board.c src/movegen.c src/eval.c src/movesearch.c

.PHONY: test
test:
	@status=0; \
	for f in tests/test_*.c; do \
		bin=$$(basename $$f .c); \
		cc -Isrc -Iunity -o tests/$$bin $$f $(TEST_SRCS) $(UNITY) && \
		./tests/$$bin || status=1; \
	done; \
	exit $$status

.PHONY: format
format:
	clang-format --style=Google -i $(SRCS)
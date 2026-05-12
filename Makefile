TARGET = blunder
ARTEFACTS = build/artefacts

SRCS = src/main.c src/fen.c src/display.c src/move.c src/board.c src/movegen.c src/eval.c src/movesearch.c src/uci.c
INCLUDES = -Iinclude

all: $(ARTEFACTS)/$(TARGET)

$(ARTEFACTS)/$(TARGET): $(SRCS)
	mkdir -p $(ARTEFACTS)
	cc $(INCLUDES) -o $(ARTEFACTS)/$(TARGET) $(SRCS)

UNITY = vendor/unity/unity.c
TEST_SRCS = src/fen.c src/display.c src/move.c src/board.c src/movegen.c src/eval.c src/movesearch.c src/uci.c

.PHONY: debug
debug: $(SRCS)
	mkdir -p $(ARTEFACTS)
	cc $(INCLUDES) -DDEBUG -o $(ARTEFACTS)/$(TARGET) $(SRCS)

.PHONY: test
test:
	@mkdir -p $(ARTEFACTS); \
	status=0; \
	for f in tests/test_*.c; do \
		bin=$$(basename $$f .c); \
		cc $(INCLUDES) -Ivendor/unity -o $(ARTEFACTS)/$$bin $$f $(TEST_SRCS) $(UNITY) && \
		./$(ARTEFACTS)/$$bin || status=1; \
	done; \
	exit $$status

.PHONY: format
format:
	clang-format --style=Google -i $(SRCS)

CFLAGS = -Wall -Wextra
DEBUG_FLAGS = -g -O0

.PHONY: debug
debug: $(ARTEFACTS)/$(TARGET)-debug

$(ARTEFACTS)/$(TARGET)-debug: $(SRCS)
	mkdir -p $(ARTEFACTS)
	cc $(INCLUDES) $(CFLAGS) $(DEBUG_FLAGS) -o $@ $(SRCS)
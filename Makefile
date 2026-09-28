TARGET = blunder
ARTEFACTS = build/artefacts

SRCS = src/main.c src/fen.c src/display.c src/move.c src/board.c src/movegen.c src/eval.c src/movesearch.c src/uci.c src/timemanager.c src/perft.c src/bench.c
INCLUDES = -Iinclude

CFLAGS = -Wall -Wextra
RELEASE_FLAGS = -O2 -DNDEBUG
DEBUG_FLAGS = -g -O0

all: $(ARTEFACTS)/$(TARGET)

$(ARTEFACTS)/$(TARGET): $(SRCS)
	mkdir -p $(ARTEFACTS)
	cc $(INCLUDES) $(CFLAGS) $(RELEASE_FLAGS) -o $(ARTEFACTS)/$(TARGET) $(SRCS)

UNITY = vendor/unity/unity.c
TEST_SRCS = src/fen.c src/display.c src/move.c src/board.c src/movegen.c src/eval.c src/movesearch.c src/uci.c src/timemanager.c src/perft.c

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
	clang-format -i $(SRCS)

.PHONY: debug
debug: $(ARTEFACTS)/$(TARGET)-debug

$(ARTEFACTS)/$(TARGET)-debug: $(SRCS)
	mkdir -p $(ARTEFACTS)
	cc $(INCLUDES) $(CFLAGS) $(DEBUG_FLAGS) -o $@ $(SRCS)
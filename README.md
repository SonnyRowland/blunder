# C-based Chess App

## Usage instructions

Clone the repository from https://github.com/SonnyRowland/blunder

```bash
git clone https://github.com/SonnyRowland/blunder
```

## Performance

Search efficiency and speed are tracked in [bench.md](bench.md). Run
`./blunder bench`
to benchmark the current build.

## References

### Piece square table values

- The piece square tables used in the evaluation function were lifted directly from [Tomasz Michniewski's post on chessprogramming.org](https://www.chessprogramming.org/Simplified_Evaluation_Function)

### UCI Specification

- The UCI specification was taken from https://www.shredderchess.com/

### Perft results

- Expected perft results were taken from [chessprogramming.org](https://chessprogramming.org/Perft_Results)

### Benchmark positions

- Benchmark positions were taken from [Stockfish](https://github.com/official-stockfish/Stockfish)
  (`src/benchmark.cpp`)

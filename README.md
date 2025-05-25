# Wordle Game

This is a terminal-based clone of the Wordle game written in C.

## Features
- Loads 5-letter words from a vocabulary file
- Implements scoring logic with green, yellow, and gray feedback
- Tracks and enforces letter constraints across guesses
- Clean CLI interaction

## Build and Run
```bash
make
./wordle_game
```

## ▶️ How to Play
You will be prompted to guess a 5-letter word. 
<br>The program provides feedback:
- g: correct letter in the correct position (green)
- y: correct letter in the wrong position (yellow)
- x: letter not in the word (gray)
- Use the clues to narrow down the correct word.

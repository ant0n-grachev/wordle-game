#include "wordle_lib.h"

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

int main(void) {
  char **vocabulary;
  size_t num_words;
  int num_guesses = 0;

  srand(time(NULL));

  // load up the vocabulary and store the number of words in it.
  vocabulary = load_vocabulary("vocabulary.txt", &num_words);

  // Randomly select one of the words from the file to be today's SECRET WORD.
  int word_index = rand() % num_words;
  char *secret = vocabulary[word_index];

  // input buffer -- we'll use this to get a guess from the user.
  char guess[80];

  // buffer for scoring each guess.
  char result[6] = {0};
  bool success = false;

  char green[5]      = {0};
  bool must_have[26] = {0};
  bool forbidden[26] = {0};

  printf("time to guess a 5-letter word! (press ctrl-D to exit)\n");
  while (!success) {
    printf("guess: ");
    if (fgets(guess, 80, stdin) == NULL) {
      break;
    }

    if (strlen(guess) < 6) {
      printf("the word must be exactly five characters\n");
      continue;
    }

    // Whatever the user input, cut it off at 5 characters.
    guess[5] = '\0';

    if (!valid_guess(guess, vocabulary, num_words)) {
      printf("not a valid guess\n");
      continue;
    } else {
      num_guesses++;
    }

    bool legal = true;
    // a) enforce locked-in greens
    for (int i = 0; i < 5; i++)
      if (green[i] && guess[i] != green[i])
        legal = false;
    // b) forbid letters ruled out entirely
    for (int i = 0; i < 5; i++)
      if (forbidden[guess[i] - 'a'])
        legal = false;
    // c) require all previously seen yellow/green letters
    for (int c = 0; c < 26; c++) if (must_have[c]) {
      bool seen = false;
      for (int i = 0; i < 5; i++)
        if (guess[i] == 'a' + c)
          seen = true;
      if (!seen) legal = false;
    }
    if (!legal) {
      printf("incompatible with previous clues\n");
      num_guesses--;
      continue;
    }

    success = score_guess(secret, guess, result);
    printf("%s\n", guess);
    printf("%s\n", result);

    for (int i = 0; i < 5; i++) {
      char c = guess[i];
      if (result[i] == 'g') {
        green[i] = c;
        must_have[c - 'a'] = true;
      } else if (result[i] == 'y') {
        must_have[c - 'a'] = true;
      } else if (result[i] == 'x') {
        bool seen_elsewhere = false;
        for (int j = 0; j < 5; j++)
          if (guess[j] == c && (result[j] == 'g' || result[j] == 'y'))
            seen_elsewhere = true;
        if (!seen_elsewhere)
          forbidden[c - 'a'] = true;
      }
    }
  }

  if (success) {
    printf("you win, in %d guesses!\n", num_guesses);
  }
  free_vocabulary(vocabulary, num_words);

  return 0;
}

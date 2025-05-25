#include "wordle_lib.h"
#include <string.h>
#include <stdlib.h>

// Returns true if the guess is an exact match with the secret word, but
// more importantly, fills in the result with the following:
// - 'x' goes in a slot if the corresponding letter in the guess does not appear
//   anywhere in the secret word
// - 'y' goes in a slot if the corresponding letter in the guess appears in the
//   secret word, but not in the corresponding slot
// - 'g' goes in a slot if the corresponding letter in the guess appears in the
//   corresponding slot in the secret word.
//   You can assume that result points at enough memory for a string of length
//   5. (ie, at least 6 bytes long)
bool score_guess(char *s, char *g, char *r) {
  int f[26] = {0}, i;
  for (i = 0; i < 5; i++)
    if (g[i] == s[i])
      r[i] = 'g';
    else
      f[s[i] - 'a']++;
  for (i = 0; i < 5; i++) {
    if (r[i] == 'g') continue;
    int k = g[i] - 'a';
    if (f[k] > 0) {
      r[i] = 'y';
      f[k]--;
    } else
      r[i] = 'x';
  }
  r[5] = '\0';
  for (i = 0; i < 5; i++)
    if (r[i] != 'g')
      return false;
  return true;
}

// Returns true if the specified guess is one of the strings in the vocabulary,
// and false otherwise. num_words is the length of the vocabulary.
bool valid_guess(char *g, char **v, size_t n) {
  for (size_t i = 0; i < n; i++)
    if (strcmp(g, v[i]) == 0)
      return true;
  return false;
}

// Returns an array of strings (so, char **), where each string contains a word
// from the specified file. The file is assumed to contain 5-letter words, one
// per line.
char **load_vocabulary(char *fn, size_t *n) {
  FILE *f = fopen(fn, "r");
  char buf[16], **a = malloc(128 * sizeof(char *));
  *n = 0;
  while (fgets(buf, sizeof buf, f)) {
    buf[5] = '\0';
    a[(*n)++] = strdup(buf);
    if (*n % 128 == 0)
      a = realloc(a, (*n + 128) * sizeof(char *));
  }
  fclose(f);
  return a;
}

// Free each of the strings in the vocabulary, as well as the pointer vocabulary
// itself (which points to an array of char *).
void free_vocabulary(char **v, size_t n) {
  for (size_t i = 0; i < n; i++)
    free(v[i]);
  free(v);
}

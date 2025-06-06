#pragma once

#include <stdbool.h>
#include <stdio.h>

bool score_guess(char *secret, char *guess, char *result);

bool valid_guess(char *guess, char **vocabulary, size_t num_words);

char **load_vocabulary(char *filename, size_t *num_words);

void free_vocabulary(char **vocabulary, size_t num_words);

#ifndef __HIGHSCORE_H__
#define __HIGHSCORE_H__

#include "gfc_text.h"

int highscore_load(char* filename);

void highscore_save(int score);

#endif

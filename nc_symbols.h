#define _XOPEN_SOURCE_EXTENDED
#include <ncurses.h>
#include <stdint.h>
#include <stddef.h>

cchar_t _unicode_varmap[] = {
  { 0, L"\u2588" },
  { 0, L"\u2589" },
};

#define NCW_BLOCK &_unicode_varmap[0]


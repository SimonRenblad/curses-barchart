wchar_t* BLK_LINE[] = {
  L"▌",
  L"🭐",
  L"🭎",
  L"🭌",

  L"🭀",
  L"🭀", // cheat the diagonal
  L"🭏",
  L"🭍",

  L"🬾",
  L"🬿",
  L"🭑",
  L"▅",
  L"🭂",
  L"🭁",

  L"🬼",
  L"🬽",
  L"▃",
  L"🭆",
  L"🭄",
  L"🭃",

  L"🭈",
  L"🭊",
  L"🭅", // we have to cheat due to the lack of a full diagonal
  L"🭅",

  L"🭇",
  L"🭉",
  L"🭋",
  L"▐",
};



void calculate_symbols(WINDOW* win, int last, int last_thirds, int curr, int new_thirds) {
  if(last > curr) {
    // handle case where last_thirds == 0
    // go from last_third to -> centre down
    waddwstr(win, third_to_down[last_thirds]);

    // move down

    // half blocks left until 1 or 2 above
    for(int i = last + i; i < curr; i++) {
      waddwstr(win, L"▌");
      // move down
    }

    // centre up -> new_third
    waddwstr(win, centre_to_third[new_thirds]);
    // 

  } else if(curr > last) {
    // go from last_third -> centre up
    waddwstr(win, third_to_up[last_thirds]);

    // move up
    // half blocks right until thirds left
    for(int i = last - 1; last > curr; i--) {
      waddwstr(win, L"▐");
      // move up
    }

    // move up
    // centre down -> new third
    waddwstr(win, centre_down_to_third[new_thirds]);
  }
  if(last == curr) {
    if(new_thirds == last_thirds) {

    }
  } else if(last > curr) {

  } else {

  }  
}

// also need the half blocks and full blocks
// need a neat way to index based on where it is going

// TODO: implement upside down line chart
// #define BLK_DIAG_22 L"🭒"
// #define BLK_DIAG_23 L"🭓"
// #define BLK_DIAG_24 L"🭔"
// #define BLK_DIAG_25 L"🭕"
// #define BLK_DIAG_26 L"🭖"
// #define BLK_DIAG_27 L"🭗"
// #define BLK_DIAG_28 L"🭘"
// #define BLK_DIAG_29 L"🭙"
// #define BLK_DIAG_30 L"🭚"
// #define BLK_DIAG_31 L"🭛"
// #define BLK_DIAG_32 L"🭜"
// #define BLK_DIAG_33 L"🭝"
// #define BLK_DIAG_34 L"🭞"
// #define BLK_DIAG_35 L"🭟"
// #define BLK_DIAG_36 L"🭠"
// #define BLK_DIAG_37 L"🭡"
// #define BLK_DIAG_38 L"🭢"
// #define BLK_DIAG_39 L"🭣"
// #define BLK_DIAG_40 L"🭤"
// #define BLK_DIAG_41 L"🭥"
// #define BLK_DIAG_42 L"🭦"

// #define LINE_0 L"🭰"
// #define LINE_1 L"🭱"
#define LINE_2 L"🭲"
#define LINE_3 L"🭳"
// #define LINE_4 L"🭴"
// #define LINE_5 L"🭵"
// #define LINE_6 L"🭶"
// #define LINE_7 L"🭷"
#define LINE_8 L"🭸"
// #define LINE_9 L"🭹"
// #define LINE_10 L"🭺"
// #define LINE_11 L"🭻"
// simplify by not using the below
// #define LINE_12 L"🭼"
// #define LINE_13 L"🭽"
// #define LINE_14 L"🭾"
// #define LINE_15 L"🭿"

#define LINE_DIAG_0 L"🮠"
#define LINE_DIAG_1 L"🮡"
#define LINE_DIAG_2 L"🮢"
#define LINE_3      L"🭳"
#define LINE_DIAG_3 L"🮣"
// #define LINE_DIAG_4 L"🮤"
// #define LINE_DIAG_5 L"🮥"
// #define LINE_DIAG_6 L"🮦"
// #define LINE_DIAG_7 L"🮧"
// #define LINE_DIAG_8 L"🮨"
// #define LINE_DIAG_9 L"🮩"
// #define LINE_DIAG_10 L"🮪"
// #define LINE_DIAG_11 L"🮫"
// #define LINE_DIAG_12 L"🮬"
// #define LINE_DIAG_13 L"🮭"
// #define LINE_DIAG_14 L"🮮"

#define LINE_DIAG2_0 L"🯐"
#define LINE_DIAG2_1 L"🯑"
#define LINE_DIAG2_2 L"🯒"
#define LINE_DIAG2_3 L"🯓"
#define LINE_DIAG2_4 L"🯔"
#define LINE_DIAG2_5 L"🯕"
#define LINE_DIAG2_6 L"🯖"
#define LINE_DIAG2_7 L"🯗"
// #define LINE_DIAG2_8 L"🯘"
// #define LINE_DIAG2_9 L"🯙"
// #define LINE_DIAG2_10 L"🯚"
// #define LINE_DIAG2_11 L"🯛"
// #define LINE_DIAG2_12 L"🯜"
// #define LINE_DIAG2_13 L"🯝"
// #define LINE_DIAG2_14 L"🯞"
// #define LINE_DIAG2_15 L"🯟"


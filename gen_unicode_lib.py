import unicodedata

BLK_DIAG_START = 0x1FB3C
BLK_DIAG_LEN = 0x2b

for i in range(BLK_DIAG_LEN):
    print(f"#define BLK_DIAG_{i} L\"{chr(i + BLK_DIAG_START)}\"")
print()

LINE_START = 0x1fb70
LINE_LEN = 0x10

for i in range(LINE_LEN):
    print(f"#define LINE_{i} L\"{chr(i + LINE_START)}\"")
print()

LINE_DIAG_START = 0x1fba0
LINE_DIAG_LEN = 0xF

for i in range(LINE_DIAG_LEN):
    print(f"#define LINE_DIAG_{i} L\"{chr(i + LINE_DIAG_START)}\"")
print()

LINE_DIAG2_START = 0x1fbd0
LINE_DIAG2_LEN = 0x10

for i in range(LINE_DIAG2_LEN):
    print(f"#define LINE_DIAG2_{i} L\"{chr(i + LINE_DIAG2_START)}\"")
print()

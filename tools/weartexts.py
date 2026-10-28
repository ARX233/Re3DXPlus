"""Read the dress-up parts' names out of `main` (under the unicorn x86 emulator) and write
tools/wear_texts.txt, the texts clSeqTgWearPartsAeroThread::run sets in font 4 (menupack.py
pre-renders them as WEAR_TEXT + k).

usage: weartexts.py <main>

- run 0x887b714 sprintf("%s%s") (0x94277c4) of get_parts_data(kind, number, 0, gem) + 0, the
  part's name, and + 0x20, what was done: 装着完了！, for the stock parts に交換完了！, for the
  wing taken off を取り外し完了！.
- The rows, as src/menu.c wear_text numbers them (16, 17 the wheel's, written as they are): the aero sets 0..3 (stock, A, B, C), the gem
  cars' aero set, the bonnets 0..3, the wings 0..4 (stock, the car's own, the GT wings, 4 none), the
  mirrors 0..1; 18 on the neons' (none, then 1..12); 31 on the stickers' patterns.
"""
import os
import sys

sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
from cardb import Main  # noqa: E402

m = Main(sys.argv[1])
m.mu.mem_write(0x8422A18, b"\xc3")  # (get_parts_data's own sprintf and printf stubbed out)
m.mu.mem_write(0x8422238, b"\xc3")
m.mu.mem_map(0x30000000, 0x100000)

ROWS = [(0, 1, n) for n in range(4)] + [(1, 1, 1)] + [(0, 2, n) for n in range(4)] + \
       [(0, 3, n) for n in range(5)] + [(0, 4, n) for n in range(2)]
out = []
for gem, kind, num in ROWS:
    d = m.call(0x88E60C4, kind, num, 0, gem) & 0xFFFFFFFF
    out.append("4\t%s%s" % (m.cstr(m.r32(d)), m.cstr(m.r32(d + 0x20))))
# clSeqTgWearPartsWheelThread's banner: 16 what was done alone (font 4 datrums 11, the
# wheel's name is its logo), 17 the stock wheel's
out += ["4\t装着完了！", "4\t純正ホイールに交換完了！"]
# 18.. the neons (get_parts_data(6, 0..6), (8, 7..12)): 取り外し完了！ (none), the straight
# neons, the spot neons
for kind, num in [(6, n) for n in range(7)] + [(8, n) for n in range(7, 13)]:
    d = m.call(0x88E60C4, kind, num, 0, 0) & 0xFFFFFFFF
    out.append("4\t%s%s" % (m.cstr(m.r32(d)), m.cstr(m.r32(d + 0x20))))
# 31.. the stickers' patterns (get_parts_data(5, n): 1 line 1, 11 line 2, 21 fire 1, 31 fire 2,
# 41 namco, 42 Pac-Man, 43 works colours, 48 line 3, 58 fire 3, 68 tribal; none is row 18's)
for num in (1, 11, 21, 31, 41, 42, 43, 48, 58, 68):
    d = m.call(0x88E60C4, 5, num, 0, 0) & 0xFFFFFFFF
    out.append("4\t%s%s" % (m.cstr(m.r32(d)), m.cstr(m.r32(d + 0x20))))
open(os.path.join(os.path.dirname(os.path.abspath(__file__)), "wear_texts.txt"), "w", encoding="utf-8").write("\n".join(out) + "\n")

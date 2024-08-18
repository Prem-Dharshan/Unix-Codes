### Seq

Usage: seq [OPTION]... LAST

  or:  seq [OPTION]... FIRST LAST

  or:  seq [OPTION]... FIRST INCREMENT LAST

Print numbers from FIRST to LAST, in steps of INCREMENT.

-f, --format=FORMAT      use printf style floating-point FORMAT

-s, --separator=STRING   use STRING to separate numbers (default: \n)

-w, --equal-width        equalize width by padding with leading zeroes

```sh
seq 10
seq 1 10
seq 1 2 10
seq -w 1 10
seq -f "22PW%02d" 1 10
seq -f "22PW%05.2f" 1 10
printf "22PW%05.2f\n" {1..10}
```

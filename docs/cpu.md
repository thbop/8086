# The 8086 CPU
[back](docs.md)

For more references, check the [README.md](../README.md#references) file.

## Register Operations

Called an E (and possibly G) argument addressing code by
[mlsite.net](http://www.mlsite.net/8086/#addr_E), *register operations* is my
name for inter-register addressing. How the processor knows that `mov ax, bx`
moves `bx` into `ax` instead of `cx` into `si`. I kind of just figured out how
this works via experimentation with nasm. Essentially the "address" is composed
of two 3 bit numbers--one for the source register and the other for the
destination register. Here are the addresses of every register depending on the
instruction:
|  Type  | AX | AL | AH | BX | BL | BH | CX | CL | CH | DX | DL | DH | SP | BP | SI | DI | CS | DS | SS | ES |
|--------|----|----|----|----|----|----|----|----|----|----|----|----|----|----|----|----|----|----|----|----|
| Eb  Gb |    | 00 | 04 |    | 03 | 07 |    | 01 | 05 |    | 02 | 06 |    |    |    |    |    |    |    |    |
| Ev  Gv | 00 |    |    | 03 |    |    | 01 |    |    | 02 |    |    | 04 | 05 | 06 | 07 |    |    |    |    |

Both addresses are stored as a byte argument in this format:

`0b11SS SDDD`

`S` is the source address and `D` is destination address.


## Classes and Targets
To speed up execution time, I am separating instruction decoding into two
stages. The first stage decodes the upper four bits (class), while the
second stage decodes the lower four bits (target). Some classes, like 0xB0
(possibly only 0xB0) consist purely of moving immediate values into registers;
thus, the function that decodes 0xB0's targets is called `CPUMoveImmediate`.
Other classes, such as 0x80 contain multiple types of instructions, thus
0x80's decode function is named `CPUExecuteClass80`.
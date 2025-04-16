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
| Opcode | AX | AL | AH | BX | BL | BH | CX | CL | CH | DX | DL | DH | SP | BP | SI | DI | CS | DS | SS | ES |
|--------|----|----|----|----|----|----|----|----|----|----|----|----|----|----|----|----|----|----|----|----|
|  0x88  |    | 00 | 04 |    | 03 | 07 |    | 01 | 05 |    | 02 | 06 |    |    |    |    |    |    |    |    |
|  0x89  | 00 |    |    | 03 |    |    | 01 |    |    | 02 |    |    | 04 | 05 | 06 | 07 |    |    |    |    |

Both addresses are stored as a byte argument in this format:

`0b11SS SDDD`

`S` is the source address and `D` is destination address.

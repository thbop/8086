# Memory
[back](docs.md)

Some notes and reading on how the 8086 handles memory.

## Memory Segmentation
0x1234:0x5678

segment:offset

Each segment contains 64 kilobytes of memory. Segments overlap every 16 bytes.

real_address = segment * 16 + offset

Code access registers:
- CS - currently running code segment
- IP - program counter; offset from CS

Other segment registers:
- DS - data segment
- SS - stack segment
- ES - extra segment

Much of this is copied from the source: [nanobyte's hello world os video](https://www.youtube.com/watch?v=9t-SPC7Tczc&list=PLFjM7v6KGMpiH2G-kT781ByCNC_0pKpPN&index=1&t=21s)

Further reading: [GeeksForGeeks.org](https://www.geeksforgeeks.org/memory-segmentation-8086-microprocessor/)
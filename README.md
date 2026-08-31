# dumbOS
It's an emulator of the dumb 8-64x01 processor. (The second version)

`8` 8 registers, everyone contains number from 0 to 255.
`64` 64 KB of RAM.
`x01` Version in hexadecimal. The second.

# How to use:
Enter the write bootloader file from the main folder.
In the code you'll see the program's array:
```c
uint8_t program[] = {}
```
There you can write your own code in hexadecimal for the dumb 8-64x01 CPU.
For example:
```
0x02, 0x00, 0x04,//D
0x0B, 0x00, 0x00, 0x00,
0x02, 0x00, 0x15,//U
0x0B, 0x00, 0x01, 0x00,
0x02, 0x00, 0x0D,//M
0x0B, 0x00, 0x02, 0x00,
0x02, 0x00, 0x02,//B
0x0B, 0x00, 0x03, 0x00,
0x02, 0x00, 0x0F,//O
0x0B, 0x00, 0x05, 0x00,
0x02, 0x00, 0x13,//S
0x0B, 0x00, 0x06, 0x00,
0x04, 0x00, 0x07
```
Writes to the register 0x00 a letter, push it to the GPU's memory and then makes a infinity loop.

# Command instructions:
```
mov reg to reg         = 0x01, r1, r2
mov immediate to reg   = 0x02, r1, num
mov to reg from memory = 0x03, r1, address, offset
jmp address            = 0x04, address, offset
add immediate to reg   = 0x05, r1, num
add reg to reg         = 0x06, r1, r2
hlt                    = 0x07 (WARNING, write 0x07 for finish the program)
sub reg to reg         = 0x08, r1, r2
sub immediate to reg   = 0x09, r1, num
move num to ram        = 0x0A, addr1, addr2, num
move reg to vram       = 0x0B, addr1, addr2, reg_addr
move to reg from vram  = 0x0C, reg_addr, addr1, addr2
```
(Note: In dumb 8-64x01 the instruction set is very short, so you can't load anything into RAM. Working with registers and graphics memory is all you can do.)

When the code is written, you can compile everything to `build` file on Linux:

1) Open the terminal in the main directory and run:
```
chmod +x compile.sh
```

2) Run the bash script:
```
./compile.sh
```
(Note: You should have GCC installed. And you should be on system that uses X11 to show the graphics)
Then you'll see two new files named `disk.bin` and `build`.

3) Run the virtual machine:
```
./build
```
Then you'll see your program work on pretty 640x480 GUI.
<img width="1862" height="1005" alt="изображение" src="https://github.com/user-attachments/assets/f718d3da-5159-41ea-bf33-41ee6970b1ef" />

# Errors

`No disk found!`
If you run CPU before write the program to disk, you'll see this error.

`Error, PC is out of RAM.` 
You'll see it when PC is bigger than `64 KB`

`Sorry, the programmer is dumb, he doesnt know how to write code well.`
`I DONT KNOW HOW TO READ YOUR CODE.`
When you are bad at your job.

`You want to contact with register *** but I have only *** registers`
`Are you good?`
When you forget about you have only 8 registers.

`File cant be open`
When the script can't open disk.bin

`Written error.`
When size of written bytes != size of your program.

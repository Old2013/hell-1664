#include <stdio.h>
#include <stdint.h>

// You can change the program to write your code on dumb 8-64x01
// Example program:
uint8_t program[] = 
    {
0x02, 0x00, 0x08,//H
0x0B, 0x00, 0x00, 0x00,
0x02, 0x00, 0x05,//E
0x0B, 0x00, 0x01, 0x00,
0x02, 0x00, 0x0C,//L
0x0B, 0x00, 0x02, 0x00,
0x02, 0x00, 0x0C,//L
0x0B, 0x00, 0x03, 0x00,
0x02, 0x00, 0x0F,//O
0x0B, 0x00, 0x05, 0x00,
0x02, 0x00, 0x13,//S
0x0B, 0x00, 0x06, 0x00,
0x04, 0x00, 0x07

    };

int main()
{
    
    size_t size = sizeof(program); 
    
    // Open the disk and write to it the code
    FILE *disk_file = fopen("disk.bin", "wb");

    if (disk_file == NULL) {
        perror("File cant be open");
        return 1;
    }
    
    size_t written;
    
    if (size < 512)
    {
        uint8_t disk[512];
        for (int i = 0; i < 512; i++)
        {
            if (i < size) disk[i] = program[i];
            else disk[i] = 0x00;
        }
        written = fwrite(disk, 1, 512, disk_file);
    }
    else written = fwrite(program, 1, size, disk_file);
    
    if (written != size) {
        perror("Written error.");
        fclose(disk_file);
        return 1;
    }
    
    fclose(disk_file);

    printf("Writed %zu bytes to disk.bin\n", written);

    return 0;
}

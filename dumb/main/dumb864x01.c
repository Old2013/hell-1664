#include <stdio.h>
#include <stdint.h>
#include "gpux01.h"

uint8_t RAM[65536]; //64 KB
uint8_t rgster[8]; // 8 registers

void print_exit_status();
int regs_check(uint8_t reg);



int main()
{
    uint16_t PC = 0;
    winit(WIDTH, HEIGHT);
    vraminit();
    gpu_tick();

    // Read bootloader form disk and write it to RAM
    FILE *disk = fopen("disk.bin", "rb");
    
    if (!disk) {printf("No disk found!\n"); return 1;}

    size_t bytes_read = fread(&RAM[0x7C00], 1, 512, disk);
    printf("Readed %zu bytes from disk.\n", bytes_read);
    printf("Success writing bootloader to RAM.\n\n");
    PC = 0x7C00;
    fclose(disk);
    ////////////////////////////////////////////////


    while (1)
    {
        if (PC >= sizeof(RAM)) 
        {
            printf("\nError, PC is out of RAM.\n");
            return 1;
        }

        uint8_t opcode = RAM[PC];
        switch (opcode)
        {
            //*Command instuctions:
            // mov reg to reg         = 0x01, r1, r2
            // mov immediate to reg   = 0x02, r1, num
            // mov to reg from memory = 0x03, r1, address, offset
            // jmp address            = 0x04, address, offset
	    // add immediate to reg   = 0x05, r1, num
            // add reg to reg         = 0x06, r1, r2
            // hlt                    = 0x07 (WARNING, write 0x07 for finish the program)
	    // sub reg to reg         = 0x08, r1, r2
            // sub immediate to reg   = 0x09, r1, num
	    // move num to ram        = 0x0A, addr1, addr2, num
            // move reg to vram       = 0x0B, addr1, addr2, reg_addr
            // move to reg from vram  = 0x0C, reg_addr, addr1, addr2
//*//

            case 0x01:
            {
                PC++;
                uint8_t r1 = RAM[PC];
                if (regs_check(r1)) return 1;
                PC++;
                uint8_t r2 = RAM[PC];
                if (regs_check(r2)) return 1;

                rgster[r1] = rgster[r2];
                break;
            };
            
            case 0x02:
            {
                PC++;
                uint8_t reg = RAM[PC];
                if (regs_check(reg)) return 1;
                PC++;
                uint8_t num = RAM[PC];

                rgster[reg] = num;
                break;
            };

            case 0x03:
            {
                PC ++;
                uint8_t reg = RAM[PC];
                if (regs_check(reg)) return 1;
                PC ++;
                uint8_t address = RAM[PC];
                PC++;
                uint8_t offset = RAM[PC];

                rgster[reg] = RAM[address*256+offset];
                
                break;
            };

            case 0x04:
            {
                PC ++;
                uint8_t address = RAM[PC];
                PC++;
                uint8_t offset = RAM[PC];

                PC = address*256+offset;
                continue;
                break;
            };

	    case 0x05:
            {
		PC ++;
		uint8_t r1 = RAM[PC];
		PC ++;
		uint8_t num = RAM[PC];
		
		rgster[r1] += num;
		break;
	    };

            case 0x06:
            {
                PC ++;
                uint8_t r1 = RAM[PC];
                if (regs_check(r1)) return 1;
                PC ++;
                uint8_t r2 = RAM[PC];
                if (regs_check(r2)) return 1;

                rgster[r1] += rgster[r2];
                break;
            };
            
            case 0x07:
            {
                print_exit_status();
                return 0;
            };

	    case 0x08:
	    {
	        PC ++;
	        uint8_t r1 = RAM[PC];
	        PC ++;
		uint8_t r2 = RAM[PC];
		
		rgster[r1] -= rgster[r2]; 
	        break;
 	    };

	    case 0x09:
	    {
	 	PC ++;
		uint8_t r1 = RAM[PC];
		PC ++;
		uint8_t num = RAM[PC];
		
		rgster[r1] -= num;
	        break;
	    };

	    case 0x0A:
	    {
		PC ++;
		uint8_t addr1 = RAM[PC];
		PC ++;
		uint8_t addr2 = RAM[PC];
		PC ++;
		uint8_t num = RAM[PC];
		
		uint8_t final_addr = addr1*256+addr2;
		RAM[final_addr] = num;
		break;
	    };

            case 0x0B:
            {
                PC ++;
                uint8_t addr1 = RAM[PC];
                PC ++;
                uint8_t addr2 = RAM[PC];
                PC ++;
                uint8_t reg_addr = RAM[PC];

                uint8_t final_addr = addr1*256+addr2;
                VRAM[final_addr] = rgster[reg_addr];
                break;
            };

            case 0x0C:
            {
                PC ++;
                uint8_t reg_addr = RAM[PC];
                PC ++;
                uint8_t addr1 = RAM[PC];
                PC ++;
                uint8_t addr2 = RAM[PC];

                uint8_t final_addr = addr1*256+addr2;
                rgster[reg_addr] = VRAM[final_addr];
                break;
            };

//            case 0x0D:
//            {
//                PC ++;
//                uint8_t r1_addr = RAM[PC];
//                PC ++;
//                uint8_t r2_addr = RAM[PC];
//                PC ++;
//                uint8_t addr1 = RAM[PC];
//                PC ++;
//                uint8_t addr2 = RAM[PC];
//
//                uint8_t mem_addr
//                break;
//            };


            case 0x00: break;

            default:
            {
                printf("\nSorry, the programmer is dumb, he doesnt know how to write code well.\nI DONT KNOW HOW TO READ YOUR CODE.\n\n");
                return 1;
            }
        }
        PC++;
        gpu_tick();
    }

}

void print_exit_status()
{
    printf("\n\nRegs:\n");
    for (int i = 0; i < sizeof(rgster); i++)
    {
        printf("%d = 0x%02x\n", i, rgster[i]);
    }
}

int regs_check(uint8_t reg)
{
    if (reg >= sizeof(rgster))
    {
        printf("\nYou want to contact with register %02x but I have only %zu registers\nAre you good?\n\n", reg, sizeof(rgster));
        return 1;
    } else return 0;
}

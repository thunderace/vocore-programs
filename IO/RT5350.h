#include <sys/mman.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>

// Peripherie
#define BLOCK_SIZE			4096
#define Bus_Base			0x10000000
#define PIO_Base			0x600

// IO Register
#define IO_Data_Low			0x20
#define IO_Data_High			0x70
#define IO_Dir_Low			0x24
#define IO_Dir_High			0x74
#define IO_Pol_Low			0x28
#define IO_Pol_High			0x78
#define IO_Set_Low			0x2c
#define IO_Set_High			0x7c
#define IO_Clear_Low			0x30
#define IO_Clear_High			0x80
#define IO_Toggle_Low			0x34
#define IO_Toggle_High			0x84

typedef struct _RT5350_Device {
	unsigned long Adresse;
	int Memory;
	void *Map;
	volatile unsigned int *Addr;
}RT5350_DEVICE;

int RAM_Map(RT5350_DEVICE *device);
int GPIO_Init(void);
int Set_Dir(int IO, char *Dir);
int Toggle_IO(int IO);
int Set_IO(int IO);
int Clear_IO(int IO);
int Read_IO(int IO);
int Set_Pol(int IO, int Pol);

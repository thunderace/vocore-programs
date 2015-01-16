#include "RT5350.h"

int Offset = 0;
int Shift = 0;

RT5350_DEVICE Bus = {Bus_Base};


int RAM_Map(RT5350_DEVICE *device)
{
	device->Memory = open("/dev/mem", O_RDWR);

	if(device->Memory < 0)
	{
		printf("No access to /dev/mem!\n\r");
		return -1;
	}

	device->Map = mmap(
		NULL,
		BLOCK_SIZE,
		PROT_READ | PROT_WRITE,
		MAP_SHARED,
		device->Memory,
		device->Adresse
	);

	if(device->Map < 0)
	{
		printf("Error during mapping of the Memory!\n\r");
		return -1;
	}

 	device->Addr = (volatile unsigned int *)device->Map;

	return 0;
}

int GPIO_Init(void)
{
	if(RAM_Map(&Bus) == -1)
	{
		printf("Error during mapping of the PIO Region!\n\r");
		return -1;
	}

	return 0;
}

int Set_Dir(int IO, char *Dir)
{
	if(IO < 22)
	{
		Offset = PIO_Base + IO_Dir_Low;
		Shift = IO;
	}
	else if((IO > 21) && (IO < 29))
	{
		Offset = PIO_Base + IO_Dir_High;
		Shift = IO - 22;
	}
	else
	{
		printf("Wrong value for IO!\n\r");
		return -1;
	}

	if(Dir = "O")
	{
		*(Bus.Addr + (Offset >> 2)) |= (1 << Shift);
	}
	else if(Dir = "I")
	{
		*(Bus.Addr + (Offset >> 2)) &= ~(1 << Shift);
	}
	else
	{
		printf("Wrong value for Dir!\n\r");
		return -1;
	}

	return 0;
}

int Toggle_IO(int IO)
{
	if(IO < 22)
	{
		Offset = PIO_Base + IO_Toggle_Low;
		Shift = IO;
	}
	else if((IO > 21) && (IO < 29))
	{
		Offset = PIO_Base + IO_Toggle_High;
		Shift = IO - 22;
	}
	else
	{
		printf("Wrong value for IO!\n\r");
		return -1;
	}

	*(Bus.Addr + (Offset >> 2)) |= (1 << Shift);

	return 0;
}

int Set_IO(int IO)
{
	if(IO < 22)
	{
		Offset = PIO_Base + IO_Set_Low;
		Shift = IO;
	}
	else if((IO > 21) && (IO < 29))
	{
		Offset = PIO_Base + IO_Set_High;
		Shift = IO - 22;
	}
	else
	{
		printf("Wrong value for IO!\n\r");
		return -1;
	}

	*(Bus.Addr + (Offset >> 2)) |= (1 << Shift);
}

int Clear_IO(int IO)
{
	if(IO < 22)
	{
		Offset = PIO_Base + IO_Clear_Low;
		Shift = IO;
	}
	else if((IO > 21) && (IO < 29))
	{
		Offset = PIO_Base + IO_Clear_High;
		Shift = IO - 22;
	}
	else
	{
		printf("Wrong value for IO!\n\r");
		return -1;
	}

	*(Bus.Addr + (Offset >> 2)) |= (1 << Shift);
}

int Read_IO(int IO)
{
	if(IO < 22)
	{
		Offset = PIO_Base + IO_Data_Low;
		Shift = IO;
	}
	else if((IO > 21) && (IO < 29))
	{
		Offset = PIO_Base + IO_Data_High;
		Shift = IO - 22;
	}
	else
	{
		printf("Wrong value for IO!\n\r");
		return -1;
	}

	return (*(Bus.Addr + (Offset >> 2)) && Shift); 
}

int Set_Pol(int IO, int Pol)
{
	if(IO < 22)
	{
		Offset = PIO_Base + IO_Pol_Low;
		Shift = IO;
	}
	else if((IO > 21) && (IO < 29))
	{
		Offset = PIO_Base + IO_Pol_High;
		Shift = IO - 22;
	}
	else
	{
		printf("Wrong value for IO!\n\r");
		return -1;
	}

	if(Pol == 0)
	{
		*(Bus.Addr + (Offset >> 2)) &= ~(1 << Shift);
	}
	else if (Pol == 1)
	{
		*(Bus.Addr + (Offset >> 2)) = (1 << Shift);
	}
	else
	{
		printf("Wrong value for Pol!\n\r");
		return -1;		
	}
}



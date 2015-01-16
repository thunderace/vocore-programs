#include <sys/types.h>
#include <sys/mman.h>
#include <err.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <math.h>

#define BLOCK   4096
#define BASE   0x10000000

unsigned int* gpio;

void GPIO_Init(){   // Inicializa los GPIO 22-26... OK
   
   int Memory;
   
   Memory = open("/dev/mem", O_RDWR);

     if(Memory==-1) 
      err(1, "Error abriendo /dev/mem\n\r");
        else {
      gpio = mmap(0, BLOCK, PROT_READ|PROT_WRITE,  MAP_SHARED, Memory, BASE);
      *(gpio + (0x674 >> 2)) = 0;
   }

   close(Memory);
}

void GPIO_Dir(int numero, char accion){      // Define los GPIO 22-26 como Entrada/Salida... OK

   int potencia = numero - 22;
   int GPIO_number = pow(2, potencia);

   // numero va desde 22 a 26, los GPIO libres...

   // accion:  
   //   'I' = GPIO definido como entrada
   //   'O' = GPIO definido como salida

   if ((numero>=22) && (numero<=26))
      switch(accion){
         case 'O': *(gpio + (0x674 >> 2)) = *(gpio + (0x674 >> 2)) | GPIO_number; break;
         case 'I': *(gpio + (0x674 >> 2)) = *(gpio + (0x674 >> 2)) & ~GPIO_number; break;
         default: err(1, "\nAccion no reconocida...\n\r"); break;
      }
   else err(1, "\nGPIO fuera de rango...\n\r");
}

void GPIO_Action(int numero, char accion){

   int potencia = numero - 22;
   int GPIO_number = pow(2, potencia);
   int base = 0;

   //numero va desde 22 a 26, los GPIO libres...
   //accion:
   //   'S' = GPIO a "set", la salida entrega 1 logico.
   //   'R' = GPIO a "reset", la salida entrega 0 logico.

   switch(accion){
      case 'S': base = 0x67c; break;   
      case 'R': base = 0x680; break;
      default: err(1, "\nAccion no reconocida...\n\r");break;
   }

   if ((numero>=22) && (numero<=26))
      *(gpio + (base >> 2)) = GPIO_number;
   else
      err(1, "\nGPIO fuera de rango...\n\r");

}

int GPIO_Read(int numero){

   int potencia = numero -22;
   int GPIO_number = pow(2, potencia);
   int lectura = 0;

   // numero va desde 22 a 26, los GPIO libres...
   // lectura entregara 1 si la entrada esta a "1" logico, correspondiente a un nivel de hasta 3.3 voltios.
   // lectura entregara 0 si la entrada esta a "0" logico, correspondiente a un nivel de 0 voltios.
   // por las caracteristicas de Vocore, no utilizar mas de 3.3 Voltios en la entrada o podria dañarse.
   // no conectar una entrada a 0, para despues entregar salida "1", podria dañar el Vocore.

   if((numero>=22) && (numero<=26))
      lectura = *(gpio + (0x670 >> 2)) & GPIO_number;
   else
      err(1, "\nGPIO fuera de rango...\n\r");

   if(lectura>0)
      lectura = 1;
   else
      lectura = 0;
   return lectura;
}

void GPIO_Toggle(int numero, char accion){
   
   int potencia = numero -22;
   int GPIO_number = pow(2, potencia);

   // numero va desde 22 a 26, los GPIO libres...
   // accion:
   //   'Y' = Toggle activado en el GPIO "numero"
   //   'N' = Toggle desactivado en el GPIO "numero"
   
   if ((numero>=22) && (numero<=26))
      switch(accion){
         case 'Y': *(gpio + (0x684 >> 2)) = *(gpio + (0x684 >> 2)) | GPIO_number; break;
         case 'N': *(gpio + (0x684 >> 2)) = *(gpio + (0x684 >> 2)) & ~GPIO_number; break;
         default: err(1, "\nAccion no reconocida...\n\r"); break;
      }
   else
      err(1, "\nGPIO fuera de rango...\n\r");
}
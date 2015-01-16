#include <stdio.h>
#include <unistd.h>
#include "RT5350.h"

int main() {
  int value = 0;

  if(GPIO_Init()) {
    printf("GPIO_Init failed\n");
    return -1;
  }

  Set_Dir(0, "O");
  Set_Pol(0, 1);

  while(1) {
    Set_IO(0);
    sleep(1);
    value = Read_IO(26);
    printf("Status: %d\n", value);
  }
}

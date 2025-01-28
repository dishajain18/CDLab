#include <stdio.h>
#iclude <stdlib>
#define ab 12

int rand(int a)
{
  return a%3;
}

int main() {
    int a = 5;
    char b[3];
    if (a > rand(a)) {
        a = a + 1;
    } else {
        a = a - 1;
        
    }
}

#include <stdio.h>
#include <stdlib.h>

/* IMPLEMENT ME: Declare your functions here */
int add (int a, int b);
int subtract (int a, int b);
int multiply (int a, int b);
int divide (int a, int b);
int end(int a, int b);
int (*ptrArr[5])(int, int);


int main (void)
{
  while(1){
    /* IMPLEMENT ME: Insert your algorithm here */
    int input, a = 6, b = 3;
    ptrArr[0] = add;
    ptrArr[1] = subtract;
    ptrArr[2] = multiply;
    ptrArr[3] = divide;
    ptrArr[4] = end;
  
    printf("Operand 'a' : %d | Operand 'b' : %d\n", a, b);
    printf("Specify the operation to perform (0 : add | 1 : subtract | 2 : Multiply | 3 : divide | 4 : exit):\n ");
    scanf("%d", &input);
  
    printf("%d\n", (int)(*ptrArr[input])(a,b));
  }
  return 0;
}

/* IMPLEMENT ME: Define your functions here */
int add (int a, int b) { printf ("Adding 'a' and 'b'\n"); return a + b; }
int subtract (int a, int b) { printf ("Subtracting 'a' and 'b'\n"); return a - b; }
int multiply (int a, int b) { printf ("Multiplying 'a' and 'b'\n"); return a * b; }
int divide (int a, int b) { printf ("Dividing 'a' and 'b'\n"); return a / b; }
int end(int a, int b) {exit(0); return 0; }


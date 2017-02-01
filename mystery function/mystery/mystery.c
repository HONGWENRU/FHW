#include    <stdio.h>
#include    <string.h>
#include    <stdlib.h>
#include    <math.h>



int mystery(int n) {
    int a = 1, b = 1;
    int i;
    for (i = 3; i <= n; i++) {
    	int c = a + b;
    	a = b;
    	b = c;
    }
    return b;
}

int main(int argc, char**argv)
{

char *p=*(argv+1);
int i= atoi(p); int b=0;
if(i>199){
printf("value:	 %d\n",b);return 0;}
b=mystery(i);
printf("value:	 %d\n",b);
return 0;
}

#include  <stdio.h>
#include  "nCr.h"
#include  <string.h>
#include  <stdlib.h>
#include <sys/time.h>
#include <unistd.h>
#include <error.h>


char *decimaltochar( long a){
	char *result; result=(char*)malloc(100*sizeof(char));
	if(a==0){
		result=strcpy(result,"0\0");return result;
	}
long decimalNumber,quotient;
	int i=0;     char temp;
	char *string;
      string=(char*)malloc(100*sizeof (char));
    decimalNumber=a;
	quotient = decimalNumber;
	while(quotient!=0) {
		temp ='0'+( quotient % 10);
		string[i++]=temp;
		quotient = quotient / 10;
	}
	string[i]='\0';

	
	int b=0,n;
	for( n=strlen(string)-1;n>=0;n--){
		result[b]=string[n];a++;b++;
	}
	free(string);
	result[b]='\0';
	return result;
}








int main(int argc,char  **argv){




struct  timeval start;
struct  timeval end;
unsigned  long diff=0;
gettimeofday(&start,NULL);
	
	char *p=*(argv+1);

        if(strcmp(p,"-h")==0){
printf("Usage: formula <positive integer>\n");
return 0;}
	
	int a=atol(p);
    char *result;
    result=(char*)malloc(500*sizeof(char));

	int i=0;
	
	while(i<=a){

if(i==0){
    int exp=nCr(a,i);
if(exp==0){
fprintf(stderr,"Error!!data overflow\n");
gettimeofday(&end,NULL);
diff = 1000000 * (end.tv_sec-start.tv_sec)+ end.tv_usec-start.tv_usec;
printf("Time Required =%ld microsecond\n",diff);
return 0;}
    char *want=decimaltochar(exp);
    result=strcat(result,want);
    result=strcat(result,"+");
    i++;continue;

}

else if(i!=0&&i!=a){
    int exp=nCr(a,i);
if(exp==0){
fprintf(stderr,"Error!!data overflow\n");
gettimeofday(&end,NULL);
diff = 1000000 * (end.tv_sec-start.tv_sec)+ end.tv_usec-start.tv_usec;
printf("Time Required =%ld microsecond\n",diff);
return 0;}
    char *want=decimaltochar(exp);
    result=strcat(result,want);
    result=strcat(result,"*");
    result=strcat(result,"x");
    result=strcat(result,"^");
    result=strcat(result,decimaltochar(i));
    result=strcat(result,"+");
    i++;continue;
}
else if(i==a){
    int exp=nCr(a,i);
if(exp==0){
fprintf(stderr,"Error!!data overflow\n");
gettimeofday(&end,NULL);
diff = 1000000 * (end.tv_sec-start.tv_sec)+ end.tv_usec-start.tv_usec;
printf("Time Required =%ld microsecond\n",diff);
return 0;}
    char *want=decimaltochar(exp);
    result=strcat(result,want);
    result=strcat(result,"*");
    result=strcat(result,"x");
    result=strcat(result,"^");
    result=strcat(result,decimaltochar(i));
    i++;continue;
}
	}


    result=strcat(result,"\0");
    
    printf("%s\n",result);
    free(result);
    
gettimeofday(&end,NULL);
diff = 1000000 * (end.tv_sec-start.tv_sec)+ end.tv_usec-start.tv_usec;
printf("Time Required =%ld microsecond\n",diff);
    
    
	
	
	
	
	
	return 0;
}



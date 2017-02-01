#include    <stdio.h>
#include    <string.h>
#include    <stdlib.h>
#include    <math.h>
#include    <error.h>

	
	
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

 
long hextodecimal(char*s)
{
char *d=s	;
int i=strlen(d)-1;
int t,n=0;
long sum=0;
for(;i>=0;i--)
{
if(d[i]<='9')
{
t=d[i]-'0';}
else if(d[i]>='a'&&d[i]<='z'){
t=d[i]-'a'+10;}
else if(d[i]>='A'&&d[i]<='Z'){
t=d[i]-'A'+10;}
sum=t*pow(16,n++)+sum;
}
return sum;
}



long decimaltoctal(long a){
	
	long octal=0;
    long n=a;
	int remainder=0;long i=1;
	  while(n != 0) {
        remainder = n%8;
        n = n/8;
        octal= octal + (remainder*i);
        i = i*10;
    }
    return octal;
}

int errordetector(char *a){
	char *temp=a;int sign=0;
	if(*temp=='o'){temp++;
while(*temp>='0'&&*temp<='7'){
	temp++;
}
		if(*temp!='\0'){
		 sign=1;
	}}
	
	if(*temp=='x'){temp++;
while((*temp>='0'&&*temp<='9')||(*temp>='A'&&*temp<='F')||(*temp>='a'&&*temp<='f')){
	temp++;
}
		if(*temp!='\0'){
			
		sign=2;} 
	}
	
	if(*temp=='b'){temp++;
while(*temp>='0'&&*temp<='1'){
	temp++;
}
		if(*temp!='\0'){
		sign=3;} 
	}	
	
	
	if(*temp=='d'){temp++;
while(*temp>='0'&&*temp<='9'){
	temp++;
}
		if(*temp!='\0')sign=4; 
	}	
	return sign;
}






long decimaltobinary(long a){
	
	long binary=0;
    long n=a;
	int remainder=0;long i=1;
	  while(n != 0) {
        remainder = n%2;
        n = n/2;
        binary= binary + (remainder*i);
        i = i*10;
    }
    return binary;
}

long octaltodecimal(long a ){
	long w=a,need=0;int i=0;
	while(w!=0){
		
		
	need=w%10*pow(8,i)+need;
		i++;
		
		w=w/10;}
	return need;
	
	
	
	
	
}
char *decimaltohex(long a){

long int decimalNumber,quotient;
	int i=0;     char temp;
	char *hexadecimalNumber;
	hexadecimalNumber=(char*)malloc(100*sizeof (char));
    decimalNumber=a;
	quotient = decimalNumber;
	while(quotient!=0) {
		temp = quotient % 16;
		if( temp < 10)
		           temp =temp + 48; else
		         temp = temp + 55;
		hexadecimalNumber[i++]=temp;
		quotient = quotient / 16;
	}
	hexadecimalNumber[i]='\0';
	char *result; result=(char*)malloc(100*sizeof(char));
	
	int b=0,n;
	for( n=strlen(hexadecimalNumber)-1;n>=0;n--){
		result[b]=hexadecimalNumber[n];a++;b++;
	}
	result[b]='\0';
	return result;
}

//long sum(long first,long second){
//	
//	 long int binary1=first,binary2=second,sumanation=0;
//    int i=0,remainder = 0,sum[32];
//
//    while(binary1!=0||binary2!=0){
//         sum[i++] =  (binary1 %10 + binary2 %10 + remainder ) % 2;
//         remainder = (binary1 %10 + binary2 %10 + remainder ) / 2;
//         binary1 = binary1/10;
//         binary2 = binary2/10;
//    }
//
//    if(remainder!=0)
//        {
//		  sum[i++] = remainder;}
//		  
//	while(i!=0){
//	--i;
//		sumanation+=sum[i]*pow(10,i);
//	}
//	return sumanation;
//	}
//	
	
	
long binarytodecimal(long binary){
	long w=binary,need=0;int i=0;
	while(w!=0){
		
		
	need=w%10*pow(2,i)+need;
		i++;
		
		w=w/10;}
	return need;
	
}

int main (int argc,char **argv){


char *op=*(argv+1);    char *input= *(argv+2);   char *input2=*(argv+3);  char *outputbase=*(argv+4);
// char *op="-";    char *input= "b111000";   char *input2="b111111";  char *outputbase="d";     
	 long inputd=0,input2d=0,result=0;

if(errordetector(input2)||errordetector(input)){
int a ,b;   a=errordetector(input);b=errordetector(input2);


if(a){

switch(a){
	case 1: fprintf(stderr,"ERROR!!number1 is not a octal!!\n");break;
	case 2: fprintf(stderr,"ERROR!!number1 is not a hex!!\n");break;	
	case 3: fprintf(stderr,"ERROR!!number1 is not a binary!!\n");break;
	case 4: fprintf(stderr,"ERROR!!number1 is not a decimal!!\n");break;
}
}	



if(b){
	
switch(b){
	case 1: fprintf(stderr,"ERROR!!number2 is not a octal!!\n");break;
	case 2: fprintf(stderr,"ERROR!!number2 is not a hex!!\n");break;	
	case 3: fprintf(stderr,"ERROR!!number2 is not a binary!!\n");break;
	case 4: fprintf(stderr,"ERROR!!number2 is not a decimal!!\n");break;
}
}
	
	
	
	
	
	
	

return 0;
}










 int turn=0,turn2=0;
 
 if(*input=='-'){
 	input++;turn=1;
 }
if(*input2=='-'){
	input2++;turn2=1;
}
if (*input=='d'){
 	input++;   inputd=atol(input);
 }
if(*input2=='d'){
    input2++;      input2d=atol(input2);
}
if(*input=='b'){
		
	input++;inputd=binarytodecimal(atol(input));
	}
if(*input2=='b'){
		input2++; input2d=binarytodecimal(atol(input2));
	}
if(*input=='o'){
	
	input++;inputd=octaltodecimal(atol(input));
}
if(*input2=='o'){
	input2++;input2d=octaltodecimal(atol(input2));
}
if(*input2=='x'){
	input2++;input2d=hextodecimal(input2);
}

if(*input=='x'){
	input++;inputd=hextodecimal(input);
}
if(turn){
	inputd=-inputd;
}
if(turn2){
	input2d=-input2d;
}
if(*op=='+'){
result=inputd+input2d;
}	
if(*op=='-'){
result=inputd-input2d;
}	




char *need;
	need=(char*)malloc(20*sizeof(char));
if(*outputbase=='b'){

	if(result<0){result=-result;
	   strcpy(need,"-b");strcat(need,decimaltochar(decimaltobinary(result)));
	}
   else 
   {strcpy(need,"b");strcat(need,decimaltochar(decimaltobinary(result)));}             
}
if(*outputbase=='x'){
		if(result<0){result=-result;
	   strcpy(need,"-x");strcat(need,decimaltohex(result));
	}
   else 
   {strcpy(need,"x");strcat(need,decimaltohex(result));}             
}

if(*outputbase=='o'){
		if(result<0){result=-result;
	   strcpy(need,"-o");strcat(need,decimaltochar(decimaltoctal(result)));
	}
   else 
   {strcpy(need,"o");strcat(need,decimaltochar(decimaltoctal(result)));}             
}

	



if(*outputbase=='d'){
	if(result<0){result=-result;
	   strcpy(need,"-d");strcat(need,decimaltochar(result));
	}
   else 
   {strcpy(need,"d");strcat(need,decimaltochar(result));}             
}
	
	

	printf("%s\n",need);
	

	return 0;

	

}




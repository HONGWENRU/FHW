#include    <stdio.h>
#include    <string.h>
#include    <stdlib.h>
#include    <math.h>
#include    <error.h>



void intToDecASCII(int a,char *b){
	int counter=0;char *c;int temp=0;char *t;
	if(a<0){temp=1;
		a=-a;
	}
	c=(char*)malloc(20*sizeof(char));
	t=(char*)malloc(20*sizeof(char));
	while(a!=0){
	
	t[counter]=a%10+'0';counter++;a=a/10;
}
int counter2=counter-1;int j=0;	
	for(;counter2>=0;counter2--){
		c[j]=t[counter2];
		j++;
		}
	c[j]='\0';

	if(temp==1){
	 b=strcpy(b,"-");b=strcat(b,c);
	}
	if(temp==0){
		b=strcpy(b,c);
	}
	free(c);free(t);
	}








static void
get_float_digit( float x, char * digit, int * pow10, float * remainder )
{
	int			p10;

	if ( x == 0.0 )
	{
		*digit = '0';			// digit is always '0'
		*pow10 = 0;
		*remainder = 0.0;
	}
	else
	{
		*pow10 = 0;			// start with 10^0
		while ( x >= 10.0 )		// reduce
		{
			x /= 10.0;		// large values get smaller
			*pow10 += 1;
		}
		while ( x < 1.0 )		// increase
		{
			x *= 10.0;		// small values get larger
			*pow10 -= 1;
		}
		*digit = '0';
		do {				// 10.0 > x >= 1.0
			x -= 1.0;
			*digit += 1;		// digit is always non-'0'zero
		} while ( x >= 1.0 );
		p10 = 0;
		while ( p10 > *pow10 )		// leading digit is now removed from x
		{
			x /= 10;
			p10 -= 1;
		}
		while ( p10 < *pow10 )
		{
			x *= 10;
			p10 += 1;
		}
		*remainder = x;
	}
}

// Improve efficiency by adding more while loops to handle larger powers of 10, e.g. :
// while ( x >= 1e1024 ) { x /= 1e0124; pow10 += 1024; }
// while ( x >= 1e512 ) { x /= 1e512; pow10 += 512; }
// ...
// while ( x >= 10.0 ) { x /= 10.0 ; pow10 += 1; }
// And
// while ( x < 1.0 ) { x *= 10; pow10 -= 1; }
// ...
// while ( x < 1e-512 ) { x *= 1e512; pow10 -= 512; }
// while ( x < 1e-1024 ) { x *= 1e1024; pow10 -= 1024; }

static void
append( char * s, char c )
{
	char		buf[2];

	buf[0] = c;
	buf[1] = '\0';
	strcat( s, buf );
}

union Number {
	int	i;
	float	f;
};

void
floatToASCII( float x, char * output )
{
	char		c;
	int		pow10, p10, plast;
	int		i;
	float		remainder;
	char		exponent[10];
	union Number	a;
	unsigned int	biasedExp;
	unsigned int	mantissa;
	int		sign;

	a.f = x;
	biasedExp = a.i >> 23 & 0x000000ff;
	mantissa = a.i & 0x007fffff;
	sign = a.i >> 31;
//	printf( "BKR x is %g.  biasedExp is %x  mantissa is %08x  sign is %d\n", x,
//		biasedExp, mantissa, sign );
	if ( biasedExp == 0xff )
	{
		if ( mantissa == 0 )
		{
			if ( sign != 0 )
			{
				strcpy( output, "-inf" );
//		printf( "BKR returning from file %s line %d\n", __FILE__, __LINE__ );
				return;
			}
			else
			{
				strcpy( output, "+inf" );
//		printf( "BKR returning from file %s line %d\n", __FILE__, __LINE__ );
				return;
			}
		}
		else
		{
			if ( sign != 0 )
			{
				strcpy( output, "-NaN" );
//		printf( "BKR returning from file %s line %d\n", __FILE__, __LINE__ );
				return;
			}
			else
			{
				strcpy( output, "+NaN" );
//		printf( "BKR returning from file %s line %d\n", __FILE__, __LINE__ );
				return;
			}
		}
	}
	output[0] ='\0';
	if ( x < 0.0 )
	{
		append( output, '-' );
		x = -x;					// make x positive
	}
	get_float_digit( x, &c, &pow10, &remainder );
	append( output, c );
	append( output, '.' );
	x = remainder;
	plast = p10 = pow10;			// pow10 set by get_float_digit()
	for ( i = 1 ; i < 7 ; i++ )		// 7 significant digits in 32-bit float
	{
		get_float_digit( x, &c, &p10, &remainder );
		if ( (plast - p10) > 1 )
		{
			append( output, '0' );	// fill in zero to next nonzero digit
			plast -= 1;
		}
		else
		{
			append( output, c );
			x = remainder;
			plast = p10;
		}
	}
	if ( pow10 < 0 )		// negative exponent
	{
		exponent[0] = 'e';
		intToDecASCII( pow10, exponent+1 );
	}
	else if ( pow10 < 10 )		// positive single-digit exponent
	{
		exponent[0] = 'e';
		exponent[1] = '+';
		exponent[2] = '0';
		intToDecASCII( pow10, exponent+3 );
	}
	else				// positive multi-digit exponent
	{
		exponent[0] = 'e';
		exponent[1] = '+';
		intToDecASCII( pow10, exponent+2 );
	}
	strcat( output, exponent );
}


long bittodecimal(char *input){
	unsigned long sum=0;
if(*input=='0'){
input++;

int counter=30;
while(counter>=0){
	while(*input=='1'){
		
		sum=sum+(*input-'0')*pow(2,counter);
		counter--;input++;
		}
	while(*input=='0'){
		counter--;input++;
	}
	}	
		
}

else if(*input=='1'){
	input++;
int counter=strlen(input)-1;int counter2=counter;
for(;counter>=0;counter--){
   if(input[counter]=='0'){
   input[counter]='1';continue;}
   if(input[counter]=='1'){
   input[counter]='0';continue;}
}
int remainder=0;input[strlen(input)-1]+=1;int temp;
	for(;counter2>=0;counter2--){
		temp=input[counter2]-'0';
         input[counter2] =(((input[counter2]-'0')+remainder)%2)+'0';
		 remainder = (((temp-0)+remainder)/2);}
         


int counter3=30;
while(counter3>=0){
	while(*input=='1'){
		
		sum=sum+(*input-'0')*pow(2,counter3);
		counter3--;input++;
		}
	while(*input=='0'){
		counter3--;input++;
	}
		}	
}

	return sum;	
}

char *decimaltochar(long a){

long int decimalNumber,quotient;
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
	char *result; result=(char*)malloc(100*sizeof(char));
	
	int b=0,n;
	for( n=strlen(string)-1;n>=0;n--){
		result[b]=string[n];a++;b++;
	}
	free(string);
	result[b]='\0';
	return result;
}

int egbittodec(char *a){
	int f=7,sum=0;
	for(;f>=0;f--){
	
	sum=sum+((a[f]-'0')*pow(2,7-f));	
		
		
		
	}
	
	return sum;
	
	
	
}

double  esbittodec(char *a){
	double sum=0;
	int f=0;
	for(;f<=22;f++){
	if(a[f]=='0'){
		continue;
	}
	sum=1/((a[f]-'0')*pow(2,f+1))+sum;	
		
		
		
	}
	
	return sum;
	
	
	
}



int main (int argc,char **argv){
	
char *p=*(argv+1); char *type=*(argv+2);
//char *p; char *type;
unsigned long result;char *s;char*f;int exp;double w;double result2;int sign=0;char *r;char *check;int count=0;

 check=(char*)malloc(35*sizeof(char));
//p=(char*)malloc(35*sizeof(char));
 s=(char*)malloc(35*sizeof(char));
f=(char*)malloc(35*sizeof(char));
// type=(char*)malloc(35*sizeof(char));
  r=(char*)malloc(35*sizeof(char));
  check=p;
// strcpy(p,"11000000010010010000111111011011"); strcpy(type,"float");
while(*check=='0'||*check=='1'){
	
	check++;count++;
}
if(count!=32){
	
	fprintf(stderr,"Eerror!!!this is a wrong flow!!!!\n");return 0;
}








if(strcmp(type,"int")==0){
	
	
	result=bittodecimal(p);
	if(*p=='0'){
	
	printf("%s\n",decimaltochar(result));return 0;}
	else if(*p=='1'){
	r=strcpy(r,"-"); r=strcat(r,decimaltochar(result));
	printf("%s\n",r);return 0;
	}
	
} 
 
 else if(strcmp(type,"float")==0){
 	

if(*p=='1'){
	sign=1;p++;
}
else if(*p=='0'){
	sign=0;p++;
}
s=strncpy(s,p,8);s[8]='\0';
f=strncpy(f,p+8,23);f[23]='\0';

if(strcmp(s,"11111111")==0){
	if(strcmp(f,"00000000000000000000000")==0){
		if(sign==1){
			
			printf("pinf\n");return 0;
		}
	    else if(sign==0){
	    	printf("ninf\n");return 0;
		}
	}
	else {
	printf("NaN\n");return 0;} ;
}
else{

if(strcmp(s,"00000000")==0){
result2=0;floatToASCII(0,r);
	if(sign==0){
	printf("%s\n",r);}
	else if(sign==1){char *wtf;
	wtf=(char*)malloc(35*sizeof(char));
	wtf=strcpy(wtf,"-");
	wtf=strcat(wtf,r);
	printf("%s\n",wtf);free(wtf);	
		
	}
}
else {


exp=egbittodec(s)-127;
free(s);
w=esbittodec(f);
free(f);
result2=(w+1)*pow(2,exp);
floatToASCII(result2,r);
if(sign==0){
printf("%s\n",r);return 0;}
if(sign==1){char*temp;
temp=(char*)malloc(35*sizeof(char));
temp[0]='-';
temp[1]='\0';
temp=strcat(temp,r);
printf("%s\n",temp);free(temp);
}

}


}

}





	return 0;
}

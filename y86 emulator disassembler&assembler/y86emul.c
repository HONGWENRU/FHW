#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define EAX 0
#define ECX 1
#define EDX 2
#define EBX 3
#define ESP 4
#define EBP 5
#define ESI 6
#define EDI 7

#define AOK "everything is fine\n"
#define HLT "halt instruction has been encountered\n"
#define ADR "some sort of invalid address\n"
#define INS "an invalid instruction\n"


char * getr(unsigned char a){

switch(a){
	case 0x00:
		return "%eax";
    case 0x01:
    	return "%ecx";
	case 0x02:
		return "%edx";
    case 0x03:
    	return "%ebx";
	case 0x04:
		return "%esp";
    case 0x05:
    	return "%ebp";
	case 0x06:
		return "%esi";
    case 0x07:
    	return "%edi";
	
	
}


}

struct cpu {

	int registers[9];
	int program_counter;
	int size;
	bool overflow;
	bool zero;
	bool negative;
	bool status;
} ;

bool disassembly=false;


char * substr(const char *inpStr, char *outStr, size_t startPos, size_t strLen) {
	strncpy(outStr, inpStr + startPos, strLen);
	outStr[strLen] = '\0';
	return outStr;
}

struct cpu Mycpu;

unsigned char *memory;






long hextodecimal(char*s)
{
char *d=s	;
int i=strlen(d)-1;
int t,n=0;
long sum=0;
for(i;i>=0;i--)
{
if(d[i]<='9')
{t=d[i]-'0';}
else if(d[i]>='A'&&d[i]<='Z'){
t=d[i]-'A'+10;}
else if(d[i]>='a'&&d[i]<='z'){
t=d[i]-'a'+10;}
sum=t*pow(16,n++)+sum;
}
return sum;
}










void initialize(char *filename){
	
	char *size;
char *directive;
char *inpt;
long sizeint;
long locationint;
char *location;
char* value ;
char* line;
int i,j;
	
    line=(char*)malloc(10000*sizeof(char));
	size=(char*)malloc(200*sizeof(char));
	directive=(char*)malloc(10000*sizeof(char));
	inpt=(char*)malloc(200*sizeof(char));
	location=(char*)malloc(200*sizeof(char));
	value=(char*)malloc(200*sizeof(char));
	
      Mycpu.negative=false;
       Mycpu.overflow=false;
          Mycpu.zero=false;

int a=0;

for(a;a<=8;a++){
	
	Mycpu.registers[a]=0;
}
	
    FILE* file = fopen(filename, "r"); 
 
 
   

     while(fgets(line, 1000, file) ){
     

           
		if(strstr(line,".size")){
		    size= strcpy(size,strtok(line,"\t\n"));
            size= strcpy(size,strtok(NULL,"\t\n"));
            sizeint=hextodecimal(size);
            Mycpu.size=sizeint;
            memory=malloc(sizeint*sizeof(unsigned char));
            continue;
			}
		   
		   
		   
		 if(strstr(line,".text")){
	        strtok(line,"\t\n");
            inpt=strcpy(inpt,strtok(NULL,"\t\n"));
           	directive=strcpy(directive,strtok(NULL,"\t\n"));
           	 j=0;  i=hextodecimal(inpt); 
           	Mycpu.program_counter=i;
           	char *sub_argument ;
           	sub_argument=(char*)malloc(10*sizeof(char));
			   while (j < strlen(directive)) {
					sub_argument = substr(directive,sub_argument, j, 2);
					memory[i] = (unsigned char) hextodecimal(sub_argument);
					i++;
					j = j + 2;}
           	continue;
		}
          
		   if(strstr(line,".byte")){
		   	location=strtok(line,"\t\n");
		   	location=strtok(NULL,"\t\n");
		   	value=strtok(NULL,"\t\n");
		   	locationint=hextodecimal(location);
		    memory[locationint]=(unsigned char)(hextodecimal(value));
	 	    continue;
		   }
		   
		   	if (strstr(line, ".string")) {
		   		strtok(line,"\t\n");
		   		location=strtok(NULL,"\t\n");
		   		value=strtok(NULL,"\t\n");
				i = hextodecimal(location);
				j = 1;
                     while (j <= (strlen(value))) {
				memory[i] = (unsigned char) value[j];
					i++;
					j++;
				}
			}
			if (strstr(line, ".long") ) {
			strtok(line,"\t\n");
			location=strtok(NULL,"\t\n");
			value=strtok(NULL,"\t\n"); 
			int long_argument= atoi(value);
			unsigned char fk;
			
			j = hextodecimal(location);
			
			memory[j]=long_argument&0x000000ff;
			memory[j+1]=(long_argument&0x0000ff00)>>8;
			memory[j+2]=(long_argument&0x00ff0000)>>16;
			memory[j+3]=(long_argument&0xff000000)>>24;
			 
			}
			
		if (strstr(line, ".bss") ) {
			strtok(line,"\t\n");
			location=strtok(NULL,"\t\n");
			value=strtok(NULL,"\t\n"); 			
				i = hextodecimal(value); 
				j = hextodecimal(location); 
				for (; i > 0; i--) {
					memory[j] = (unsigned char)0; 
					j++;
				}
			} 
              
    }

    fclose(file);
    free(line);
	free(size);
	free(directive);
	free(inpt);


}

void execute(){
	
	unsigned char temp1;
	
	unsigned char high;
	unsigned char low;
	
	int value ;
	unsigned int dest;
	unsigned int src;
	
	int temp;
	Mycpu.status=true;
	
	while(Mycpu.status){
		
		if(memory[Mycpu.program_counter]==0x00){
			if(disassembly){
			printf("%x\tnop\n", Mycpu.program_counter);}
			Mycpu.program_counter++;
			continue;
		}
		
		if(memory[Mycpu.program_counter]==0x10){
				
				printf(HLT);
				printf(AOK);
				Mycpu.status = false;
				return ;
		}
		
		if(memory[Mycpu.program_counter]==0x20){
			    high = (memory[Mycpu.program_counter + 1] & 0xf0) >> 4;
				low = (memory[Mycpu.program_counter + 1] & 0x0f) ;
				
				if(disassembly){
				
					printf("%x\trrmovl", Mycpu.program_counter);
					printf("\t%s\t%s\n", getr(high), getr(low));
			}

				Mycpu.registers[low] = Mycpu.registers[high];

			     Mycpu.program_counter += 2;

				continue;
		}
		
		if(memory[Mycpu.program_counter]==0x30){
			    
				
				high = (memory[Mycpu.program_counter + 1] & 0xf0) >> 4;
				low = (memory[Mycpu.program_counter + 1] & 0x0f);

				value =    memory[Mycpu.program_counter + 2] 
				      + (memory[Mycpu.program_counter + 3] << 8)
				      + (memory[Mycpu.program_counter + 4] << 16)
				      + (memory[Mycpu.program_counter + 5] << 24);

				if(disassembly){
				
					printf("%x\tirmovl", Mycpu.program_counter);
					printf("\t%s\tV:%x\n", getr(low), value);
			}

				Mycpu.registers[low] = value;

				Mycpu.program_counter += 6;
				continue;
			
		}	
		
		
		
		    if(memory[Mycpu.program_counter]==0x40){
				high = (memory[Mycpu.program_counter + 1] & 0xf0) >> 4;
				low = (memory[Mycpu.program_counter + 1] & 0x0f);
				
				dest =  memory[Mycpu.program_counter + 2] 
				      + (memory[Mycpu.program_counter + 3] << 8)
				      + (memory[Mycpu.program_counter + 4] << 16)
				      + (memory[Mycpu.program_counter + 5] << 24);

				if(disassembly){
				
					printf("%x\trmmvol", Mycpu.program_counter);
					printf("\t%s\t%s\tD:%x\n", getr(high),getr(low), dest);
		}
                memory[Mycpu.registers[low] + dest + 0] = (Mycpu.registers[high] & 0x000000ff);
				memory[Mycpu.registers[low] + dest + 1] = (Mycpu.registers[high] & 0x0000ff00) >> 8;	
				memory[Mycpu.registers[low] + dest + 2] = (Mycpu.registers[high] & 0x00ff0000) >> 16;
				memory[Mycpu.registers[low] + dest + 3] = (Mycpu.registers[high] & 0xff000000) >> 24;

				Mycpu.program_counter += 6;

			continue;
			}
	
	
	if(memory[Mycpu.program_counter]==0x50) {
				high = (memory[Mycpu.program_counter + 1] & 0xf0) >> 4;
				low = (memory[Mycpu.program_counter + 1] & 0x0f);
				
				dest =  memory[Mycpu.program_counter + 2] 
				      + (memory[Mycpu.program_counter + 3] << 8)
				      + (memory[Mycpu.program_counter + 4] << 16)
				      + (memory[Mycpu.program_counter + 5] << 24);

		if(disassembly){
		
					printf("%x\tmrmovl", Mycpu.program_counter);
					printf("\t%s\t%s\tD:%x\n", getr(high),getr(low), dest);
			}

				Mycpu.registers[high] =  (memory[Mycpu.registers[low] + dest + 0])
				                    + (memory[Mycpu.registers[low] + dest + 1]  <<  8)
			                            +  (memory[Mycpu.registers[low] + dest + 2]  << 16)
				                    +  (memory[Mycpu.registers[low] + dest + 3]  << 24);
			
				Mycpu.program_counter += 6;

				continue;}
			if(memory[Mycpu.program_counter]==0x60){
				high = (memory[Mycpu.program_counter + 1] & 0xf0) >> 4;
				low = (memory[Mycpu.program_counter + 1] & 0x0f);

				Mycpu.overflow = false;
				Mycpu.negative = false;
				Mycpu.zero     = false;

				value = Mycpu.registers[high] + Mycpu.registers[low];

				if ((Mycpu.registers[high] > 0 && Mycpu.registers[low] > 0 && value < 0) || 
			            (Mycpu.registers[high] < 0 && Mycpu.registers[low] < 0 && value > 0)) {
					Mycpu.overflow = true;
				}

				if (value == 0) {
					Mycpu.zero = true;
				}

				if (value < 0) {
					Mycpu.negative = true;
				}

				
			if(disassembly){
			
					printf("%x\taddl", Mycpu.program_counter);
					printf("\t%s\t%s", getr(high),getr(low));
					printf("\t(%i = %i + %i )\n", value, Mycpu.registers[high], Mycpu.registers[low]);
			}
            	Mycpu.registers[low] = value;
				Mycpu.program_counter += 2;

				continue;}
		if(memory[Mycpu.program_counter]==0x61){
				high = (memory[Mycpu.program_counter + 1] & 0xf0) >> 4;
				low = (memory[Mycpu.program_counter + 1] & 0x0f);

				Mycpu.overflow = false;
				Mycpu.negative = false;
				Mycpu.zero     = false;

				value = Mycpu.registers[low] - Mycpu.registers[high];

				if ((Mycpu.registers[high] < 0 && Mycpu.registers[low] > 0 && value < 0) || 
			            (Mycpu.registers[high] > 0 && Mycpu.registers[low] < 0 && value > 0))
					Mycpu.overflow = true;

				if (value == 0) {
					Mycpu.zero = true;
				}

				if (value < 0) {
					Mycpu.negative = true;
				}

			if(disassembly){
			
					printf("%x\tsubl", Mycpu.program_counter);
					printf("\t%s\t%s",  getr(high),getr(low));
					printf("\t(%i = %i - %i )\n", value, Mycpu.registers[low], Mycpu.registers[high]);
				
}
				Mycpu.registers[low] = value;
				Mycpu.program_counter += 2;

			continue;}
			if(memory[Mycpu.program_counter]==0x64) {
			
				high = (memory[Mycpu.program_counter + 1] & 0xf0) >> 4;
				low = (memory[Mycpu.program_counter + 1] & 0x0f);

				Mycpu.overflow = false;
				Mycpu.negative = false;
				Mycpu.zero     = false;

				value = Mycpu.registers[high] * Mycpu.registers[low];

				if ((Mycpu.registers[high] > 0 && Mycpu.registers[low] > 0 && value < 0) ||
				    (Mycpu.registers[high] < 0 && Mycpu.registers[low] < 0 && value < 0) ||
				    (Mycpu.registers[high] < 0 && Mycpu.registers[low] > 0 && value > 0) ||
				    (Mycpu.registers[high] > 0 && Mycpu.registers[low] < 0 && value > 0)) {
					Mycpu.overflow = true;
				}

				if (value == 0) {
					Mycpu.zero = true;
				}

				if (value < 0) {
					Mycpu.negative = true;
				}

if(disassembly){
			
					printf("%x\timull", Mycpu.program_counter);
					printf("\t%s\t%s",  getr(high),getr(low));
					printf("\t(%i = %i * %i )\n", value, Mycpu.registers[high], Mycpu.registers[low]);
}
				Mycpu.registers[low] = Mycpu.registers[high] * Mycpu.registers[low];
				Mycpu.program_counter += 2;

				continue;}
			if(memory[Mycpu.program_counter]==0x62){ 
				high = (memory[Mycpu.program_counter + 1] & 0xf0) >> 4;
				low = (memory[Mycpu.program_counter + 1] & 0x0f);

				Mycpu.negative = false;
				Mycpu.zero     = false;

               if(disassembly){

					printf("%x\tandl", Mycpu.program_counter);
					printf("\t%s\t%s\n",  getr(high),getr(low));
				}
				value = Mycpu.registers[high] & Mycpu.registers[low];

				if (value == 0) {
					Mycpu.zero = true;
				}

				if (value !=0) {
					Mycpu.zero = false;
				}

				Mycpu.program_counter += 2;

				continue;			}
			if(memory[Mycpu.program_counter]==0x63){
				high = (memory[Mycpu.program_counter + 1] & 0xf0) >> 4;
				low = (memory[Mycpu.program_counter + 1] & 0x0f);

				Mycpu.negative = false;
				Mycpu.zero     = false;

if(disassembly){

					printf("%x\txorl", Mycpu.program_counter);
					printf("\t\%s\t%s\n", getr(high),getr(low));
}
				
				value = high ^ low;

				if (value == 0) {
					Mycpu.zero = true;
				}

				if (value < 0) {
					Mycpu.negative = true;
				}
				

				Mycpu.program_counter += 2;

				continue;}
				
				
				if(memory[Mycpu.program_counter]==0x65){
				high = (memory[Mycpu.program_counter + 1] & 0xf0) >> 4;
				low = (memory[Mycpu.program_counter + 1] & 0x0f);

			
				Mycpu.zero     = false;
				Mycpu.negative=false;

if(disassembly){
				
					printf("%x\tcmpl", Mycpu.program_counter);
					printf("\t%s\t%s\n", getr(high),getr(low));
}
				bool temp9;
				temp9 = Mycpu.registers[high] == Mycpu.registers[low];
                
				if (temp9 == true) {
					Mycpu.zero = true;
				}
				if(Mycpu.registers[high] <Mycpu.registers[low]){
					
					Mycpu.negative=true;
				}
				

				Mycpu.program_counter += 2;

				continue;}
				
				
			if(memory[Mycpu.program_counter]==0x70){
			
				dest =    memory[Mycpu.program_counter + 1] 
				      + (memory[Mycpu.program_counter + 2] << 8)
				      + (memory[Mycpu.program_counter + 3] << 16)
				      + (memory[Mycpu.program_counter + 4] << 24);

if(disassembly){

					printf("%x\tjmp\t%x\n", Mycpu.program_counter, dest);
}

				Mycpu.program_counter = dest;

			continue;}
			if(memory[Mycpu.program_counter]==0x71){
			
				dest =    memory[Mycpu.program_counter + 1] 
				      + (memory[Mycpu.program_counter + 2] << 8)
				      + (memory[Mycpu.program_counter + 3] << 16)
				      + (memory[Mycpu.program_counter + 4] << 24);

if(disassembly){

					printf("%x\tjle\t%x\n", Mycpu.program_counter, dest);
}
				if (Mycpu.negative ^ Mycpu.overflow || Mycpu.zero)
					Mycpu.program_counter = dest;
				else
					Mycpu.program_counter += 5;

				continue;}
			if(memory[Mycpu.program_counter]==0x72){
			
				dest =    memory[Mycpu.program_counter + 1] 
				      + (memory[Mycpu.program_counter + 2] << 8)
				      + (memory[Mycpu.program_counter + 3] << 16)
				      + (memory[Mycpu.program_counter + 4] << 24);

if(disassembly){
			
					printf("%x\tjl\t%x\n", Mycpu.program_counter, dest);
}
				if (Mycpu.negative ^ Mycpu.overflow)
					Mycpu.program_counter = dest;
				else
					Mycpu.program_counter += 5;

				continue;}
			if(memory[Mycpu.program_counter]==0x73){
			
				dest =    memory[Mycpu.program_counter + 1] 
				      + (memory[Mycpu.program_counter + 2] << 8)
				      + (memory[Mycpu.program_counter + 3] << 16)
				      + (memory[Mycpu.program_counter + 4] << 24);

if(disassembly){

						
					printf("%x\tje\t%x\n", Mycpu.program_counter, dest);
}
				if (Mycpu.zero)
					Mycpu.program_counter = dest;
				else
					Mycpu.program_counter += 5;

				continue;}
		if(memory[Mycpu.program_counter]==0x74){
		
				dest =    memory[Mycpu.program_counter + 1] 
				      + (memory[Mycpu.program_counter + 2] << 8)
				      + (memory[Mycpu.program_counter + 3] << 16)
				      + (memory[Mycpu.program_counter + 4] << 24);

if(disassembly){
			
					printf("%x\tjne\t%x\n", Mycpu.program_counter, dest);
}
				if (!Mycpu.zero)
					Mycpu.program_counter = dest;
				else
					Mycpu.program_counter += 5;

				continue;}
			if(memory[Mycpu.program_counter]==0x75){
			
				dest =    memory[Mycpu.program_counter + 1] 
				      + (memory[Mycpu.program_counter + 2] << 8)
				      + (memory[Mycpu.program_counter + 3] << 16)
				      + (memory[Mycpu.program_counter + 4] << 24);

if(disassembly){

					printf("%x\tjge\t%x\n", Mycpu.program_counter, dest);
}
				if (!(Mycpu.negative ^ Mycpu.overflow))
					Mycpu.program_counter = dest;
				else
					Mycpu.program_counter += 5;

				continue;}
			if(memory[Mycpu.program_counter]==0x76){
			
				dest =    memory[Mycpu.program_counter + 1] 
				      + (memory[Mycpu.program_counter + 2] << 8)
				      + (memory[Mycpu.program_counter + 3] << 16)
				      + (memory[Mycpu.program_counter + 4] << 24);

if(disassembly){

					printf("%x\tjg\t%x\n", Mycpu.program_counter, dest);
}
				if (!(Mycpu.negative ^ Mycpu.overflow) && !Mycpu.zero)
					Mycpu.program_counter = dest;
				else
					Mycpu.program_counter += 5;

			continue;}
		
		if(memory[Mycpu.program_counter]==0x80){
		
				dest =    memory[Mycpu.program_counter + 1] 
				      + (memory[Mycpu.program_counter + 2] << 8)
				      + (memory[Mycpu.program_counter + 3] << 16)
				      + (memory[Mycpu.program_counter + 4] << 24);
Mycpu.registers[ESP] -= 4;
if(disassembly){
				
					printf("%x\tcall\tD:%x\n", Mycpu.program_counter, dest);
}
				
				temp = Mycpu.program_counter + 5; 
				value = 0;
				
				memory[Mycpu.registers[ESP] + 0] = (temp & 0x000000ff);
				memory[Mycpu.registers[ESP] + 1] = (temp & 0x0000ff00) >> 8;
				memory[Mycpu.registers[ESP] + 2] = (temp & 0x00ff0000) >> 16;
				memory[Mycpu.registers[ESP] + 3] = (temp & 0xff000000) >> 24;


				Mycpu.program_counter = dest;

				continue;}
				if(memory[Mycpu.program_counter]==0x90){
				if(disassembly){
				
			
					printf("%x\tret\t\n", Mycpu.program_counter);
}
				Mycpu.program_counter = (memory[Mycpu.registers[ESP] + 0])
				                     + (memory[Mycpu.registers[ESP] + 1] << 8)
				                     + (memory[Mycpu.registers[ESP] + 2] << 16)
				                     + (memory[Mycpu.registers[ESP] + 3] << 24);
				
				Mycpu.registers[ESP] += 4;

				continue;}
				if(memory[Mycpu.program_counter]==0xa0){
				high = (memory[Mycpu.program_counter + 1] & 0xf0) >> 4;
				low = (memory[Mycpu.program_counter + 1] & 0x0f);
	Mycpu.registers[ESP] -= 4;
if(disassembly){
		
					printf("%x\tpushl", Mycpu.program_counter);
					printf("\t%s\tesp:%x\n", getr(high), Mycpu.registers[ESP]);
}

			
				
				memory[Mycpu.registers[ESP] + 0] = (Mycpu.registers[high]);
				memory[Mycpu.registers[ESP] + 1] = (Mycpu.registers[high] & 0x0000ff00) >> 8;
				memory[Mycpu.registers[ESP] + 2] = (Mycpu.registers[high] & 0x00ff0000) >> 16;
				memory[Mycpu.registers[ESP] + 3] = (Mycpu.registers[high] & 0xff000000) >> 24;

				Mycpu.program_counter += 2;
				continue;}
			if(memory[Mycpu.program_counter]==0xb0){
			
				high = (memory[Mycpu.program_counter + 1] & 0xf0) >> 4;
				low = (memory[Mycpu.program_counter + 1] & 0x0f);

if(disassembly){
			
					printf("%x\tpopl", Mycpu.program_counter);
					printf("\t%s\n", getr(high));
}
				
				Mycpu.registers[high] = (memory[Mycpu.registers[ESP] + 0])
				                    + (memory[Mycpu.registers[ESP] + 1] << 8)
				                    + (memory[Mycpu.registers[ESP] + 2] << 16)
				                    + (memory[Mycpu.registers[ESP] + 3] << 24);

				Mycpu.registers[ESP] += 4;
				Mycpu.program_counter += 2;
				continue;}
				
				
				if(memory[Mycpu.program_counter]==0xc0){
				high = (memory[Mycpu.program_counter + 1] & 0xf0) >> 4;
				low = (memory[Mycpu.program_counter + 1] & 0x0f);
				
				dest =    memory[Mycpu.program_counter + 2] 
				      + (memory[Mycpu.program_counter + 3] << 8)
				      + (memory[Mycpu.program_counter + 4] << 16)
				      + (memory[Mycpu.program_counter + 5] << 24);

if(disassembly){
			
					printf("%x\treadb", Mycpu.program_counter);
					printf("\t%s\t%s\tD:%x\n", getr(high),getr(low), dest);
}

				if (EOF == scanf("%c", &temp1)) {
					Mycpu.zero = true;
				} else Mycpu.zero = false;

				memory[Mycpu.registers[high] + dest] = temp1;

				Mycpu.program_counter += 6;
				continue;}
			
			if(memory[Mycpu.program_counter]==0xc1){
			
				high = (memory[Mycpu.program_counter + 1] & 0xf0) >> 4;
				low = (memory[Mycpu.program_counter + 1] & 0x0f);
	
				dest =    memory[Mycpu.program_counter + 2] 
				      + (memory[Mycpu.program_counter + 3] << 8)
				      + (memory[Mycpu.program_counter + 4] << 16)
				      + (memory[Mycpu.program_counter + 5] << 24);

                   if (EOF == scanf("%i", &temp)) {
					Mycpu.zero = true;
				} else Mycpu.zero = false;
				
				memory[Mycpu.registers[high] + dest + 0] =  temp & 0x000000ff;
				memory[Mycpu.registers[high] + dest + 1] = (temp & 0x0000ff00) >> 8;
				memory[Mycpu.registers[high] + dest + 2] = (temp & 0x00ff0000) >> 16;
				memory[Mycpu.registers[high] + dest + 3] = (temp & 0xff000000) >> 24;

if(disassembly){
			
					printf("%x\treadl", Mycpu.program_counter);
					printf("\t%s\tD:%x\t%i\n",getr(high), dest,temp);
}

				Mycpu.program_counter += 6;

				continue;}
				if(memory[Mycpu.program_counter]==0xd0){
				high = (memory[Mycpu.program_counter + 1] & 0xf0) >> 4;
				low = (memory[Mycpu.program_counter + 1] & 0x0f);
				dest =    memory[Mycpu.program_counter + 2] 
				      + (memory[Mycpu.program_counter + 3] << 8)
				      + (memory[Mycpu.program_counter + 4] << 16)
				      + (memory[Mycpu.program_counter + 5] << 24);
if(disassembly){
					printf("%x\twriteb memory[%x + %x] - ", Mycpu.program_counter, Mycpu.registers[high], dest);

				printf("%c",memory[Mycpu.registers[high] + dest]);

				
					printf("\n");
}

if(!disassembly){
	printf("%c",memory[Mycpu.registers[high] + dest]);
}
				Mycpu.program_counter += 6;

				continue;}
				 
				 
				 if(memory[Mycpu.program_counter]==0xd1){
			
				high = (memory[Mycpu.program_counter + 1] & 0xf0) >> 4;
				low = (memory[Mycpu.program_counter + 1] & 0x0f);
				
				dest =    memory[Mycpu.program_counter + 2] 
				      + (memory[Mycpu.program_counter + 3] << 8)
				      + (memory[Mycpu.program_counter + 4] << 16)
				      + (memory[Mycpu.program_counter + 5] << 24);

				value =  (memory[Mycpu.registers[high] + dest + 0])
				     + (memory[Mycpu.registers[high] + dest + 1 ]<< 8)
			             + (memory[Mycpu.registers[high] + dest + 2] << 16)
				     + (memory[Mycpu.registers[high] + dest + 3] << 24);	

					if(disassembly){
					printf("%x\twritel memory[%x + %x] - ", Mycpu.program_counter, Mycpu.registers[high], dest);
			         printf("%i",value);
			         printf("\n");
				}
				if(!disassembly){
					
					printf("%i",value);
			         printf("\n");
				}

				Mycpu.program_counter += 6;
				continue;}
				
			if(memory[Mycpu.program_counter]==0xe0){
				
				high = (memory[Mycpu.program_counter + 1] & 0xf0) >> 4;
				low = (memory[Mycpu.program_counter + 1] & 0x0f);
				
				dest =  memory[Mycpu.program_counter + 2] 
				      + (memory[Mycpu.program_counter + 3] << 8)
				      + (memory[Mycpu.program_counter + 4] << 16)
				      + (memory[Mycpu.program_counter + 5] << 24);

		if(disassembly){
		
					printf("%x\tmovsbl", Mycpu.program_counter);
					printf("\t%s\t%s\tD:%x\n", getr(high),getr(low), dest);
}
			    unsigned char temp4=(memory[Mycpu.registers[low] + dest + 0])>>7;
			    if(temp4==1){
			    	
			    	Mycpu.registers[high]=(memory[Mycpu.registers[low] + dest + 0])+0xffffff00;
			    						
				}
				else if(temp4==0){
					
					Mycpu.registers[high]=(memory[Mycpu.registers[low] + dest + 0])+0x00000000;
				}
				                   
				Mycpu.program_counter += 6;
				continue;
				
			}
			else{	
			 	fprintf(stderr, INS); 
				break;return;
			}
				
		}


	fprintf(stderr, ADR);
	return ;

	}
	
	
	
	
	

	
	
	
	
	
	

int main(int argc,char *argv[]){

char *p=*(argv+1);
if(strcmp(p,"-h")==0){
printf("y86emul <y86 input file>\n");
return 0;}

initialize(p);
 
execute();
 
	return 0;
	
	
}

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

bool disassembly=true;
int legin=0;

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
	
    FILE* file = fopen(filename, "r"); /* should check the result */
 
 
   

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
           	legin=strlen(directive);
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
				i = hextodecimal(value); /* in decimal */
				j = hextodecimal(location); /* in hex */
				for (; i > 0; i--) {
					memory[j] = (unsigned char)0; /* make them all zeroes! */
					j++;
				}
			} 
              
    }
    /* may check feof here to make a difference between eof and io failure -- nelowrk
       timeout for instance */

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
	int unpperboud=Mycpu.program_counter+(legin/2)-1;
	int temp;
	Mycpu.status=true;
	int couter=0;
	while(Mycpu.program_counter<=unpperboud){
		
		if(memory[Mycpu.program_counter]==0x00){
			if(disassembly){
			fprintf(stdout,"%x\tnop\n", Mycpu.program_counter);}
			Mycpu.program_counter++;
			continue;
		}
		
		if(memory[Mycpu.program_counter]==0x10){
				
			fprintf(stdout,"%x\thalt\n",Mycpu.program_counter);
			Mycpu.program_counter++;
			continue;
		}
		
		if(memory[Mycpu.program_counter]==0x20){
			    high = (memory[Mycpu.program_counter + 1] & 0xf0) >> 4;
				low = (memory[Mycpu.program_counter + 1] & 0x0f) ;
				
				if(disassembly){
				
					fprintf(stdout,"%x\trrmovl", Mycpu.program_counter);
					fprintf(stdout,"\t%s\t%s\n", getr(high), getr(low));
			}

			

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
				
					fprintf(stdout,"%x\tirmovl", Mycpu.program_counter);
					fprintf(stdout,"\t%x\t%s\n", value,getr(low) );
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
				
					fprintf(stdout,"%x\trmmovl", Mycpu.program_counter);
					fprintf(stdout,"\t%s\t%x(%s)\t\n", getr(high), dest,getr(low));
}

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
		
					fprintf(stdout,"%x\tmrmovl", Mycpu.program_counter);
					fprintf(stdout,"\t%x(%s)\t%s\n", dest,getr(low),getr(high));
			}

			
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
			
					fprintf(stdout,"%x\taddl", Mycpu.program_counter);
					fprintf(stdout,"\t%s\t%s\n", getr(high),getr(low));
					
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
			
					fprintf(stdout,"%x\tsubl", Mycpu.program_counter);
					fprintf(stdout,"\t%s\t%s\n",  getr(high),getr(low));
				
				
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
			
					fprintf(stdout,"%x\tmull", Mycpu.program_counter);
					fprintf(stdout,"\t%s\t%s\n",  getr(high),getr(low));
				
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

					fprintf(stdout,"%x\tandl", Mycpu.program_counter);
					fprintf(stdout,"\t%s\t%s\n",  getr(high),getr(low));
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

					fprintf(stdout,"%x\txorl", Mycpu.program_counter);
					fprintf(stdout,"\t\%s\t%s\n", getr(high),getr(low));
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
				
					fprintf(stdout,"%x\tcmpl", Mycpu.program_counter);
					fprintf(stdout,"\t%s\t%s\n", getr(high),getr(low));
}
				bool temp9;
				temp9 = Mycpu.registers[high] == Mycpu.registers[low];

				if (temp9 == true) {
					Mycpu.zero = true;
				}
				

				Mycpu.program_counter += 2;

				continue;}
				
				
			if(memory[Mycpu.program_counter]==0x70){
			
				dest =    memory[Mycpu.program_counter + 1] 
				      + (memory[Mycpu.program_counter + 2] << 8)
				      + (memory[Mycpu.program_counter + 3] << 16)
				      + (memory[Mycpu.program_counter + 4] << 24);

if(disassembly){

					fprintf(stdout,"%x\tjmp\t%x\n", Mycpu.program_counter, dest);
}

				Mycpu.program_counter +=5;

			continue;}
			if(memory[Mycpu.program_counter]==0x71){
			
				dest =    memory[Mycpu.program_counter + 1] 
				      + (memory[Mycpu.program_counter + 2] << 8)
				      + (memory[Mycpu.program_counter + 3] << 16)
				      + (memory[Mycpu.program_counter + 4] << 24);

if(disassembly){

					fprintf(stdout,"%x\tjle\t%x\n", Mycpu.program_counter, dest);
}
				
					Mycpu.program_counter += 5;

				continue;}
			if(memory[Mycpu.program_counter]==0x72){
			
				dest =    memory[Mycpu.program_counter + 1] 
				      + (memory[Mycpu.program_counter + 2] << 8)
				      + (memory[Mycpu.program_counter + 3] << 16)
				      + (memory[Mycpu.program_counter + 4] << 24);

if(disassembly){
			
					fprintf(stdout,"%x\tjl\t%x\n", Mycpu.program_counter, dest);
}
					Mycpu.program_counter += 5;

				continue;}
			if(memory[Mycpu.program_counter]==0x73){
			
				dest =    memory[Mycpu.program_counter + 1] 
				      + (memory[Mycpu.program_counter + 2] << 8)
				      + (memory[Mycpu.program_counter + 3] << 16)
				      + (memory[Mycpu.program_counter + 4] << 24);

if(disassembly){

						
					fprintf(stdout,"%x\tje\t%x\n", Mycpu.program_counter, dest);
}
					Mycpu.program_counter += 5;

				continue;}
		if(memory[Mycpu.program_counter]==0x74){
		
				dest =    memory[Mycpu.program_counter + 1] 
				      + (memory[Mycpu.program_counter + 2] << 8)
				      + (memory[Mycpu.program_counter + 3] << 16)
				      + (memory[Mycpu.program_counter + 4] << 24);

if(disassembly){
			
					fprintf(stdout,"%x\tjne\t%x\n", Mycpu.program_counter, dest);
}
					Mycpu.program_counter += 5;

				continue;}
			if(memory[Mycpu.program_counter]==0x75){
			
				dest =    memory[Mycpu.program_counter + 1] 
				      + (memory[Mycpu.program_counter + 2] << 8)
				      + (memory[Mycpu.program_counter + 3] << 16)
				      + (memory[Mycpu.program_counter + 4] << 24);

if(disassembly){

					fprintf(stdout,"%x\tjge\t%x\n", Mycpu.program_counter, dest);
}
					Mycpu.program_counter += 5;

				continue;}
			if(memory[Mycpu.program_counter]==0x76){
			
				dest =    memory[Mycpu.program_counter + 1] 
				      + (memory[Mycpu.program_counter + 2] << 8)
				      + (memory[Mycpu.program_counter + 3] << 16)
				      + (memory[Mycpu.program_counter + 4] << 24);

if(disassembly){

					fprintf(stdout,"%x\tjg\t%x\n", Mycpu.program_counter, dest);
}
					Mycpu.program_counter += 5;

			continue;}
		
		if(memory[Mycpu.program_counter]==0x80){
		
				dest =    memory[Mycpu.program_counter + 1] 
				      + (memory[Mycpu.program_counter + 2] << 8)
				      + (memory[Mycpu.program_counter + 3] << 16)
				      + (memory[Mycpu.program_counter + 4] << 24);
Mycpu.registers[ESP] -= 4;
if(disassembly){
				
					fprintf(stdout,"%x\tcall\t%x\n", Mycpu.program_counter, dest);
}
				
				temp = Mycpu.program_counter + 5; 
				value = 0;
				
				memory[Mycpu.registers[ESP] + 0] = (temp & 0x000000ff);
				memory[Mycpu.registers[ESP] + 1] = (temp & 0x0000ff00) >> 8;
				memory[Mycpu.registers[ESP] + 2] = (temp & 0x00ff0000) >> 16;
				memory[Mycpu.registers[ESP] + 3] = (temp & 0xff000000) >> 24;


				Mycpu.program_counter +=5;

				continue;}
				if(memory[Mycpu.program_counter]==0x90){
				if(disassembly){
				
			
					fprintf(stdout,"%x\tret\t\n", Mycpu.program_counter);
}
				Mycpu.program_counter ++;
				Mycpu.registers[ESP] += 4;

				continue;}
				if(memory[Mycpu.program_counter]==0xa0){
				high = (memory[Mycpu.program_counter + 1] & 0xf0) >> 4;
				low = (memory[Mycpu.program_counter + 1] & 0x0f);
	Mycpu.registers[ESP] -= 4;
if(disassembly){
		
					fprintf(stdout,"%x\tpushl", Mycpu.program_counter);
					fprintf(stdout,"\t%s\n", getr(high));
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
			
					fprintf(stdout,"%x\tpopl", Mycpu.program_counter);
					fprintf(stdout,"\t%s\n", getr(high));
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
				
				

if(disassembly){
			
					fprintf(stdout,"%x\treadb", Mycpu.program_counter);
					fprintf(stdout,"\t%x(%s)\n", dest, getr(high));
}

			
				Mycpu.program_counter += 6;
				continue;}
			
			if(memory[Mycpu.program_counter]==0xc1){
			
				high = (memory[Mycpu.program_counter + 1] & 0xf0) >> 4;
				low = (memory[Mycpu.program_counter + 1] & 0x0f);
	
		dest =    memory[Mycpu.program_counter + 2] 
				      + (memory[Mycpu.program_counter + 3] << 8)
				      + (memory[Mycpu.program_counter + 4] << 16)
				      + (memory[Mycpu.program_counter + 5] << 24);
			
				
			
if(disassembly){
			
					fprintf(stdout,"%x\treadl", Mycpu.program_counter);
					fprintf(stdout,"\t%x(%s)\n", dest,getr(high));
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
					fprintf(stdout,"%x\twriteb\t%x(%s)", Mycpu.program_counter, dest, getr(high));

			

				
					fprintf(stdout,"\n");
}

if(!disassembly){
	fprintf(stdout,"%c",memory[Mycpu.registers[high] + dest]);
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
					fprintf(stdout,"%x\twritel\t%x(%s)", Mycpu.program_counter, dest, getr(high));
			         fprintf(stdout,"\n");
				}
				if(!disassembly){
					
					fprintf(stdout,"%i",value);
			         fprintf(stdout,"\n");
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
		
					fprintf(stdout,"%x\tmovsbl", Mycpu.program_counter);
					fprintf(stdout,"\t%x(%s)\t%s\t\n", dest, getr(low),getr(high));
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

	return ;

	}
	
	
	
	
	

	
	
	
	
	
	

int main(int argc,char *argv[]){

char *p=*(argv+1);
if(strcmp(p,"-h")==0){
printf("y86dis <y86 input file>\n");
return 0;}

 initialize(p)  ;
 
 unsigned char test =memory[325];
 
 execute();
 
unsigned char i =48;
unsigned char b =49;
bool wx=i==b;
//int test = hextodecimal("000002f3");
unsigned char test1=memory[test];
	return 0;
	
	
}

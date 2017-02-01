#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

char  getn(char * a){
if(strcmp(a,"%eax")==0){
	return '0';
}
if(strcmp(a,"%ecx")==0){
	return '1';
}
if(strcmp(a,"%edx")==0){
	return '2';
}
if(strcmp(a,"%ebx")==0){
	return '3';
}
if(strcmp(a,"%esp")==0){
	return '4';
}
if(strcmp(a,"%ebp")==0){
	return '5';
}
if(strcmp(a,"%esi")==0){
	return '6';
}
if(strcmp(a,"%edi")==0){
	return '7';
}

	
}


char *ret(char *input){	
char *use;
use=malloc(10*sizeof(char));
if(strlen(input)%2==1){

int s=strlen(input);
for(;s>=0;s--){
	
	use[s+1]=input[s];
	
}
use[0]='0';
use[strlen(input)+1]='\0';
	
}
else{
strcpy(use,input);}



	char *need;int f=strlen(use);
	need=malloc(9*sizeof(char));
	int i=0;int cout=0;
	char *temp;
		temp=malloc(2*sizeof(char));
	for(i=strlen(use)-1;i>=0;){
		strncpy(temp,use+i-1,2);
		temp[2]='\0';		
		need[cout]=temp[0];
		need[cout+1]=temp[1];
		cout+=2;	i-=2;
		}
	for(;f<8;f++){
		need[f]='0';
	}
	need[8]='\0';
		return need;		
	}



void assembly(char *filename){

FILE* file = fopen(filename, "r"); 
fprintf(stdout,".text\t");
 	
char * incout;
incout=malloc(10*sizeof(char));
fscanf(file,"%s",incout);	
rewind(file); 	
fprintf(stdout,"%s\t",incout); 	
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
 
   

     while(fgets(line, 1000, file) ){
     
if(strstr(line,"irmovl")){
	strtok(line," \n\t");strtok(NULL," \n\t");
	inpt=strtok(NULL," \n\t");
	value=strtok(NULL," \n\t");
	fprintf(stdout,"30f");
	fprintf(stdout,"%c",getn(value));
	fprintf(stdout,"%s",ret(inpt));
		
	continue;
	
}
 
if(strstr(line,"rrmovl")){
	strtok(line," \n\t");strtok(NULL," \n\t");
	inpt=strtok(NULL," \n\t");
	value=strtok(NULL," \n\t");
	fprintf(stdout,"20");
	fprintf(stdout,"%c",getn(inpt));
	fprintf(stdout,"%c",getn(value));
		
	continue;
	
}           

if(strstr(line,"call")){
	fprintf(stdout,"80");
	strtok(line," \n\t");strtok(NULL," \n\t");
	inpt=strtok(NULL," \n\t");
	fprintf(stdout,"%s",ret(inpt));
continue;
	
}     

if(strstr(line,"halt")){
fprintf(stdout,"10");		
	continue;
	
}           
if(strstr(line,"nop")){
	fprintf(stdout,"00");
		
	continue;
	
}           
if(strstr(line,"pushl")){
	strtok(line," \n\t");strtok(NULL," \n\t");
	inpt=strtok(NULL," \n\t");
	value=strtok(NULL," \n\t");
	fprintf(stdout,"a0");
	fprintf(stdout,"%c",getn(inpt));
	fprintf(stdout,"f");
		
	continue;
	
}           
if(strstr(line,"subl")){
	strtok(line," \n\t");strtok(NULL," \n\t");
	inpt=strtok(NULL," \n\t");
	value=strtok(NULL," \n\t");
	fprintf(stdout,"61");
	fprintf(stdout,"%c",getn(inpt));
	fprintf(stdout,"%c",getn(value));
		
	continue;
	
}           
if(strstr(line,"rmmovl")){
	strtok(line," \n\t()");strtok(NULL," \n\t()");
	inpt=strtok(NULL," \n\t()");
	value=strtok(NULL," \n\t()");
	location=strtok(NULL," \n\t()");
	fprintf(stdout,"40");
	fprintf(stdout,"%c",getn(inpt));
	fprintf(stdout,"%c",getn(location));
	fprintf(stdout,"%s",ret(value));
	continue;
	
}  
if(strstr(line,"andl")){
	strtok(line," \n\t");strtok(NULL," \n\t");
	inpt=strtok(NULL," \n\t");
	value=strtok(NULL," \n\t");
	fprintf(stdout,"62");
	fprintf(stdout,"%c",getn(inpt));
	fprintf(stdout,"%c",getn(value));
		
	continue;
	
}  
if(strstr(line,"addl")){
	strtok(line," \n\t");strtok(NULL," \n\t");
	inpt=strtok(NULL," \n\t");
	value=strtok(NULL," \n\t");
	fprintf(stdout,"60");
	fprintf(stdout,"%c",getn(inpt));
	fprintf(stdout,"%c",getn(value));
		
	continue;
	
}  
if(strstr(line,"xorl")){
	strtok(line," \n\t");strtok(NULL," \n\t");
	inpt=strtok(NULL," \n\t");
	value=strtok(NULL," \n\t");
	fprintf(stdout,"63");
	fprintf(stdout,"%c",getn(inpt));
	fprintf(stdout,"%c",getn(value));
		
	continue;
	
}  
if(strstr(line,"mull")){
	strtok(line," \n\t");strtok(NULL," \n\t");
	inpt=strtok(NULL," \n\t");
	value=strtok(NULL," \n\t");
	fprintf(stdout,"64");
	fprintf(stdout,"%c",getn(inpt));
	fprintf(stdout,"%c",getn(value));
		
	continue;
	
}  
if(strstr(line,"cmpl")){
	strtok(line," \n\t");strtok(NULL," \n\t");
	inpt=strtok(NULL," \n\t");
	value=strtok(NULL," \n\t");
	fprintf(stdout,"65");
	fprintf(stdout,"%c",getn(inpt));
	fprintf(stdout,"%c",getn(value));
		
	continue;
	
}  
if(strstr(line,"popl")){
	strtok(line," \n\t");strtok(NULL," \n\t");
	inpt=strtok(NULL," \n\t");
	value=strtok(NULL," \n\t");
	fprintf(stdout,"b0");
	fprintf(stdout,"%c",getn(inpt));
	fprintf(stdout,"f");
		
	continue;
	
}  
if(strstr(line,"je")){
	strtok(line," \n\t");strtok(NULL," \n\t");
	inpt=strtok(NULL," \n\t");
	fprintf(stdout,"73");
	fprintf(stdout,"%s",ret(inpt));
	continue;
	
}                    
if(strstr(line,"jle")){
	strtok(line," \n\t");strtok(NULL," \n\t");
	inpt=strtok(NULL," \n\t");
	fprintf(stdout,"71");
	fprintf(stdout,"%s",ret(inpt));
	continue;
	
}         
if(strstr(line,"jmp")){
	strtok(line," \n\t");strtok(NULL," \n\t");
	inpt=strtok(NULL," \n\t");
	fprintf(stdout,"70");
	fprintf(stdout,"%s",ret(inpt));
	continue;
	
}               
if(strstr(line,"jl")){
	strtok(line," \n\t");strtok(NULL," \n\t");
	inpt=strtok(NULL," \n\t");
	fprintf(stdout,"72");
	fprintf(stdout,"%s",ret(inpt));
	continue;
	
}    
if(strstr(line,"jne")){
	strtok(line," \n\t");strtok(NULL," \n\t");
	inpt=strtok(NULL," \n\t");
	fprintf(stdout,"74");
	fprintf(stdout,"%s",ret(inpt));
	continue;
	
}    
if(strstr(line,"jge")){
	strtok(line," \n\t");strtok(NULL," \n\t");
	inpt=strtok(NULL," \n\t");
	fprintf(stdout,"75");
	fprintf(stdout,"%s",ret(inpt));
	continue;
	
}    
if(strstr(line,"jg")){
	strtok(line," \n\t");strtok(NULL," \n\t");
	inpt=strtok(NULL," \n\t");
	fprintf(stdout,"76");
	fprintf(stdout,"%s",ret(inpt));
	continue;
	
}    
if(strstr(line,"readb")){
	strtok(line," \n\t()");strtok(NULL," \n\t()");
	inpt=strtok(NULL," \n\t()");
	value=strtok(NULL," \n\t()");
	fprintf(stdout,"c0");
	fprintf(stdout,"%c",getn(value));
	fprintf(stdout,"f");
	fprintf(stdout,"%s",ret(inpt));
	continue;
	
}    
if(strstr(line,"readl")){
	strtok(line," \n\t()");strtok(NULL," \n\t()");
	inpt=strtok(NULL," \n\t()");
	value=strtok(NULL," \n\t()");
	fprintf(stdout,"c1");
	fprintf(stdout,"%c",getn(value));
	fprintf(stdout,"f");
	fprintf(stdout,"%s",ret(inpt));
	continue;
	
} 
if(strstr(line,"writeb")){
	strtok(line," \n\t()");strtok(NULL," \n\t()");
	inpt=strtok(NULL," \n\t()");
	value=strtok(NULL," \n\t()");
	fprintf(stdout,"d0");
	fprintf(stdout,"%c",getn(value));
	fprintf(stdout,"f");
	fprintf(stdout,"%s",ret(inpt));
	continue;
	
} 
if(strstr(line,"writel")){
	strtok(line," \n\t()");strtok(NULL," \n\t()");
	inpt=strtok(NULL," \n\t()");
	value=strtok(NULL," \n\t()");
	fprintf(stdout,"d1");
	fprintf(stdout,"%c",getn(value));
	fprintf(stdout,"f");
	fprintf(stdout,"%s",ret(inpt));
	continue;
	
} 
if(strstr(line,"mrmovl")){
	strtok(line," \n\t()");strtok(NULL," \n\t()");
	inpt=strtok(NULL," \n\t()");
	value=strtok(NULL," \n\t()");
	location=strtok(NULL," \n\t()");
	fprintf(stdout,"50");
	fprintf(stdout,"%c",getn(location));
	fprintf(stdout,"%c",getn(value));
	fprintf(stdout,"%s",ret(inpt));
	continue;
	
} 
if(strstr(line,"movsbl")){
	strtok(line," \n\t()");strtok(NULL," \n\t()");
	inpt=strtok(NULL," \n\t()");
	value=strtok(NULL," \n\t()");
	location=strtok(NULL," \n\t()");
	fprintf(stdout,"e0");
	fprintf(stdout,"%c",getn(location));
	fprintf(stdout,"%c",getn(value));
	fprintf(stdout,"%s",ret(inpt));
	continue;
	
} 
if(strstr(line,"ret")){
	
	fprintf(stdout,"90");
	continue;
}






    fclose(file);
    free(line);
	free(size);
	free(directive);
	
return;

}
}


	
	
	




int main(int argc,char *argv[]){

char *p=*(argv+1);
if(strcmp(p,"-h")==0){
printf("y86ass <y86 assembly instruction txt file generate by my y86dis program>\n");
return 0;}


assembly(p);
 printf("\n");

 
	return 0;
	
	
}


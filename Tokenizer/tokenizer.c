/*
 * tokenizer.c
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
int strToHex(char *ch, char *hex);
int hexCharToValue(const char ch);
char valueToHexCh(const int value);
/*
 * Tokenizer type.  You need to fill in the type as part of your implementation.
 */
struct TokenizerT_ {
    char *stream;
    char *ptr;
};

typedef struct TokenizerT_ TokenizerT;


int isWhitespace(char c)
{
    if (c == 0x0a || c == 0x0b || c == 0x09 || c == 0x0d||
        c == 0x0c|| c == 0x20)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

/*
 * TKCreate creates a new TokenizerT object for a given token stream
 * (given as a string).
 * 
 * TKCreate should copy the arguments so that it is not dependent on
 * them staying immutable after returning. (In the future, this may change
 * to increase efficiency.)
 *
 * If the function succeeds, it returns a non-NULL TokenizerT.
 * Else it returns NULL.
 *
 * You need to fill in this function as part of your implementation.
 */
TokenizerT *TKCreate(char *ts)
{
    
    if (strlen(ts) == 0)
    {
        return NULL;
    }
	TokenizerT *token = (TokenizerT *) malloc( sizeof (TokenizerT) );
    if (!token)
    {
        return NULL;
    }
	
    token->stream = malloc(strlen(ts) + 1);
    strcpy(token->stream, ts);


    token->ptr = token->stream;
	
    return token;
}

/*
 * TKDestroy destroys a TokenizerT object. It should free all dynamically
 * allocated memory that is part of the object being destroyed.
 *
 * You need to fill in this function as part of your implementation.
 */
void TKDestroy(TokenizerT *tk)
{
    tk->ptr = NULL;free(tk->stream);free(tk);	
}

/*
 * TKGetNextToken returns the next token from the token stream as a
 * character string. Space for the returned token should be dynamically
 * allocated. The caller is responsible for freeing the space once it is
 * no longer needed.
 *
 * If the function succeeds, it returns a C string (delimited by '\0')
 * containing the token. Else it returns 0.
 *
 * You need to fill in this function as part of your implementation.
 */
char *TKGetNextToken(TokenizerT *tk)
{
    //Use a pointer to do tokenizing without modifying original string
    char *ptr = tk->ptr;
    int length = 0;

    while ( *ptr != '\0')
    {
        if ( isWhitespace(*ptr))
        {
           
            char *token = (char *) malloc(length + 1 );
            strncpy(token, tk->ptr, length);
            token[length] = '\0';
            tk->ptr = ptr;
            while ( isWhitespace(*tk->ptr))
            {
                tk->ptr++;
            }
                        
            return token;
        }
        else
        {
            ptr++;
            length++;
        }
    }
    char *token = (char *) malloc(length + 1 );
    strncpy(token, tk->ptr, length);
    token[length] = '\0';
    tk->ptr = ptr;

    return token;
}


int isFloat(const char *s)
{
    char *check = NULL;
    long i = strtol(s, &check, 0);
   if (i!=0){
    if (!*check)
    {
        return 0;  
    }
    if (*check == 'e'  ||*check == 'E'  ||*check == '.')
    {
        return 1;
    }
}
    return 0;  
}

int isHex(char *s)
{
    char *ptr = s;

    if(*ptr++ == '0' && (*ptr == 'x' || *ptr == 'X'))
    {
        while(*(++ptr) != '\0')
        {
            if (!isxdigit(*ptr))
            {
                return 0;
            }
        }

        return 1;
    }

    return 0;
}


int isOctal(char *s)
{
    char *ptr = s;

    if (*ptr != '0')
    {
        return 0;
    }
     ptr++;
    while (isdigit(*ptr) && *ptr != '8' && *ptr != '9')
    {
        ptr++;

        if(*ptr == '\0')
        {
            return 1;
        }
    }
    return 0;
}

int isDecimal(char *s)
{
    char *ptr = s;

    while (*ptr != '\0')
    {
        if (!isdigit(*ptr++))
        {
            return 0;
        }
    }

    return 1;
}



void FSM(char* token)
{
    
    if (isFloat(token))
    {
        printf("Float: '%s'\n", token);
    }
    else if (isHex(token))
    {
        printf("Hex: '%s'\n", token);
    }
    else if (isOctal(token))
    {
        printf("Octal: '%s'\n", token);
    }
    else if (isDecimal(token))
    {
        printf("Decimal: '%s'\n", token);
    }
    else
    {    
    char hex[1024];   char *phex=hex;
    strToHex(token,phex);
        printf("Error: [0x%s]\n", phex);
    }
    free(token);
}



int strToHex(char *ch, char *hex)
{
  int high,low;
  int tmp = 0;
  if(ch == NULL || hex == NULL){
    return -1;
  }

  if(strlen(ch) == 0){
    return -2;
  }

  while(*ch){
    tmp = (int)*ch;
    high = tmp >> 4;
    low = tmp & 15;
    *hex++ = valueToHexCh(high); 
    *hex++ = valueToHexCh(low); 
    ch++;
  }
  *hex = '\0';
  return 0;
}



char valueToHexCh(const int value)
{
  char result = '\0';
  if(value >= 0 && value <= 9){
    result = (char)(value + 48); 
  }
  else if(value >= 10 && value <= 15){
    result = (char)(value - 10 + 65); 
  }
  else{
    ;
  }

  return result;
}



char *getstr()
{  
        char* str;  
        char* _str;  
        int i = 1;  
        str = (char*)malloc(sizeof(char) * (i + 1));  
        while('\n' != (str[i - 1] = getchar()))  
        {  
                i ++;  
                _str = (char*)malloc(strlen(str) + 1); 
                str[i - 1] = '\0'; 
                strcpy(_str, str);  
                free(str);  
                str = (char*)malloc(sizeof(char) * (i + 1));  
                if(NULL == str)  
                {  
                        free(_str);  
                        printf("No enough memory!");  
                        return NULL;  
                }  
                strcpy(str, _str);  
                free(_str);  
        }  
        str[i - 1] = '\0';  
        return str;  
        
} 
/*
 * main will have a string argument (in argv[1]).
 * The string argument contains the tokens.
 * Print out the tokens in the second string in left-to-right order.
 * Each token should be printed on a separate line.
 */
int main(int argc, char **argv)
{
	char *input=getstr();

TokenizerT *tokenizer = TKCreate(input);

    if (tokenizer == NULL)
    {
        return 1;
    }

    printf("The input string is:%s\n\n", tokenizer->stream);
    char *token;
    while (*(token = TKGetNextToken(tokenizer)) != '\0')
    {
        FSM(token);
    }

    TKDestroy(tokenizer);

    return 0;
}

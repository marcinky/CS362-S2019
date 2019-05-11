#include<stdio.h>
#include<unistd.h>
#include<string.h>
#include<stdlib.h>
#include<time.h>
//slow this thing down
#define SNOOZE 1
//define length for string
#define STRLENGTH 5

char inputChar()
{
	//generate random characters
  	char c = (char)((rand() % (95)) + 32);

/*
	//to test the test and refine
	if (c=='['||c=='('||c=='{'||c==' '||c=='a'||c=='x'||c=='}'||c==')'||c==']')
	{
		printf(  "\n  paydirt\n\n" );
		sleep(SNOOZE);
	}
*/
	return c;
}

char *inputString()
{
	//variables
	int i;
	//char *s = "abcdefghijklmnopqrstuvwxyz1234567890";
	char *s = "erst1234567890";

	//allocate memory
	char *randString = malloc(STRLENGTH * sizeof(char) + 1);

	//initialize
	memset(randString, '\0', sizeof(STRLENGTH));
	
	//generate random string 
	int k=0;

	for(i = 0; i < STRLENGTH; i++)
	{
		k = rand() % strlen(s); 	
		randString[i] = s[k]; 	
		//randString[i] = (char)(rand() % s); 	
		//sleep(SNOOZE);
	}
	
	//terminate string
	randString[STRLENGTH] = '\0';
	
	//return a random string
   return randString;
}

void testme()
{
  int tcCount = 0;
  char *s;
  char c;
  int state = 0;
  while (1)
  {
    tcCount++;
    c = inputChar();
    s = inputString();
    printf("Iteration %d: c = %c, s = %s, state = %d\n", tcCount, c, s, state);

    if (c == '[' && state == 0) state = 1;
    if (c == '(' && state == 1) state = 2;
    if (c == '{' && state == 2) state = 3;
    if (c == ' ' && state == 3) state = 4;
    if (c == 'a' && state == 4) state = 5;
    if (c == 'x' && state == 5) state = 6;
    if (c == '}' && state == 6) state = 7;
    if (c == ')' && state == 7) state = 8;
    if (c == ']' && state == 8) state = 9;
    if (s[0] == 'r' && s[1] == 'e'
       && s[2] == 's' && s[3] == 'e'
       && s[4] == 't' && s[5] == '\0'
       && state == 9)
    {
      printf("error ");
      exit(200);
    }
  }
}

int main(int argc, char *argv[])
{
    srand(time(NULL));
    testme();
    return 0;
}

#include <stdio.h>
#include <stdlib.h>	//library for malloc usage

int makearg(char s[], char*** args);	//token function

int wordsize(char s1[]);	//function or largest word size
int words(char s2[]);		//function for number of words

int main()
{
	char** args, str[1000];

		printf("Please Enter some words you would like to have parsed: ");
		scanf("%[^\n]", str);	//imput string

	int argc;

	argc = makearg(str, &args);	//call to function, return number of arguments

	printf("Sample Text: %s\n", &str);
	printf("Number of Tokens: %d\n", argc);

	int i;
	for (i = 0; i < argc; i++)		//printing all the tokens
	{
		printf("%d : %s\n", i, args[i]);
	}

	return 0;
}

int makearg(char s[], char*** args)
{
	int wordcount = 0, charcount = 0, count = 0;

	char* p1 = malloc((wordsize(s) + 1) * sizeof(char));	//allocate memory
	char** copy = malloc((words(s) + 1) * sizeof(char*));	//allocate memory

	int j;
	for (j = 0; j < words(s); j++)	//allocate memory for the seconde dimension
	{
		copy[j] = malloc((wordsize(s) + 1) *sizeof(char*));
	}

	while (s[charcount] == ' ')		//edge case of miss typing with a space
	{								//this will skip those
		charcount++;
	}

	while (s[charcount] != '\0')	//travers through the string
	{
		if (s[charcount] == ' ')	//when space is found read in word
		{
			p1[count] = '\0';

			int k;
			for (k = 0; k < count + 1; k++)
			{
				copy[wordcount][k] = p1[k];	//copy it to a two dimentional array
			}
				
			wordcount++;
			count = 0;
			charcount++;
		}

		p1[count] = *(s + charcount);	//read characters into p1
		count++;
		charcount++;
	}

	if (s[charcount] == '\0')	//checking for the last null at end of string
	{
		p1[count] = '\0';

		int k;
		for (k = 0; k < count + 1; k++)
		{
			copy[wordcount][k] = p1[k];	//read in the final word to the two dimentional array
		}

		wordcount++;
	}

	copy[wordcount] = '\0';


	args[0] = copy;		//copy all the information into args

	return wordcount;	//return tokens
}

int wordsize(char s1[])	//find largest word
{
	int largest = 0, current = 1;

	int i = 0;
	while (s1[i] != '\0')	//when string isn't finished
	{
		if (s1[i] == ' ')
		{
			largest = current;
			current = 0;
		}
		current++;	//add one to current word
		i++;
	}

	if (s1[i] == '\0' && (current > largest))	//if the last word is largest
	{											//change the largest word to current
		largest = current;
	}
	return largest;
}

int words(char s2[])	//function to count words
{
	int wordnum = 1;

	int i = 0;
	while (s2[i] != '\0')	//while string isn't finished
	{
		if (s2[i] == ' ')
		{
			wordnum++;	//when a word is finished add one to count
		}
		i++;
	}
	wordnum++;	//add one to word count

	return wordnum + 1;		//return count plus one for null character
}
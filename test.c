#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_INPUT_COUNT 10

void split_string(const char* line, char* tokens[], int* count)
{
	const char* start = line;
	const char* end;
	*count = 0;

	while(*start)
	{
		end = strchr(start, ';');
		if(end)
		{
			size_t token_length = end - start;
			tokens[*count] = (char*) malloc(token_length + 1);
			if (tokens[*count] == NULL)
			{
				perror("Memory allocation failed");
				exit(1);
			} 
			strncpy(tokens[*count], start, token_length);
			tokens[*count][token_length] = '\0';
			(*count)++;
			start = end + 1;
		}
		else
		{
			tokens[*count] = strdup(start);
			if (tokens[*count] == NULL)
			{
				perror("Memory allocation failed");
				exit(1);
			}
			(*count)++;
			break;
		}
	}
}

int main()
{

    int inputsCount = 0;
    char* inputs[MAX_INPUT_COUNT];
    char* string = strdup("z1;a3/w1;a1/w1;a1/w2");

    split_string(string, inputs, &inputsCount);
    // char* token = strtok(string, ";");
    // inputs[inputsCount] = token;
    // printf("%s\n", inputs[inputsCount]);
    // inputsCount++;
    // if (token == NULL)
    // {
    //     perror("Error token == NULL");
    //     return 1;
    // }
    // while((token = strtok(NULL, ";")) != NULL)
    // {
    //     printf("2:%s\n", token);
    //     inputs[inputsCount] = token;
    //     inputsCount++;
    // }
    
    for (int i = 0; i < inputsCount; i++)
    {
        printf("%s[%d]\n", inputs[i], i);
    }
    free(string);
    return 0;
}




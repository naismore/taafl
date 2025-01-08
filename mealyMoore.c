#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_TRANSITIONS 100
#define MAX_LINE_LENGTH 256
#define MAX_STATES 20
#define MAX_INPUTS 10

typedef struct 
{
	char* currentState; // Текущее состояние
	char* nextState; // Следующее состояние
	char* output; // Выходной символ
	char* input; // Входной символ
} MealyTransition;

typedef struct
{
	char* stateName;
	char* currentState;
	char* nextState;
	char* output;
} MooreState;

void split_string(const char* line, char* tokens[], int* count, char* delim)
{
	const char* start = line;
	const char* end;
	*count = 0;

	while(*start)
	{
		end = strchr(start, *delim);
		if(end)
		{
			size_t token_length = end - start;
			if (token_length != 0)
			{
				tokens[*count] = (char*) malloc(token_length + 1);
				if (tokens[*count] == NULL)
				{
					perror("Memory allocation failed");
					exit(1);
				} 
				strncpy(tokens[*count], start, token_length);
				tokens[*count][token_length] = '\0';
				(*count)++;
			}
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

void readMealyFromFile(const char* filename, MealyTransition transitions[MAX_TRANSITIONS][MAX_STATES], int* countLines, int* countStates)
{
	char* lines[MAX_TRANSITIONS / MAX_STATES];
	char line[MAX_LINE_LENGTH]; // Буфер для чтения файла

	char* rowTransitions[MAX_TRANSITIONS]; // Массив строк (указателей)
	int countTransitions = 0; // Количество переходов
	char* states[MAX_STATES]; // Массив состояний


	FILE *fp = fopen(filename, "r"); // Открытие файла
	if (fp == NULL)
	{
		perror("Unable to open file");
		exit(1);
	}

	if(fgets(line, sizeof(line), fp)) // Считываем состояния
	{
		char* lineCopy = strdup(line);
		printf("%s\n", line);
		split_string(lineCopy, states, &countStates, ";");
		printf("exit\n");
		free(lineCopy);
		for(int i = 0; i < countStates; i++)
		{
			printf("states[%d]: %s\n", i, states[i]);
		}
	}

	while(fgets(line, sizeof(line), fp)) // Считываем все строки переходов и входных символов
	{
		lines[*countLines] = strdup(line);
		countLines++;
	}

	for (int i = 0; i < countLines; i++)
	{
		for(int j = 0; j < countStates; j++)
		{
			transitions[i][j].currentState = states[j];
			printf("Transtitons[%d][%d]: %s\n", i, j, transitions[i][j].currentState);
		}
	}

	int indexTransition = 0;

	for (int i = 0; i < countLines; i++)
	{
		indexTransition = 0;
		char* token = strtok(lines[i], ";"); 
		for(int j = 0; j < countStates; j++)
		{
			transitions[i][j].input = strdup(token);
		}
		while((token = strtok(NULL, ";")) != NULL)
		{
			char *stateString = strdup(token);
			printf("stateString: %s\n", stateString);
			split_string(stateString, rowTransitions, &countTransitions, "/");
			transitions[i][indexTransition].nextState = rowTransitions[0];
			transitions[i][indexTransition].output = rowTransitions[1];
			printf("Transition[%d][%d]: %s/%s\n", i, indexTransition, rowTransitions[0], rowTransitions[1]);
			printf("\n");
			indexTransition++;
			free(stateString);
		}
	}
	
	// for (int i = 0; i < linesCount; i++)
	// {
	// 	for (int j = 0; j < countStates; j++)
	// 	{
	// 		printf("Transtitons[%d][%d]:\n\tCurrent State: %s\n\tInput: %s\n\tNext State: %s\n\tOutput: %s\n\t", i, j, transitions[i][j].currentState, transitions[i][j].input, transitions[i][j].nextState, transitions[i][j].output);
	// 		printf("\n");
	// 	}	
	// }

}

int main()
{
	MealyTransition transitions[MAX_STATES][MAX_INPUTS]; // Массив переходов
	char* filename = "input0.csv"; // Имя файла
	int countLines = 0;
	int countStates = 0; // Количество состояний символов
	readMealyFromFile(filename, transitions, countLines, countStates);

	return 0;
}


#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <time.h>
#include "math.h"

#define maxHiddenLayers 3

enum weightCase{
    oneWeight,
    twoWeight,
    threeWeight,
    fourWeight
};

struct matrix_t
{
	uint8_t rows;
	uint8_t columns;
	double **ptr;
};

typedef struct matrix_t *weights_t;
typedef struct matrix_t *input_t;
typedef struct matrix_t *output_t;

struct neural_t
{
	double input;
	double output;
	double *threshold;
};

typedef struct neural_t *neural;

struct layers_t
{
	uint8_t neuralsNumber;
	neural neural;
};

typedef struct layers_t *layers;

struct neuralNetwork_t
{
	uint8_t layersNumber;
	uint8_t weightsNumber;
	uint8_t neuralsInputNumber;
	uint8_t neuralsOutputNumber;
	input_t inputNeural;
	output_t outputNeural;
	weights_t weights;
	layers Hidderlayers;
};

typedef struct neuralNetwork_t *neuralNetworks;

static void set_weights_number(neuralNetworks neuralNetwork, uint8_t numberMatrices)
{
	neuralNetwork->weightsNumber = numberMatrices;
}

static void set_layer_number(neuralNetworks neuralNetwork, uint8_t numberLayers)
{
	neuralNetwork->layersNumber = numberLayers;
}

static void set_matrix_input_rows(neuralNetworks neuralNetwork, uint8_t rows)
{
	neuralNetwork->inputNeural->rows = rows;
}

static void set_matrix_output_rows(neuralNetworks neuralNetwork, uint8_t rows)
{
	neuralNetwork->outputNeural->rows = rows;
}

static void set_matrix_input_columns(neuralNetworks neuralNetwork, uint8_t columns)
{
	neuralNetwork->inputNeural->columns = columns;
}

static void set_matrix_output_columns(neuralNetworks neuralNetwork, uint8_t columns)
{
	neuralNetwork->outputNeural->columns = columns;
}

static uint8_t get_weights_number(neuralNetworks neuralNetwork)
{
	return neuralNetwork->weightsNumber;
}

static uint8_t get_layer_number(neuralNetworks neuralNetwork)
{
	return neuralNetwork->layersNumber;
}

static uint8_t get_matrix_input_rows(neuralNetworks neuralNetwork)
{
	return neuralNetwork->inputNeural->rows;
}

static uint8_t get_matrix_output_rows(neuralNetworks neuralNetwork)
{
	return neuralNetwork->outputNeural->rows;
}

static uint8_t get_matrix_input_columns(neuralNetworks neuralNetwork)
{
	return neuralNetwork->inputNeural->columns;
}

static uint8_t get_matrix_output_columns(neuralNetworks neuralNetwork)
{
	return neuralNetwork->outputNeural->columns;
}

neuralNetworks create_neural_network()
{
    uint8_t rows;
    uint8_t columns;
    uint8_t numberExamples;
    uint8_t numberInputVariables;
    uint8_t numberOutVariables;
    uint8_t numberHiddenLayers;
    uint8_t numberNeurals;
    uint8_t numberMatrices;
    enum weightCase cases = oneWeight;
	neuralNetworks neuralNetwork = (neuralNetworks)malloc(sizeof(struct neuralNetwork_t));
	if (!neuralNetwork)
	{
		perror("error allocating memory\n\r");
		exit(1);
	}
    do
    {
        printf("Enter the number of hidden layers\n\r");
        printf("The maximum is 3 layers\n\r");
        scanf("%hhu", &numberHiddenLayers);
		if(numberHiddenLayers <= 0 || numberHiddenLayers > maxHiddenLayers)
        {
            printf("Error please enter a number greater than 0 and less than 3\n\r");
        }
    } while (numberHiddenLayers <= 0 || numberHiddenLayers > maxHiddenLayers);
	set_layer_number(neuralNetwork, numberHiddenLayers);
	neuralNetwork->Hidderlayers = (layers)malloc(sizeof(struct layers_t)*neuralNetwork->layersNumber);
	if (!neuralNetwork->Hidderlayers)
	{
		perror("error allocating memory\n\r");
		exit(1);
	}
	for(uint8_t i = 0; i < get_layer_number(neuralNetwork); i++)
	{
		printf("Enter the number of neurons in the hidden layer #%hhu\n\r", i + 1);
		scanf("%hhu", &numberNeurals);
		neuralNetwork->Hidderlayers[i].neuralsNumber = numberNeurals;
		neuralNetwork->Hidderlayers[i].neural = (neural)malloc(sizeof(struct neural_t)*numberNeurals);
		if (!neuralNetwork->Hidderlayers[i].neural)
		{
			perror("error allocating memory\n\r");
			exit(1);
		}
	}
    neuralNetwork->inputNeural = (input_t)malloc(sizeof(struct matrix_t));
    if (!neuralNetwork->inputNeural)
	{
		perror("error allocating memory\n\r");
		exit(1);
	}
    printf("Enter the number of examples of the neural network\n\r");
    scanf("%hhu", &numberExamples);
    printf("Enter the number of neural network input variables\n\r");
    scanf("%hhu", &numberInputVariables);
    set_matrix_input_rows(neuralNetwork, numberExamples);
    set_matrix_input_columns(neuralNetwork, numberInputVariables);
    neuralNetwork->inputNeural->ptr = (double**)malloc(sizeof(double*)*get_matrix_input_rows(neuralNetwork));
    if (!neuralNetwork->inputNeural->ptr)
	{
		perror("error allocating memory\n\r");
		exit(1);
	}
    for(uint8_t i = 0; i < get_matrix_input_rows(neuralNetwork); i++)
    {
        neuralNetwork->inputNeural->ptr[i] = (double*)malloc(sizeof(double)*get_matrix_input_columns(neuralNetwork));
        if (!neuralNetwork->inputNeural->ptr[i])
        {
            perror("error allocating memory\n\r");
            exit(1);
        }
    }
    neuralNetwork->outputNeural = (output_t)malloc(sizeof(struct matrix_t));
    if (!neuralNetwork->outputNeural)
	{
		perror("error allocating memory\n\r");
		exit(1);
	}
    set_matrix_output_rows(neuralNetwork, numberExamples);
    printf("Enter the number of neural network output variables\n\r");
    scanf("%hhu", &numberOutVariables);
    set_matrix_output_columns(neuralNetwork, numberOutVariables);
    neuralNetwork->outputNeural->ptr = (double**)malloc(sizeof(double*)*get_matrix_output_rows(neuralNetwork));
    if (!neuralNetwork->outputNeural->ptr)
	{
		perror("error allocating memory\n\r");
		exit(1);
	}
    for(uint8_t i = 0; i < get_matrix_output_rows(neuralNetwork); i++)
    {
        neuralNetwork->outputNeural->ptr[i] = (double*)malloc(sizeof(double)*get_matrix_output_columns(neuralNetwork));
        if (!neuralNetwork->outputNeural->ptr[i])
        {
            perror("error allocating memory\n\r");
            exit(1);
        }
    }
    set_weights_number(neuralNetwork, numberHiddenLayers + 1);
	neuralNetwork->weights = (weights_t)malloc(sizeof(struct matrix_t)*get_weights_number(neuralNetwork));
	if (!neuralNetwork->weights)
	{
		perror("error allocating memory\n\r");
		exit(1);
	}
	for(uint8_t i = 0; i < get_weights_number(neuralNetwork); i++)
	{
        switch (cases)
        {
        case oneWeight:
			neuralNetwork->weights[i].rows = numberInputVariables;
			neuralNetwork->weights[i].columns = neuralNetwork->Hidderlayers[oneWeight].neuralsNumber;
            cases = twoWeight;
            break;
        case twoWeight:
			printf("%hhu\n\r",get_weights_number(neuralNetwork));
            if(get_weights_number(neuralNetwork) == twoWeight + 1)
            {
				neuralNetwork->weights[i].rows = neuralNetwork->Hidderlayers[oneWeight].neuralsNumber;
				neuralNetwork->weights[i].columns = numberOutVariables;
                break;
            }
            else
            {
				neuralNetwork->weights[i].rows = neuralNetwork->Hidderlayers[oneWeight].neuralsNumber;
				neuralNetwork->weights[i].columns = neuralNetwork->Hidderlayers[twoWeight].neuralsNumber;
                printf("%hhu\n\r",neuralNetwork->weights[i].rows);
				printf("%hhu\n\r",neuralNetwork->weights[i].columns);
				cases = threeWeight;
                break;
            }
            break;      
        case threeWeight:
            if(get_weights_number(neuralNetwork) == threeWeight + 1)
            {
				neuralNetwork->weights[i].rows = neuralNetwork->Hidderlayers[twoWeight].neuralsNumber;
				neuralNetwork->weights[i].columns = numberOutVariables;
                break;
            }
            else
            {
				neuralNetwork->weights[i].rows = neuralNetwork->Hidderlayers[twoWeight].neuralsNumber;
				neuralNetwork->weights[i].columns = neuralNetwork->Hidderlayers[threeWeight].neuralsNumber;
                cases = fourWeight;
                break;
            }
            break;  
        case fourWeight:
			neuralNetwork->weights[i].rows = neuralNetwork->Hidderlayers[threeWeight].neuralsNumber;
			neuralNetwork->weights[i].columns = numberOutVariables;
            break;  
        default:
            break;
        }
		neuralNetwork->weights[i].ptr = (double**)malloc(sizeof(double*)*neuralNetwork->weights[i].rows);
		if (!neuralNetwork->weights[i].ptr)
		{
			perror("error allocating memory\n\r");
			exit(1);
		}
		for(uint8_t j = 0; j < neuralNetwork->weights[i].rows; j++)
		{
			neuralNetwork->weights[i].ptr[j] = (double*)malloc(sizeof(double)*neuralNetwork->weights[i].columns);
			if (!neuralNetwork->weights[i].ptr[j])
			{
				perror("error allocating memory\n\r");
				exit(1);
			}
		}
	}
	return neuralNetwork;
}

void load_neural_network(neuralNetworks neuralNetwork)
{
	enum weightCase cases = oneWeight;
	srand((unsigned int)time(NULL));
	for (uint8_t i = 0; i < get_matrix_input_rows(neuralNetwork); i++)
	{
		for (uint8_t j = 0; j < get_matrix_input_columns(neuralNetwork); j++)
		{
			neuralNetwork->inputNeural->ptr[i][j] =  rand() / (double) RAND_MAX;
		}
	}
	for (uint8_t i = 0; i < get_matrix_output_rows(neuralNetwork); i++)
	{
		for (uint8_t j = 0; j < get_matrix_output_columns(neuralNetwork); j++)
		{
			neuralNetwork->outputNeural->ptr[i][j] =  rand() / (double) RAND_MAX;
		}
	}
	for(uint8_t i = 0; i < get_weights_number(neuralNetwork); i++)
	{
		for (uint8_t j = 0; j < neuralNetwork->weights[i].rows; j++)
		{	
			for (uint8_t k = 0; k < neuralNetwork->weights[i].columns; k++)
			{
				neuralNetwork->weights[i].ptr[j][k] =  rand() / (double) RAND_MAX;
			}
		}
	}
}

static double output_neural_network(neuralNetworks neuralNetwork)
{

}

void show_input_neural(neuralNetworks neuralNetwork)
{
	for (uint8_t i = 0; i < get_matrix_input_rows(neuralNetwork); i++)
	{
		for (uint8_t j = 0; j < get_matrix_input_columns(neuralNetwork); j++)
		{
			printf("%.2f ", neuralNetwork->inputNeural->ptr[i][j]);
		}
		printf("\n\r");
	}
}

void show_output_neural(neuralNetworks neuralNetwork)
{
	for (uint8_t i = 0; i < get_matrix_output_rows(neuralNetwork); i++)
	{
		for (uint8_t j = 0; j < get_matrix_output_columns(neuralNetwork); j++)
		{
			printf("%.2f ", neuralNetwork->outputNeural->ptr[i][j]);
		}
		printf("\n\r");
	}
}

void show_weight(neuralNetworks neuralNetwork)
{
	enum weightCase cases = oneWeight;
	for(uint8_t i = 0; i < get_weights_number(neuralNetwork); i++)
	{
		for (uint8_t j = 0; j < neuralNetwork->weights[i].rows; j++)
		{	
			for (uint8_t k = 0; k < neuralNetwork->weights[i].columns; k++)
			{
				printf("%.2f ",neuralNetwork->weights[i].ptr[j][k]);
			}
			printf("\n\r");
		}
	}
}

int main()
{
    neuralNetworks neuralNetwork = create_neural_network();
	load_neural_network(neuralNetwork);
	show_input_neural(neuralNetwork);
	show_output_neural(neuralNetwork);
	show_weight(neuralNetwork);
    return 0;
}
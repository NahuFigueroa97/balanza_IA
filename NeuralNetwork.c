#include "NeuralNetwork.h"

static float sigmoide(float x) 
{
	return 1.0 / (1.0 + exp(-x));
}

static float rand_generator()
{
    float scale = rand() / (float) RAND_MAX; 
    return min + scale * ( max - min );      
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
	neuralNetwork->layersNumber = numberHiddenLayers;
	neuralNetwork->Hidderlayers = (layers)malloc(sizeof(struct layers_t)*neuralNetwork->layersNumber);
	if (!neuralNetwork->Hidderlayers)
	{
		perror("error allocating memory\n\r");
		exit(1);
	}
	printf("Enter the number of examples of the neural network\n\r");
	scanf("%hhu", &numberExamples);
	neuralNetwork->examples = numberExamples;
	printf("Enter the number of neural network input variables\n\r");
	scanf("%hhu", &numberInputVariables);
	neuralNetwork->neuralsInputNumber = numberInputVariables;
	for(uint8_t i = 0; i < neuralNetwork->layersNumber; i++)
	{
		printf("Enter the number of neurons in the hidden layer #%hhu\n\r", i + 1);
		scanf("%hhu", &numberNeurals);
		neuralNetwork->Hidderlayers[i].neuralsNumber = numberNeurals;
		neuralNetwork->Hidderlayers[i].neural = (neural)malloc(sizeof(struct neural_t)*neuralNetwork->Hidderlayers[i].neuralsNumber);
		if (!neuralNetwork->Hidderlayers[i].neural)
		{
			perror("error allocating memory\n\r");
			exit(1);
		}
		neuralNetwork->Hidderlayers[i].neural->threshold = (float*)malloc(sizeof(float)*neuralNetwork->Hidderlayers[i].neuralsNumber);
		if (!neuralNetwork->Hidderlayers[i].neural->threshold)
		{
			perror("error allocating memory\n\r");
			exit(1);
		}
		neuralNetwork->Hidderlayers[i].neural->input = (float**)malloc(sizeof(float*)*neuralNetwork->examples);
		if (!neuralNetwork->Hidderlayers[i].neural->input)
		{
			perror("error allocating memory\n\r");
			exit(1);
		}
		for (uint8_t j = 0; j < neuralNetwork->examples; j++)
		{
			neuralNetwork->Hidderlayers[i].neural->input[j] = (float*)malloc(sizeof(float)*neuralNetwork->Hidderlayers[i].neuralsNumber);
			if (!neuralNetwork->Hidderlayers[i].neural->input[j])
			{
				perror("error allocating memory\n\r");
				exit(1);
			}	
		}
		neuralNetwork->Hidderlayers[i].neural->output = (float**)malloc(sizeof(float)*neuralNetwork->examples);
		if (!neuralNetwork->Hidderlayers[i].neural->output)
		{
			perror("error allocating memory\n\r");
			exit(1);
		}
		for (uint8_t j = 0; j < neuralNetwork->examples; j++)
		{
			neuralNetwork->Hidderlayers[i].neural->output[j] = (float*)malloc(sizeof(float)*neuralNetwork->Hidderlayers[i].neuralsNumber);
			if (!neuralNetwork->Hidderlayers[i].neural->output[j])
			{
				perror("error allocating memory\n\r");
				exit(1);
			}	
		}
	}
    neuralNetwork->inputNeural = (input_t)malloc(sizeof(struct matrix_t));
	neuralNetwork->inputNeural->rows = neuralNetwork->examples;
	neuralNetwork->inputNeural->columns = neuralNetwork->neuralsInputNumber;
    if (!neuralNetwork->inputNeural)
	{
		perror("error allocating memory\n\r");
		exit(1);
	}
    neuralNetwork->inputNeural->ptr = (float**)malloc(sizeof(float*)*neuralNetwork->inputNeural->rows);
    if (!neuralNetwork->inputNeural->ptr)
	{
		perror("error allocating memory\n\r");
		exit(1);
	}
    for(uint8_t i = 0; i < neuralNetwork->inputNeural->rows; i++)
    {
        neuralNetwork->inputNeural->ptr[i] = (float*)malloc(sizeof(float)*neuralNetwork->inputNeural->columns);
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
	neuralNetwork->outputNeural->rows = numberExamples;
    printf("Enter the number of neural network output variables\n\r");
    scanf("%hhu", &numberOutVariables);
	neuralNetwork->outputNeural->columns = numberOutVariables;
    neuralNetwork->outputNeural->ptr = (float**)malloc(sizeof(float*)*neuralNetwork->outputNeural->rows);
    if (!neuralNetwork->outputNeural->ptr)
	{
		perror("error allocating memory\n\r");
		exit(1);
	}
    for(uint8_t i = 0; i < neuralNetwork->outputNeural->rows; i++)
    {
        neuralNetwork->outputNeural->ptr[i] = (float*)malloc(sizeof(float)*neuralNetwork->outputNeural->columns);
        if (!neuralNetwork->outputNeural->ptr[i])
        {
            perror("error allocating memory\n\r");
            exit(1);
        }
    }
	neuralNetwork->desired_output = (desired_output_t)malloc(sizeof(struct matrix_t));
	if(!neuralNetwork->desired_output)
	{
		perror("error allocating memory\n\r");
		exit(1);
	}
	neuralNetwork->desired_output->ptr = (float**)malloc(sizeof(float*)*neuralNetwork->outputNeural->rows);
	if(!neuralNetwork->desired_output->ptr)
	{
		perror("error allocating memory\n\r");
		exit(1);
	}
	for(uint8_t i = 0; i < neuralNetwork->outputNeural->rows; i++)
    {
        neuralNetwork->desired_output->ptr[i] = (float*)malloc(sizeof(float)*neuralNetwork->outputNeural->columns);
        if (!neuralNetwork->desired_output->ptr[i])
        {
            perror("error allocating memory\n\r");
            exit(1);
        }
    }
	neuralNetwork->threshold = (float*)malloc(sizeof(float)*neuralNetwork->neuralsOutputNumber);
    if (!neuralNetwork->threshold)
    {
		perror("error allocating memory\n\r");
		exit(1);
    }
	neuralNetwork->weightsNumber = numberHiddenLayers + 1;
	neuralNetwork->weights = (weights_t)malloc(sizeof(struct matrix_t)*neuralNetwork->weightsNumber);
	if (!neuralNetwork->weights)
	{
		perror("error allocating memory\n\r");
		exit(1);
	}
	for(uint8_t i = 0; i < neuralNetwork->weightsNumber; i++)
	{
        switch (cases)
        {
        case oneWeight:
			neuralNetwork->weights[i].rows = numberInputVariables;
			neuralNetwork->weights[i].columns = neuralNetwork->Hidderlayers[oneWeight].neuralsNumber;
            cases = twoWeight;
            break;
        case twoWeight:
            if(neuralNetwork->weightsNumber == twoWeight + 1)
            {
				neuralNetwork->weights[i].rows = neuralNetwork->Hidderlayers[oneWeight].neuralsNumber;
				neuralNetwork->weights[i].columns = numberOutVariables;
                break;
            }
            else
            {
				neuralNetwork->weights[i].rows = neuralNetwork->Hidderlayers[oneWeight].neuralsNumber;
				neuralNetwork->weights[i].columns = neuralNetwork->Hidderlayers[twoWeight].neuralsNumber;
				cases = threeWeight;
                break;
            }
            break;      
        case threeWeight:
            if(neuralNetwork->weightsNumber == threeWeight + 1)
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
		neuralNetwork->weights[i].ptr = (float**)malloc(sizeof(float*)*neuralNetwork->weights[i].rows);
		if (!neuralNetwork->weights[i].ptr)
		{
			perror("error allocating memory\n\r");
			exit(1);
		}
		for(uint8_t j = 0; j < neuralNetwork->weights[i].rows; j++)
		{
			neuralNetwork->weights[i].ptr[j] = (float*)malloc(sizeof(float)*neuralNetwork->weights[i].columns);
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
	float value;
	srand((unsigned int)time(NULL));
	for (uint8_t i = 0; i < neuralNetwork->inputNeural->rows; i++)
	{
		for (uint8_t j = 0; j < neuralNetwork->inputNeural->columns; j++)
		{
			printf("Enter the value of variable #%hhu from example #%hhu\n\r", j + 1, i + 1);
			scanf("%f", &value);
			neuralNetwork->inputNeural->ptr[i][j] =  value;
		}
	}
	for (uint8_t i = 0; i < neuralNetwork->outputNeural->rows; i++)
	{
		for (uint8_t j = 0; j < neuralNetwork->outputNeural->columns; j++)
		{
			printf("Enter the value of output #%hhu from example #%hhu\n\r", j + 1, i + 1);
			scanf("%f", &value);
			neuralNetwork->desired_output->ptr[i][j]= value;
		}
	}
	for (uint8_t i = 0; i < neuralNetwork->outputNeural->rows; i++)
	{
		for (uint8_t j = 0; j < neuralNetwork->outputNeural->columns; j++)
		{
			neuralNetwork->outputNeural->ptr[i][j] =  0.0;
			neuralNetwork->threshold[j] = rand_generator();
		}
	}
	for (uint8_t i = 0; i < neuralNetwork->layersNumber; i++)
	{
		for (uint8_t j = 0; j < neuralNetwork->Hidderlayers[i].neuralsNumber; j++)
		{
			neuralNetwork->Hidderlayers[i].neural->threshold[j] = rand_generator();
		}
		for (uint8_t k = 0; k < neuralNetwork->inputNeural->rows; k++)
		{
			for (uint8_t j = 0; j < neuralNetwork->Hidderlayers[i].neuralsNumber; j++)
			{
				neuralNetwork->Hidderlayers[i].neural->input[k][j]  = 0.0;
				neuralNetwork->Hidderlayers[i].neural->output[k][j] = 0.0;
			}
		}
	}
	for(uint8_t i = 0; i < neuralNetwork->weightsNumber; i++)
	{
		for (uint8_t j = 0; j < neuralNetwork->weights[i].rows; j++)
		{	
			for (uint8_t k = 0; k < neuralNetwork->weights[i].columns; k++)
			{
				neuralNetwork->weights[i].ptr[j][k] = rand_generator();
			}
		}
	}
}

static void a_2(neuralNetworks neuralNetwork, uint8_t k)
{
    float acum = 0;
	uint8_t i = neuralNetwork->example;
	for(uint8_t j = 0; j < neuralNetwork->inputNeural->columns; j++)
	{
		acum += neuralNetwork->inputNeural->ptr[i][j]*neuralNetwork->weights[0].ptr[j][k];
	}
	neuralNetwork->Hidderlayers[0].neural->input[i][k] = acum + neuralNetwork->Hidderlayers[0].neural->threshold[k];
	neuralNetwork->Hidderlayers[0].neural->output[i][k] = sigmoide(neuralNetwork->Hidderlayers[0].neural->input[i][k]);
}

static void a_3(neuralNetworks neuralNetwork, uint8_t p)
{
    float acum = 0;
	uint8_t i = neuralNetwork->example;
	for(uint8_t k = 0; k < neuralNetwork->Hidderlayers[0].neuralsNumber; k++)
	{
		a_2(neuralNetwork, k);
		acum += neuralNetwork->Hidderlayers[0].neural->output[i][k]*neuralNetwork->weights[1].ptr[k][p];
	}
	neuralNetwork->Hidderlayers[1].neural->input[i][p] = acum + neuralNetwork->Hidderlayers[1].neural->threshold[p];
	neuralNetwork->Hidderlayers[1].neural->output[i][p] = sigmoide(neuralNetwork->Hidderlayers[1].neural->input[i][p]);
}

static void a_4(neuralNetworks neuralNetwork, uint8_t t)
{
    float acum = 0;
	uint8_t i = neuralNetwork->example;
	for(uint8_t p = 0; p < neuralNetwork->Hidderlayers[1].neuralsNumber; p++)
	{
		a_3(neuralNetwork, p);
		acum += neuralNetwork->Hidderlayers[1].neural->output[i][p]*neuralNetwork->weights[2].ptr[p][t];
	}
	neuralNetwork->Hidderlayers[2].neural->input[i][t] = acum + neuralNetwork->Hidderlayers[2].neural->threshold[t];
	neuralNetwork->Hidderlayers[2].neural->output[i][t] = sigmoide(neuralNetwork->Hidderlayers[2].neural->input[i][t]);
}

static void output_neural_network(neuralNetworks neuralNetwork, uint8_t output)
{
	uint8_t target = neuralNetwork->layersNumber;
	float acum = 0;
	switch (target)
	{
	case 1:
	for (uint8_t i = 0; i < neuralNetwork->inputNeural->rows; i++)
	{
		neuralNetwork->example = i;
		float acum = 0;
		for(uint8_t k = 0; k < neuralNetwork->Hidderlayers[0].neuralsNumber; k++)
		{
			a_2(neuralNetwork, k);
			acum += neuralNetwork->Hidderlayers[0].neural->output[i][k]*neuralNetwork->weights[1].ptr[k][output];
		}
		neuralNetwork->outputNeural->ptr[i][output] = sigmoide(acum + neuralNetwork->threshold[output]);
	}
	break;
	case 2:
	for (uint8_t i = 0; i < neuralNetwork->inputNeural->rows; i++)
	{
		neuralNetwork->example = i;
		float acum = 0;
		for(uint8_t p = 0; p < neuralNetwork->Hidderlayers[1].neuralsNumber; p++)
		{
			a_3(neuralNetwork, p);
			acum += neuralNetwork->Hidderlayers[1].neural->output[i][p]*neuralNetwork->weights[2].ptr[p][output];
		}
		neuralNetwork->outputNeural->ptr[i][output] = sigmoide(acum + neuralNetwork->threshold[output]);
	}
	break;
	case 3:
	for (uint8_t i = 0; i < neuralNetwork->inputNeural->rows; i++)
	{
		neuralNetwork->example = i;
		float acum = 0;
		for(uint8_t t = 0; t < neuralNetwork->Hidderlayers[2].neuralsNumber; t++)
		{
			a_4(neuralNetwork, t);
			acum += neuralNetwork->Hidderlayers[2].neural->output[i][t]*neuralNetwork->weights[3].ptr[t][output];
		}
		neuralNetwork->outputNeural->ptr[i][output] = sigmoide(acum + neuralNetwork->threshold[output]);
	}
	break;
	default:
		break;
	}
}

void back_propagation(neuralNetworks neuralNetwork)
{
	uint8_t target = neuralNetwork->layersNumber;
	float error[neuralNetwork->outputNeural->rows][neuralNetwork->outputNeural->columns];
	float alfa = 0.65;
	for (uint8_t i = 0; i < neuralNetwork->outputNeural->rows; i++)
	{
		for (uint8_t p = 0; p < neuralNetwork->outputNeural->columns; p++)
		{
			output_neural_network(neuralNetwork, p);
			error[i][p] = neuralNetwork->outputNeural->ptr[i][p] - neuralNetwork->desired_output->ptr[i][p];
		}
	}
	switch (target)
	{
	case 1:
		for (uint8_t i = 0; i < neuralNetwork->outputNeural->rows; i++)
		{
			for (uint8_t p = 0; p < neuralNetwork->outputNeural->columns; p++)
			{
				float a_pi = neuralNetwork->outputNeural->ptr[i][p];
				float s = neuralNetwork->desired_output->ptr[i][p];
				for (uint8_t j = 0; j < neuralNetwork->inputNeural->columns; j++)
				{
					for (uint8_t k = 0; k < neuralNetwork->Hidderlayers[0].neuralsNumber; k++)
					{
						float a_k  = neuralNetwork->Hidderlayers[0].neural->output[i][k];
						float a_ij = neuralNetwork->inputNeural->ptr[i][j];
						
						neuralNetwork->weights[1].ptr[k][p] = neuralNetwork->weights[1].ptr[k][p] - alfa*error[i][p]*a_pi*(1 - a_pi)*a_k;
						neuralNetwork->threshold[p] = neuralNetwork->threshold[p] - alfa*error[i][p]*a_pi*(1 - a_pi);
						
						neuralNetwork->weights[0].ptr[j][k] = neuralNetwork->weights[0].ptr[j][k] - alfa*error[i][p]*a_pi*(1 - a_pi)*neuralNetwork->weights[1].ptr[k][p]*a_k*(1 - a_k)*a_ij;
						neuralNetwork->Hidderlayers[0].neural->threshold[k] = neuralNetwork->Hidderlayers[0].neural->threshold[k] - alfa*error[i][p]*a_pi*(1 - a_pi)*neuralNetwork->weights[1].ptr[k][p]*a_k*(1 - a_k);
					}
				}
			}	
		}
		break;
	case 2:
		for (uint8_t i = 0; i < neuralNetwork->outputNeural->rows; i++)
		{
			for (uint8_t t = 0; t < neuralNetwork->outputNeural->columns; t++)
			{
				float a_ti = neuralNetwork->outputNeural->ptr[i][t];
				float s = neuralNetwork->desired_output->ptr[i][t];
				for (uint8_t j = 0; j < neuralNetwork->inputNeural->columns; j++)
				{
					for (uint8_t k = 0; k < neuralNetwork->Hidderlayers[0].neuralsNumber; k++)
					{
						for (uint8_t p = 0; p < neuralNetwork->Hidderlayers[1].neuralsNumber; p++)
						{
							float a_p = neuralNetwork->Hidderlayers[1].neural->output[i][p];
							float a_k  = neuralNetwork->Hidderlayers[0].neural->output[i][k];
							float a_ij = neuralNetwork->inputNeural->ptr[i][j];

							neuralNetwork->weights[2].ptr[p][t] = neuralNetwork->weights[2].ptr[p][t] - alfa*error[i][t]*a_ti*(1 - a_ti)*a_p;
							neuralNetwork->threshold[t] = neuralNetwork->threshold[t] - alfa*error[i][t]*a_ti*(1 - a_ti);
							
							neuralNetwork->weights[1].ptr[k][p] = neuralNetwork->weights[1].ptr[k][p] - alfa*error[i][t]*a_ti*(1 - a_ti)*neuralNetwork->weights[2].ptr[p][t]*a_p*(1 - a_p)*a_k;
							neuralNetwork->Hidderlayers[1].neural->threshold[p] = neuralNetwork->Hidderlayers[1].neural->threshold[p] - alfa*error[i][t]*a_ti*(1 - a_ti)*neuralNetwork->weights[2].ptr[p][t]*a_p*(1 - a_p);
							
							neuralNetwork->weights[0].ptr[j][k] = neuralNetwork->weights[0].ptr[j][k] - alfa*error[i][t]*a_ti*(1 - a_ti)*neuralNetwork->weights[2].ptr[p][t]*a_p*(1 - a_p)*neuralNetwork->weights[1].ptr[k][p]*a_k*(1 - a_k)*a_ij;
							neuralNetwork->Hidderlayers[0].neural->threshold[k] = neuralNetwork->Hidderlayers[0].neural->threshold[k] - alfa*error[i][t]*a_ti*(1 - a_ti)*neuralNetwork->weights[2].ptr[p][t]*a_p*(1 - a_p)*neuralNetwork->weights[1].ptr[k][p]*a_k*(1 - a_k);
						}
					}
				}
			}	
		}
		break;
	case 3:
		for (uint8_t i = 0; i < neuralNetwork->outputNeural->rows; i++)
		{
			for (uint8_t v = 0; v < neuralNetwork->outputNeural->columns; v++)
			{
				float a_vi = neuralNetwork->outputNeural->ptr[i][v];
				float s = neuralNetwork->desired_output->ptr[i][v];
				for (uint8_t j = 0; j < neuralNetwork->inputNeural->columns; j++)
				{
					for (uint8_t k = 0; k < neuralNetwork->Hidderlayers[0].neuralsNumber; k++)
					{
						for (uint8_t p = 0; p < neuralNetwork->Hidderlayers[1].neuralsNumber; p++)
						{
							for (uint8_t t = 0; t < neuralNetwork->Hidderlayers[2].neuralsNumber; t++)
							{
								float a_t  = neuralNetwork->Hidderlayers[2].neural->output[i][t];
								float a_p  = neuralNetwork->Hidderlayers[1].neural->output[i][p];
								float a_k  = neuralNetwork->Hidderlayers[0].neural->output[i][k];
								float a_ij = neuralNetwork->inputNeural->ptr[i][j];

								neuralNetwork->weights[3].ptr[t][v] = neuralNetwork->weights[3].ptr[t][v] - alfa*error[i][v]*a_vi*(1 - a_vi)*a_t;
								neuralNetwork->threshold[v] = neuralNetwork->threshold[v] - alfa*error[i][v]*a_vi*(1 - a_vi);

								neuralNetwork->weights[2].ptr[p][t] = neuralNetwork->weights[2].ptr[p][t] - alfa*error[i][t]*a_vi*(1 - a_vi)*neuralNetwork->weights[3].ptr[t][v]*a_t*(1 - a_t)*a_p;
								neuralNetwork->Hidderlayers[2].neural->threshold[t] = neuralNetwork->Hidderlayers[2].neural->threshold[t] - alfa*error[i][t]*a_vi*(1 - a_vi)*neuralNetwork->weights[3].ptr[t][v]*a_t*(1 - a_t);
								
								neuralNetwork->weights[1].ptr[k][p] = neuralNetwork->weights[1].ptr[k][p] - alfa*error[i][t]*a_vi*(1 - a_vi)*neuralNetwork->weights[3].ptr[t][v]*a_t*(1 - a_t)*neuralNetwork->weights[2].ptr[p][t]*a_p*(1 - a_p)*a_k;
								neuralNetwork->Hidderlayers[1].neural->threshold[p] = neuralNetwork->Hidderlayers[1].neural->threshold[p] - alfa*error[i][t]*a_vi*(1 - a_vi)*neuralNetwork->weights[3].ptr[t][v]*a_t*(1 - a_t)*neuralNetwork->weights[2].ptr[p][t]*a_p*(1 - a_p);
								
								neuralNetwork->weights[0].ptr[j][k] = neuralNetwork->weights[0].ptr[j][k] - alfa*error[i][t]*a_vi*(1 - a_vi)*neuralNetwork->weights[3].ptr[t][v]*a_t*(1 - a_t)*neuralNetwork->weights[2].ptr[p][t]*a_p*(1 - a_p)*neuralNetwork->weights[1].ptr[k][p]*a_k*(1 - a_k)*a_ij;
								neuralNetwork->Hidderlayers[0].neural->threshold[k] = neuralNetwork->Hidderlayers[0].neural->threshold[k] - alfa*error[i][t]*a_vi*(1 - a_vi)*neuralNetwork->weights[3].ptr[t][v]*a_t*(1 - a_t)*neuralNetwork->weights[2].ptr[p][t]*a_p*(1 - a_p)*neuralNetwork->weights[1].ptr[k][p]*a_k*(1 - a_k);
							}
						}
					}
				}
			}	
		}
		break;
	default:
		break;
	}

}

void show_input_neural(neuralNetworks neuralNetwork)
{
	for (uint8_t i = 0; i < neuralNetwork->inputNeural->rows; i++)
	{
		for (uint8_t j = 0; j < neuralNetwork->inputNeural->columns; j++)
		{
			printf("%.2f ", neuralNetwork->inputNeural->ptr[i][j]);
		}
		printf("\n\r");
	}
}

void show_desired_output(neuralNetworks neuralNetwork)
{
	for (uint8_t i = 0; i < neuralNetwork->outputNeural->rows; i++)
	{
		for (uint8_t j = 0; j < neuralNetwork->outputNeural->columns; j++)
		{
			printf("%.2f ", neuralNetwork->desired_output->ptr[i][j]);
		}
		printf("\n\r");
	}
}

void show_output_neural(neuralNetworks neuralNetwork)
{
	for (uint8_t i = 0; i < neuralNetwork->outputNeural->rows; i++)
	{
		for (uint8_t j = 0; j < neuralNetwork->outputNeural->columns; j++)
		{
			printf("%f ", neuralNetwork->outputNeural->ptr[i][j]);
		}
		printf("\n\r");
	}
}

void show_weight(neuralNetworks neuralNetwork)
{
	enum weightCase cases = oneWeight;
	for(uint8_t i = 0; i < neuralNetwork->weightsNumber; i++)
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

void show_threshold(neuralNetworks neuralNetwork)
{
	for (uint8_t i = 0; i < neuralNetwork->layersNumber; i++)
	{
		for (uint8_t j = 0; j < neuralNetwork->Hidderlayers[i].neuralsNumber; j++)
		{
			printf("%.2f ", neuralNetwork->Hidderlayers[i].neural->threshold[j]);
		}
		printf("\n\r");
	}
	for (uint8_t i = 0; i < neuralNetwork->outputNeural->columns; i++)
	{
		printf("%.2f ", neuralNetwork->threshold[i]);
	}
	printf("\n\r");
}

void show_neural_networks(neuralNetworks neuralNetwork)
{
	show_input_neural(neuralNetwork);
	printf("\n\r");
	show_output_neural(neuralNetwork);
	printf("\n\r");
	show_weight(neuralNetwork);
	printf("\n\r");
	show_threshold(neuralNetwork);
}

int main()
{
    neuralNetworks neuralNetwork = create_neural_network();
	load_neural_network(neuralNetwork);
	show_input_neural(neuralNetwork);
	show_desired_output(neuralNetwork);
	for (uint8_t output = 0; output < neuralNetwork->outputNeural->columns; output++)
	{
		output_neural_network(neuralNetwork, output);
	}
	show_output_neural(neuralNetwork);
	for (uint16_t i = 0; i < 1000; i++)
	{
		back_propagation(neuralNetwork);
	}
	printf("###################\n\r");
	show_output_neural(neuralNetwork);
    return 0;
}
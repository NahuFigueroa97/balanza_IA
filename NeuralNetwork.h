#ifndef _NEURALNETWORK_H__
#define _NEURALNETWORK_H__

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <time.h>
#include <math.h>

#define maxHiddenLayers 3
#define min -1
#define max 1

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
	float **ptr;
};

typedef struct matrix_t *weights_t;
typedef struct matrix_t *input_t;
typedef struct matrix_t *output_t;
typedef struct matrix_t *desired_output_t;

struct neural_t
{
	float **input;
	float **output;
	float *threshold;
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
	uint8_t example;
	uint8_t examples;
	uint8_t layersNumber;
	uint8_t weightsNumber;
	uint8_t neuralsInputNumber;
	uint8_t neuralsOutputNumber;
	input_t inputNeural;
	output_t outputNeural;
	desired_output_t desired_output;
	weights_t weights;
	layers Hidderlayers;
	float *threshold;
};

typedef struct neuralNetwork_t *neuralNetworks;

neuralNetworks create_neural_network();

void load_neural_network(neuralNetworks neuralNetwork);

static void a_2(neuralNetworks neuralNetwork, uint8_t k);

static void a_3(neuralNetworks neuralNetwork, uint8_t p);

static void a_4(neuralNetworks neuralNetwork, uint8_t t);

static void output_neural_network(neuralNetworks neuralNetwork, uint8_t output);

void back_propagation(neuralNetworks neuralNetwork);

void show_input_neural(neuralNetworks neuralNetwork);

void show_desired_output(neuralNetworks neuralNetwork);

void show_output_neural(neuralNetworks neuralNetwork);

void show_weight(neuralNetworks neuralNetwork);

void show_threshold(neuralNetworks neuralNetwork);

void show_neural_networks(neuralNetworks neuralNetwork);

#endif
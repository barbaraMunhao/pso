#include "Knapsack.h"

//Construtor
Knapsack::Knapsack(FILE* fileIn)
{	
	fscanf(fileIn, "%d", &numItems);
	fscanf(fileIn, "%d", &numResources);

	//printf("Num Objs  = %d Num Comparts = %d\n", m->qtdObjs, m->numConstraints);

	fscanf(fileIn, "%d", &optSol);

	//Alocação do vetor de values
	values = new int[numItems];//(int*) malloc(numItems * sizeof(int));

	//Leitura do vetor de values
	for (int j = 0; j < numItems; j++)
		fscanf(fileIn, "%d", &(values[j]));

	//Alocação da matriz de useResources como um vetor
	useResources = new int*[numResources];//(int**) malloc(numResources * sizeof(int*));

	for (int j = 0; j < numResources; j++)
		useResources[j] = new int[numItems];//(int*) malloc(numItems * sizeof(int));

	//Leitura da matriz de useResources
	for (int j = 0; j < numResources; j++)
		for (int k = 0; k < numItems; k++)
			fscanf(fileIn, "%d", &(useResources[j][k]));


	//Alocação do vetor de restrições
	capResources = new int[numResources];//(int*) malloc(numResources * sizeof(int));

	//Leitura do vetor de restrições
	for (int j = 0; j < numResources; j++)
		fscanf(fileIn, "%d", &(capResources[j]));
}

//Getters
int
Knapsack::getOptSol()
{
	return optSol;
}

int 
Knapsack::getNumItems()
{
	return numItems;
}

int 
Knapsack::getNumResources()
{
	return numResources;
}

//Destrutor
Knapsack::~Knapsack()
{
	delete[] values;
	
	for (int j = 0; j < numResources; j++)
		delete[] useResources[j];
		
	delete[] useResources;
	
	delete[] capResources;
}

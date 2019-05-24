/*
 * Definição da Mochila Multidimensional
 */
 #ifndef __Knapsack__
 #define __Knapsack__
#include <stdio.h>

class Knapsack
{
	private:
		int optSol;  // Valor somados dos itens
		int numItems;        // Número de itens
		int numResources;  	 // Número de recursos
		int* values;       // Valores dos itens
		int** useResources;  // O quanto cada item consome de cada recurso (matriz em forma de vetor)
		int* capResources;   // Quantidade disponível de cada recurso
		
	public:
		//Construtor
		Knapsack(FILE*);
		
		//Getters
		int getOptSol();
		int getNumItems();
		int getNumResources();
		
		//Destrutor
		~Knapsack();
		
		friend class Application;
        friend class Particle;
};
#endif// __Knapsack
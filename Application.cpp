#include "Application.h"
Application::Application(char* argv[], bool& erro)
{
	char nomeArq[20];
	
	//Seta a taxa de aprendizado e o número máximo de épocas
	strcpy(nomeArq, argv[1]);

    FILE* fileIn = 0;
        
	//Tenta abrir o arquivo de entrada para leitura
	fileIn = fopen(nomeArq, "r");

	if (fileIn == NULL)
	{
	    printf("Erro na abertura do arquivo de entrada.\n");
	    erro = true;
	    return;
	}
   
    //Instancia a mochila
    k = new Knapsack(fileIn);
    
    fclose(fileIn);   
    
    sprintf(fileOutName, "pso_%s it_%s size%s", argv[2], argv[3], ".out");
	
	vetGaps = new float[EXECS];//(float*) malloc(EXECS * sizeof(float));
	vetTimes = new float[EXECS];//(float*) malloc(EXECS * sizeof(float));
}

void
Application::run(int epochs, int swarmSize, float w, int c1, int c2, float penalty )
{
	timeval start, finish;
	double totalTime; 
	
	/*******************************************************************
	 * Laço de execuções                                               *
	 ******************************************************************/
	mediumTime = 0.0;
	mediumGap = 0.0;
	bestOverallSolValue = 0.0;
	numOpt = 0;
	numBetter = 0;
	param * p = new param(c1, c2, w, penalty);
	for (int exec = 0; exec < EXECS; exec++)
	{		
		srand(time(NULL));
		gettimeofday(&start, NULL);		
		
        //Executa o Heuristica
		heuristic::Pso& pso = * (new heuristic::Pso(epochs, swarmSize, k, p));  // review
        pso.initialize();
		pso.execute();
		
		//Fim da tomada de tempo
		gettimeofday(&finish, NULL);

		long start_usecs, finish_usecs, diff_usecs;

		finish_usecs = finish.tv_usec + (1000000 * finish.tv_sec);
		start_usecs = start.tv_usec + (1000000 * start.tv_sec);
		diff_usecs = finish_usecs - start_usecs;

		totalTime = (double)(diff_usecs) / 1000000;
		
		//Escreve o resultado final da execução
		writeBestResult(fileOutName, totalTime, exec);
		
		vetGaps[exec] = ((k->optSol - pso.fitness()) / (float)k->optSol) * 100.0f; // review
		vetTimes[exec] = totalTime;
		
		mediumTime += totalTime;
		mediumGap += vetGaps[exec];
		
		if (pso.fitness() >= bestOverallSolValue)
		{
			bestOverallSolValue = pso.fitness();
			bestOverallTime = totalTime;
			bestOverallGap = vetGaps[exec];
		}
		
		if (vetGaps[exec] == 0.0)
			numOpt++;
		else if (vetGaps[exec] < 0.0)
			numBetter++;
			
	}//Fim das execuções
	
	//Calcular média e desvio padrão das execuções
	mediumTime /= EXECS;
	mediumGap /= EXECS;
	
	dpTimes = 0.0;
	dpGaps = 0.0;
	
	for (int i = 0; i < EXECS; i++)
	{
		dpTimes += pow((vetTimes[i] - mediumTime), 2);
		dpGaps += pow((vetGaps[i] - mediumGap), 2);
	}
	
	dpTimes /= EXECS;
	dpGaps /= EXECS;
	
	dpTimes = sqrt(dpTimes);
	dpGaps = sqrt(dpGaps);
	
	//finalWrite(fileOutName);
	printf("%f", bestOverallSolValue);
}



void 
Application::writeBestResult(char* nome, double time, int exec) // TODO
{
	FILE* f;
	FILE* fGaps;
	FILE* fSols;
	FILE* fTimes;

	f = fopen(nome, "a+");
    fGaps = fopen("seqsa_allgaps_pr.out", "a+");
    fSols = fopen("seqsa_allsols_pr.out", "a+");
	fTimes = fopen("seqsa_alltimes_pr.out", "a+");

	/*float gap = (float)((k->optSol - gBestFitness) / k->optSol) * 100;
	
    fprintf(f, "Execução: %d\nTempo Total: %.4f", exec, time);
    fprintf(f, "\nSolução ótima = %d\nMelhor solução = %.2f\nErro: %f%%\n",
			k->optSol, gBestFitness, gap);

    fprintf(fGaps,"%f\n", gap);
	fprintf(fSols,"%.2f\n", gBestFitness);
	fprintf(fTimes,"%.4f\n", time);
    fprintf(f, "Solução:\n");

    for (int i = 0; i < k->numItems; i++)
		fprintf(f, "%d", gBest[i]);*/

    fprintf(f, "\n\n");

    fclose(f);
    fclose(fGaps);
    fclose(fSols);
    fclose(fTimes);
}

/*
 * Método para escrever no arquivo de saída
 */
void 
Application::finalWrite(char* nome) // TODO
{
	FILE* f2;
	double bestGap = (float)((k->optSol - bestOverallSolValue) / k->optSol) * 100;
	
    FILE* f = fopen(nome, "a+");
    f2 = fopen("dadostabela.out", "a+");

   /* fprintf(f, "Execuções: %d \nNumero de Iteracoes: %d \nTamanho do enxame: %d\nTempo Medio: %.4f \nErro Médio: %lf \nDesvio-Padrão (Gaps): %.4lf\nDesvio-Padrão (Tempos): %.4lf\nMelhor Solução: %.4lf, Melhor Gap: %.4lf, Melhor Tempo: %.4lf\nÓtimas: %d\nMelhores: %d\n",
			EXECS, numIteracoes, sizeOfSwarm, mediumTime, mediumGap, dpGaps, dpTimes, bestOverallSolValue, bestGap, bestOverallTime, numOpt, numBetter);*/

	fprintf(f2, "%d %.4f %.4f %.4f %.4f %.4f\n", numOpt, bestGap, mediumGap, dpGaps, mediumTime, dpTimes);
    //fprintf(f, "\n\n");

    fclose(f);
    fclose(f2);
}

Application::~Application()
{
	//Libera a memória alocada
	delete k;
    
    
	delete[] vetGaps;
	delete[] vetTimes;
}

//pso file.in epochs swarmSize
#include "Application.h"

int main(int argc, char *argv[])
{
	//Verifica se o número de argumentos do programa está correto
    if (argc != 4)
    {
		printf("Uso:\n./pso arq_teste num_it tam_enxame\n");

		return 0;
    }

	bool erro = false;
	
	Application* app = new Application(argv, erro);
	
	if (erro)
	{
		printf("Não foi possível executar a aplicação!\n");
	
		return 1;
	}
		auto epochs = atoi(argv[2]);
		auto swarmSize = atoi(argv[3]);

	app->run(epochs,swarmSize, 1.0f, 2 , 2, 5000.0f);
	
    
    delete app;
	
	return 0;
}

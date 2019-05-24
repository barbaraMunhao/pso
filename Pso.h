


#ifndef __PSO__
#define __PSO__
#include "Particle.h"
namespace heuristic
{
class Pso
{
public:
    Pso(int swarmSize, int epochs, Knapsack *k, param *parameters):_sizeOfSwarm{swarmSize},_numIteracoes{epochs}
    {
         //Instancia o enxame
        _particles = new Particle*[_sizeOfSwarm];
        _parameters = parameters;
        for (int i = 0; i < _sizeOfSwarm; i++)
            _particles[i] = new Particle(k);

        //Instancia o vetor que conterá a melhor posição global
        _gBest = new int[k->getNumItems()];
    }
    void execute();
    int initParticles();
    void updateGBestPosition(int);
    char* print();
    void initialize();
    auto fitness() const
    {
        return _gBestFitness;
    }
    ~Pso()
    {
        for (int i = 0; i < _sizeOfSwarm; i++)
            delete _particles[i];    
        delete[] _particles;    
        delete[] _gBest;		
    }

    
private:
    Particle** _particles;
    int* _gBest;
    float _gBestFitness;
    int _numIteracoes;
	int _sizeOfSwarm;
    param * _parameters;

    
};


}// end namespace
#endif // __PSO__


#include "Pso.h"
//Método para construir a solução inicial
using namespace heuristic;
int
Pso::initParticles()
{
    int iBest = 0;
    
    for (int i = 0; i < _sizeOfSwarm; i++)
    {
        _particles[i]->setupParticle();
        
        if (_particles[i]->fitness() > _particles[iBest]->fitness())
            iBest = i;
    }
    
    return iBest;
}

void
Pso::updateGBestPosition(int index)
{
    for (int i = 0; i < _particles[index]->dimension(); i++)
        _gBest[i] = _particles[index]->pos(i);
    _gBestFitness = _particles[index]->fitness();
    
}
//Método que implementa o algoritmo PSO
void
Pso::execute()
{
    for (int i = 0; i < _numIteracoes; i++)
    {
        int bestIndex = 0;
        for (int part = 0; part < _sizeOfSwarm; part++)
        {
            if (_particles[part]->fitness()> _particles[bestIndex]->fitness())
                bestIndex = part;
            
            if (_particles[part]->fitness() > _particles[part]->bestFitness())
            {
                //Atualiza a melhor posição da partícula
                _particles[part]->updateBestPosition();
            }
        }
        
        //Verifica se a melhor partícula superou a melhor global até então
        if (_particles[bestIndex]->fitness() > _gBestFitness)
            updateGBestPosition(bestIndex);
        
        //Atualização das velocidades
        for (int part = 0; part < _sizeOfSwarm; part++)
        {
            _particles[part]->updateVelocity(_gBest);
            _particles[part]->updatePosition();
        }
        //TODO _ change w
    }
}
void
Pso::initialize()
{
    //Inicializa as partículas
    int iBest = initParticles();        
    _gBestFitness = _particles[iBest]->fitness();
    updateGBestPosition(iBest);
        
}
char *
Pso::print()
{
    //TODO
    return nullptr;
}
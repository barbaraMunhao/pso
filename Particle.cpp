#include "Particle.h"


void
Particle::setupParticle()//TODO
{
    srand(time(0));
    //Inicialização das posições _MKP
    //Inicialização das velocidades MKP

    for (int i = 0; i < _dimension; i++)
    {
        _pos[i] = rand()%2;
        _vel[i] = rand()%2;
    }
    computeFitness();
    
   
}

//Método para o cálculo do fitness com penalização para soluções inviáveis
void
Particle::computeFitness()
{
	//DEIXEI COMO SUGERIDO NO ARTIGO, TENTEM ALTERAR OS CÁLCULOS DA PENALIZAÇÃO  TODO
	
    float value, penalty;
    
    value = 0.0;
    
    for (int i = 0; i < _knapsack->numItems; i++)
        value += _pos[i] * _knapsack->values[i];
    
    penalty = 0.0;
    
    for (int i = 0; i < _knapsack->numResources; i++)
        penalty += posLin(i);
    
    _fitness = value - this->penalty()*penalty; // arrumar
}

int
Particle::posLin(int index)
{
    int spentResources;
    
    spentResources = 0;
    
    for (int i = 0; i < _knapsack->numItems; i++)
        spentResources += _knapsack->useResources[index][i] * _pos[i];
    
    spentResources -= _knapsack->capResources[index];
    
    if (spentResources < 0)//Não esgotou o recurso
        return 0;
    
    return spentResources;
}

void
Particle::updateBestPosition()
{
    for (int i = 0; i < _dimension; i++)
        _pBest[i] = _pos[i];
    
    _pBestFitness = _fitness;
}

void
Particle::updateVelocity(int* gBest)//TODO
{   
    //Atualização de velocidades    
    for(int d = 0; d < _dimension; d++)
    {
        _vel[d] = w()*_vel[d] + c1()*rand()*(_pBest[d]-_pos[d]) + c2()*rand()*(gBest[d]-_pos[d]);
    }
}

void
Particle::updatePosition()//TODO
{
    //Atualização das posições
     for(int d = 0; d < _dimension; d++)
    {
        if(sigmoid(_vel[d])<=(rand()%2))
            _pos[d] = abs(_pos[d] -1);        
    }
    //Atualiza o fitness equivalente à solução.
    computeFitness();
}

float
Particle::sigmoid(float vel)
{
    return ((float) 1.0 / (1.0 + exp(-1.0 * vel)));
}


Particle::~Particle()
{
    delete[] _pos;
    delete[] _vel;
    delete[] _pBest;
}

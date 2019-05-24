#include "Knapsack.h"
#ifndef __Particle__
#define __Particle__
#include <cstdlib>
#include <math.h>
#include <stdlib.h>
#include <sys/time.h>
#include <time.h>
//#define penaltyFactor 5000//Fator de penalização, testar valores
//#define omega 0.3 // fator de inércia 
//#define c1 2.0
//#define c2 2.0
struct param{
    float penalty; // panlidade função objetivo
    float w; // fator de inércia
    int c1, c2; //constantes - intesificação e diversificação

    param(int c1, int c2, float w, float pf):
    c1{c1},c2{c2},w{w},penalty{pf}
    {
        //do nothing
    }
};
class Particle
{
	private: 
		int _dimension;
		int* _pos; // vector[_dimension]
		float* _vel; // vector[_dimension]
		float _fitness;
		int* _pBest; // vector[_dimension]
		float _pBestFitness;    
        Knapsack* _knapsack;
        param * _parameters;
        int posLin(int);
		
	public:
		Particle(Knapsack* k)       
        {
	        _dimension = k->numItems;
            _knapsack = k;	        
	        //Aloca os vetores
	        _pos = new int[_dimension];
	        _vel = new float[_dimension];
	        _pBest = new int[_dimension];
	
	        _pBestFitness = 0.0;
        }
        void setupParticle();
        void computeFitness();
        void updateBestPosition();
        void updateVelocity(int*);
        void updatePosition();
        float sigmoid(float);
        ~Particle();
    
    auto dimension() const
    {
        return _dimension;
    }
    auto fitness() const
    {
        return _fitness;
    }
    auto pos(int i)const
    {
        return _pos[i];
    }
    auto bestFitness() const
    {
        return _pBestFitness;
    }
    int c1()const
    {
        return _parameters->c1;   
    }
    int c2()const{
        return _parameters->c2;   
    }
    float w()const{
        return _parameters->w;
    }
    float penalty()const{
        return _parameters->penalty;
    }    
};
#endif //__Particle__
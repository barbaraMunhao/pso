
#include "Pso.h"
#include <math.h>
#include <string.h>

#define EXECS 1

class Application
{
	private:
		Knapsack* k;
		FILE* fileIn;
		char fileOutName[50];
    
		float gap;
		
		
		
		float* vetGaps;
		float* vetTimes;
		double mediumGap;
		double mediumTime;
		double dpTimes;
		double dpGaps;
		double bestOverallSolValue;
		double bestOverallTime;
		double bestOverallGap;
		int numOpt;
		int numBetter;
		
       
       
		void writeBestResult(char*, double, int);
		void finalWrite(char*);
		
	public:
		Application(char*[], bool&);
		
		void run(int, int, float, int, int, float);
		
		~Application();
};

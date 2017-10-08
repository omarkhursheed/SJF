#include <iostream>
#include <cstdlib>
#include <vector>
using namespace std;
class process
{
	int arrivalTime;
	int CPUBursts;
	int processTime;
public:
	process(int arrival, int CPU)
	{
		arrivalTime = arrival;
		CPUBursts = CPU;
	}
};
int main(int argc, char const *argv[])
{

	int numberOfProcesses = -1;
	char affirm = 'y';
	vector<process> v;
	cout << "Enter number of processes";
	cin >> numberOfProcesses;
	if(numberOfProcesses <= 0)
	{
		cout << "Number of processes must be positive";
		return 0;
	}
	for(int i = 0; i < )
	while(affirm == 'y')
	{
		cout << "Enter arrival time" << endl;
		cin >> 
		cout << "Enter number of CPU bursts" << endl;
		
	}
	return 0;
}

void preemptiveSJF()
{
	return;
}

void nonPreemptiveSJF()
{
	return;
}
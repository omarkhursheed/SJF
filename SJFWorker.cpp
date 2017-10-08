#include <iostream>
#include <cstdlib>
#include <vector>
#include <string>
using namespace std;
class process
{
	int arrivalTime;
	int CPUBursts;
	string processName;
public:
	process(string pname, int arrival, int CPU)
	{
		arrivalTime = arrival;
		CPUBursts = CPU;
		processName = pname;
	}
};
int main(int argc, char const *argv[])
{

	int numberOfProcesses = -1;
	char affirm = 'y';
	vector<process> v;
	while(affirm == 'y')
	{

		string pname;
		int arr;
		int cpu;
		cout << "Enter process name" << endl;
		cin >> pname;
		cout << "Enter arrival time" << endl;
		cin >> arr;
		cout << "Enter number of CPU bursts" << endl;
		cin >> cpu;
		process p(pname, arr, cpu);
				
		cout << "Do you wish to enter another process?" << endl;
		cin >> affirm;
		v.push_back(p);
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
#include <iostream>
#include <cstdlib>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;
class process
{
public:

	int arrivalTime;
	int CPUBursts;
	string processName;
	process(string pname, int arrival, int CPU)
	{
		arrivalTime = arrival;
		CPUBursts = CPU;
		processName = pname;
	}
	int getArrivalTimes() const
	{
		return arrivalTime;
	}
	int getCPUBursts() const
	{
		return CPUBursts;	
	}
	string getProcessName() const
	{
		return processName;
	}
	bool operator <(process rhs)
	{ 
		if(arrivalTime == rhs.arrivalTime || rhs.arrivalTime < arrivalTime + CPUBursts){ return CPUBursts < rhs.CPUBursts; }return arrivalTime < rhs.arrivalTime;
	}
};
void preemptiveSJF(vector<process>);
void nonPreemptiveSJF(vector<process>);
int main(int argc, char const *argv[])
{

	int numberOfProcesses = -1;
	char affirm = 'y';
	int choice;
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
	cout << "Do you wish to use nonpreemptive SJF (1) or preemptive SJF (2)";
	cin >> choice;
	if (choice == 1)
	{
		nonPreemptiveSJF(v);
	}
	else if (choice == 2)
	{
		preemptiveSJF(v);
	}
	else
	{
		cout << "Erronous input" << endl;
		return 0;
	}

	return 0;
}

void preemptiveSJF(vector<process> v)
{
	vector <process>:: iterator it; 
	for(it = v.begin(); it != v.end(); it++)
	{
		return;
	}
	return;
}

void nonPreemptiveSJF(vector<process> v)
{
	vector <process>:: iterator it; 
	int arrTimes[v.size()];
	int i = 0;
	sort(v.begin(), v.end());
	
	//sort(v.begin(), v.end(), cmp);
	cout << endl;
	cout << "Process Name\tArrival Time\tCPU Bursts:" << endl;
	for(it = v.begin(); it != v.end(); it++)
	{
		cout << it->getProcessName() << '\t' << it->getArrivalTimes() << '\t' << it->getCPUBursts() << endl;
	}
	return;
}
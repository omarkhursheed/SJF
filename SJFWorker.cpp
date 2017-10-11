#include <iostream>
#include <cstdlib>
#include <vector>
#include <string>
#include <algorithm>
#include <iterator>
#include <fstream>
using namespace std;
class process
{
public:

	int arrivalTime;
	int CPUBursts;
	string processName;
	int processStartTime;
	int processEndTime;
	int processed;
	int currentProcessLength;
	int pseudoArrivalTime;
	int pseudoCPUBursts;
	process()
	{
	}
	process(string pname, int arrival, int CPU)
	{
		arrivalTime = arrival;
		CPUBursts = CPU;
		processName = pname;
		pseudoArrivalTime = arrival;
		pseudoCPUBursts = CPU;
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
	int getProcessStartTime()
	{
		return processStartTime;
	}
	int getProcessEndTime()
	{
		return processEndTime;
	}
	int setProcessStartTime(int a)
	{
		processStartTime  = a;
	}
	int setProcessEndTime(int b)
	{
		processEndTime = b;
	}
	bool operator <(process rhs)
	{ 
		//if((rhs.arrivalTime == arrivalTime || rhs.arrivalTime <= arrivalTime + CPUBursts)){ return CPUBursts < rhs.CPUBursts; }return arrivalTime < rhs.arrivalTime;
		
		if(rhs.arrivalTime == arrivalTime)
		{
			if(CPUBursts == rhs.CPUBursts)
			{
				return pseudoArrivalTime < rhs.pseudoArrivalTime;
			}
			return CPUBursts < rhs.CPUBursts;
		}

		return arrivalTime < rhs.arrivalTime;
	}
	int setProcessedFlag()
	{
		processed = 1;
	}
	int getProcessedFlag()
	{
		return processed;
	}
	int setCurrentProcessLength(int a)
	{
		currentProcessLength = a;
	}
	int getCurrentProcessLength()
	{
		return currentProcessLength; 
	}
	int decrementCurrentProcessLength()
	{
		currentProcessLength--;
	}
	int setCPUBursts(int a)
	{
		CPUBursts = a;
	}
	int decrementCPUBursts()
	{
		CPUBursts--;
	}
	int decrementArrivalTime()
	{
		arrivalTime--;
	}
	int getPseudoArrivalTime()
	{
		return pseudoArrivalTime;
	}
	int getPseudoCPUBursts()
	{
		return pseudoCPUBursts;
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
	vector <process> orderedProcesses;
	vector <process>:: iterator nextProcessIndex;
	vector <process>:: iterator it; 
	int totalCPUBursts = 0;

 	ofstream myfile;
  	myfile.open ("preemptive.txt", ios::out | ios::trunc);

	for (it = v.begin(); it != v.end(); it++)
	{
		totalCPUBursts+=it->getPseudoCPUBursts();
	}
	int size = v.size();
	int currentTime = 0;
	sort(v.begin(), v.end());
	nextProcessIndex = v.begin();
	nextProcessIndex->setProcessStartTime(nextProcessIndex->getArrivalTimes());
	nextProcessIndex->decrementCPUBursts();
	currentTime++;

	for(it = v.begin(); it != v.end(); it++)
		{
			if(it->getArrivalTimes()!=0)
			{
				it->decrementArrivalTime();
			}
		}
	if(nextProcessIndex->getCPUBursts()==0)
		{
			nextProcessIndex->setProcessEndTime(currentTime);
			orderedProcesses.push_back(*nextProcessIndex);
			v.erase(nextProcessIndex);
		}
	while(orderedProcesses.size() != size)
	{
		sort(v.begin(), v.end());
		nextProcessIndex = v.begin();
		if(nextProcessIndex->getCPUBursts() == nextProcessIndex->getPseudoCPUBursts())
		{
			if(currentTime < nextProcessIndex->getPseudoArrivalTime())
			{
				currentTime = nextProcessIndex->getPseudoArrivalTime();
			}
			nextProcessIndex->setProcessStartTime(currentTime);
		}
		nextProcessIndex->decrementCPUBursts();
		currentTime++;
		//cout << nextProcessIndex->getCPUBursts() << "abc" << endl;
		//cout << nextProcessIndex->getPseudoCPUBursts() <<"def" << endl;

		
		for(it = v.begin(); it != v.end(); it++)
		{
			if(it->getArrivalTimes()!=0)
			{
				it->decrementArrivalTime();
			}
		}	
		if(nextProcessIndex->getCPUBursts()==0)
		{
			nextProcessIndex->setProcessEndTime(currentTime);
			orderedProcesses.push_back(*nextProcessIndex);
			v.erase(nextProcessIndex);
		}

	}
	cout << "Process Name" << '\t' << "Turnaround Time" << '\t' << "Waiting Time" << endl;
	float turnaroundAvg = 0;
	float waitingAvg = 0;
	for(it = orderedProcesses.begin(); it != orderedProcesses.end(); it++)
	{
		cout << it->getProcessName() << '\t' << '\t' << it->getProcessEndTime()-it->getPseudoArrivalTime() << '\t' << '\t' << 
		it->getProcessEndTime()-it->getPseudoArrivalTime()-it->getPseudoCPUBursts() << endl;
		turnaroundAvg +=  it->getProcessEndTime()-it->getPseudoArrivalTime();
		waitingAvg += it->getProcessEndTime()-it->getPseudoArrivalTime()-it->getPseudoCPUBursts();
	}
	cout << endl << "Average Waiting Time: " << float(waitingAvg)/float(size)<<endl;
	
	cout << endl << "Average Turnaround Time: " << float(turnaroundAvg)/float(size)<<endl;
	return;
}

void nonPreemptiveSJF(vector<process> v)
{
	vector <process>:: iterator it; 
	vector <process> orderedProcesses;
	vector <process> currentAvailableProcesses;
	//ofstream myfile.open("answers.txt");
	ofstream myfile;
  	myfile.open ("nonpreemptive.txt", ios::out | ios::trunc);

	vector <process>:: iterator nextProcessIndex = v.begin();
	/*nextProcessIndex->setProcessStartTime(nextProcessIndex->getArrivalTimes());
	cout << nextProcessIndex->getProcessName() << '\t' << nextProcessIndex->getProcessStartTime() << endl;
	int currentTime = nextProcessIndex->getProcessStartTime();*/
	int currentTime = 0;
	sort(v.begin(), v.end());
	
	int size = v.size();

	nextProcessIndex = v.begin();
	
	currentTime = nextProcessIndex->getArrivalTimes();
	nextProcessIndex->setProcessStartTime(currentTime);
	nextProcessIndex->setProcessEndTime(currentTime+nextProcessIndex->getCPUBursts());
	currentTime += nextProcessIndex->getCPUBursts();
	orderedProcesses.push_back(*nextProcessIndex);
	for(it = v.begin(); it != v.end(); it++)
	{
		int count = 0;
		while(it->getArrivalTimes()!=0 && count !=nextProcessIndex->getCPUBursts())
		{
			it->decrementArrivalTime();
			count++;
		}
	}
	v.erase(nextProcessIndex);

	while(orderedProcesses.size() != size)
	{	
		sort(v.begin(), v.end());
		nextProcessIndex = v.begin();
		if(currentTime < nextProcessIndex->getPseudoArrivalTime())
		{
			currentTime = nextProcessIndex->getPseudoArrivalTime();	
		}
		nextProcessIndex->setProcessStartTime(currentTime);
		nextProcessIndex->setProcessEndTime(currentTime+nextProcessIndex->getCPUBursts());
		currentTime+=nextProcessIndex->getCPUBursts();	
		orderedProcesses.push_back(*nextProcessIndex);
		
		for(it = v.begin(); it != v.end(); it++)
		{
			int count = 0;
			while(it->getArrivalTimes()!=0 && count != nextProcessIndex->getCPUBursts())
			{
				it->decrementArrivalTime();
				count++;
			}
		}
		v.erase(nextProcessIndex);	
	}
	cout << "Process Name" << '\t' << "Turnaround Time" << '\t' << "Waiting Time" << endl;
	float turnaroundAvg = 0;
	float waitingAvg = 0;
	for(it = orderedProcesses.begin(); it != orderedProcesses.end(); it++)
	{
		cout << it->getProcessName() << '\t' << '\t' << it->getProcessEndTime()-it->getPseudoArrivalTime() << '\t' << '\t' << 
		it->getProcessEndTime()-it->getPseudoArrivalTime()-it->getPseudoCPUBursts() << endl;
		turnaroundAvg +=  it->getProcessEndTime()-it->getPseudoArrivalTime();
		waitingAvg += it->getProcessEndTime()-it->getPseudoArrivalTime()-it->getPseudoCPUBursts();
		myfile << it->getProcessName() << ',' << it->getProcessStartTime() << ',' << it->getProcessEndTime() << endl;
	}
	cout << endl << "Average Waiting Time: " << float(waitingAvg)/float(size)<<endl;
	
	cout << endl << "Average Turnaround Time: " << float(turnaroundAvg)/float(size)<<endl;
	return;
}
#include <iostream>
#include <vector>
using namespace std;

int noResources, noProcesses;
vector<int> avResources;

void readData(){
    cout << "Please enter no of resources : "; 
    cin >> noResources; 
    for (int i = 0; i < noResources; i++)
    {
        int temp;
        cout << "Please enter available resources for resource " << i << " : ";
        cin >> temp;
        avResources.push_back(temp);
    }
      
    cout << "Please enter no of processes : "; 
    cin >> noResources;   
}


int main(){
    readData();
}
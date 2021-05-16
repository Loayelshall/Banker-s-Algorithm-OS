#include <iostream>
#include <vector>
using namespace std;


// Global Vars
int noResources, noProcesses;
vector<int> avResources;
vector<vector<int>> aloRes;
vector<vector<int>> maxRes;
vector<vector<int>> need;
vector<int> finish;
vector<int> safeState;

// -----------------------------------SAFETY ALGORITHM---------------------------------------------------------------
// Helper functions
void readData(){
    cout << "Please enter no of resources : "; 
    cin >> noResources;
    for (int i = 0; i < noResources; i++)
    {
        int temp;
        cout << "Enter available instances of resource " << i << " : ";
        cin >> temp;
        avResources.push_back(temp);
    }
    
      
    cout << "Please enter no of processes : "; 
    cin >> noProcesses;
    for (int i = 0; i < noProcesses; i++)
    {
        finish.push_back(0);
        int temp;
        vector<int> tempAloVec;
        vector<int> tempMaxVec;
        for (int j = 0; j < noResources; j++)
        {
            cout << "Enter allocated instances of " << j << " for process " << i  << " : ";
            cin >> temp;
            tempAloVec.push_back(temp);

            cout << "Enter max instances of " << j << " for process " << i  << " : ";
            cin >> temp;
            tempMaxVec.push_back(temp);
        }
        aloRes.push_back(tempAloVec);
        maxRes.push_back(tempMaxVec);
    }
       
}

void clcNeed(){
    for (int i = 0; i < noProcesses; i++)
    {
        vector<int> temp;
        for (int j = 0; j < noResources; j++)
        {
            int tempV = maxRes[i][j] - aloRes[i][j];
            temp.push_back(tempV);
        }
        need.push_back(temp);
    }
    
}

void clcFinish(){

    for (int i = 0; i < noProcesses; i++)
    {
        
        for (int j = 0; j < noProcesses; j++)
        {
            int currentSum = 0;
            int isSmall = 1;
            for (int x = 0; x < noResources; x++)
            {
                if(need[j][x] > avResources[x]){
                    isSmall = 0;
                }
            }
            if(isSmall == 1 && finish[j] == 0){
                finish[j] = 1;
                safeState.push_back(j);
                for (int x = 0; x < noResources; x++)
                {
                    avResources[x] += aloRes[j][x];
                }
                
            }
        }
    }
    
    
    
}

int isSafe(){
    int safe = 1;
    for (int i = 0; i < finish.size(); i++)
    {
        if(finish[i] == 0){
            safe = 0;
        }     
    }
    return safe;
}

// -----------------------------------END SAFETY ALGORITHM---------------------------------------------------------------

int main(){
    readData();
    clcNeed();
    clcFinish();
    int safe = isSafe();
    cout << "IS SAFE? " << safe << endl;
    for (int i = 0; i < safeState.size(); i++)
    {
        cout << safeState[i] << endl;
    }
    
}
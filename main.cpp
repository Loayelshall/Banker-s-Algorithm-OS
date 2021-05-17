#include <iostream>
#include <vector>
using namespace std;


// Global Vars
int noResources, noProcesses, algType, reqProcess;
vector<int> avResources;
vector<vector<int>> aloRes;
vector<vector<int>> maxRes;
vector<vector<int>> need;
vector<int> finish;
vector<int> safeState;
vector<int> reqAlg;


void readAlgType(){
    int isRight = 1;
    do
    {
        cout << "Enter 1 for Safety algorithm and 2 for request algorithm : ";
        cin >> algType;
        if(algType == 2){
            cout << "Enter requested process number starting from 0 : ";
            cin >> reqProcess;
            cout << "Enter requested resources instances separated by spaces : ";
            int temp;
            for (int i = 0; i < noResources; i++)
            {
                cin >> temp;
                reqAlg.push_back(temp);
            }
            isRight = 0;
        } else if(algType == 1){ 
            isRight = 0;
        } else if(algType != 1){
            cout << "Please enter 1 or 2.";
        }    
    } while (isRight);
    
}


// -----------------------------------Request ALGORITHM------------------------------------------------------------------
void clcReq(){
    int isLess = 1;
    for (int i = 0; i < noResources; i++)
    {
        if(reqAlg[i] > need[reqProcess][i] || reqAlg[i] > avResources[i]){
            isLess = 0;
        }
    }
    if(isLess == 1){
        for (int i = 0; i < noResources; i++)
        {
            aloRes[reqProcess][i] += reqAlg[i];
            need[reqProcess][i] -= reqAlg[i];
            avResources[i] -= reqAlg[i];
        }
    }
    
}



// -------------------------------------END REQUEST----------------------------------------------------------------------


// -----------------------------------SAFETY ALGORITHM-------------------------------------------------------------------
// Helper functions
void readData(){
    cout << "Please enter no of resources : "; 
    cin >> noResources;
    cout << "Enter available instances of resources separated by spaces : ";
    for (int i = 0; i < noResources; i++)
    {
        int temp;
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
        cout << "Enter allocated instances of process " << i << " separated by spaces : " ; 
        for (int j = 0; j < noResources; j++)
        {
            cin >> temp;
            tempAloVec.push_back(temp);            
        }
        cout << "Enter maximum needed instances of process " << i << " separated by spaces : " ; 
        for (int j = 0; j < noResources; j++)
        {
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
    readAlgType();
    clcNeed();
    if(algType == 2){
        clcReq();
    }
    clcFinish();
    int safe = isSafe();
    cout << "IS SAFE? " << safe << endl;
    for (int i = 0; i < safeState.size(); i++)
    {
        cout << safeState[i] << endl;
    }


    
}
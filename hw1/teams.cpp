#include <iostream>
#include <iomanip>
#include <string>
#include <fstream>

using namespace std;

// *You* are not allowed to use global variables
//  but for just the output portion *we* will. ;>
int combo = 1;

// @brief Prints a single combination of teams
//
// @param[in] team1 Array containing the names of team 1
// @param[in] team2 Array containing the names of team 2
// @param[in] len Size of each array
void printSolution(const string* team1, 
		   const string* team2,
		   int len)
{
  cout << "\nCombination " << combo++ << endl;
  cout << "T1: ";
  for(int i=0; i < len; i++){
    cout << team1[i] << " ";
  }
  cout << endl;
  cout << "T2: ";
  for(int i=0; i < len; i++){
    cout << team2[i] << " ";
  }
  cout << endl;
}

// You may add additional functions here

void athelper( string*& names, string* team1, int num, int index, int start)
{
	if(index == num/2)
	{	
		string* team2 = new string[num];
		int k = 0;

		for(int i = 0; i < num; i ++)
		{
			bool already = false;
			for(int j = 0; j < num/2; j++)
			{
				if(names[i] == team1[j]) already = true;
			}
			if(!already) {
				team2[k] = names[i];
				k++;
			}
		}

		k = 0;
		printSolution(team1, team2, num/2);
		delete[] team2;
	}
	else if (index < num/2)
	{
		for( int i = start; i < num ; i++)
		{
			team1[index] = names[i];
			athelper(names, team1, num, index + 1, i + 1);
		}
	}
}

void allteams( string*& names, int num)
{

	string* team1 = new string[num/2];

	athelper(names, team1, num, 0,0);
	delete[] team1;

}

int main(int argc, char* argv[])
{
  unsigned int num = 0;
  if(argc < 2){
    cerr << "Please provide a file of names" << endl;
    return 1;
  }
  // Complete the rest of main
  ifstream ifile(argv[1]);
  if(ifile.fail()){
    cerr << "Error" << endl;
    return 1;
  }

  ifile >> num;
  if(ifile.fail()){
  	cerr << "Error" << endl;
  	return 1;
  }

  string* names = new string[num];
  for(unsigned int i = 0; i < num; i++)
  {
  	ifile >> names[i];

  	 if(ifile.fail()){
  		cout << "Error" << endl;
  		delete[] names;
  		return 1;
  	}
  }
  ifile.close();

  allteams(names, num);

  delete[] names;
  return 0;
}

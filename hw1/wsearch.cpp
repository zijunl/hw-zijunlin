#include <iostream>
#include <iomanip>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>

using namespace std;

struct Location
{
  Location()
  {
    row = -1;
    col = -1;
  }
  Location(int r, int c)
  {
    row = r;
    col = c;
  }
  int row;
  int col;
};

// @param[in] instream - Input (file) stream for the input file.  Opened in main()
// @param[out] grid Blank vector of vectors.  Should be updated with the
//                  contents of the grid from the input file
// @return true if successful, false otherwise (see HW writeup for details
//         about possible error cases to be checked)
bool readGrid(istream& instream, vector<vector<char> >& grid )
{
  /** You complete **/
	string myline;
	char c;
	vector<char> v;
	if( !getline(instream, myline)) return false;
	do
	{
		stringstream ss(myline);
		while (ss >> c)
		{
			v.push_back(c);
		}
		grid.push_back(v);
		v.clear();
	}while( getline(instream, myline));

	unsigned int temp = grid[0].size();
	for(unsigned int i = 0; i < grid.size(); i++)
	{
		if(temp != grid[i].size()) return false;
		temp = grid[i].size();
	}

	return true;
}

// prototype - will be implemented below
bool findWordHelper(
   const vector<vector<char> >& grid, 
   Location currLoc,
   Location delta,
   string word,
   unsigned int currWordIndex);

// Do not change
void printSolution(const string& targetWord, const Location& start, string direction)
{
  cout << targetWord << " starts at (row,col) = (" << start.row << "," << start.col
       << ") and proceeds " << direction << "." << endl;
}

// Do not change
void printNoSolution(const string& targetWord)
{
  cout << targetWord << " does NOT occur." << endl;
}

// Complete - you should not need to change this.
void findWord(const vector<vector<char> >& grid, 
	      const string& targetWord)
{
  bool found = false;
  if(targetWord.size() < 2){
    cout << "Need a word of length 2 or more." << endl;
    return;
  }
  for(unsigned int r=0; r < grid.size(); r++){
    for(unsigned int c=0; c < grid[r].size(); c++){
      if(grid[r][c] == targetWord[0]){
		Location loc(r,c);
		if( findWordHelper(grid, Location(r-1,c), Location(-1, 0), targetWord, 1) ){
		  printSolution(targetWord, loc, "up");
		  found = true;
		}
		if( findWordHelper(grid, Location(r,c-1), Location(0,-1), targetWord, 1) ){
		  printSolution(targetWord, loc, "left");
		  found = true;
		}
		if( findWordHelper(grid, Location(r+1,c), Location(1, 0), targetWord, 1) ){
		  printSolution(targetWord, loc, "down");
		  found = true;
		}
		if( findWordHelper(grid, Location(r,c+1), Location(0,1), targetWord, 1) ){
		  printSolution(targetWord, loc, "right");
		  found = true;
		}
      }      
    }
  }
  if(!found){
    printNoSolution(targetWord);
  }
}

/**
 * @param[in] grid The 2D vector containing the entire search contents
 * @param[in] currLoc Current row and column location to try to match 
 *                    with the next letter
 * @param[in] delta   Indicates direction to move for the next search
 *                    by containing the *change* in row, col values
 *                    (i.e. 1,0 = down since adding 1 will move down 1 row)
 * @param[in] word The word for which you are searching
 * @param[in] currWordIndex The index to word indicating which letter must
 *                          be matched by this call
 */
bool findWordHelper(const vector<vector<char> >& grid, 
		 Location currLoc,
		 Location delta,
		 string word,
		 unsigned int currWordIndex)
{
  /*** You complete ***/
	if( currLoc.row >= 0 && currLoc.col >= 0 
		&& currLoc.row< (signed) grid.size() && currLoc.col< (signed) grid[0].size())
	{
		if( grid[currLoc.row][currLoc.col] == word[currWordIndex])
		{
			if(currWordIndex + 1 == word.length())
			{
				return true;
			}
			else
			{
				return findWordHelper(grid, Location((currLoc.row + delta.row),(currLoc.col + delta.col)), delta, word, currWordIndex+1);
			}
		}
		else return false;
	}
	else return false;	
}



int main(int argc, char* argv[])
{
  if(argc < 3){
    cerr << "Please provide a grid filename and targetWord" << endl;
    return 1;
  }
  ifstream ifile(argv[1]);
  string targetWord(argv[2]);
  if(ifile.fail()){
    cerr << "Unable to open input grid file" << endl;
    return 1;
  }

  vector<vector<char> > mygrid;
  if( ! readGrid(ifile, mygrid) ){
    cerr << "Error reading grid" << endl;
    ifile.close();
    return 1;
  }

  /*for(unsigned int i = 0; i < mygrid.size(); i++)
  {
	for (unsigned int j = 0; j < mygrid[i].size(); j++)
	{
		cout <<  mygrid[i][j] << " ";
	}
	cout << endl;
  }
*/
 findWord(mygrid, targetWord);

  return 0;
}

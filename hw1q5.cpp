#include <iostream>
#include <fstream>
#include <cstring> 

using namespace std;

bool helper(ifstream &input)
{
	string prev;

	if (!(input>>prev)) return true;
	//input >> prev;

	helper(input);
	cout<<prev<<endl;
	return true;
}

//do not change the main function.
int main(int argc, char* argv[])
{
  int trash;
  if(argc < 2){
    cerr << "Please enter a filename" << endl;
    return 1;
  }
  ifstream inFile;
  inFile.open(argv[1]);
  if(!inFile)
  {
  	cerr<<"Unable to open file"<<endl;
    return 1;
  } 
  inFile>>trash;
  helper(inFile);
  inFile.close();
  return 0;
}

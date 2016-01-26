#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;

int main(int argc, char* argv[])
{
  if(argc < 3){
    cerr << "Please provide an input and output file." << endl;
    return 1;
  }
  ifstream input;
  ofstream output;
  input.open(argv[1]);
  output.open(argv[2]);

  int floors;
  int *floorsizes;
  string ***trojans;
  string curr;

  input >> floors;
  trojans = new string**[floors];

  //you will need to keep track of how many people are on each floor.
  floorsizes = new int[floors];
  int** possessions = new int*[floors];

  for (int i = 0; i < floors; i++) {
	  floorsizes[i] = 0;
	  trojans[i] = NULL;
	  possessions[i] = 0;
  }
  while(getline(input, curr)) {
	  stringstream ss;
	  ss << curr;
	  ss >> curr;
	  if (curr == "MOVEIN") {
	  	cout<<"MOVEIN"<<endl;
		  int i,k;
		  ss >> i;
		  ss >> k;
		  if (ss.fail()) {
			  output << "Error - incorrect command" << endl;
		  }
		  else {
		  	if(i<floors&&i>=0){
		  		if(trojans[i]!=NULL){
		  			output<<"Error - floor has residents"<<endl;
		  		}
		  		else{
		  			possessions[i] = new int[k];
		  			trojans[i] = new string*[k];
		  			floorsizes[i] = k;
		  			for (int m = 0; m < k; m++) {
		  				trojans[i][m] = NULL;
		  				possessions[i][m] = 0;
  					}
		  		}
		  	}
		  	else{
		  		output<<"Error - floor not found"<<endl;
		  	}
		  }
	  }
	  else if (curr == "MOVEOUT") {
	  	cout<<"MOVEOUT"<<endl;
	  	int i,j,x=0;
		  ss >> i;
		  j=floorsizes[i];
		  if (ss.fail()) {
			  output << "Error - incorrect command" << endl;
		  }
		  else{
		  	  if(i<0||i>=floors){
		  	  	output<<"Error - floor not found"<<endl;
		  	  	continue;
		  	  }
		  	  while(x<j){
		  	  	delete [] trojans[i][x];
		  	  	x++;
		  	  }
		  	  delete [] trojans[i];
		  	  delete [] possessions[i];
		  	  possessions[i] = 0;
		  	  trojans[i] = NULL;
		  	  floorsizes[i] = 0;
		  }
	  }
	  else if (curr == "OBTAIN") {
	  	cout<<"OBTAIN"<<endl;
	  	int i,j,k,x=0;
	  	string possession;
		  ss >> i;
		  ss >> j;
		  ss >> k;
		  if (ss.fail()) {
			  output << "Error - incorrect command" << endl;
		  }
		  else{
		  		if(i>=floors){
		  			output<<"Error - floor not found"<<endl;
		  			continue;
		  		}
		  		else if(!(j<floorsizes[i])){
		  			output<<"Error - student not found"<<endl;
		  			continue;
		  		}
		  	  possessions[i][j] = k;
		  	  trojans[i][j] = new string[k];
		  	  while(x<k){
		  	  	ss>>possession;
		  	  	trojans[i][j][x] = possession;
		  	  cout<<trojans[i][j][x]<<endl;
		  	  	x++;
		  	  }
		  }
	  }
	  else if (curr == "OUTPUT") {
	  	cout<<"OUTPUT"<<endl;
	  	int i,j;
		  ss >> i;
		  ss >> j;
		  if (ss.fail()) {
			  output << "Error - incorrect command" << endl;
		  }
		  else {
		  	if(i>=floors||i<0){
		  		output << "Not a valid floor"<<endl;
		  	}
		  	else{
		  		if(j>=floorsizes[i]||j<0){
		  			output<<"No student "<<j<<" on floor "<<i<<endl;
		  		}
		  		else{
		  			for(int m = 0; m<possessions[i][j]; m++){
		  				output<<trojans[i][j][m]<<endl;
		  			}
		  		}
		  	}
		  }
	  }
	  else if(curr==""){
	  	continue;
	  }
	  else {
	  	cout<<curr<<endl;
	  	output << "Error - not a command" << endl;
	  }
  }
  int x = 0;
  int y;
  while(x<floors){
  	y = 0;
  	while(y<floorsizes[x]){
  		delete [] trojans[x][y];
  		y++;
  	}
  	delete [] trojans[x];
  	if(possessions[x]!=0){
  		delete [] possessions[x];
  	}
  	x++;
  }
  delete [] possessions;
  delete [] trojans;
  delete [] floorsizes;
  input.close();
  output.close();
  return 0;
}

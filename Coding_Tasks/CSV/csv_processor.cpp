/* 
 * Author : Aditya Mohan 
 * Date   : 19-06-2017
 * Info	  : This code will take a csv file as input from the command line and interpolate on all the 0 values by taking the mean of the 8  
 *          spatial neighbors of the element, and write it to the CSV file
*/	

#include <fstream>
#include <iostream>
#include <stdlib.h>
#include <vector>
#include <string.h>

#define DEBUG 			//Remove this line to disable printing the output
#define BUFSZ 65535

using namespace std;

int main(int argc, char **argv) {

	char *line = new char [BUFSZ];
	vector< vector <int> > matrix;

	ifstream inputFile( argv[1] ) ;

	while( !inputFile.eof() ) {

		inputFile.getline(line, BUFSZ, '\n');
		
		if (strlen(line) <= 1) continue;

		vector<int> temp;

		temp.push_back(0); //Add left boundary
		
		char *thing = strtok(line, " ,");
		
		while (thing != NULL) {

			temp.push_back(atoi(thing));
			thing = strtok(NULL, " ,");
		}
		
		temp.push_back(0); //Add right boundary

		matrix.push_back(temp);
	}

	inputFile.close();

	int rowLen = matrix[0].size();
	
	vector<int> temp;
	
	for(int i = 0; i < rowLen; i++) {
		
		temp.push_back(0);
	}

	//Add upper and lower boundaries
	
	matrix.push_back(temp); 
	matrix.insert(matrix.begin(), temp);

	int colLen = matrix.size();

	ofstream outputFile(argv[2]);

	int i = 0;
	
	for (auto& row : matrix) {
		
		int j = 0;
 		
 		for (auto& element : row) {

			if (i != 0 && j != 0 && i != (colLen-1) && j != (rowLen-1)) {		//Ignore boundary
				
				if (element == 0) {

					int sum = 0;
					int count = 0;

					//Find average
					for (int h = -1; h <= 1; h++) {

						for (int k = -1; k <= 1; k++) {

							sum += matrix[i + h][j + k];
							count += (matrix[i + h][j + k] != 0) ? 1 : 0;
						}
					}
					
					element = sum / count; 									   //Count is assured to be non-zero and so no check required 
				}

				//Write element to output

				if (j != (rowLen-2)) {

					outputFile << element << ',';
				}
				else {

					outputFile << element << '\n';
				}
				
			}
			
			j++;
		}
		
		i++;
	}
	
	outputFile.close();

#ifdef DEBUG

	for (auto row : matrix) {

		for (auto element : row) {

			cout << element << " ";
		}
		
		cout << endl;
	}
	
#endif
	
	return 0;
}

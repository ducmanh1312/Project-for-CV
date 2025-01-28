#include<bits/stdc++.h>
using namespace std;

/// @brief 
/// @return 
/// @note 


// Returns vector of Pre Processed perfect cubes
vector<string> preProcess(long long int n)
{
	vector<string> listCube;
	for (int i = 1; i * i * i <= n; i++) {
		long long int iThCube = i * i * i;

		string cubeString = to_string(iThCube);
		listCube.push_back(cubeString);
	}
	return listCube;
}

/* Utility function for findLargestCube(). 
Returns the Largest cube number that can be formed */
string findLargestCubeUtil(string num, vector<string> preProcessedCubes)
{
	reverse(preProcessedCubes.begin(), preProcessedCubes.end());

	int totalCubes = preProcessedCubes.size();

	for (int i = 0; i < totalCubes; i++) {
		string currCube = preProcessedCubes[i];

		int digitsInCube = currCube.length();
		int index = 0;
		int digitsInNumber = num.length();
		for (int j = 0; j < digitsInNumber; j++) {

			if (num[j] == currCube[index]) 
				index++;
			
			if (digitsInCube == index)				 
				return currCube;		 
		}
	}

	return "-1";
}

// wrapper for findLargestCubeUtil()
void findLargestCube(long long int n)
{
	// pre process perfect cubes
	vector<string> preProcessedCubes = preProcess(n);

	// convert number n to string
	string num = to_string(n);

	string ans = findLargestCubeUtil(num, preProcessedCubes);

	cout << ans << endl;
}



int main(){
	//

	//
	int test;
	cin >> test;
	while(test--)
	{
        int N;
		cin >> N;
		findLargestCube(N);
		
	}

}
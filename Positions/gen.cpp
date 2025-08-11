#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>

#define DIM 9

bool fill(std::vector<int>& positions, std::vector<int> pieces, int c_index, int& count){
	if(c_index >= DIM){
		
		// Verifications des positions
		for(int i=0; i<(int)pieces.size(); i++){
			int c = std::count(positions.begin(), positions.end(), pieces[i]);
			if(pieces[i] == 0 && c != 3) return false;
			if(c > 3) return false;
		}
		
		// Affichage
		for(int i=0; i<DIM; i++) std::cout << positions[i] << " ";
		std::cout << std::endl;
		
		count++;
		return true;
	}
	
	for(int i = 0; i < (int)pieces.size(); i++){
		positions[c_index] = pieces[i];
		fill(positions, pieces, c_index+1, count);
	}

	return true;
}

int main(){
	int count = 0;
	std::vector<int> pieces {0,-1,1,-2,2};
	// Index de piece à parcourir
	int c_index = 0;
	
	std::vector<int> positions(9);
	
	// Fonction récursive pour remplir petit à petit les positions
	fill(positions, pieces, c_index, count);
	std::cout << count;
	
	return 0;
}



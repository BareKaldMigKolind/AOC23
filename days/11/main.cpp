#include "../../lib/file.hpp"
#include "../../lib/helper.hpp"

// =================== FILE READING ======================== //
File myfile("input.txt", "test.txt");
std::vector<std::string> lines = myfile.file_to_vector<std::string>(false);
int numberOfLines = lines.size();
// ======================================================== //

int partAFactor = 1;
int partBFactor = 1000000;

std::vector<int> findEmptySpace(std::vector<std::string>& lines, bool lookForRows){
    std::vector<int> emptyVector;
    int iStop = (lookForRows) ? lines.size() : lines[0].length();
    int jStop = (lookForRows) ? lines[0].length() : lines.size();
    for(int i = 0; i < iStop; i++){
        bool empty = true;
        for(int j = 0; j < jStop; j++){
            if(lookForRows && lines[i][j] != '.'){
                empty = false;
                break;
            } else if(!lookForRows && lines[j][i] != '.'){
                empty = false;
                break;
            }
        }
        if(empty) emptyVector.push_back(i);
    }
    return emptyVector;
}

std::vector<std::pair<int,int>> getGalaxies(std::vector<std::string>& lines){
    std::vector<std::pair<int,int>> galaxies;
    for(int i = 0; i < lines.size(); i++){
        for(int j = 0; j < lines[0].length(); j++){
            if(lines[i][j] == '#'){
                galaxies.push_back(std::make_pair(j,i));                
            }
        }
    }
    return galaxies;
}

int64_t getShortestDist(std::pair<int, int>& gala1, std::pair<int, int>& gala2, std::pair<int, int>& emptySpacePair, bool partA){
    int factor = (partA) ? partAFactor : partBFactor - 1;

    int64_t xDist = std::abs(gala1.first - gala2.first) + emptySpacePair.first * factor;
    int64_t yDist = std::abs(gala1.second - gala2.second) + emptySpacePair.second * factor;

    return xDist + yDist;
}

std::pair<int, int> getEmptyRowsBetweenGalaxies(std::pair<int,int>& gala1, std::pair<int,int>& gala2, std::vector<int>& emptyRows, std::vector<int>& emptyCols){
    int emptyRowCounter = 0;
    int emptyColCounter = 0;

    int colIndexStart = std::min(gala1.first, gala2.first);
    int colIndexEnd = std::max(gala1.first, gala2.first);

    int rowIndexStart = std::min(gala1.second, gala2.second);
    int rowIndexEnd = std::max(gala1.second, gala2.second);

    for(auto column : emptyCols){
        if(column > colIndexStart && column < colIndexEnd){
            emptyColCounter++;
        }
    }
    for(auto row : emptyRows){
        if(row > rowIndexStart && row < rowIndexEnd){
            emptyRowCounter++;
        }
    } 
    return std::make_pair(emptyRowCounter, emptyColCounter); 
}

int solution1(){
    std::vector<int> emptyRows = findEmptySpace(lines, true);
    std::vector<int> emptyCols = findEmptySpace(lines, false);

    std::vector<std::pair<int,int>> galaxies = getGalaxies(lines);

    int sum = 0;
    for(int i = 0; i < galaxies.size(); i++){
        for(int j = i; j < galaxies.size() - 1; j++){
           std::pair<int, int> emptySpacePair = getEmptyRowsBetweenGalaxies(galaxies[i], galaxies[j+1], emptyRows, emptyCols);
            sum += getShortestDist(galaxies[i], galaxies[j + 1], emptySpacePair, true);
        }
    }

    return sum;
}


int64_t solution2(){
    std::vector<int> emptyRows = findEmptySpace(lines, true);
    std::vector<int> emptyCols = findEmptySpace(lines, false);

    std::vector<std::pair<int,int>> galaxies = getGalaxies(lines);

    int64_t sum = 0;
    for(int i = 0; i < galaxies.size(); i++){
        for(int j = i; j < galaxies.size() - 1; j++){
            std::pair<int, int> emptySpacePair = getEmptyRowsBetweenGalaxies(galaxies[i], galaxies[j+1], emptyRows, emptyCols);
            sum += getShortestDist(galaxies[i], galaxies[j + 1], emptySpacePair, false);
        }
    }
    return sum;
}

int main(){

    std::cout << "Solution for part a: " << solution1() << std::endl;
    std::cout << "Solution for part b: " << solution2() << std::endl;

    return 0;
}
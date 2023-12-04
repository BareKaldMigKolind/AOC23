#include "../../lib/file.hpp"
#include "../../lib/helper.hpp"

// =================== FILE READING ======================== //
File myfile("input.txt", "test.txt");
std::vector<std::string> lines = myfile.file_to_vector<std::string>(false);
int numberOfLines = lines.size();
// ======================================================== //

bool isSymbol(char c){
    if(!isdigit(c) && c != '.'){
      return true;
    }
    return false;
}

bool isGear(char c){
    if(c == '*'){
      return true;
    }
    return false;
}

int getStartIndex(std::vector<std::string>& lines, int line, int index){
    int startIndex;
    while(isdigit(lines[line][index])){
        startIndex = index;
        index--;
    }
    return startIndex;
}

int checkForInts(std::vector<std::string>& lines, int line, int index){

    int intValue = 0;

    if(!isdigit(lines[line][index])){
        return 0;
    }

    int startIndex = getStartIndex(lines, line, index);
    
    for (int i = startIndex; i < startIndex + 3; i++){
        if(!isdigit(lines[line][i])){
            break;
        }
        intValue = intValue*10 + int(lines[line][i] - 48);
        lines[line][i] = '.';
    }

    return intValue;
}

int getAdjacentSum(std::vector<std::string>& lines, int line, int index){
    int sum = 0;
  
    // Line above left
    if(isdigit(lines[line-1][index-1])){
        sum += checkForInts(lines, line - 1, index - 1);
    }

    // Line above right
    if(isdigit(lines[line-1][index+1])){
        sum += checkForInts(lines, line - 1, index + 1);
    }

    // To the left
    if(isdigit(lines[line][index-1])){
        sum += checkForInts(lines, line, index - 1);
    }

    // To the right
    if(isdigit(lines[line][index+1])){
        sum += checkForInts(lines, line, index + 1);
    }

    // Line below left
    if(isdigit(lines[line+1][index-1])){
        sum += checkForInts(lines, line + 1, index - 1);
    }

    // Line below right
    if(isdigit(lines[line+1][index+1])){
        sum += checkForInts(lines, line + 1, index + 1);
    }
  
    return sum;
}

int getAdjacentMul(std::vector<std::string>& lines, int line, int index){
    int partsCount = 0;
    int mulProduct = 1;

    int charIndex = index;
  
    // Line above left
    if(isdigit(lines[line-1][charIndex-1])){
        if(partsCount == 2){
            return 0;
        }
        mulProduct *= checkForInts(lines, line - 1, charIndex - 1);
        partsCount++;
    }

    // Line above right
    if(isdigit(lines[line-1][charIndex+1])){
        if(partsCount == 2){
            return 0;
        }
        mulProduct *= checkForInts(lines, line - 1, charIndex + 1);
        partsCount++;
    }

    // To the left
    if(isdigit(lines[line][charIndex-1])){
        if(partsCount == 2){
            return 0;
        }
        mulProduct *= checkForInts(lines, line, charIndex - 1);
        partsCount++;
    }

    // To the right
    if(isdigit(lines[line][charIndex+1])){
        if(partsCount == 2){
            return 0;
        }
        mulProduct *= checkForInts(lines, line, charIndex + 1);
        partsCount++;
    }

    // Line below left
    if(isdigit(lines[line+1][charIndex-1])){
        if(partsCount == 2){
            return 0;
        }
        mulProduct *= checkForInts(lines, line + 1, charIndex - 1);
        partsCount++;
    }

    // Line below right
    if(isdigit(lines[line+1][charIndex+1])){
        if(partsCount == 2){
            return 0;
        }
        mulProduct *= checkForInts(lines, line + 1, charIndex + 1);
        partsCount++;
    }

    if(mulProduct == 1 || partsCount != 2){
        mulProduct = 0;
    }
    
    return mulProduct;
}

int solution1(){
    int sum = 0;
    std::vector<std::string> firstlines = lines;

    for (int i = 0; i < numberOfLines; i++){ 
        for (int j = 0; j < firstlines[i].length(); j++){
            if(isSymbol(firstlines[i][j])){
                sum += getAdjacentSum(firstlines, i, j);
            }
        }
    }

  return sum;
}

int solution2(){
    int sum = 0;
    std::vector<std::string> secondlines = lines;

    for (int i = 0; i < numberOfLines; i++){ 
        for (int j = 0; j < secondlines[i].length(); j++){
            if(isGear(secondlines[i][j])){
                sum += getAdjacentMul(secondlines, i, j);
            }
        }
    }

    return sum;
}

int main(){

    std::cout << "Solution for part a: " << solution1() << std::endl;
    std::cout << "Solution for part b: " << solution2() << std::endl;

    return 0;
}
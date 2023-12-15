#include "../../lib/file.hpp"
#include "../../lib/helper.hpp"

// =================== FILE READING ======================== //
File myfile("input.txt", "test.txt");
std::vector<std::string> lines = myfile.file_to_vector<std::string>(false);
int numberOfLines = lines.size();
// ======================================================== //
int lineCount = 0;

std::vector<std::vector<std::string>> setDataStraight(){
    std::vector<std::vector<std::string>> returnVec;
    std::vector<std::string> lineVector;
    for(auto line : lines){
        if(line == ""){
            lineCount++;
            returnVec.push_back(lineVector);
            lineVector.clear();
            continue;
        }
        lineVector.push_back(line);
    }
    returnVec.push_back(lineVector);
    return returnVec;
}

std::vector<std::vector<std::string>> patterns = setDataStraight();
bool columnsAreEqual(std::vector<std::string> pattern, int col, int nextCol){
    for(int i = 0; i < pattern.size(); i++){
        if(pattern[i][col] != pattern[i][nextCol]) return false;
    }
    return true;
}

int count = 0;
int patternCount = 0;

std::vector<std::string> flipPattern(std::vector<std::string>& pattern) {

    std::vector<std::string> returnVec(pattern[0].length());

    for (int i = 0; i < pattern.size(); i++) {
        for (int j = 0; j < pattern[i].size(); j++) {
            returnVec[j].push_back(pattern[i][j]);
        }
    }
    return returnVec;
}

int getLinesAbove(std::vector<std::string>& pattern){
    int linesAbove = 0;
    for (int i = 0; i < pattern.size() - 1; i++) {
            int top = i;
            int bottom = i + 1;
            bool isMirror = true;

            while (top >= 0 && bottom < pattern.size()) {
                if (pattern[top] != pattern[bottom]) {
                    isMirror = false;
                    break;
                } else {
                    top--;
                    bottom++;
                }
            }
            if (isMirror) {
                linesAbove =  i + 1;
                break;
            }
        }
    return linesAbove;
}

int getLinesAbove2(std::vector<std::string>& pattern){
    int linesAbove = 0;

    for (int i = 0; i < pattern.size() - 1; i++) {
        int top = i;
        int bottom = i + 1;
        int numOfMistakes = 0;

        while (top >= 0 && bottom < pattern.size()) {
            for(int j = 0; j < pattern[0].length(); j++){
                if (pattern[top][j] != pattern[bottom][j]) numOfMistakes++;
            } 

            if(numOfMistakes > 1) break;

            top--;
            bottom++;
        }

        if(numOfMistakes == 1){
            linesAbove = i + 1;
            return linesAbove;
        }
    }
    return linesAbove;
}

int checkForMirror(std::vector<std::string>& pattern, bool withSmudge){

    //Checking horizontal first:
    int linesAbove = (withSmudge) ? getLinesAbove2(pattern) : getLinesAbove(pattern);
    if(linesAbove != 0){
        return linesAbove * 100;
    }

    //Checking vertical by flipping the pattern and then doing the same method. 
    std::vector<std::string> flippedPattern = flipPattern(pattern);

    int colsToTheLeft = (withSmudge) ? getLinesAbove2(flippedPattern) : getLinesAbove(flippedPattern);
    if(colsToTheLeft != 0) {
        return colsToTheLeft;
    }
    
    std::cout << "NOT GOOD\n" << pattern[0] << "\n" << pattern[1] << std::endl;
    exit(0);

    return -1;
}

int solution1(){
    int sum = 0;

    for(auto pattern : patterns){
        sum += checkForMirror(pattern, false);
    }
    return sum;
}

int solution2(){
    int sum = 0;
    int patternNumber = 0;

    for(auto pattern : patterns){
        std::cout << "Pattern nr: " << patternNumber << std::endl;
        patternNumber++;
        sum += checkForMirror(pattern, true);
    }

    return sum;
}

int main(){

    std::cout << "Solution for part a: " << solution1() << std::endl;
    std::cout << "Solution for part b: " << solution2() << std::endl;

    return 0;
}
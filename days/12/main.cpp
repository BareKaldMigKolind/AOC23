#include "../../lib/file.hpp"
#include "../../lib/helper.hpp"

// =================== FILE READING ======================== //
File myfile("input.txt", "test.txt");
std::vector<std::string> lines = myfile.file_to_vector<std::string>(true);
int numberOfLines = lines.size();
// ======================================================== //

std::vector<std::vector<std::string>> puzzleChars;
std::vector<std::vector<int>> groupsOfInts;

void setDataStraight(){
    if(puzzleChars.size() > 0) return;
    for(auto line : lines){
        std::vector<std::string> groupOfChars;
        std::vector<int> lineInts;

        std::vector<std::string> splittedLine = split_on_char<std::string>(line, ' ');
        
        std::vector<std::string> splittedChars = split_on_char<std::string>(splittedLine[0], '.');
        for(auto chars : splittedChars){
            if(chars.length() == 0) continue;
            groupOfChars.push_back(chars);
        }
        puzzleChars.push_back(groupOfChars);

        lineInts = stringOfIntsToIntVector(splittedLine[1], ',');
        groupsOfInts.push_back(lineInts);
    }
}


int solution1(){
    setDataStraight();

    for(int i = 0; i < puzzleChars.size(); i++){
        
    }

    std::cout << "GROUP OF CHARS PRINTED" << std::endl;
    for(auto group : puzzleChars){
        for(auto charGroup : group){
            std::cout << charGroup << " ";
        }
        std::cout << std::endl;
    }
    
    std::cout << "GROUP OF INTS PRINTED" << std::endl;
    for(auto group : groupsOfInts){
        for(auto number : group){
            std::cout << number << " ";
        }
        std::cout << std::endl;
    }

    


    return 0;
}

int solution2(){
    setDataStraight();

    return 0;
}






int main(){

    std::cout << "Solution for part a: " << solution1() << std::endl;
    //std::cout << "Solution for part b: " << solution2() << std::endl;

    return 0;
}
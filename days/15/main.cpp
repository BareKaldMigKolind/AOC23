#include "../../lib/file.hpp"
#include "../../lib/helper.hpp"

// =================== FILE READING ======================== //
File myfile("input.txt", "test.txt");
std::vector<std::string> lines = myfile.file_to_vector<std::string>(false);
int numberOfLines = lines.size();
// ======================================================== //

int HASHFUNC(std::string str){
     int tempSum = 0;
        for(int i = 0; i < str.length(); i++){
            tempSum += int(str[i]);
            tempSum *= 17;
            tempSum %= 256;
        }
    return tempSum;
}

struct Lens{
    std::string label;
    int value;
};

int findLabel(std::vector<Lens> box, std::string label){
    for(int i = 0; i < box.size(); i++){
        if(box[i].label == label) return i;
    }
    return -1;
}

std::vector<std::string> csvData = split_on_char<std::string>(lines[0],',');

int solution1(){
    int sum = 0;
    for(auto line : csvData){
        sum += HASHFUNC(line);
    }
    return sum;
}

int solution2(){

    std::vector<std::vector<Lens>> boxes(256);

    for(auto line : csvData){

        std::size_t found = line.find('=');
        char operationChar = (found != std::string::npos) ? '=' : '-';

        std::vector<std::string> splittedLine = split_on_char<std::string>(line, operationChar);

        if(operationChar == '='){
            Lens lens  = {splittedLine[0], std::stoi(splittedLine[1])};

            int boxNumber = HASHFUNC(lens.label);

            int found = findLabel(boxes[boxNumber], lens.label);

            if(found != -1){
                boxes[boxNumber][found].value = lens.value;
            } else{
                boxes[boxNumber].push_back(lens);
            }

        } else{
            int boxNumber = HASHFUNC(splittedLine[0]);
            
            int found = findLabel(boxes[boxNumber], splittedLine[0]);

            if(found != -1){
                boxes[boxNumber].erase(boxes[boxNumber].begin() + found);
            } else{
                // Do nothing
            }
        }

    }

    // CALCULATING FOCUSING POWER
    int focusingPower = 0;
    for(int i = 0; i < boxes.size(); i++){
        if(boxes[i].size() == 0) continue;
        for(int j = 0; j < boxes[i].size(); j++){
            focusingPower += (1 + i) * (j + 1) * boxes[i][j].value;
        }
    }

    return focusingPower;
}

int main(){

    std::cout << "Solution for part a: " << solution1() << std::endl;
    std::cout << "Solution for part b: " << solution2() << std::endl;

    return 0;
}
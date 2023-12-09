#include "../../lib/file.hpp"
#include "../../lib/helper.hpp"

// =================== FILE READING ======================== //
File myfile("input.txt", "test.txt");
std::vector<std::string> lines = myfile.file_to_vector<std::string>(false);
int numberOfLines = lines.size();
// ======================================================== //

bool allZeros(std::vector<int> difVector){
    for(auto dif : difVector){
        if(dif != 0){
            return false;
        }
    }
    return true;
}

int computePrediction(std::vector<int> values){
    
    if(allZeros(values)){
        return 0;
    }

    for(int i = 0; i < values.size() - 1; i++){
        values[i] = values[i+1] - values[i];
    }
    int backVal = values.back();
    values.pop_back();

    return backVal + computePrediction(values);
}

int solution1(){
    int sum = 0;

    for(auto line : lines){
        std::vector<int> values = stringOfIntsToIntVector(line, ' ');
        sum += computePrediction(values);
    }
    
    return sum;
}

int solution2(){
    int sum = 0;

    for(auto line : lines){
        std::vector<int> values = stringOfIntsToIntVector(line, ' ');
        std::reverse(values.begin(), values.end());
        sum += computePrediction(values);
    }
    
    return sum;
}

int main(){

    std::cout << "Solution for part a: " << solution1() << std::endl;
    std::cout << "Solution for part b: " << solution2() << std::endl;

    return 0;
}
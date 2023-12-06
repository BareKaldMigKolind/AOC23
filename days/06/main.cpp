#include "../../lib/file.hpp"
#include "../../lib/helper.hpp"

// =================== FILE READING ======================== //
File myfile("input.txt", "test.txt");
std::vector<std::string> lines = myfile.file_to_vector<std::string>(false);
int numberOfLines = lines.size();
// ======================================================== //


int solution1(){
    std::vector<std::string> myLines = cleanedLines(lines, ':');
    std::vector<int> time = stringOfIntsToIntVector(myLines[0], ' ');
    std::vector<int> distance = stringOfIntsToIntVector(myLines[1], ' ');

    int runningMul = 1;

    for(int i = 0; i < time.size(); i++){
        int tempTime = time[i];
        for(int j = 0; j < time[i]/2; j++){
            if(j * (time[i] - j) > distance[i]){
                runningMul *= (time[i] - j) - j + 1;
                break;
            }
        }

    }

    return runningMul;
}

int solution2(){
    std::vector<std::string> newLines = cleanedLines(lines, ':');
    std::vector<int64_t> timeVector = stringOfIntsToLLVector(newLines[0], ' ');
    std::vector<int64_t> distVector = stringOfIntsToLLVector(newLines[1], ' ');


    int64_t totalTime = concatenateVector(timeVector);
    int64_t totalDistance = concatenateVector(distVector);   

    int runningMul = 1;
    
    for(int i = 0; i < totalTime / 2; i++){
        if(i * (totalTime - i) > totalDistance){
            runningMul *= (totalTime - i) - i + 1;
            break;
        }
    }

    return runningMul;
}






int main(){

    std::cout << "Solution for part a: " << solution1() << std::endl;
    std::cout << "Solution for part b: " << solution2() << std::endl;

    return 0;
}
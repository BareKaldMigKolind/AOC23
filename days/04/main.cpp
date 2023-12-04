#include "../../lib/file.hpp"
#include "../../lib/helper.hpp"

#include <unordered_set>
#include <unordered_map>

// =================== FILE READING ======================== //
File myfile("input.txt", "test.txt");
std::vector<std::string> lines = myfile.file_to_vector<std::string>(false);
int n = lines.size();
// ======================================================== //

std::vector<int> winnerNumbers;
std::vector<int> drawnNumbers;

int solution1(){
    int sum = 0;

    std::vector<std::string> cleanedLines = lines;
    // Cleaning the lines:
    for(int i = 0; i < cleanedLines.size(); i++){
        int runningSum = 0;

        //Splitting line on ":"
        std::vector<std::string> tempVector = split_on_char<std::string>(cleanedLines[i], ':');
        cleanedLines[i] = tempVector[1];

        //Splitting each cleaned line on "|" and dividing them into winnerNumbers and drawnNumbers;
        tempVector.clear();
        tempVector = split_on_char<std::string>(cleanedLines[i], '|');

        //tempVector[0] contains string of winner numbers, tempVector[1] contains string of drawn numbers.        
        winnerNumbers = stringOfIntsToIntVector(tempVector[0], ' ');    
        drawnNumbers = stringOfIntsToIntVector(tempVector[1], ' ');

        std::unordered_set<int> winnerSet;
        for(int number : winnerNumbers){
            winnerSet.insert(number);
        }

        // Checking to see if a drawn number matches any winner number.  
        for(int number : drawnNumbers){
            if(winnerSet.find(number) != winnerSet.end()){
                if(runningSum == 0){
                    runningSum++;
                } else{
                    runningSum = runningSum << 1;
                }
            }
        }
        sum += runningSum;
    }

    return sum;
}

int sumOfVector(std::vector<int> vec){
    int sum = 0;
    for(int value : vec){
        sum += value;
    }
    return sum;
}

int solution2(){
    int sum = 0;

    std::vector<int> numberOfScratchcards(n, 1);

    std::vector<std::string> cleanedLines = lines;
    // Cleaning the lines:
    for(int lineNumber = 0; lineNumber < n; lineNumber++){
        int runningSum = 0;

        //Splitting line on ":"
        std::vector<std::string> tempVector = split_on_char<std::string>(cleanedLines[lineNumber], ':');
        cleanedLines[lineNumber] = tempVector[1];

        //Splitting each cleaned line on "|" and dividing them into winnerNumbers and drawnNumbers;
        tempVector.clear();
        tempVector = split_on_char<std::string>(cleanedLines[lineNumber], '|');

        //tempVector[0] contains string of winner numbers, tempVector[1] contains string of drawn numbers.        
        winnerNumbers = stringOfIntsToIntVector(tempVector[0], ' ');    
        drawnNumbers = stringOfIntsToIntVector(tempVector[1], ' ');

        std::unordered_set<int> winnerSet;
        for(int number : winnerNumbers){
            winnerSet.insert(number);
        }

        // Checking to see if a drawn number matches any winner number. 
        for(int num : drawnNumbers){
            if(winnerSet.find(num) != winnerSet.end()){
                runningSum++;                    
            }
        }

        // runningSum controls which copies we get.
        for(int j = 0; j < runningSum; j++){
            // numberOfScratchcards[lineNumber] controls how many copies we get
            for(int k = 0; k < numberOfScratchcards[lineNumber]; k++){
                numberOfScratchcards[lineNumber+(j+1)]++;
            }
        }
    }

    return sumOfVector(numberOfScratchcards);
}


int main(){

    std::cout << "Solution for part a: " << solution1() << std::endl;
    std::cout << "Solution for part b: " << solution2() << std::endl;

    return 0;
}
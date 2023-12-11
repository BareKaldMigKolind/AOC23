#include "../../lib/file.hpp"
#include "../../lib/helper.hpp"

#include <unordered_map>

#define xPos int
#define yPos int

// =================== FILE READING ======================== //
File myfile("input.txt", "test.txt");
std::vector<std::string> lines = myfile.file_to_vector<std::string>(false);
int numberOfLines = lines.size();
// ======================================================== //

std::pair<xPos,yPos> coordinatesForS(){
    for(int row = 0; row < numberOfLines; row++){
        for(int col = 0; col < lines[row].length(); col++){
            if(lines[row][col] == 'S'){
                return std::make_pair(col, row);
            }
        }
    }
    return std::make_pair(-1, -1);
}

std::pair<xPos, yPos> startPos = coordinatesForS();

std::unordered_map<char, std::pair<char, char>> movement;

void setMap(){
    movement.insert(std::make_pair('|', std::make_pair('n', 's')));
    movement.insert(std::make_pair('-', std::make_pair('w', 'e')));
    movement.insert(std::make_pair('L', std::make_pair('n', 'e')));
    movement.insert(std::make_pair('J', std::make_pair('n', 'w')));
    movement.insert(std::make_pair('7', std::make_pair('s', 'w')));
    movement.insert(std::make_pair('F', std::make_pair('s', 'e')));  
}

bool isLegal (int x, int y, char direction){
    if(direction == 'n' && (lines[y+1][x] == '|' || lines[y+1][x] == '7' || lines[y+1][x] == 'F')){
        return true;
    } else if(direction == 's' && (lines[y-1][x] == '|' || lines[y-1][x] == 'L' || lines[y-1][x] == 'J')){
        return true;
    } else if(direction == 'e' && (lines[y][x + 1] == '-' || lines[y][x + 1] == '7' || lines[y][x + 1] == 'J')){
        return true;
    } else if(direction == 'w' && (lines[y][x-1] == '-' || lines[y][x-1] == 'L' || lines[y][x-1] == 'F')){
        return true;
    } else {
        return false;
    }
}

char getOpposite(char ch){
    if(ch == 'n') return 's';
    if(ch == 's') return 'n';
    if(ch == 'w') return 'e';
    if(ch == 'e') return 'w';

    //std::cout << "GETOPPOSITE IS WRONG" << std::endl;
    return 'M';
}

std::pair<int, int> getNextStep(char ch){
    if(ch == 'n'){
        return std::make_pair(0, -1);
    } 
    if(ch == 's'){
        return std::make_pair(0, 1);
    }
    if(ch == 'e'){
        return std::make_pair(1, 0);
    }
    if(ch == 'w'){
        return std::make_pair(-1, 0);
    }
    
    //std::cout << "getNextStep is shit" << std::endl;
    return std::make_pair(-1000, -1000);
}

void move(int x, int y, char cameFrom, int& steps){

    steps++;

    if(x == startPos.first && y == startPos.second){
        //std::cout << "At position (" << x << ";" << y << ") is the char: " << lines[y][x] << std::endl;
        return;
    }

    char ch = lines[y][x];
    //std::cout << "At Position: (" << x << ";" << y << ") is the char: " << ch << std::endl;
    std::pair<char, char> pipe = movement[ch];
    //std::cout << "This means movement is between: " << pipe.first << " and " << pipe.second << std::endl;
    //std::cout << "As I came from " << cameFrom << std::endl;

    if(cameFrom == pipe.first){
        std::pair nextStep = getNextStep(pipe.second);
        //std::cout << "Next step says go to: " << nextStep.first + x << ";" << nextStep.second + y<< std::endl;
        move(nextStep.first + x, nextStep.second + y, getOpposite(pipe.second), steps);
    } else if(cameFrom == pipe.second){
        std::pair nextStep = getNextStep(pipe.first);
        //std::cout << "=Next Step says move: " << nextStep.first << ";" << nextStep.second << std::endl;
        move(nextStep.first + x, nextStep.second + y, getOpposite(pipe.first), steps);
    } else {
       //std::cout << "This goes bad.. \nAt position: " << x << ";" << y << ") is the char: " << lines[y][x] << std::endl;
    }

}

char getOverwriteChar(char ch){
    if (ch == 'F' || ch == '7' || ch == 'J' || ch == 'L' ) {
        return 'X';
    } else {
        return '0';
    }
}

void overwriteChar(int x, int y, char cameFrom){

    if(x == startPos.first && y == startPos.second){
        //std::cout << "At position (" << x << ";" << y << ") is the char: " << lines[y][x] << std::endl;
        return;
    }

    char ch = lines[y][x];
    //std::cout << "At Position: (" << x << ";" << y << ") is the char: " << ch << std::endl;
    std::pair<char, char> pipe = movement[ch];
    //std::cout << "This means movement is between: " << pipe.first << " and " << pipe.second << std::endl;
    //std::cout << "As I came from " << cameFrom << std::endl;
    lines[y][x] = getOverwriteChar(ch);

    if(cameFrom == pipe.first){
        std::pair nextStep = getNextStep(pipe.second);
        //std::cout << "Next step says go to: " << nextStep.first + x << ";" << nextStep.second + y<< std::endl;
        overwriteChar(nextStep.first + x, nextStep.second + y, getOpposite(pipe.second));
    } else if(cameFrom == pipe.second){
        std::pair nextStep = getNextStep(pipe.first);
        //std::cout << "=Next Step says move: " << nextStep.first << ";" << nextStep.second << std::endl;
        overwriteChar(nextStep.first + x, nextStep.second + y, getOpposite(pipe.first));
    } else {
       //std::cout << "This goes bad.. \nAt position: " << x << ";" << y << ") is the char: " << lines[y][x] << std::endl;
    }

}


int solution1(){
    setMap();

    int steps = 0;

    int x = startPos.first;
    int y = startPos.second;


    if(isLegal(x,y,'n') && y != 0){
        move(x, y, 's', steps);
    } else if(isLegal(x, y, 's' && y != numberOfLines - 1)){
        move(x, y, 'n',steps);
    } else if(isLegal(x, y, 'e' && x != lines[0].length())){
        move(x, y, 'w',steps);
    } else if(isLegal(x, y, 'w' && x != 0)){
        move(x, y, 'e',steps);
    } else {
        std::cout << "At pos: (" << x << ";" << y << ") something went wrong" << std::endl;
    }

    return steps / 2;
}

bool oddNumberOfZero(int X, int Y, char ch){
    int count = 0;
    int corners = 0;
    //std::cout << lines[Y][X] << std::endl;
    if(ch == 'n'){
        for(int i = Y; i > 0; i--){
            if(lines[i][X] == '0'){
                corners++;
            }
            if(lines[i][X] == '0'){
                count++;
            }
        }
    }
    if(ch == 's'){
        for(int i = Y; i < numberOfLines; i++){
            if(lines[i][X] == '0'){
                corners++;
            }
            if(lines[i][X] == '0'){
                count++;
            }
        }
    }
    if(ch == 'e'){
        for(int i = X; i < lines[Y].length(); i++){
            if(lines[Y][i] == '0'){
                corners++;
            }
            if(lines[Y][i] == '0'){
                count++;
            }
        }
    }
    if(ch == 'w'){
        for(int i = X; i < 0; i--){
            if(lines[Y][i] == '0'){
                corners++;
            }
            if(lines[Y][i] == '0'){
                count++;
            }
        }
    }
    if(corners != 0) return corners % 2 == 1;
    return count % 2 == 1;
}

bool isInside(int X, int Y){
    if(oddNumberOfZero(X,Y, 'n') 
    && oddNumberOfZero(X,Y, 's') 
    && oddNumberOfZero(X,Y, 'e') 
    && oddNumberOfZero(X,Y, 'w')) return true;

    return false;
}

int solution2(){
    setMap();

    int x = startPos.first;
    int y = startPos.second;

    std::cout << x << y << std::endl;

    if(isLegal(x,y,'n')){
        //std::cout << "n" << std::endl;
        overwriteChar(x, y - 1, 's');
    } else if(isLegal(x, y, 's')){
        //std::cout << "s" << std::endl;
        overwriteChar(x, y-1, 'n');
    } else if(isLegal(x, y, 'e')){
        //std::cout << "s" << std::endl;
        overwriteChar(x + 1, y, 'w');
    } else if(isLegal(x, y, 'w')){
        //std::cout << "s" << std::endl;
        overwriteChar(x - 1, y, 'e');
    } else {
        //std::cout << "At pos: (" << x << ";" << y << ") something went wrong" << std::endl;
    }



    int count = 0;

    print_vector<std::string>(lines, "Lines");


   for(int Y = 0; Y < numberOfLines; Y++){
    for(int X = 0; X < lines[0].length(); X++){
        //std::cout << "HEP" << std::endl;
        if(isInside(X, Y)){
            std::cout << "Found a 0 at (" << X << ";" << Y << ")" << std::endl;
            count++;
        } 
    } 
   }

    return count;
}






int main(){

    std::cout << "Solution for part a: \n" << solution1() << std::endl;
    //std::cout << "Solution for part b: " << solution2() << std::endl;

    return 0;
}
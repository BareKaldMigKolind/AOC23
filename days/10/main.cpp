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
    if(y != 0 && (direction == 'n' && (lines[y-1][x] == '|' || lines[y-1][x] == '7' || lines[y-1][x] == 'F'))){
        return true;
    } else if(y != numberOfLines && (direction == 's' && (lines[y+1][x] == '|' || lines[y+1][x] == 'L' || lines[y+1][x] == 'J'))){
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
    if(ch == 'n')   return 's';
    if(ch == 's')   return 'n';
    if(ch == 'w')   return 'e';
    else            return 'w';
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
    else {
        return std::make_pair(-1, 0);
    }
}

void move(int x, int y, char cameFrom, int& steps){

    steps++;

    if(x == startPos.first && y == startPos.second){
        return;
    }

    char ch = lines[y][x];
    std::pair<char, char> pipe = movement[ch];

    if(cameFrom == pipe.first){
        std::pair nextStep = getNextStep(pipe.second);
        move(nextStep.first + x, nextStep.second + y, getOpposite(pipe.second), steps);
    } else if(cameFrom == pipe.second){
        std::pair nextStep = getNextStep(pipe.first);
        move(nextStep.first + x, nextStep.second + y, getOpposite(pipe.first), steps);
    } else {
       std::cout << "This goes bad.. \nAt position: " << x << ";" << y << ") is the char: " << lines[y][x] << std::endl;
    }
}

char getOverwriteChar(char ch){
    if(ch == 'L' || ch == 'F'){
        return 'H';
    } else if(ch == '7' || ch == 'J'){
        return 'V';
    } else if(ch == '-'){
        return '_';
    } else if(ch == '|'){
        return 'I';
    } else if(ch == 'S'){
        return 'S';
    } else {
        return ch;
    }
    
}

void overwriteChar(int x, int y, char cameFrom){
    if(x == startPos.first && y == startPos.second){
        return;
    }

    char ch = lines[y][x];
    std::pair<char, char> pipe = movement[ch];
    lines[y][x] =  getOverwriteChar(ch);

    if(cameFrom == pipe.first){
        std::pair nextStep = getNextStep(pipe.second);
        overwriteChar(nextStep.first + x, nextStep.second + y, getOpposite(pipe.second));
    } else if(cameFrom == pipe.second){
        std::pair nextStep = getNextStep(pipe.first);
        overwriteChar(nextStep.first + x, nextStep.second + y, getOpposite(pipe.first));
    } else {
       std::cout << "This goes bad.. \nAt position: " << x << ";" << y << ") is the char: " << lines[y][x] << std::endl;
    }
}

int solution1(){
    setMap();

    int steps = 0;

    int x = startPos.first;
    int y = startPos.second;


    if(isLegal(x,y,'n') && y != 0){
       move(x, y - 1, 's', steps);
    } else if(isLegal(x, y, 's') && y != numberOfLines - 1){
       move(x, y + 1, 'n',steps);
    } else if(isLegal(x, y, 'e') && x != lines[0].length()){
       move(x + 1, y, 'w',steps);
    } else if(isLegal(x, y, 'w') && x != 0){
       move(x - 1, y, 'e',steps);
    } else {
       std::cout << "At pos: (" << x << ";" << y << ") something went wrong" << std::endl;
    }

    return steps / 2;
}

bool oddNumberOfLines(int X, int Y, char ch){
    int count = 0;
    int corners = 0;
    bool checkThisOne = false;
    char cornerChar = 'q';

// THIS IS SOME GOOD USE OF IF
    if(ch == 'n'){
        for(int i = Y - 1; i >= 0; i--){
            if(lines[i][X] == '_'){
                count++;
            } else if(lines[i][X] == 'H'){
                if(cornerChar == 'H'){
                    cornerChar = 'q';
                } else if(cornerChar == 'V'){
                    count++;
                    cornerChar = 'q';
                } else{
                    cornerChar = 'H';
                }
                continue;
            } else if(lines[i][X] == 'V'){
                if(cornerChar == 'V'){
                    cornerChar = 'q';
                } else if(cornerChar == 'H'){
                    count++;
                    cornerChar = 'q';
                } else{
                    cornerChar = 'V';
                }
                continue;
            }
        }
    }

    if(ch == 's'){
        for(int i = Y + 1; i > numberOfLines; i++){
            if(lines[i][X] == '_'){
                count++;
            } else if(lines[i][X] == 'H'){
                if(cornerChar == 'H'){
                    cornerChar = 'q';
                } else if(cornerChar == 'V'){
                    count++;
                    cornerChar = 'q';
                } else{
                    cornerChar = 'H';
                }
            } else if(lines[i][X] == 'V'){
                if(cornerChar == 'V'){
                    cornerChar = 'q';
                } else if(cornerChar == 'H'){
                    count++;
                    cornerChar = 'q';
                } else{
                    cornerChar = 'V';
                }
            }
        }
    }

    return count % 2 == 1;
}

bool isInside(int X, int Y){
    if(oddNumberOfLines(X,Y, 'n') || oddNumberOfLines(X,Y, 's')) return true;
    return false;
}

bool isPipe(char ch){
    if(ch == 'H' || ch == 'V' || ch == 'I' || ch == '_') return true;
    return false;
}


int solution2(){
    setMap();

    int x = startPos.first;
    int y = startPos.second;

    if(isLegal(x,y,'n')){
        lines[y][x] = 'V';
        overwriteChar(x, y-1, 's');
    } else if(isLegal(x, y, 's')){
        lines[y][x] = 'V';
        overwriteChar(x, y + 1, 'n');
    } else if(isLegal(x, y, 'e')){
        overwriteChar(x+1, y, 'w');
    } else if(isLegal(x, y, 'w')){
        overwriteChar(x-1, y, 'e');
    }

    int count = 0;

   for(int Y = 0; Y < numberOfLines; Y++){
        for(int X = 0; X < lines[0].length(); X++){
            char ch = lines[Y][X];
            if(isPipe(ch)) continue;

            if(isInside(X, Y)) count++; 
        } 
   }
    return count;
}

int main(){

    std::cout << "Solution for part a: " << solution1() << std::endl;
    std::cout << "Solution for part b: " << solution2() << std::endl;

    return 0;
}
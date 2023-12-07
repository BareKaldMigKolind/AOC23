#include "../../lib/file.hpp"
#include "../../lib/helper.hpp"

#include <set>

// =================== FILE READING ======================== //
File myfile("input.txt", "test.txt");
std::vector<std::string> lines = myfile.file_to_vector<std::string>(false);
int numberOfLines = lines.size();
// ======================================================== //

enum TypeOfHand{
    HighCard = 1,
    OnePair = 2,
    TwoPair = 3,
    ThreeOfAKind = 4,
    FullHouse = 5,
    FourOfAKind = 6,
    FiveOfAKind = 7
};

int getValue(char ch, bool withJoker){
    if(ch == 'A')               return 14;
    if(ch == 'K')               return 13;
    if(ch == 'Q')               return 12;
    if(ch == 'J' && !withJoker) return 11;
    if(ch == 'J' && withJoker)  return 1;
    if(ch == 'T')               return 10;
    /*These are just casted*/   return int(ch) - 48; 
}

struct Cards{
    std::string cards;

    bool operator < (const Cards& otherCards) const{
        for(int i = 0; i < cards.length(); i++){
            int value = getValue(cards[i], false);
            int otherValue = getValue(otherCards.cards[i],false);

            if(value != otherValue) return value < otherValue;
            else                    continue;
        }
        return false;
    }

    bool operator > (const Cards& otherCards) const{
       return !(*this < otherCards);
   }
   bool operator == (const Cards& otherCards) const{
        return !(*this < otherCards || *this > otherCards);
   }
   bool operator != (const Cards& otherCards) const{
        return !(*this == otherCards);
   }

};

struct Hand{
    TypeOfHand handType;
    Cards cards;
    int bid;

    bool operator < (const Hand& other) const{
        if(handType != other.handType)      return handType < other.handType;
        else if(cards != other.cards)       return cards < other.cards;
        else return bid < other.bid; // This is just to please the warnings, shouldn't happen with the given data.
    }

    bool operator > (const Hand& other) const{
       return !(*this < other);
   }
};

TypeOfHand computeTypeOfHand(int numOfPairs, int numOfAKinds){
    if(numOfAKinds == 5)                    return TypeOfHand::FiveOfAKind;
    if(numOfAKinds == 4)                    return TypeOfHand::FourOfAKind;
    if(numOfAKinds == 3 && numOfPairs == 1) return TypeOfHand::FullHouse;
    if(numOfAKinds == 3)                    return TypeOfHand::ThreeOfAKind;
    if(numOfPairs == 2)                     return TypeOfHand::TwoPair;
    if(numOfPairs == 1)                     return TypeOfHand::OnePair;
    /*Just high card :(*/                   return TypeOfHand::HighCard;
}
TypeOfHand computeTypeOfHandWithJoker(int numberOfPairs, int numOfAKinds, int numberOfJ){
    // Here we only have one option, fiveOfAKind
    if(numberOfJ == 5 || numberOfJ == 4) return TypeOfHand::FiveOfAKind;
    // Having three Js means we can either have a pair or two nonequal cards
    if(numberOfJ == 3){
        if(numberOfPairs == 1) return TypeOfHand::FiveOfAKind;
        else return TypeOfHand::FourOfAKind;
    }
    // Two Js we can have three of a kind, a pair or three different cards. 
    if(numberOfJ == 2){
        if(numOfAKinds == 3) return TypeOfHand::FiveOfAKind;
        if(numberOfPairs == 1) return TypeOfHand::FourOfAKind;
        else return TypeOfHand::ThreeOfAKind;
    }
    // 1 J means we can have Four Of Kinds, Three of Kinds, Two pairs, One pair or all different cards
    if(numOfAKinds == 4) return TypeOfHand::FiveOfAKind;
    if(numOfAKinds == 3) return TypeOfHand::FourOfAKind;
    if(numberOfPairs == 2) return TypeOfHand::FullHouse;
    if(numberOfPairs == 1) return TypeOfHand::ThreeOfAKind;
    return TypeOfHand::OnePair;
}

TypeOfHand getTypeOfHand(std::string& cards, bool withJoker){
    std::vector<int> valueCounter(15,0);
    int numOfPairs = 0;
    int numOfAKinds = 0;
    int highestCard = 0;
    int numOfJs = 0;

    for(int i = 0; i < cards.length(); i++){
        int card = getValue(cards[i], withJoker);
        if(card == 1 && withJoker){
            numOfJs++;
            continue;
        }
        valueCounter[card]++;
        if(valueCounter[card] == 1) {
            if(highestCard < card){
                highestCard = card;
            }
        }
        else if(valueCounter[card] == 2) numOfPairs++;
        else if(valueCounter[card] == 3) {
            numOfPairs--;
            numOfAKinds = 3;
        }
        else if(valueCounter[card] == 4) numOfAKinds = 4;
        else if(valueCounter[card] == 5) numOfAKinds = 5;
    }

    if(withJoker && numOfJs > 0){
        return computeTypeOfHandWithJoker(numOfPairs, numOfAKinds, numOfJs);
    } else {
        return computeTypeOfHand(numOfPairs, numOfAKinds);
    }
}

int solution1(){
    int sum = 0;

    std::set<Hand> sortedHands;

    for(auto line : lines){
        std::vector<std::string> handAndBid = split_on_char<std::string>(line, ' ');

        Hand hand{
            getTypeOfHand(handAndBid[0], false),
            handAndBid[0],
            stringToInt(handAndBid[1])
        };

        sortedHands.insert(hand);
    }

    int rank = 1;
    for(auto hand : sortedHands){
        sum += rank * hand.bid;
        rank++;
    }
    
    return sum;
}

struct Cards2{
    std::string cards;

    bool operator < (const Cards2& otherCards) const{
        for(int i = 0; i < cards.length(); i++){
            int value = getValue(cards[i],true);
            int otherValue = getValue(otherCards.cards[i], true);
            if(value != otherValue) return value < otherValue;
            else                    continue;
        }
        return false;
    }

    bool operator > (const Cards2& otherCards) const{
        return !(*this < otherCards);
   }
    bool operator == (const Cards2& otherCards) const{
        return !(*this < otherCards || *this > otherCards);
   }
    bool operator != (const Cards2& otherCards) const{
        return !(*this == otherCards);
    }
};

struct Hand2{
    TypeOfHand handType;
    Cards2 cards;
    int bid;

    bool operator < (const Hand2& other) const{
        if(handType != other.handType)      return handType < other.handType;
        else if(cards != other.cards)       return cards < other.cards;
        else return bid < other.bid; // This is just to please the warnings, shouldn't happen with the given data.
    }

    bool operator > (const Hand2& other) const{
       return !(*this < other);
   }
};

int solution2(){
    long long sum = 0;

    std::set<Hand2> sortedHands;

    for(auto line : lines){
        std::vector<std::string> handAndBid = split_on_char<std::string>(line, ' ');

        Hand2 hand{
            getTypeOfHand(handAndBid[0], true),
            handAndBid[0],
            stringToInt(handAndBid[1])
        };

        sortedHands.insert(hand);
    }

    int rank = 1;
    for(auto hand : sortedHands){
        sum += rank * hand.bid;
        rank++;
    }
    
    return sum;
}

int main(){

    std::cout << "Solution for part a: " << solution1() << std::endl;
    std::cout << "Solution for part b: " << solution2() << std::endl;

    return 0;
}
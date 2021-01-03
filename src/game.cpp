#include <iostream>
#include <string>
#include <thread>
#include <chrono>

#define AY

class Game{
private:
    std::string state;
public:
	std::string getState(){
	   return state;
	}
    void gameStart(){
        for(int i = 0; i < 9; ++i){
            state [i] = (i + 1 + '0');
        }
    }
    
    Game():state(){
        gameStart();
    }
    
    bool turnX(int x){
        if(state[x - 1] != 'O' && state[x - 1] != 'X' && x <= (9) && x >= (1)){
            
            state[x - 1] = 'X';
            return true;
        }
        else{
            std::cout << (x <= (0));
            std::cout << "Invalid Move\n";
            return false;
        }
    }
    
    bool turnO(int o){
        if(state[o - 1] != 'X' && state[o - 1] != 'O' && o <= 9 && o >= 1){
            state[o - 1] = 'O';
            return true;
        }
        else{
            std::cout << "Invalid Move\n";
            return false;
        }
    }
    
    friend std::ostream& operator<<(std::ostream& out, Game& x){
        for(int i = 0; i < 3; ++i){
            out << x.state[(i * 3)] << '|' <<
            x.state[((i*3) + 1)] << '|' << 
            x.state[((i * 3) + 2)] << '\n';
        }
        return out;
    }
    
    int checkGame(){
        for(int i = 0; i < 3; ++i){
            if(state[(i * 3)] == state [(i * 3) + 1] && state[(i * 3 ) + 1] == state[(i * 3) + 2]){
                std::cout << state[i * 3] << " has won the game\n";
                if(state[i * 3] == 'X'){
            
                    return 2;
                }
                else if(state[i * 3] == 'O'){
                    return 3;
                }
            }
            if(state[i] == state[i + 3] && state[i + 3] == state[i + 6]){
                std::cout << state[i] << " has won the game\n";
                if(state[i] == 'X'){
            
                    return 2;
                }
                else if(state[i] == 'O'){
                    return 3;
                }
            }
        
        
        
        }
        if(state[0] == state[4] && state[4] == state[8]){
        		std::cout << state[0] << " has won the game\n";
                if(state[0] == 'X'){            
                    return 2;
                }
                else if(state[0] == 'O'){
                    return 3;
                }
        }
        else if(state[2] == state[4] && state[4] == state[6]){
        		std::cout << state[2] << " has won the game\n";
                if(state[2] == 'X'){
            
                    return 2;
                }
                else if(state[2] == 'O'){
                    return 3;
                }
        }
        return 1;
    }
};

#ifdef AY
/*
int main(){
    Game game;
    while(true){
    game.gameStart();
    bool Winning = true;
    std::cout << game;
    while(Winning){
    
    while(true){
    	int input;
   	 std::cout << "What number X?\n";
    	std::cin >> input;
    	bool pass = game.turnX(input);
    	if(pass)
    		break;
    }
    int state = game.checkGame();
    std::cout << game;
    if(state != 1)
        break;
    while(true){
   	 int input2;
 	   std::cout << "What number O?\n";
 	   std::cin >> input2;
 	   bool pass = game.turnO(input2);
 	   if(pass)
 	   	break;
    }
    state = game.checkGame();
    std::cout << game;
    if(state != 1){
        break;
    }
    }
    std::cout << "\n";
std::this_thread::sleep_for(std::chrono::milliseconds(2000));
    }
}*/
#endif
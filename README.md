# Interactive BlackJack

## Authors and areas of contribution:
1. Tridib Banik: Test scripts written in Bash, game_result(), reveal_hand(), generate 100% test coverage and upload artifacts through build script.
2. Harrison Johns: Makefile, test script for GUI, header file, special_case(), deal_player_hand(), get_result(), card_handler.c and get_initial_bet().
3. Jeslyn Lu: --help flag, special_case(), hit(), player_hit_loop(), blackjack_manager(), play_blackjack() and main().
4. Ahmed Zafar: Entire interactive GUI, testing and validating GUI, integrate back-end logic with front-end, and readme file.

## Description:
Have you ever wanted to **2x** your money?? How about **10x**??? With our new app, you can get the rush of winning big, without any of the risk, anywhere, anytime.
Our app is recreating the card game BlackJack. The user will be dealt two random cards and then decide whether to add another card to their deck. (The player can have two options: stand or draw a card.) The player loses if their hand values are over 21 or the dealer has a higher hand less than 21. The ACE is worth 1 or 11 depending on whether the player exceeds 21. Face cards are worth 10 each. All other cards are worth the number written on the card. The user bets before each game and their overall balance is tracked.

## Usage:
Our code is split into two different components, making it more accessible to play.

### Command-Line:
To run the code in the command line, use the command: <br />
 ```
make
``` 
to make the executable file, and then: <br />
```
./blackjack
```
and follow the on screen instructions to play.

### GUI:
To play the game using the GUI, you first must install the necessary dependencies. To install Simple DirectMedia Layer 2 (sdl2) use these two command: <br />
```
sudo apt install libsdl2-dev
```
```
sudo apt install libsdl2-ttf-dev
```
and continue with signing into your administrator account (don't forget to sign out later!). <br />
Then, create the executable file: <br />
```
make gui_blackjack
```
Finally, run: <br /> 
```
./gui_blackjack
```
and allow the computer to run the GUI!


Enjoy!!

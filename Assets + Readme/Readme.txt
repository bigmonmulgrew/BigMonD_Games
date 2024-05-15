## Readme file for assignment 1 submission 100705789
Built in Unreal 5.2.1

# Known issues
I've regularly had to switch from unreal version 5.2 to unreal version 5.2 when changing machine or I get some unpredicable behaviour. 

# Instructions
From the title screen press the number line buttons 1 to 9 to select a level. You can do this inside levels too, Pressing the key for the level you are currently on will reload the level.
Games with a thumbnail on the title screen are playable, the rest are planned additions later
Games 1 to 4 are workng and playable. 
0 returns you to to the title screen.

1. Pong				Classic
2. Breakout			Classic
3. Peggle			Classic
4. Mario clone			Classic
5. Fiendly Pong			Up to 4 player game mode, friendly because you have to be to play 4 players to one keyboard
6. Breakout ????
7. Peggle ??????
8. Mario ??????
9. Unused
0. Return to title Screen

# 1 Pong
This is classsic pong. Game plays first to 3 scores, winner will be announced and then after a short delay will return to the title screen
There is a GameManager in the outliner with a setting for the MaxScore
Controls:  W - Up, S - Down 

# 2 Breakout
This is classic Breakout, you have 3 extra lives, lose the 4th ball and you lose.
Controls: A - Left, D - Right

# Peggle
A simple Peggle clone, one ball at a time.
Controls: A - Aim Left, D - Aim Right, Left Click - Fire

# Mario
A simple mario clone demo.
Controls: A - Left, D - Right, Space - Jump
Threee types of enemy. 
White - Dumb enemy walks off ledges
Blue - Smart enemy turns around at edges
Red- 3rd enemy leaves a corpse that can be kicked around, you can bounce it over terrain, with some difficulty

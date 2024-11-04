# groupsix
gameProjectSthlmGroup6

SRS SPELPROJECT



Introduction:
The project is a game of advanced battleships. The game is going to be playable single-player against computer and multiplayer 1v1 on the same computer. The project is a 2d game. 
What makes it different from a normal “battleship” is the different weapons and different ways to aid you. You have unlimited “normal” weapons. One use of the “missile” and the “rapid fire cannon”. 
Instead of shooting on you can use one of your gadgets on your turn, you can use the “first aid kit”, the “scanning device” or “move one of your ships”. 


Intended Audience and Intended Use:

Requirements of target audience
Must be able to read.
Be able to operate a basic terminal application.
What is required to make such a user?
The necessary software installed through education

How can the user be helped?
Coloring text is very helpful for readability and makes the text seem more professional and flashy. While utilizing grammatically correct text.

Functional Requirements

1. Must have a 2D grid that can be played on that is 15x15.
2. Let the two players enter their names before the game starts.
3. Be able to place 5 ships onto a 2D plane with varying sizes on the ships. Then keep track of the positions for the player that placed them. Ships should not be able to be placed in the same position as another ship. 
4. Lets the players place 1 x 2 spaced ship, 2 x 3 spaced ship, 1 x 4 spaced ship and 1 x 5 spaced ship. 
5. Have varying turns that switch between players where players get the opportunity to target a plane on the 2d grid. If a target is hit it should inform the players that the strike was successful.
6. Support multiplayer for 2 users.
7. Must have a convenient transition from player one to player two without the players being able to see each other's boards.
8. The game should keep track of where a player previously hit on the 2d grid as well as if that hit was a success or a misfire.
9. Should be able to detect invalid input 
10. If you hit a ship, the turn goes to the other player. 
11. The “missile” is a one time use, and it hits 3x3 spaces. 
12. The “scanning function” lets the user scan an area for boats 3x3. If a boat/boats are found, make visible but not “hit”.
13. The “First aid kit” takes away a hit on one of your ships. 
14. The “rapid fire cannon” randomly hits different coordinates. 
15. The “move one of your ships” function lets the player move a ship to a non-hit space. If your ship is already hit and you move it, it will still show the area that the opponent hit. 
16. If you have sunk all your opponents ships, you win the game! If your opponent has sunk all of your ships, you have lost! 


Non-Functional requirements

1. Readable and maintainable code. As multiple users will work on the same project.
2. Scalability: The project needs to be able to be scaled where new functions and mechanisms should be able to be added.
3. Usability: needs to be able to be used by users that are unfamiliar with the system and the commands required to operate the terminal.
4. Performance: The game will update the 2d board directly after action.



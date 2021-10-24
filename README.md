<p align="center">
<img src="images/bomb.png" width="128" height="128"/>
<br/>
<h3 align="center">Minesweeper</h3>
<p align="center">A command line Minesweeper game.</p>
<h2></h2>
</p>
<br />

<p align="center">
<a href="../../issues"><img src="https://img.shields.io/github/issues/aminbeigi/Minesweeper?style=flat-square" /></a>
<a href="../../pulls"><img src="https://img.shields.io/github/issues-pr/aminbeigi/Minesweeper?style=flat-square" /></a>
<img src="https://img.shields.io/github/license/aminbeigi/minesweeper?style=flat-square">
</p>

## Description
### What is Minesweeper?
The aim of minesweeper is to reveal every square in the minefield except for the ones containing mines.
### The Minefield
The minefield is a two dimensional array of integers that represents the space that the game is played in. We will be referring to individual elements of these arrays as squares in the minefield.

The minefield is a fixed size grid and has `SIZE` rows, and `SIZE` columns. `SIZE` is a `#define`'d constant.

Both the rows and columns start at 0, not at 1.

The top left corner of the grid is `(0, 0)` and the bottom right corner of the grid is `(SIZE - 1, SIZE - 1)`. Note that we are using rows as the first coordinate in pairs of coordinates.

In the game of minesweeper these states are displayed to the player:
* A revealed square
* A square that is unrevealed

Since a square that has not been revealed may or may not contain a mine, there are actually 3 values a square can take. These are represented by the following `#define`'d integers:
* `#define VISIBLE_SAFE 0`: this represents a square that has been revealed.
* `#define HIDDEN_SAFE 1`: this represents a square that has not been revealed but does not contain a mine.
* `#define HIDDEN_MINE 2`: this represents a square that has not been revealed and contains a mine.

When the program is started, all of the squares should be `HIDDEN_SAFE`. The minefield is then populated with mines (i.e., `HIDDEN_MINE`) by scanning the locations of the mines.

The revealing command:
* `REVEAL_CROSS`: reveal the selected square, for each of the four directly connected squares, only reveal if they have no mines adjacent. This could result in the program revealing anything from 1 - 5 squares.

The game ends when either:
* The game is won: All of the squares are revealed except for those containing mines.
* The game is lost: A user attempts to reveal a square containing a mine.

### How to play?
Minesweeper first prompts the user to enter the location of mines on the minefield, and place them on the board. Then it allows the user to check the number of mines in a location, and reveal spaces on the minefield until the end of the game.

The program will be given commands as a series of integers on standard input. The program will scan in these integers and then make the necessary changes in the minefield.

### Input Commands
The program first asks for the number of mines as an integer. Then, the program will scan the locations of the mines as pairs of integers in the format: row column

After specifying the location of the mines, each command given to the program will be a series of integers. These input commands continue to be read and executed until the game is won, lost, or when there is an EOF (Ctrl + D)

The first input will always be an integer representing the type of command, e.g. 1 means How many mines in a row?

Depending on what command the first integer specifies, scan in some number of "arguments" (additional integers) that have a specific meaning for that command.

For example, 1 5 2 5 asks for how many mines in row 5, from column 2 to 6 inclusive, checking along 5 columns in total.

Input to the program will be via standard input (e.g. typing into the terminal).

## Example
![](https://i.imgur.com/zPjv7xZ.gif)

## Acknowledgements
Project specification from - UNSW COMP1511.

## Contributions
Contributions are always welcome!  
Just make a [pull request](../../pulls).


## Licence
MIT license

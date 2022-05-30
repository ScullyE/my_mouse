# My_Mouse
***

## Task
The objective of my_mouse was to create a program for finding the solution, if any exists, for an ASCII text maze.

## Description
My_mouse uses a breadth first search to find the shortest route through the maze, with some error checking to ensure the map is valid, as well as a response if the maze is unsolvable.

## Installation
To install, simply navigate to the root folder and execute Make in your command line.

## Usage
To use my_mouse, you must provide a valid map file. A valid map file:

- Has a first line that only contains information about the map, with the map itself found on the remaining lines.
- The first line should start with the maps correct size (i.e `100x100`), then, in order, the character used for the walls of the maze, for the navigatible areas of the map, for the resulting path in the solution, for the entrance, and for the exit.
- Each line of map itself should end with newline characters.

Here is an example of a valid map:

```
10x10* o12
***1******
*   **   *
* **** * *
*      * *
******** *
*     *  *
*  *     *
**  ******
*      * *
*****2****
```

To find the solution for a file, run `./my_mouse` followed by the path to the desired map, i.e:

```
./my_mouse maps/mapfile.txt
```

### The Core Team


<span><i>Made by Ethan Scully at <a href='https://qwasar.io'>Qwasar Silicon Valley</a></i></span> <span><img alt='Qwasar Silicon Valley Logo' src='https://storage.googleapis.com/qwasar-public/qwasar-logo_50x50.png' width='20px'></span>

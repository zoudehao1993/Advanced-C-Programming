#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include "solver.h"
#include "mazehelper.h"
#include "path.h"
#include "list.h"

PathLL * solveMaze(Maze * m) {
	
	PathLL * successPaths = buildPaths();
	char * retval = malloc(((m->height * m->width) + 1) * sizeof(char));

	MazePos mp = {.xpos = m->start.xpos, .ypos = m->start.ypos};
	depthFirstSolve(m, mp, retval, 0, successPaths);
	
	free(retval);
	
	return successPaths;
}

void depthFirstSolve(Maze * m, MazePos curpos, char * path, int step, PathLL * successPaths) {
    int i = 0;
    MazePos beforemove;
    MazePos aftermove;
    //FOR LOOP (N -> S -> E -> W)
    for( i = 0; i < 4; i++){
        beforemove.ypos = curpos.ypos;
        beforemove.xpos = curpos.xpos;
        //NORTH
        if( i == 0 ){
            aftermove.ypos = curpos.ypos - 1;
            aftermove.xpos = curpos.xpos;
            if( aftermove.ypos >= 0 ){
                curpos.ypos--;
            }
        }
        //SOUTH
        else if( i == 1 ){
            aftermove.ypos = curpos.ypos + 1;
            aftermove.xpos = curpos.xpos;
            if( aftermove.ypos <= (m->height - 1) ){
                curpos.ypos++;
            }
        }
        //EAST
        else if( i == 2 ){
            aftermove.xpos = curpos.xpos + 1;
            aftermove.ypos = curpos.ypos;
            if( aftermove.xpos <= (m->width - 1) ){
                curpos.xpos++;
            }
        }
        //WEST
        else{
            aftermove.xpos = curpos.xpos - 1;
            aftermove.ypos = curpos.ypos;
            if( aftermove.xpos >= 0 ){
                curpos.xpos--;
            }
        }
        //IF MOVED POSITION IS OUT OF BOUND SKIP CHECK AND MOVE ONE TO NEXT DIRECTION
        if( curpos.ypos != aftermove.ypos || curpos.xpos != aftermove.xpos ){
        }
        //VISITED CHECK
        else if( m->maze[curpos.ypos][curpos.xpos].visited == true ){
			curpos.ypos = beforemove.ypos;
            curpos.xpos = beforemove.xpos;
        }
        //SPACE CHECK
        else if( m->maze[curpos.ypos][curpos.xpos].type == SPACE ){
            m->maze[beforemove.ypos][beforemove.xpos].visited = true;
            switch(i){
                case 0: path[step] = 'n';
                        break;
                case 1: path[step] = 's';
                        break;
                case 2: path[step] = 'e';
                        break;
                case 3: path[step] = 'w';
                        break;
            }
            step++;
            depthFirstSolve(m, curpos, path, step, successPaths);
            m->maze[curpos.ypos][curpos.xpos].visited = false;
			curpos.ypos = beforemove.ypos;
            curpos.xpos = beforemove.xpos;
			step--;
        }
        //END CHECK
        else if( m->maze[curpos.ypos][curpos.xpos].type == END ){
            m->maze[beforemove.ypos][beforemove.xpos].visited = true;
            switch(i){
                case 0: path[step] = 'n';
                        break;
                case 1: path[step] = 's';
                        break;
                case 2: path[step] = 'e';
                        break;
                case 3: path[step] = 'w';
                        break;
            }
            path[step + 1] = '\0';
            addNode(successPaths, path);
			curpos.ypos = beforemove.ypos;
			curpos.xpos = beforemove.xpos;
		}
        //WALL CHECK
        else if( m->maze[curpos.ypos][curpos.xpos].type == WALL ){
            m->maze[curpos.ypos][curpos.xpos].visited = true;
            curpos.ypos = beforemove.ypos;
            curpos.xpos = beforemove.xpos;
        }
        //
        //else{
            //return false;
        //}
    }
    //return false;	
	//Fill in. (Your best bet is to modify a working implementation from PA08)
}

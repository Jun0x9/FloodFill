#include <raylib.h> 

#define ROWS 32  
#define COLS 32 
#define CELL_SIZE 32
#define EMPTY 0 
#define FILLED 1 
#define OBSTACLE 2 

const int WINDOW_W  = COLS * CELL_SIZE ; 
const int WINDOW_H  = ROWS * CELL_SIZE ; 

int cells [ ROWS ][ COLS ] ; 

void emptyCells ( ) ;
void renderCells( ) ; 
void floodFill  ( int , int ) ; 

int main( void ){ 
	InitWindow( WINDOW_W, WINDOW_H, "FLoodFill") ; 
	SetTargetFPS( 30 ); 

	Vector2 mouse_pos ; 
	int row, col ; 
	while( !WindowShouldClose () ){ 
		mouse_pos = ( Vector2 ) GetMousePosition( ) ; 
		row = (int)(mouse_pos.y / CELL_SIZE ); 
		col = (int)(mouse_pos.x / CELL_SIZE) ; 

		if( IsMouseButtonPressed( MOUSE_LEFT_BUTTON ) ) {
			if( cells[ row ] [ col ] == EMPTY ){
				floodFill( col, row ); 	
			}
		}
		else if( IsMouseButtonPressed( MOUSE_RIGHT_BUTTON )) { 
			if( cells[ row ][ col ] == OBSTACLE)
				cells[ row ][ col ] = EMPTY;
			else
				cells[ row ][ col ] = OBSTACLE;
		}
		
		BeginDrawing () ; 
			
			ClearBackground( BLACK ); 
			renderCells() ; 
		EndDrawing () ; 
	}
	CloseWindow() ; 
	return 0; 

}


void renderCells( ) { 
	for(int i = 0; i < ROWS; i ++)  	
		for( int j = 0; j < COLS ; j++){ 
			if( cells [ i ][ j ] == FILLED ){ 
				DrawRectangle( j * CELL_SIZE, i * CELL_SIZE, CELL_SIZE, CELL_SIZE, GREEN) ;
			}
			if( cells [ i ][ j ] == OBSTACLE){ 
				DrawRectangle( j * CELL_SIZE , i * CELL_SIZE, CELL_SIZE, CELL_SIZE, RED) ;
			}
	}		
	for(int i = 0; i < ROWS; i ++) { 	
		DrawLine( 0, i * CELL_SIZE, WINDOW_W, i * CELL_SIZE, WHITE); 
		DrawLine( i * CELL_SIZE, 0, i * CELL_SIZE, WINDOW_H , WHITE); 

	}

	return ; 
}


void floodFill  ( int x, int y) { 
	//base cases 
	if( x < 0 || x >= COLS ) return ; 
	if( y < 0 || y >= ROWS ) return ; 

	if( cells[ y ][ x ] == OBSTACLE ) return ; 
	if( cells[ y ][ x ] == FILLED ) return ; 
	cells[ y ][ x ] = FILLED; 	

	floodFill( x - 1, y) ; 
	floodFill( x + 1, y) ; 
	floodFill( x , y + 1 ) ; 
	floodFill( x , y - 1) ; 
	return  ; 
}

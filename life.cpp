
#include <stdlib.h>
#include "life.h"


  // a few macros and stuff to define our field...
  #define FIELD_WIDTH     23      /* field width, in characters */
  #define FIELD_HEIGHT    23      /* field height, in characters */
  #define EMPTY_CHAR      " "     /* character used for empty spaces on the grid. */
  #define CELL_CHAR       "O"     /* character used for occupied spaces on the grid. */
  #define NUM_CELLS       ( (FIELD_WIDTH * FIELD_HEIGHT) / 2 )  /* the amount of randomly placed cells to start with */


  void displayField( LifeField *fieldobj ){
    for( unsigned long int drawfieldloop = 0; drawfieldloop < (fieldobj->fieldWidth * fieldobj->fieldHeight); drawfieldloop++ ){

      if( drawfieldloop%fieldobj->fieldWidth ){
        if( *(unsigned char*)( fieldobj->fieldPtr + drawfieldloop ) )   printf( CELL_CHAR );    else printf( EMPTY_CHAR );

      } else printf( "\n" );
    }
    printf( "\n" );   // just for formatting...
  }



  LifeField *fieldObj;  // our global playing field object...

  int main( int argc, char** argv ){

    char *dummystr;
    fieldObj = new LifeField( FIELD_WIDTH, FIELD_HEIGHT );
    
    fieldObj->randomizeField( NUM_CELLS );

    do {
      displayField( fieldObj );
      fieldObj->processField();
      fieldObj->updateField();


      gets( dummystr ); // "Press Any Key to Continue..."

    } while( *dummystr == *(char*)"" );

    return 0;
  }

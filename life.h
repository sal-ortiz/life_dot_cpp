/* 
 * File:   lifeobjects.hpp
 * Author: salvador
 *
 * Created on July 6, 2011, 10:44 AM
 */

#ifndef _LIFEOBJECTS_HPP_
  #define	_LIFEOBJECTS_HPP_

  #include <stdio.h>      // printf...gets...
  #include <string.h>     // memset...
  #include <stdlib.h>     // rand...
  #include <time.h>       // time...


  class LifeField {

    public:
    unsigned char *fieldPtr;  // a pointer to our actual field's data.
    unsigned long int fieldWidth;
    unsigned long int fieldHeight;

    // constructicons form DEVASTATOR...
    LifeField(){   /* intentionally left blank */  }
    LifeField( unsigned long int field_width, unsigned long int field_height ){
      fieldWidth = field_width;   fieldHeight = field_height
      initField( field_width * field_height );
    }

    // ...the most powerful Decepticon!
    ~LifeField(){  deinitField();  }
    // -------------------------------------------------------------------------

    void initField( unsigned long int field_size ){
      fieldPtr = new unsigned char [field_size];  // init the field...
      memset( fieldPtr, field_size, 0x00 );         // ...and clear it.
    }

    void deinitField(){
    	delete fieldPtr;
    }

    void randomizeField( unsigned long int numcells ){
      srand( time( NULL ) );

      unsigned char *memptr;   // avoid redundancy in thr following do loop.
      do {
        memptr = ( fieldPtr + ( ((rand() % fieldHeight) * fieldWidth) + (rand() % fieldWidth) ) );
        if( *memptr ) numcells++; // there is a cell here so this round is repeated.
        else *memptr = 1;
      } while( numcells-- );
    }

    unsigned char numNeighbors( unsigned long int current_cell_pos ){   // TODO: This algorithm *might* be broken, fix it!
      unsigned char retval = 0;                 // the number of live cells counted.
      unsigned int cell_x_pos, cell_y_pos;      // store our center cell's position.
      signed int cell_neighbor_x_modifier, cell_neighbor_y_modifier;  // help us find our neighbor cells.


      // Peep this bizarre algorithm:
      //  * we loop from 0 to 8
      //  * the loop index is converted into x and y modifiers between -1 and +1 each.
      //  * the modifiers are applied to the center cell's position.
      // The algorithm is similar to that used to convert linear framebuffer indexes to and from x and y coordinates.
      for( unsigned char count_neighbors_loop_index=0; count_neighbors_loop_index < 9; count_neighbors_loop_index++ ){
        cell_x_pos = (unsigned int)current_cell_pos % fieldWidth;                // the x coordinate of our center cell.
        cell_neighbor_x_modifier = (signed int)(count_neighbors_loop_index%3)-1;   // a modifier to adjust the above x position to convert it to those of our neighbors.
        cell_y_pos = (unsigned int)current_cell_pos / fieldWidth;                // the y coordinate or our center cell.
        cell_neighbor_y_modifier = (signed int)(count_neighbors_loop_index/3)-1;   // a modifier to adjust the above y position to convert it to those of our neighbors.

        switch( *(unsigned char *)(fieldPtr + ( (( (cell_y_pos + cell_neighbor_y_modifier) % fieldHeight ) * fieldWidth) + ( (cell_x_pos + cell_neighbor_x_modifier) % fieldWidth ) )) ){
          case 1: /* the cell is currently alive, but will be dead tomorrow...or it's alive and hasn't been processed yet. */
          case 2: /* the cell is currently alive. */
            retval++;   break;
        }
      }
      return retval-1;    // our algorithm will count our current cell as it's own neighbor...
    }

    unsigned char numNeighbors( unsigned long int cell_x_pos, unsigned long int cell_y_pos ){
      numNeighbors( (cell_y_pos * fieldWidth) + cell_x_pos );
    }

    void processField(){
      for( unsigned long int processfieldloop = 0; processfieldloop < (fieldWidth * fieldHeight); processfieldloop++ ){
        if( *(unsigned char*) (fieldPtr + processfieldloop) ){
          if( ((numNeighbors(processfieldloop)==2) || (numNeighbors(processfieldloop)==3)) )  *(unsigned char *)(fieldPtr+processfieldloop)=2;    // stays alive...
          //else *(unsigned char*)( fieldPtr + processfieldloop ) = 1;   // will die...
        } else {
          if( ((numNeighbors(processfieldloop)==2) || (numNeighbors(processfieldloop)==3)) )  *(unsigned char *)(fieldPtr+processfieldloop)=3;    // will become alive...
          //else *(unsigned char*)( fieldPtr + processfieldloop ) = 0;   // stays dead...
        }
      }
    }

    void updateField(){
      for( unsigned long int updatefieldloop = 0; updatefieldloop < (fieldWidth*fieldHeight); *(unsigned char*)(fieldPtr + updatefieldloop++) /= 2 );
    }

  };  // class LifeField



#endif	/* _LIFEOBJECTS_HPP_ */


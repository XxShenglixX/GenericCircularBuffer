#include "CircularBuffer.h"
#include <stdio.h>
#include <malloc.h>
#include "CException.h"

/* void dummy()
{
	int integer ; //static allocation
	int *ptr2integer ;
	
	ptr2integer = malloc(sizeof(int)); //dynamic allocation
	
	free(ptr2integer); // free the memory
}
 */
 
/* Initialise the circular buffer
 *
 * Input :
 *	length is the total number of item allowable in the buffer
 *	sizeOfType is the size of the object
 */
 
CircularBuffer *circularBufferNew(int length,int sizeOfType)
{
	CircularBuffer *circularBuffer;
	
	circularBuffer = malloc(sizeof(CircularBuffer));
	circularBuffer->buffer = malloc(sizeOfType * length);
	circularBuffer->length = length;
	circularBuffer->size = 0;
	circularBuffer->sizeOfType = sizeOfType;
	circularBuffer->head = circularBuffer->buffer ;
	circularBuffer->tail = circularBuffer->buffer ;
	
	return circularBuffer;
}

/* Free the memory
 * 
 */
void circularBufferDelete(CircularBuffer *circularBuffer)
{
	free(circularBuffer);
}

void circularBufferAdd(
						CircularBuffer *cb,
						void *obj,
						void (*copy)(void *,void *)
					   )
{
	if (circularBufferIsFull(cb))
		Throw (ERR_BUFFER_IS_FULL);
	
	cb->head = cb->buffer ; //reset head to buffer
	cb->head += (cb->size * cb->sizeOfType) ;// move head to the first encountered available location
	
	copy(cb->head,obj);
	cb->size++;
	cb->head += cb->sizeOfType;
	if (cb->size > 1)
		cb->tail = (cb->head - cb->sizeOfType); // tail is 1 step behind of head
}				


void circularBufferRemove(
						CircularBuffer *cb,
						void *obj,
						void (*copy)(void *,void *)
					   )
{
	if (circularBufferIsEmpty(cb))
		Throw (ERR_BUFFER_IS_EMPTY);
	

	copy(obj,cb->tail);
	cb->size -- ;
	cb->tail -= cb->sizeOfType ;

}
		

int circularBufferIsEmpty(CircularBuffer *circularBuffer)
{
	if (circularBuffer->size <=0 )
		return 1 ;
	else 
		return 0 ;
}

int circularBufferIsFull(CircularBuffer *circularBuffer)
{
	if (circularBuffer->size >= circularBuffer->length )
		return 1 ;
	else 
		return 0 ;
}		

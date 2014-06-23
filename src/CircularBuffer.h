#ifndef CircularBuffer_H
#define CircularBuffer_H

typedef enum {ERR_NO_ERROR,
			  ERR_BUFFER_IS_FULL,
			  ERR_BUFFER_IS_EMPTY
			 } ErrorCode;

typedef struct
{
	void *head;
	void *tail;
	int size;		//current number of item in the buffer
	int sizeOfType;
	int length;		//total number of item allowable in the buffer
	void *buffer;
}CircularBuffer;



CircularBuffer *circularBufferNew(int length,int sizeOfType);
void circularBufferDelete(CircularBuffer *circularBuffer);

void circularBufferAdd(
						CircularBuffer *cb,
						void *obj,
						void (*copy)(void *,void *)
					   );


void circularBufferRemove(
							CircularBuffer *cb,
							void *obj,
							void (*copy)(void *,void *)
						  );

int circularBufferIsEmpty(CircularBuffer *circularBuffer);
int circularBufferIsFull(CircularBuffer *circularBuffer);
#endif // CircularBuffer_H

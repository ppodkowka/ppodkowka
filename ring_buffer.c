/* Includes ------------------------------------------------------------------*/
#include <assert.h>
#include "ring_buffer.h"


bool RingBuffer_Init(RingBuffer *ringBuffer, char *dataBuffer, size_t dataBufferSize) 
{
	assert(ringBuffer);
	assert(dataBuffer);
	assert(dataBufferSize > 0);
	
	if ((ringBuffer) && (dataBuffer) && (dataBufferSize > 0)) {
	  //TODO
	  ringBuffer->head=0;
	  ringBuffer->tail=0;
	  ringBuffer->length=0;
	  ringBuffer->size=dataBufferSize;
	  ringBuffer->data=dataBuffer;
	  return true;
	}
	
	return false;
}

bool RingBuffer_Clear(RingBuffer *ringBuffer)
{
	assert(ringBuffer);
	
	if (ringBuffer) {
		//TODO
		for(uint16_t i=0; i<ringBuffer->size;i++){
		    ringBuffer->data[i]=0;
		}
		ringBuffer->head=0;
		ringBuffer->tail=0;
		ringBuffer->length=0;
		return true;
	}
	return false;
}

bool RingBuffer_IsEmpty(const RingBuffer *ringBuffer)
{
  assert(ringBuffer);	
	//TODO
	if(ringBuffer->length!=0){
	    return false;
	}
	
	return true;
}

size_t RingBuffer_GetLen(const RingBuffer *ringBuffer)
{
	assert(ringBuffer);
	
	if (ringBuffer) {
		// TODO
		return ringBuffer->length;
	}
	return 0;
	
}

size_t RingBuffer_GetCapacity(const RingBuffer *ringBuffer)
{
	assert(ringBuffer);
	
	if (ringBuffer) {
		// TODO
		return ringBuffer->size;
	}
	return 0;	
}


bool RingBuffer_PutChar(RingBuffer *ringBuffer, char c)
{
	assert(ringBuffer);
	
	if (ringBuffer) {
		//TODO
		if(ringBuffer->size==ringBuffer->length){
		    return false;
		}
		ringBuffer->data[ringBuffer->head]=c;
		ringBuffer->length++;
		ringBuffer->head++;
		
        if(ringBuffer->head>=ringBuffer->size){
		    ringBuffer->head=0;
		}
		
		return true;
	}
	return false;
}

bool RingBuffer_GetChar(RingBuffer *ringBuffer, char *c)
{
	assert(ringBuffer);
	assert(c);
	
  if ((ringBuffer) && (c)) {
		//TODO
		if(ringBuffer->length==0){
		    return false;
		}
		*c = ringBuffer->data[ringBuffer->tail];
		ringBuffer->tail++;
		ringBuffer->length--;
		if(ringBuffer->tail>=ringBuffer->size){
		    ringBuffer->tail=0;
		}
		return true;
	}
	return false;
}

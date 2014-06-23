#include "unity.h"
#include "CircularBuffer.h"
#include "CException.h"
#include "Integer.h"
#include "Double.c"
#include <stdio.h>

void setUp(void)
{
}

void tearDown(void)
{
}

void test_circularBufferNew_should_create_new_circularBuffer_object_of_integer_type()
{
	CircularBuffer *cb = circularBufferNew(7,sizeof(int));
	
	TEST_ASSERT_NOT_NULL(cb);
	TEST_ASSERT_NOT_NULL(cb->buffer);
	TEST_ASSERT_EQUAL(7,cb->length);
	TEST_ASSERT_EQUAL(0,cb->size);
	TEST_ASSERT_EQUAL(cb->sizeOfType,(sizeof(int)));
	TEST_ASSERT_EQUAL_PTR(cb->buffer,cb->head);
	TEST_ASSERT_EQUAL_PTR(cb->buffer,cb->tail);

	
	circularBufferDelete(cb);
}

void test_circularBufferNew_should_create_new_circularBuffer_object_of_double_type()
{
	CircularBuffer *cb = circularBufferNew(13,sizeof(double));
	
	TEST_ASSERT_NOT_NULL(cb);
	TEST_ASSERT_NOT_NULL(cb->buffer);
	TEST_ASSERT_EQUAL(13,cb->length);
	TEST_ASSERT_EQUAL(0,cb->size);
	TEST_ASSERT_EQUAL(cb->sizeOfType,(sizeof(double)));
	TEST_ASSERT_EQUAL_PTR(cb->buffer,cb->head);
	TEST_ASSERT_EQUAL_PTR(cb->buffer,cb->tail);
	
	circularBufferDelete(cb);
}

void test_circularBufferIsEmpty_should_return_1_for_empty_buffer()
{
	CircularBuffer *cb = circularBufferNew(7,sizeof(int));
	TEST_ASSERT_EQUAL(1,circularBufferIsEmpty(cb));
	circularBufferDelete(cb);
}

void test_circularBufferIsFull_should_return_1_for_full_buffer()
{
	CircularBuffer *cb = circularBufferNew(7,sizeof(int));
	cb->size = 7;
	TEST_ASSERT_EQUAL(1,circularBufferIsFull(cb));
	circularBufferDelete(cb);
}

void test_circularBufferAddInt_given_1_should_add_1_to_the_buffer()
{
	CircularBuffer *cb = circularBufferNew(7,sizeof(int));
	int data[] = {1};
	circularBufferAdd(cb,&data[0],&copyInt);
	
	TEST_ASSERT_EQUAL(1,*(int*)cb->buffer);
	TEST_ASSERT_EQUAL(1,cb->size);
	
	circularBufferDelete(cb);
}

void test_circularBufferAddInt_given_11_12_13_14_should_add_11_12_13_14_to_the_buffer()
{
	CEXCEPTION_T err;
	CircularBuffer *cb = circularBufferNew(7,sizeof(int));
	int data[] = {11,12,13,14};
	Try
	{
		circularBufferAdd(cb,&data[0],&copyInt);
		circularBufferAdd(cb,&data[1],&copyInt);
		circularBufferAdd(cb,&data[2],&copyInt);
		circularBufferAdd(cb,&data[3],&copyInt);
	}
	Catch(err)
	{
		TEST_FAIL_MESSAGE("Do not expect error to be generated");	
	}
	TEST_ASSERT_EQUAL(11,*(int*)cb->buffer);
	TEST_ASSERT_EQUAL(12,*(int*)cb->buffer+1);
	TEST_ASSERT_EQUAL(13,*(int*)cb->buffer+2);
	TEST_ASSERT_EQUAL(14,*(int*)cb->tail);
	TEST_ASSERT_EQUAL(4,cb->size);
	
	circularBufferDelete(cb);
}

void test_circularBufferAddInt_given_21_to_28_should_add_21_to_27_to_the_buffer_and_throw_err()
{
	CEXCEPTION_T err;
	CircularBuffer *cb = circularBufferNew(7,sizeof(int));
	int data[] = {21,22,23,24,25,26,27,28};
	
	Try
	{
		circularBufferAdd(cb,&data[0],&copyInt);
		circularBufferAdd(cb,&data[1],&copyInt);
		circularBufferAdd(cb,&data[2],&copyInt);
		circularBufferAdd(cb,&data[3],&copyInt);
		circularBufferAdd(cb,&data[4],&copyInt);
		circularBufferAdd(cb,&data[5],&copyInt);
		circularBufferAdd(cb,&data[6],&copyInt);
		circularBufferAdd(cb,&data[7],&copyInt);
		TEST_FAIL_MESSAGE("Should generate an exception due to full buffer.");
	}
	Catch(err)
	{
		TEST_ASSERT_EQUAL(ERR_BUFFER_IS_FULL,err);
		printf("Error [%d] : Buffer is full",err);
	}
	
	
	TEST_ASSERT_EQUAL(21,*(int*)cb->buffer);
	TEST_ASSERT_EQUAL(22,*(int*)cb->buffer+1);
	TEST_ASSERT_EQUAL(23,*(int*)cb->buffer+2);
	TEST_ASSERT_EQUAL(24,*(int*)cb->buffer+3);
	TEST_ASSERT_EQUAL(25,*(int*)cb->buffer+4);
	TEST_ASSERT_EQUAL(26,*(int*)cb->buffer+5);
	TEST_ASSERT_EQUAL(27,*(int*)cb->tail);

	TEST_ASSERT_EQUAL(7,cb->size);
	circularBufferDelete(cb);
}

void test_circularBufferRemoveInt_x1_given_31_32_33_should_return_33_and_size_2()
{
	CEXCEPTION_T err;
	CircularBuffer *cb = circularBufferNew(7,sizeof(int));
	int data[] = {31,32,33};
	int *result ;
	
	Try
	{
		circularBufferAdd(cb,&data[0],&copyInt);
		circularBufferAdd(cb,&data[1],&copyInt);
		circularBufferAdd(cb,&data[2],&copyInt);
	
	
		circularBufferRemove(cb,&result,&copyInt);
	}
	Catch(err)
	{
		TEST_FAIL_MESSAGE("Do not expect error to be generated");	
	}
	
	TEST_ASSERT_EQUAL(33,result);
	TEST_ASSERT_EQUAL(2,cb->size);
	circularBufferDelete(cb);
}

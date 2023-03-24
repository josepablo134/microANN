#include "uANN.h"
#include "uHeap.h"
#include <math.h>

/// Sigmoid function, also called logistic function
uANN_data sigmoid( uANN_data a ){
	uANN_data temp = exp( -1.0f * a );
	temp = 1.0f + temp;
	return (1.0f)/temp;
}


typedef enum uANN_activation_ids{
	uANN_sigmoid=0u,
	uANN_num_functions,
} uANN_activation_ids;
/// Table size
const uANN_size uANN_activation_function_table_size=uANN_num_functions;
/// Table of activation function callbacks
const uANN_activation_callback uANN_activation_function_table[] = {
	sigmoid,
};

const uANN_activation_id uANN_default_activation_function_id=uANN_sigmoid;

/// Heap bytes array
#define	ANN_HEAP_MAX_SIZE		1024u
static unsigned char ann_uheap_buffer[ ANN_HEAP_MAX_SIZE ];
/// Heap manager object
static struct uheap* ann_uheap;

int uANN_hook_init( void ){
	ann_uheap = uheap_init( ann_uheap_buffer , ANN_HEAP_MAX_SIZE );
	if( !ann_uheap ){ return -1; }
	return 0;
}

unsigned char* uANN_hook_malloc( uANN_size size ){
		return uheap_malloc( ann_uheap, size );
}


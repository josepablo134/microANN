/*!
*	@file		uANN.c
*	@version	0.0
*	@author		Josepablo Cruz Baas
*	@date		09/07/2020
*	@brief		micro Artificial Neural Network library definitions.
**/
#include "uANN.h"
#include "uANN_config.h"
#include "uHeap.h"

#include <math.h>

#define umalloc( SIZE ) uheap_malloc( ann_uheap , SIZE )

/// Dummy activation function that returns the input
float dummy( float a ){
	return a;//+1.0f;
}

/// Sigmoid function, also called logistic function
float sigmoid( float a ){
	float temp = exp( -1.0f * a );
	temp = 1.0f + temp;
	return (1.0f)/temp;
}

/// Table of activation function callbacks
static ann_activation activation_cb_table[ ann_total_activation_functions ] = {
	sigmoid,
	dummy
};

/// Heap bytes array
static unsigned char ann_uheap_buffer[ ANN_HEAP_MAX_SIZE ];

/// Heap manager object
static struct uheap* ann_uheap;

/// Initialize and clear ann driver
int ann_init( void ){
	ann_uheap = uheap_init( ann_uheap_buffer , ANN_HEAP_MAX_SIZE );
	if( !ann_uheap ){ return -1; }
	return 0;
}

/// Create new ann_net structure
struct ann_net* ann_net_create(){
	struct ann_net* temp= (struct ann_net*) umalloc( sizeof( struct ann_layer ) );
	ann_net_init( temp );
	return temp;
}

/// Initialize and clear ann_net structure
void ann_net_init( struct ann_net* ann ){
	if( !ann ){ return; }
	ann->input = 0x00;
	ann->output = 0x00;
	ann->layers = 0;
}

/// Create new ann_layer structure
struct ann_layer* ann_layer_create(){
	struct ann_layer*	temp = (struct ann_layer*) umalloc( sizeof(struct ann_layer) );
	ann_layer_init( temp );
	return temp;
}

/// Initialize and clear ann_layer structure
void ann_layer_init( struct ann_layer* ann_layer){
	if( !ann_layer ){ return; }
	ann_layer->_inputHolder = 0x00;
	ann_layer->_outputHolder = 0x00;
	ann_layer->_weightHolder = 0x00;
	ann_layer->_biasHolder = 0x00;
	ann_layer->_next = 0x00;
	
	ann_layer->activation = ann_sigmoid;
	ann_layer->inputLen = 0;
	ann_layer->neurons = 0;
}

/// Connect a new layer with the last layer.
int ann_net_push( struct ann_net* ann , struct ann_layer* layer ){
	if( !ann ){ return -1; }
	if( !layer ){ return -1; }
	
	layer->_next = 0x00;

	if( ann->output == 0x00 ){
		ann->input = ann->output = layer;
	}else{
		if( ann->output->neurons != layer->inputLen ){
			/// Incompatible dimension link!
			return -1;
		}
		ann->output->_next = layer;
		ann->output = layer;
	}
	ann->layers++;
	return 0;
}

/// Disconnect the very last layer.
struct ann_layer* ann_net_pop( struct ann_net* ann ){
	struct ann_layer* lastLayer = 0x00;
	struct ann_layer* layerActual = ann->input;

	while( layerActual != ann->output ){
		lastLayer = layerActual;
		layerActual = layerActual->_next;
	}

	ann->output = lastLayer;

	ann->layers = (ann->layers)? ann->layers-1 : 0 ;

	return layerActual;
}

/// Allocate memory for every layer data holder.
int ann_alloc( struct ann_net* ann ){
	if( !ann ){ return -1; }
	if( !ann->layers ){ return -1; }

	unsigned int	localSize=0;

	struct ann_layer*	lastLayer = 0x00;
	struct ann_layer*	temp = ann->input;
		/// Input holders + Weight holders + Bias holders + Output holders
		localSize = temp->inputLen + ( temp->inputLen * temp->neurons ) + temp->neurons + temp->neurons ;

		float*	holders = (float*) umalloc( sizeof( float ) * localSize );
		if( !holders ){ return -1; }

		temp->_inputHolder = holders;

		temp->_weightHolder = holders + temp->inputLen;
		temp->_biasHolder = temp->_weightHolder + (temp->inputLen * temp->neurons);

		localSize -= temp->neurons;
		temp->_outputHolder = holders + localSize;

		lastLayer = temp;
		temp = temp->_next;
	while( temp ){
		/// Weight holders + Bias holders + Output holders
		//	in this case input holders are last layer output holders
		localSize = ( temp->inputLen * temp->neurons ) + temp->neurons + temp->neurons ;

		float*	holders = (float*) umalloc( sizeof( float ) * localSize );
		if( !holders ){ return -1; }

		//	This holder is the same as the last layer output holder
		temp->_inputHolder = lastLayer->_outputHolder;

		temp->_weightHolder = holders;
		temp->_biasHolder = holders + (temp->inputLen * temp->neurons);
	
		localSize -= temp->neurons;
		temp->_outputHolder = holders + localSize;

		lastLayer = temp;
		temp = temp->_next;
	}
	return 0;
}

/// Vector dot product
static float vdot( float *vectA , float *vectB , unsigned int length ){
	unsigned int counter;
	float output=0.0;
	for( counter=0; counter<length; counter++ ){
		output += vectA[counter] * vectB[counter];
	}
	return output;
}

/// Propagate input data in the input layer through the ann.
int ann_compute( struct ann_net* ann ){
	if( !ann ){ return -1; }
	struct ann_layer*	temp = ann->input;
	unsigned int	neuronCounter;
	unsigned int	weightCounter;

	while( temp ){
		weightCounter= temp->inputLen;
		for( neuronCounter=0; neuronCounter< temp->neurons; neuronCounter++ ){
			/// activation( <input,weight> + bias )
			temp->_outputHolder[ neuronCounter ] =
				activation_cb_table[ temp->activation ](
					vdot( temp->_inputHolder ,\
					&(temp->_weightHolder[ (weightCounter)*neuronCounter ]),\
					temp->inputLen ) +
					\
					temp->_biasHolder[ neuronCounter ]
				);
		}
		temp = temp->_next;
	}

	return 0;
}

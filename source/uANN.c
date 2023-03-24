/*!
*	@file		uANN.c
*	@version	1.0.0
*	@author		Josepablo Cruz Baas
*	@date		23/03/2023
*	@brief		micro Artificial Neural Network library definitions.
**/

#include "uANN.h"

#define umalloc( SIZE ) uANN_hook_malloc( SIZE )

/// Initialize and clear uANN driver
int uANN_init( void ){
	return uANN_hook_init();
}

/// Create new uANN_net structure
uANN_net* uANN_create(){
	uANN_net* temp= (struct uANN_net*) umalloc( sizeof( struct uANN_layer ) );
	uANN_net_init( temp );
	return temp;
}

/// Initialize and clear uANN_net structure
void uANN_net_init( uANN_net* uANN ){
	if( !uANN ){ return; }
	uANN->input = 0x00;
	uANN->output = 0x00;
	uANN->layers = 0;
}

/// Create new uANN_layer structure
uANN_layer* uANN_layer_create(){
	uANN_layer*	temp = (struct uANN_layer*) umalloc( sizeof(struct uANN_layer) );
	uANN_layer_init( temp );
	return temp;
}

/// Initialize and clear uANN_layer structure
void uANN_layer_init( uANN_layer* uANN_layer){
	if( !uANN_layer ){ return; }
	uANN_layer->_inputHolder = 0x00;
	uANN_layer->_outputHolder = 0x00;
	uANN_layer->_weightHolder = 0x00;
	uANN_layer->_biasHolder = 0x00;
	uANN_layer->_next = 0x00;
	
	uANN_layer->activation = uANN_default_activation_function_id;
	uANN_layer->inputLen = 0;
	uANN_layer->neurons = 0;
}

/// Connect a new layer with the last layer.
int uANN_push( uANN_net* uANN , struct uANN_layer* layer ){
	if( !uANN ){ return -1; }
	if( !layer ){ return -1; }
	
	layer->_next = 0x00;

	if( uANN->output == 0x00 ){
		uANN->input = uANN->output = layer;
	}else{
		if( uANN->output->neurons != layer->inputLen ){
			/// Incompatible dimension link!
			return -1;
		}
		uANN->output->_next = layer;
		uANN->output = layer;
	}
	uANN->layers++;
	return 0;
}

/// Disconnect the very last layer.
uANN_layer* uANN_pop( struct uANN_net* uANN ){
	uANN_layer* lastLayer = 0x00;
	uANN_layer* layerActual = uANN->input;

	while( layerActual != uANN->output ){
		lastLayer = layerActual;
		layerActual = layerActual->_next;
	}

	uANN->output = lastLayer;

	uANN->layers = (uANN->layers)? uANN->layers-1 : 0 ;

	return layerActual;
}

/// Allocate memory for every layer data holder.
int uANN_alloc( uANN_net* uANN ){
	if( !uANN ){ return -1; }
	if( !uANN->layers ){ return -1; }

	uANN_size	localSize=0;

	uANN_layer*	lastLayer = 0x00;
	uANN_layer*	temp = uANN->input;
		/// Input holders + Weight holders + Bias holders + Output holders
		localSize = temp->inputLen + ( temp->inputLen * temp->neurons ) + temp->neurons + temp->neurons ;

		uANN_data*	holders = (uANN_data*) umalloc( sizeof( uANN_data ) * localSize );
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

		uANN_data*	holders = (uANN_data*) umalloc( sizeof( uANN_data ) * localSize );
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
static uANN_data vdot( uANN_data *vectA , uANN_data *vectB , uANN_len length ){
	uANN_len counter;
	uANN_data output=0.0;
	for( counter=0; counter<length; counter++ ){
		output += vectA[counter] * vectB[counter];
	}
	return output;
}

/// Propagate input data in the input layer through the uANN.
int uANN_compute( uANN_net* uANN ){
	if( !uANN ){ return -1; }
	uANN_layer*	temp = uANN->input;
	uANN_len	neuronCounter;
	uANN_len	weightCounter;

	while( temp ){
		weightCounter= temp->inputLen;
		for( neuronCounter=0; neuronCounter< temp->neurons; neuronCounter++ ){
			/// activation( <input,weight> + bias )
			temp->_outputHolder[ neuronCounter ] =
				uANN_activation_function_table[ temp->activation ](
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

#ifndef _UANN_H_
#define _UANN_H_

#ifdef __cplusplus
	extern "C" {
#endif
	
	#include <stdint.h>

	typedef enum ann_activation_id{
		ann_sigmoid=0,
		ann_dummy,
		ann_total_activation_functions
	}ann_activation_id;
	
	struct ann_layer{
		unsigned int		inputLen;	/// Input length for this layer
		unsigned int		neurons;	/// Number of neurons
		ann_activation_id	activation;	/// Activation function id
		
		struct ann_layer*	_next;			///Next layer
		float*				_inputHolder;	///Input data to process
		float*				_weightHolder;	///Weight values for this layer
		float*				_biasHolder;	///Bias values for this layer
		float*				_outputHolder;	///Output data, (Input holder for the next layer)
	};
	
	struct ann_net{
		struct ann_layer*	input;			///Input layer, the very first layer
		struct ann_layer*	output;			///Output layer, the very last layer
		unsigned int		layers;			///Layers counter
	};

	typedef float (*ann_activation)( float );

	extern int ann_init( void );/// Init and clear heap

	extern struct ann_net* ann_net_create();/// Create new ann layer structure

	extern void ann_net_init( struct ann_net* );/// Clear pointers.

	extern struct ann_layer* ann_net_pop( struct ann_net* );/// Remove very last layer
	
	extern int ann_net_push( struct ann_net* , struct ann_layer* );/// Append very last layer
	
	extern struct ann_layer* ann_layer_create();/// Create new ann layer structure.

	extern void ann_layer_init( struct ann_layer* );/// Clear pointers.

	extern int ann_alloc( struct ann_net* );/// Allocate memory for this network.

	extern int ann_compute( struct ann_net* );/// Compute a new iteration.

#ifdef __cplusplus
	}
#endif

#endif

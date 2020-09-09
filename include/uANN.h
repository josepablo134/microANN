/*!
*	@file		uANN.h
*	@version	0.0
*	@author		Josepablo Cruz Baas
*	@date		09/07/2020
*	@brief		micro Artificial Neural Network library declarations.
**/
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
		/// Input length for this layer
		unsigned int		inputLen;
		/// Number of neurons
		unsigned int		neurons;
		/// Activation function id
		ann_activation_id	activation;
		
		///Next layer
		struct ann_layer*	_next;
		///Input data to process
		float*				_inputHolder;
		///Weight values for this layer
		float*				_weightHolder;
		///Bias values for this layer
		float*				_biasHolder;
		///Output data, (Input holder for the next layer)
		float*				_outputHolder;
	};
	
	struct ann_net{
		///Input layer, the very first layer
		struct ann_layer*	input;
		///Output layer, the very last layer
		struct ann_layer*	output;
		///Layers counter
		unsigned int		layers;
	};

	/// Activation function declaration.
	typedef float (*ann_activation)( float );

	extern int ann_init( void );
	/// Create new ann layer structure
	extern struct ann_net* ann_net_create();
	/// Clear pointers.
	extern void ann_net_init( struct ann_net* );
	/// Remove very last layer
	extern struct ann_layer* ann_net_pop( struct ann_net* );
	/// Append very last layer
	extern int ann_net_push( struct ann_net* , struct ann_layer* );
	/// Create new ann layer structure.
	extern struct ann_layer* ann_layer_create();
	/// Clear pointers.
	extern void ann_layer_init( struct ann_layer* );
	/// Allocate memory for this network.
	extern int ann_alloc( struct ann_net* );
	/// Compute new iteration.
	extern int ann_compute( struct ann_net* );

#ifdef __cplusplus
	}
#endif

#endif

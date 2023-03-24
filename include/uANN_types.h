/*!
*	@file		uANN_types.h
*	@version	1.0.0
*	@author		Josepablo Cruz Baas
*	@date		23/03/2023
*	@brief		micro Artificial Neural Network library types definition.
**/
#ifndef _UANN_TYPES_H_
#define _UANN_TYPES_H_

#ifdef __cplusplus
	extern "C" {
#endif

	/*!
	 * uANN_activation_id
	 * @brief custom activation id identifies the activation
	 * function from the activation function table.
	 * */
	typedef uANN_size uANN_activation_id;

	/*!
	 * uANN_activation_callback
	 * @brief Activation function callback definition
	 * */
	typedef uANN_data (*uANN_activation_callback)( uANN_data );

	/*!
	 * @brief Network Layer structure
	 * */
	typedef struct uANN_layer{
		/// Length of the input holder
		uANN_len		inputLen;
		/// Number of neurons
		uANN_len		neurons;
		/// Activation function id
		uANN_activation_id	activation;
		
		///Pointer to next layer
		struct uANN_layer*	_next;
		///Holder of input values to propagate
		uANN_data*				_inputHolder;
		///Holder for weights values
		uANN_data*				_weightHolder;
		///Holder for bias values
		uANN_data*				_biasHolder;
		///Holder of output data.
		///Can be used as input holder to the next layer
		uANN_data*				_outputHolder;
	} uANN_layer;
	
	/*!
	 * @brief Neural Network structure
	 * */
	typedef struct uANN_net{
		///Input layer, the very first layer
		struct uANN_layer*	input;
		///Output layer, the very last layer
		struct uANN_layer*	output;
		///Layers counter
		uANN_len			layers;
	} uANN_net;

#ifdef __cplusplus
	}
#endif

#endif

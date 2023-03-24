/*!
*	@file		uANN.h
*	@version	1.0.0
*	@author		Josepablo Cruz Baas
*	@date		23/03/2023
*	@brief		micro Artificial Neural Network library declarations.
**/
#ifndef _UANN_H_
#define _UANN_H_

#ifdef __cplusplus
	extern "C" {
#endif
	
	#include "uANN_cfg.h"
	#include "uANN_types.h"
	#include "uANN_hooks.h"

	/*!
	 * uANN_default_activation_function
	 * @brief Defined by the developer.
	 * Identifies the default activation function for the init routines.
	 * */
	extern const uANN_activation_id uANN_default_activation_function_id;

	/*!
	 * uANN_activation_function_table.
	 * @brief Function table containing the pointers to the
	 * activation function callbacks defined by the developer.
	 * */
	extern const uANN_activation_callback uANN_activation_function_table[];
 
	/*!
	 * uANN_activation_function_table_size
	 * @brief Size of the activation function table.
	 * Should be defined by the developer.
	 * */
	extern const uANN_size uANN_activation_function_table_size;

	/*!
	 * uANN_init
	 * @brief Triggers all internal initializations like the memory heap.
	 * */
	extern int uANN_init( void );

	/*!
	 * uANN_create
	 * @brief Creates a new Network struct into the heap and
	 * provides the pointer to that memory.
	 * */
	extern uANN_net* uANN_create();

	/*!
	 * uANN_net_init
	 * @brief Clears the Network struct pointers.
	 * */
	extern void uANN_net_init( struct uANN_net* );

	/*!
	 * uANN_pop
	 * @brief Removes the very last layer from the
	 * network and returns the pointer to that layer struct.
	 * This does not release any allocated memory.
	 * */
	extern uANN_layer* uANN_pop( struct uANN_net* );

	/*!
	 * uANN_push
	 * @brief Adds a new layer to the end of the network struct.
	 * */
	extern int uANN_push( struct uANN_net* , struct uANN_layer* );

	/*!
	 * uANN_layer_create
	 * @brief Create a new layer structure.
	 * */
	extern uANN_layer* uANN_layer_create();

	/*!
	 * uANN_layer_init
	 * @brief Clears the LAyer struct pointers.
	 * */
	extern void uANN_layer_init( struct uANN_layer* );

	/*!
	 * uANN_alloc
	 * @brief Allocates all necessary memory for the
	 * Network in the Heap area.
	 * */
	extern int uANN_alloc( struct uANN_net* );

	/*!
	 * uANN_init
	 * @brief Triggers the propagation of data.
	 * The input is taked from the first layer input holder.
	 * */
	extern int uANN_compute( struct uANN_net* );

#ifdef __cplusplus
	}
#endif

#endif

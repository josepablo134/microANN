/*!
*	@file		uANN_cfg.h
*	@version	1.0.0
*	@author		Josepablo Cruz Baas
*	@date		23/03/2023
*	@brief		micro Artificial Neural Network library configuration file
**/
#ifndef _UANN_CONFIG_H_
#define _UANN_CONFIG_H_

#ifdef __cplusplus
	extern "C" {
#endif

	#include <stdint.h>

	/*!
	 * uANN_data
	 * @brief custom data type for inputs and outputs.
	 * Can be redefined to use double precision or single
	 * precision floating point numbers.
	 * */
	typedef float uANN_data;

	/*!
	 * uANN_size
	 * @brief Size type to define tables like the activation functions table.
	 * Can be redefined to allocate more activation functions.
	 * */
	typedef uint8_t uANN_size;

	/*!
	 * uANN_len
	 * @brief Length variable type.
	 * Can be redefined to allocate more neurons or to optimize the network size.
	 * */
	typedef uint8_t uANN_len;

#ifdef __cplusplus
	}
#endif

#endif

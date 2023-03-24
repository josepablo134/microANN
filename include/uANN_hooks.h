/*!
*	@file		uANN_hooks.h
*	@version	1.0.0
*	@author		Josepablo Cruz Baas
*	@date		23/03/2023
*	@brief		micro Artificial Neural Network hooks delcaration.
**/
#ifndef _UANN_HOOKS_H_
#define _UANN_HOOKS_H_

#ifdef __cplusplus
	extern "C" {
#endif

	extern int uANN_hook_init( void );

	extern unsigned char* uANN_hook_malloc( uANN_size size );

#ifdef __cplusplus
	}
#endif

#endif

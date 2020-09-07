# microANN

Micro Artificial Neural Network is a minimalist ANN library to implement AI in microcontrollers

This is work in progress.

# Requirements

uANN requires dynamic memory, not all the microcontrollers have any heap implemented on its
standard library, thats why this project assumes that is not available and uses uHeap (micro heap)
as dependency.

 * uHeap from [microMiddlewares](https://github.com/josepablo134/microMiddlewares)

# Example of use

```c
	#include "uANN.h"
	#include "uANN_config.h"
	
	void example(){
		struct ann_net*		ann;
		struct ann_layer*	layer;

		///	Initialize and clear private pointers
		ann_init();

		ann = ann_net_create();
		layer = ann_layer_create();

		///	Setting layer properties
		layer->inputLen = 2;
		layer->neurons  = 1;
		layer->activation = ann_sigmoid;
		
		///	Pushing new layer over last layer
		if( ann_net_push( ann , layer ) < 0 ){
			fprintf( stderr , "This layer is not compatible with last layer" );
		}
		
		///	Allocating memory for each layer
		if( ann_alloc( ann ) < 0 ){
			fprintf( stdout , "This neural netowork requires memory not available" );
		}
	
		///	Setting weights and bias
		layer->_weightHolder[0] = 0.85;
		layer->_weightHolder[1] = 0.85;
		
		layer->_biasHolder[0] = 0.0;
	
		///	Setting input vector
		layer->_inputHolder[0] = 1.0;
		layer->_inputHolder[1] = 1.0;

		///	Propagate through neural network
		ann_compute( ann );
		
		///	The output of the neural network is now available
		layer->_outputHolder[0];
	}
```

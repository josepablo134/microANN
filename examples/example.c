#include "uANN.h"
#include "uANN_config.h"

#include <stdio.h>
	
void example(){
	struct ann_net*		ann;
	struct ann_layer*	layer;
	const float	input[2] = {1.0, 1.0};
	float	output;

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
	layer->_inputHolder[0] = input[0];
	layer->_inputHolder[1] = input[1];

	///	Propagate through neural network
	ann_compute( ann );

	///	The output of the neural network is now available
	output = layer->_outputHolder[0];
	fprintf( stdout, "AND Gate example: \n");
	fprintf( stdout, "Input: [%f] [%f]\n", input[0], input[1]);
	fprintf( stdout, "result: %f\n", output );
}

int main( int argc, char* argv[] ){
	example();	
	return 0;
}

# microANN

Micro Artificial Neural Network is a minimalist ANN library to implement AI in microcontrollers

# Requirements

uANN requires dynamic memory, not all the microcontrollers have any heap implemented in its
stdlib, thats why this project assumes that is not available and uses uHeap (micro heap)
as dependency.

 * uHeap from [microMiddlewares](git@github.com:josepablo134/microMiddlewares.git)

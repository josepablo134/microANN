################################################################################
# @file CMakeLists.txt
# @author Josepablo C (josepablo134@gmail.com)
################################################################################
cmake_minimum_required( VERSION 3.18.4 )

project( uANN
		DESCRIPTION "Micro Artificial Neural Network is a minimalist ANN library to implement AI in microcontrollers"
		VERSION 1.0.0
		LANGUAGES C
)
set(COMPONENT_NAME microANN)

add_library(${COMPONENT_NAME} STATIC
		${CMAKE_CURRENT_LIST_DIR}/source/uANN.c
)

target_include_directories(${COMPONENT_NAME} PUBLIC
		${CMAKE_CURRENT_LIST_DIR}/include/
)


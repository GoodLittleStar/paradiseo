# Lesson 2

######################################################################################
### 0) Define files
######################################################################################

set(files
    lesson2_homogeneous
    )

######################################################################################
### 1) Create the lesson 
######################################################################################
    
add_lesson(smp Lesson2 "${files}")

######################################################################################
### 2) Include dependencies
######################################################################################

include_directories(${EO_SRC_DIR}/src
					${SMP_SRC_DIR}/src
					${PROBLEMS_SRC_DIR})

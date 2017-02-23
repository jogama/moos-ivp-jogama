#--------------------------------------------------------
# The CMakeLists.txt for:                       pPrimeFactor
# Author(s):                              Jonathan Garcia-Mallen
#--------------------------------------------------------

# FILE(GLOB SRC *.cpp)

SET(SRC
  PrimeFactor.cpp
  PrimeFactor_Info.cpp
  FactoredInput.cpp
  main.cpp
)


ADD_EXECUTABLE(pPrimeFactor ${SRC})


TARGET_LINK_LIBRARIES(pPrimeFactor
   ${MOOS_LIBRARIES}
   mbutil
   m
   pthread)

SET(CMAKE_CXX_FLAGS "-std=c++11")
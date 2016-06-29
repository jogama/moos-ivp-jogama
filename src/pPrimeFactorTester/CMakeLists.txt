#--------------------------------------------------------
# The CMakeLists.txt for:                       pPrimeFactorTester
# Author(s):                              Jonathan Garcia-Mallen
#--------------------------------------------------------

# FILE(GLOB SRC *.cpp)

SET(SRC
  PrimeFactorTester.cpp
  PrimeFactorTester_Info.cpp
  main.cpp
)



ADD_EXECUTABLE(pPrimeFactorTester ${SRC})

TARGET_LINK_LIBRARIES(pPrimeFactorTester
   ${MOOS_LIBRARIES}
   mbutil
   m
   pthread)

 SET(CMAKE_CXX_FLAGS "-std=c++11")
project(QcvCore)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG ${CMAKE_BINARY_DIR}/bin/Debug/)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE ${CMAKE_BINARY_DIR}/bin/Release/)

file(GLOB CORE_HDR include/*.h)
file(GLOB CORE_SRC *.cc)

include_directories(include)

add_library(QcvCore SHARED ${CORE_HDR} ${CORE_SRC})
target_link_libraries(QcvCore ${QT_LIBS} ${OpenCV_LIBS})
INSTALL(TARGETS QcvCore RUNTIME DESTINATION ${INSTALL_DIR})
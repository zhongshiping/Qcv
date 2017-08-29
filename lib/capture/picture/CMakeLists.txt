set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG ${CMAKE_BINARY_DIR}/bin/Debug/plugins/capture/picture)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE ${CMAKE_BINARY_DIR}/bin/Release/plugins/capture/picture)

file(GLOB HDR include/*.h)
file(GLOB SRC src/*.cc)

include_directories(include)

add_library(Picture SHARED ${HDR} ${SRC})
target_link_libraries(Picture ${QT_LIBS} ${OpenCV_LIBS} QcvCore)

set_target_folder(Picture "Libs/Capture")
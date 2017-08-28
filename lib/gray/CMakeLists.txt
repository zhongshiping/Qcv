set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG ${CMAKE_BINARY_DIR}/bin/Debug/plugins/gray)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE ${CMAKE_BINARY_DIR}/bin/Release/plugins/gray)

file(GLOB GRAY_HDR include/*.h)
file(GLOB GRAY_SRC src/*.cc)

include_directories(include)

qt5_add_resources(gray_rc gray.qrc)

add_library(GrayFeature SHARED ${GRAY_HDR} ${GRAY_SRC} ${gray_rc})
target_link_libraries(GrayFeature ${QT_LIBS} ${OpenCV_LIBS} QcvCore)

install(TARGETS GrayFeature RUNTIME DESTINATION ${INSTALL_DIR}/plugins/Feature)

set_target_folder(GrayFeature "Libs/Feature")
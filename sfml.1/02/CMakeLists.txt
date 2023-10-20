add_executable(rectangles main.cpp)
#set(SFML_STATIC_LIBRARIES TRUE)
set(SFML_DIR "/usr/local/lib/cmake/SFML")

find_package(Freetype)
find_package(JPEG)
find_package(SFML 2 COMPONENTS window graphics system)

target_compile_features(rectangles PUBLIC cxx_std_17)
target_compile_definitions(rectangles PRIVATE SFML_STATIC)

target_link_libraries(rectangles ${SFML_LIBRARIES} ${SFML_DEPENDENCIES})
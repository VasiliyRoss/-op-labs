add_executable(shapes main.cpp)

#set(SFML_STATIC_LIBRARIES TRUE)
set(SFML_DIR "/usr/local/lib/cmake/SFML")

find_package(Freetype)
find_package(JPEG)
find_package(SFML 2 COMPONENTS window graphics system)

target_compile_features(shapes PUBLIC cxx_std_17)
target_compile_definitions(shapes PRIVATE SFML_STATIC)

target_link_libraries(shapes ${SFML_LIBRARIES} ${SFML_DEPENDENCIES})
add_executable(figure_name main.cpp)

#set(SFML_STATIC_LIBRARIES TRUE)
set(SFML_DIR "/usr/local/lib/cmake/SFML")

find_package(Freetype)
find_package(JPEG)
find_package(SFML 2 COMPONENTS window graphics system)

target_compile_features(figure_name PUBLIC cxx_std_17)
target_compile_definitions(figure_name PRIVATE SFML_STATIC)

target_link_libraries(figure_name ${SFML_LIBRARIES} ${SFML_DEPENDENCIES})
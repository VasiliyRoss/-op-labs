add_executable(trafficlight main.cpp)

set(SFML_STATIC_LIBRARIES TRUE)

find_package(Freetype)
find_package(JPEG)
find_package(SFML 2 COMPONENTS window graphics system)

target_compile_features(trafficlight PUBLIC cxx_std_17)
target_compile_definitions(trafficlight PRIVATE SFML_STATIC)

target_link_libraries(trafficlight ${SFML_LIBRARIES} ${SFML_DEPENDENCIES})
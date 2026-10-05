cmake_minimum_required(VERSION 3.12)
project(kafka-cpp-example 
        VERSION 0.1 
        LANGUAGES CXX)

# Wymaganie standardu C++17
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Wyszukiwanie pakietu przez pkg-config w środowisku programowania
find_package(PkgConfig REQUIRED)
pkg_check_modules(RDKAFKA REQUIRED IMPORTED_TARGET rdkafka++)

# Aplikacja producenta (producer_app)
add_executable(producer_app src/producer.cpp)
target_link_libraries(producer_app PRIVATE PkgConfig::RDKAFKA)

# Aplikacja konsumenta (consumer_app)
add_executable(consumer_app src/consumer.cpp)
target_link_libraries(consumer_app PRIVATE PkgConfig::RDKAFKA)

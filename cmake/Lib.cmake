add_library(quantcpp 
    STATIC 
        src/LetsBeRational/LetsBeRational.cpp
)

target_link_libraries(quantcpp
    PUBLIC
        numcpp
)

target_include_directories(quantcpp
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include>
)

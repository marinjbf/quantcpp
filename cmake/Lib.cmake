add_library(quantcpp 
    STATIC 
        src/LetsBeRational/LetsBeRational.cpp
        src/GeometricLocalVolBackwardPDE/PricerConstructors.cpp
        src/GeometricLocalVolBackwardPDE/TransitionMatrix/ImplicitMatrix.cpp
        src/GeometricLocalVolBackwardPDE/ImplicitPricer/EuroVanilla.cpp
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

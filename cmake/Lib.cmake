add_library(quantcpp 
    STATIC 
        src/LetsBeRational/LetsBeRational.cpp
        src/GeometricLocalVolPDE/PricerConstructors.cpp
        src/GeometricLocalVolPDE/TransitionMatrix/ImplicitMatrix.cpp
        src/GeometricLocalVolPDE/ImplicitBackwardPricer/EuroVanilla.cpp
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

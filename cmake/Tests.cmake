include(CTest)

set(TESTS

    quantcpp-tests-bachelier tests/Bachelier/Bachelier.cpp
    quantcpp-tests-letsberational tests/LetsBeRational/LetsBeRational.cpp
    quantcpp-tests-blackscholes tests/BlackScholes/BlackScholes.cpp
    quantcpp-tests-ssvi tests/SSVI/SSVI.cpp
    quantcpp-tests-heston tests/Heston/Heston.cpp
    quantcpp-tests-nelsonsiegelsvensson tests/NelsonSiegelSvensson/NelsonSiegelSvensson.cpp
    quantcpp-tests-baroneadesiwhaley tests/BaroneAdesiWhaley/BaroneAdesiWhaley.cpp
    
    quantcpp-geolvpde-implicit-european tests/GeometricLocalVolBackwardPDE/ImplicitPricer/EuroVanilla.cpp
)

while(TESTS)
    list(POP_FRONT TESTS test_name test_file)

    add_executable(${test_name} ${test_file})
    target_link_libraries(${test_name} PRIVATE quantcpp)

    add_test(NAME ${test_name} COMMAND ${test_name})
endwhile()
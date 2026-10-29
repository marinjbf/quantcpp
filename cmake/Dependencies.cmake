include(FetchContent)

FetchContent_Declare(
    numcpp
    GIT_REPOSITORY ssh://git@github.com/marinjbf/numcpp.git #https://github.com/marquesasarbitrage/numcpp.git  
    GIT_TAG main  # or a release tag
)
FetchContent_MakeAvailable(numcpp)

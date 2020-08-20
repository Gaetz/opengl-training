file( GLOB maths_SOURCES *.cpp )
add_library( maths ${maths_SOURCES} )
target_include_directories(maths PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

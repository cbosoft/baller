# specify which version and components you need
find_package(OGRE 1.12 REQUIRED COMPONENTS Bites RTShaderSystem)

# copy resource.cfg next to our binaries where OGRE looks for it
file(COPY ${OGRE_CONFIG_DIR}/resources.cfg DESTINATION ${CMAKE_CURRENT_BINARY_DIR})

# add the source files as usual
add_executable(baller src/main.cpp)

# this also sets the includes and pulls third party dependencies
target_link_libraries(baller OgreBites OgreRTShaderSystem)

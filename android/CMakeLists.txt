cmake_minimum_required(VERSION 3.4.1)  # for example
link_libraries(OpenSLES)
# link_libraries(aaudio)
add_library( native_player

             # Sets the library as a shared library.
             SHARED

             # Provides a relative path to your source file(s).
             ${tag_LIB_SRCS}
             ../miniaudio/miniplayer.c )

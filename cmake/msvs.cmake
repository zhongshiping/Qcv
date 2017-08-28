
option(CMAKE_USE_FOLDERS "Enable folder grouping of projects in IDEs." ON)
mark_as_advanced(CMAKE_USE_FOLDERS)
macro(set_target_folder tgt folder)
    if(CMAKE_USE_FOLDERS)
        set_property(GLOBAL PROPERTY USE_FOLDERS ON)
        # Really, I just want this to be an "if(TARGET ${tgt})" ...
        # but I'm not sure that our min req'd., CMake 2.4.5 can handle
        # that... so I'm just activating this for now, with a version
        # compare, and only for MSVC builds.
        if(MSVC)
            if(NOT ${CMAKE_MAJOR_VERSION}.${CMAKE_MINOR_VERSION} LESS 2.8)
                set_property(TARGET "${tgt}" PROPERTY FOLDER "${folder}")
            endif()
        endif()
	else()
        set_property(GLOBAL PROPERTY USE_FOLDERS OFF)
    endif()
endmacro(set_target_folder)


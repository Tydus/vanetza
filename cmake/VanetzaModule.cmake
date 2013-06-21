macro(vanetza_module NAME)
    set(_sources ${ARGN})
    add_library(vanetza_${NAME} SHARED ${_sources})
    set_target_properties(vanetza_${NAME} PROPERTIES
        INCLUDE_DIRECTORIES ${PROJECT_SOURCE_DIR})
    add_library(vanetza_${NAME}_static STATIC ${_sources})
    set_target_properties(vanetza_${NAME}_static PROPERTIES
        INCLUDE_DIRECTORIES ${PROJECT_SOURCE_DIR})
endmacro()

macro(vanetza_module_dependencies NAME)
    set(_deps ${ARGN})
    foreach(_dep ${_deps})
        target_link_libraries(vanetza_${NAME} ${_dep})
        target_link_libraries(vanetza_${NAME}_static ${_dep})
    endforeach()
endmacro()

macro(target_link_vanetza TARGET)
    set(_modules ${ARGN})
    foreach(_module ${_modules})
        target_link_libraries(${TARGET} vanetza_${_module}_static)
    endforeach()
endmacro()
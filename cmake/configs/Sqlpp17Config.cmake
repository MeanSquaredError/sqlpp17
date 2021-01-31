include(CMakeFindDependencyMacro)
find_dependency(Threads)

# Work out the set of components to load
if(${CMAKE_FIND_PACKAGE_NAME}_FIND_COMPONENTS)
    set(${CMAKE_FIND_PACKAGE_NAME}_comps ${${CMAKE_FIND_PACKAGE_NAME}_FIND_COMPONENTS})
endif()

# Check all required components are available before trying to load any
foreach(comp IN LISTS ${CMAKE_FIND_PACKAGE_NAME}_comps)
    if(${CMAKE_FIND_PACKAGE_NAME}_FIND_REQUIRED_${comp} AND NOT EXISTS ${CMAKE_CURRENT_LIST_DIR}/Sqlpp17${comp}Config.cmake)
        set(${CMAKE_FIND_PACKAGE_NAME}_NOT_FOUND_MESSAGE "Sqlpp17 missing required component: ${comp}")
        set(${CMAKE_FIND_PACKAGE_NAME}_FOUND FALSE)
        return()
    endif()
endforeach()

# Add the target file
include(${CMAKE_CURRENT_LIST_DIR}/Sqlpp17Targets.cmake)

# Load any optional components 
foreach(comp IN LISTS ${CMAKE_FIND_PACKAGE_NAME}_comps)
    include(${CMAKE_CURRENT_LIST_DIR}/Sqlpp17_${comp}.cmake OPTIONAL)
endforeach()

# Find Wt libraries
#
# Output variables:
# - WT_INCLUDE_DIRS
# - WT_LIBRARIES
# - WT_FOUND

set(WT_SEARCH_PATHS
        /usr
        /usr/local
        /opt)

find_path(WT_INCLUDE_DIRS
        NAMES WApplication.h
        PATHS ${WT_SEARCH_PATHS}
        PATH_SUFFIXES include/Wt)

find_library(WT_LIBRARY
        NAMES wt
        PATHS ${WT_SEARCH_PATHS}
        PATH_SUFFIXES lib)

find_library(WT_HTTP_LIBRARY
        NAMES wthttp
        PATHS ${WT_SEARCH_PATHS}
        PATH_SUFFIXES lib)

if(WT_INCLUDE_DIRS AND WT_LIBRARY AND WT_HTTP_LIBRARY)
    cmake_path(GET WT_INCLUDE_DIRS PARENT_PATH WT_INCLUDE_DIRS)
    set(WT_LIBRARIES
            ${WT_LIBRARY}
            ${WT_HTTP_LIBRARY})
    set(Wt_FOUND TRUE)
else()
    set(Wt_FOUND FALSE)
endif()
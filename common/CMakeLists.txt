add_library(netchat_common STATIC
	common.cpp
)

target_include_directories(netchat_common
	PUBLIC
		${CMAKE_CURRENT_SOURCE_DIR}
)
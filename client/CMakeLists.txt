add_executable(chat_client
	main.cpp
	chat_client.cpp
)

target_include_directories(chat_client
	PRIVATE
		${CMAKE_CURRENT_SOURCE_DIR}
)

find_package(Threads REQUIRED)
target_link_libraries(chat_client
	PRIVATE
		netchat_common
		Threads::Threads
)
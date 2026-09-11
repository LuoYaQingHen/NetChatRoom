add_executable(chat_server
	main.cpp
	chat_server.cpp
	user_manager.cpp
)

target_include_directories(chat_server
	PRIVATE
		${CMAKE_CURRENT_SOURCE_DIR}
)

find_package(Threads REQUIRED)
target_link_libraries(chat_server
	PRIVATE
		netchat_common
		Threads::Threads
)
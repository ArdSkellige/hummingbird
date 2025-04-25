cmake_minimum_required(VERSION 3.23.0)

set(CMAKE_C_STANDARD       11)
set(CMAKE_CXX_STANDARD     20)

project(hummingbird VERSION 1.0 LANGUAGES C CXX)

#region packages for Qt
find_package(Qt6 COMPONENTS REQUIRED
	Core
	Widgets
	Gui
)

qt_standard_project_setup()
#endregion

# region QtApplication
file(GLOB QT_LIB_SOURSCE ${CMAKE_SOURCE_DIR}/qt_app/*.cpp)

qt_add_executable(main_qt ${CMAKE_SOURCE_DIR}/main_qt.cpp ${QT_LIB_SOURSCE})

target_include_directories(main_qt PRIVATE
	${CMAKE_CURRENT_SOURCE_DIR}
	${CMAKE_CURRENT_SOURCE_DIR}/qt_app
)

target_link_libraries(main_qt PRIVATE
	Qt6::Core
	Qt6::Gui
	Qt6::Widgets
)
#endregion
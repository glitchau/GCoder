if(DEFINED ENV{VCPKG_ROOT} AND NOT DEFINED CMAKE_TOOLCHAIN_FILE)
  set(CMAKE_TOOLCHAIN_FILE "$ENV{VCPKG_ROOT}/scripts/buildsystems/vcpkg.cmake"
      CACHE STRING "")
endif()

cmake_minimum_required(VERSION 3.1.0)

project(GCoder VERSION 1.0.1 DESCRIPTION "Core description")

# specify the C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -D_WIN32_WINNT=0x0601 -DBOOST_UUID_FORCE_AUTO_LINK") #turned off by vcpkg "https://github.com/microsoft/vcpkg/issues/4481"
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -D_WIN32_WINNT=0x0601 -DBOOST_UUID_FORCE_AUTO_LINK")

if(CMAKE_VERSION VERSION_LESS "3.7.0")
    set(CMAKE_INCLUDE_CURRENT_DIR ON)
endif()

find_package(Qt5 COMPONENTS Widgets REQUIRED)
#find_package(Qt5Charts REQUIRED)
find_package(Boost REQUIRED)

include_directories(include)
include_directories(${Boost_INCLUDE_DIR})

set(MY_SOURCES
	src/mainwindow.h
	src/mainwindow.cpp
	src/gcoder_widget.h
	src/gcoder_widget.cpp
)

set(MY_MOCS
	src/gcoder_widget.ui
	src/mainwindow.ui
)


add_executable(GCoder ${MY_SOURCES} ${MY_MOCS} src/main.cpp)

target_link_libraries(GCoder Qt5::Widgets)
#target_link_libraries(GCoder Qt5::Widgets Qt5::Charts)
#target_link_libraries(main PRIVATE Qt5::Charts Qt5::ChartsPrivate)
target_link_libraries(GCoder ${Boost_LIBRARIES})


target_include_directories(GCoder PRIVATE include)
target_include_directories(GCoder PRIVATE src)

#install(TARGETS Core
#    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
#    PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})


cmake_minimum_required(VERSION 3.16)

project(firestation_manager_qt VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)

add_subdirectory(lib/firestation_manager_lib)

set(PROJECT_SOURCES
        src/main.cpp
        src/emptylasttablewidgetitem.cpp
        src/bankdialog.cpp
        src/firefighterdialog.cpp
        src/firefightertrainingdialog.cpp
        src/medicalexaminationsdialog.cpp
        src/trainingdialog.cpp
        src/mainwindow.cpp
        src/mainwindow.h
        src/mainwindow.ui
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(firestation_manager_qt
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
    )
# Define target properties for Android with Qt 6 as:
#    set_property(TARGET firestation_manager_qt APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
#                 ${CMAKE_CURRENT_SOURCE_DIR}/android)
# For more information, see https://doc.qt.io/qt-6/qt-add-executable.html#target-creation
else()
    if(ANDROID)
        add_library(firestation_manager_qt SHARED
            ${PROJECT_SOURCES}
        )
# Define properties for Android with Qt 5 after find_package() calls as:
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
    else()
        add_executable(firestation_manager_qt
            ${PROJECT_SOURCES}
            src/firefighterdialog.h
            src/bankdialog.cpp src/bankdialog.h
            src/bankdialog.cpp src/bankdialog.h src/emptylasttablewidgetitem.cpp src/emptylasttablewidgetitem.h src/firefighterdialog.cpp src/firefighterdialog.h src/main.cpp src/mainwindow.cpp src/mainwindow.h src/mainwindow.ui
            src/bankdialog.cpp src/bankdialog.h src/emptylasttablewidgetitem.cpp src/emptylasttablewidgetitem.h src/firefighterdialog.cpp src/firefighterdialog.h src/main.cpp src/mainwindow.cpp src/mainwindow.h src/mainwindow.ui src/medicalexaminationsdialog.cpp src/medicalexaminationsdialog.h
            src/bankdialog.cpp src/bankdialog.h src/emptylasttablewidgetitem.cpp src/emptylasttablewidgetitem.h src/firefighterdialog.cpp src/firefighterdialog.h src/firefightertrainingdialog.cpp src/firefightertrainingdialog.h src/main.cpp src/mainwindow.cpp src/mainwindow.h src/mainwindow.ui src/medicalexaminationsdialog.cpp src/medicalexaminationsdialog.h src/trainingdialog.cpp src/trainingdialog.h

        )
    endif()
endif()

target_link_libraries(firestation_manager_qt PRIVATE
    Qt${QT_VERSION_MAJOR}::Widgets
    firestation_manager_lib
)

# Qt for iOS sets MACOSX_BUNDLE_GUI_IDENTIFIER automatically since Qt 6.1.
# If you are developing for iOS or macOS you should consider setting an
# explicit, fixed bundle identifier manually though.
if(${QT_VERSION} VERSION_LESS 6.1.0)
  set(BUNDLE_ID_OPTION MACOSX_BUNDLE_GUI_IDENTIFIER com.example.firestation_manager_qt)
endif()
set_target_properties(firestation_manager_qt PROPERTIES
    ${BUNDLE_ID_OPTION}
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

include(GNUInstallDirs)
install(TARGETS firestation_manager_qt
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(firestation_manager_qt)
endif()

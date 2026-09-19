cmake_minimum_required(VERSION 3.16)

project(GameNet VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)

set(PROJECT_SOURCES
    main.cpp

    UI/mainwindow.cpp
    UI/mainwindow.h
    UI/mainwindow.ui

    UI/system.cpp
    UI/system.h
    UI/system.ui

    UI/startsessiondialog.cpp
    UI/startsessiondialog.h
    UI/startsessiondialog.ui

    Logic/timer.cpp
    Logic/timer.h
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)

    qt_add_executable(GameNet
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
        Logic/pricingrule.h Logic/pricingrule.cpp
        Logic/Platform.h
        Logic/pricingmanager.h Logic/pricingmanager.cpp
        Logic/product.h Logic/product.cpp
        Logic/productcatalog.h Logic/productcatalog.cpp
        Logic/productitem.h Logic/productitem.cpp
        UI/productsdialog.h UI/productsdialog.cpp UI/productsdialog.ui
        UI/menudialog.h UI/menudialog.cpp UI/menudialog.ui
        UI/extendtimedialog.h UI/extendtimedialog.cpp UI/extendtimedialog.ui
        UI/descriptiondialog.h UI/descriptiondialog.cpp UI/descriptiondialog.ui
        UI/changeplayercountdialog.h UI/changeplayercountdialog.cpp UI/changeplayercountdialog.ui
        UI/sessionsummarydialog.h UI/sessionsummarydialog.cpp UI/sessionsummarydialog.ui
    )

else()

    if(ANDROID)

        add_library(GameNet SHARED
            ${PROJECT_SOURCES}
        )

    else()

        add_executable(GameNet
            ${PROJECT_SOURCES}
        )

    endif()

endif()

target_link_libraries(GameNet PRIVATE
    Qt${QT_VERSION_MAJOR}::Widgets
)

if(${QT_VERSION} VERSION_LESS 6.1.0)

    set(BUNDLE_ID_OPTION
        MACOSX_BUNDLE_GUI_IDENTIFIER com.example.GameNet
    )

endif()

set_target_properties(GameNet PROPERTIES
    ${BUNDLE_ID_OPTION}
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

include(GNUInstallDirs)

install(TARGETS GameNet
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(GameNet)
endif()
cmake_minimum_required(VERSION 3.16)

project(GameNet VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets Multimedia)

set(PROJECT_SOURCES
    main.cpp

    UI/MainWindow/mainwindow.cpp
    UI/MainWindow/mainwindow.h
    UI/MainWindow/mainwindow.ui

    UI/System/system.cpp
    UI/System/system.h
    UI/System/system.ui

    UI/StartSession/startsessiondialog.cpp
    UI/StartSession/startsessiondialog.h
    UI/StartSession/startsessiondialog.ui

    Logic/Timer/timer.cpp
    Logic/Timer/timer.h
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)

    qt_add_executable(GameNet
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
        Logic/Price/pricingrule.h Logic/Price/pricingrule.cpp
        Logic/Platform/Platform.h
        Logic/Price/pricingmanager.h Logic/Price/pricingmanager.cpp
        Logic/Product/product.h Logic/Product/product.cpp
        Logic/Product/productcatalog.h Logic/Product/productcatalog.cpp
        Logic/Product/productitem.h Logic/Product/productitem.cpp
        UI/Products/productsdialog.h UI/Products/productsdialog.cpp UI/Products/productsdialog.ui
        UI/Menu/menudialog.h UI/Menu/menudialog.cpp UI/Menu/menudialog.ui
        UI/ExtendTime/extendtimedialog.h UI/ExtendTime/extendtimedialog.cpp UI/ExtendTime/extendtimedialog.ui
        UI/Description/descriptiondialog.h UI/Description/descriptiondialog.cpp UI/Description/descriptiondialog.ui
        UI/ChangePlayerCount/changeplayercountdialog.h UI/ChangePlayerCount/changeplayercountdialog.cpp UI/ChangePlayerCount/changeplayercountdialog.ui
        UI/SessionSummary/sessionsummarydialog.h UI/SessionSummary/sessionsummarydialog.cpp UI/SessionSummary/sessionsummarydialog.ui
        resources/resources.qrc
        UI/TimeExpired/timeexpireddialog.h UI/TimeExpired/timeexpireddialog.cpp UI/TimeExpired/timeexpireddialog.ui
        app.rc
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
    Qt6::Multimedia
)
target_include_directories(GameNet PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}
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
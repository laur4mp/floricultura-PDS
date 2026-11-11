cmake_minimum_required(VERSION 3.16)

project(TELL_FloresFinal VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_AUTOUIC_SEARCH_PATHS
    ${CMAKE_CURRENT_SOURCE_DIR}/design
)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets Svg)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets Svg)

set(PROJECT_SOURCES     
        src/Comprador.cpp
        src/Desconto.cpp
        src/DescontoRepositorio.cpp
        src/Endereco.cpp
        src/Gerente.cpp
        src/ItemPedido.cpp
        src/Pessoa.cpp
        src/PessoaRepositorio.cpp
        src/Produto.cpp
        src/ProdutoRepositorio.cpp
        src/Sistema.cpp
        src/Venda.cpp
        src/VendaRepositorio.cpp
        src/interface.cpp
        src/main.cpp
        src/interface.ui
        src/cardproduto.cpp
        src/cardproduto.ui
        src/Estilos.cpp
        src/cardcarrinho.cpp
        src/cardcarrinho.ui
        src/cardhistorico.cpp
        src/cardhistorico.ui

        include/Comprador.hpp
        include/Desconto.hpp
        include/DescontoRepositorio.hpp
        include/Endereco.hpp
        include/Gerente.hpp
        include/ItemPedido.hpp
        include/Pessoa.hpp
        include/PessoaRepositorio.hpp
        include/Produto.hpp
        include/ProdutoRepositorio.hpp
        include/Sistema.hpp
        include/Venda.hpp
        include/VendaRepositorio.hpp
        include/interface.h
        include/cardproduto.h
        include/Estilos.hpp
        src/cardcarrinho.h
        src/cardhistorico.h

        ${CMAKE_CURRENT_SOURCE_DIR}/Resources/resources.qrc
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(TELL_FloresFinal
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
    )
# Define target properties for Android with Qt 6 as:
#    set_property(TARGET TELL_Flores APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
#                 ${CMAKE_CURRENT_SOURCE_DIR}/android)
# For more information, see https://doc.qt.io/qt-6/qt-add-executable.html#target-creation
else()
    if(ANDROID)
        add_library(TELL_FloresFinal SHARED
            ${PROJECT_SOURCES}
        )
# Define properties for Android with Qt 5 after find_package() calls as:
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
    else()
        add_executable(TELL_FloresFinal
            ${PROJECT_SOURCES}
        )
    endif()
endif()

target_include_directories(TELL_FloresFinal PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    ${CMAKE_CURRENT_SOURCE_DIR}/src
)

target_link_libraries(TELL_FloresFinal PRIVATE
    Qt${QT_VERSION_MAJOR}::Widgets
    Qt${QT_VERSION_MAJOR}::Svg
)

# Qt for iOS sets MACOSX_BUNDLE_GUI_IDENTIFIER automatically since Qt 6.1.
# If you are developing for iOS or macOS you should consider setting an
# explicit, fixed bundle identifier manually though.
if(${QT_VERSION} VERSION_LESS 6.1.0)
  set(BUNDLE_ID_OPTION MACOSX_BUNDLE_GUI_IDENTIFIER com.example.TELL_FloresFinal)
endif()
set_target_properties(TELL_FloresFinal PROPERTIES
    ${BUNDLE_ID_OPTION}
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

include(GNUInstallDirs)
install(TARGETS TELL_FloresFinal
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(TELL_FloresFinal)
endif()
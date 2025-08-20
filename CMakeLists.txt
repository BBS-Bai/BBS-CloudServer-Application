cmake_minimum_required(VERSION 3.25)
project(BBS-CloudServer-Application LANGUAGES CXX)

# 基础配置
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 启用自动 UI 编译（必须！）
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)  # 自动处理 moc（若使用信号槽）
set(CMAKE_AUTORCC ON)  # 自动处理资源文件（若有）

# 仅需Qt Widgets模块
find_package(Qt6 COMPONENTS Widgets Core Network REQUIRED)
qt6_wrap_ui(UI_HEADERS mainwindow.ui)
# 主可执行文件
add_executable(${PROJECT_NAME}
        main.cpp
        src/mainwindow/mainwindow.cpp
        src/mainwindow/mainwindow.h
        src/mainwindow/mainwindow.ui
        src/network/websocket.cpp
        src/network/websocket_client.cpp
        src/network/websocket_client.h
        src/core/logger.h
        src/core/logger.cpp
        src/core/config_loader.h
        src/core/config_loader.cpp
        src/models/message_model.h
        src/models/message_model.cpp
)

# 链接Qt Widgets库
target_link_libraries(${PROJECT_NAME} PRIVATE Qt6::Widgets Qt6::Network Qt6::Core)
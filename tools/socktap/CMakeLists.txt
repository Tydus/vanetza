find_package(Boost COMPONENTS system REQUIRED)
find_package(Threads REQUIRED)
find_package(GPS REQUIRED)

add_executable(socktap
    application.cpp
    ethernet_device.cpp
    gps_position_provider.cpp
    hello_application.cpp
    main.cpp
    router_context.cpp
    time_trigger.cpp
)
target_include_directories(socktap PRIVATE ${Boost_INCLUDE_DIRS})
target_link_libraries(socktap ${Boost_SYSTEM_LIBRARY} Threads::Threads GPS::GPS geonet btp net)

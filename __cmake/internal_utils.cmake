#
# 是否为动态编译
#
macro(FIX_DEFAULT_COMPILER_SETTINGS_MT)
    message("-- Building with MT")

    if (MSVC)
        foreach(flag_var
                CMAKE_C_FLAGS 
                CMAKE_C_FLAGS_DEBUG 
                CMAKE_C_FLAGS_RELEASE
                CMAKE_C_FLAGS_MINSIZEREL 
                CMAKE_C_FLAGS_RELWITHDEBINFO

                CMAKE_CXX_FLAGS 
                CMAKE_CXX_FLAGS_DEBUG 
                CMAKE_CXX_FLAGS_RELEASE
                CMAKE_CXX_FLAGS_MINSIZEREL 
                CMAKE_CXX_FLAGS_RELWITHDEBINFO)
           if(${flag_var} MATCHES "/MD")
              string(REGEX REPLACE "/MD" "/MT" ${flag_var} "${${flag_var}}")
           endif(${flag_var} MATCHES "/MD")
        endforeach(flag_var)
    endif()
endmacro()

#
# 是否启用wchar_t 为内置类型
#
macro(FIX_DEFAULT_COMPILER_SETTINGS_WCHAR)
    set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /Zc:wchar_t-")
    set (CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} /Zc:wchar_t-")
    set (CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} /Zc:wchar_t-")
    set (CMAKE_CXX_FLAGS_MINSIZEREL "${CMAKE_CXX_FLAGS_MINSIZEREL} /Zc:wchar_t-")
    set (CMAKE_CXX_FLAGS_RELWITHDEBINFO "${CMAKE_CXX_FLAGS_RELWITHDEBINFO} /Zc:wchar_t-")    
endmacro()

macro(config_compiler_and_linker)
    #
    # 修正编译参数
    #
    if (NOT SHARED_CRT)
        FIX_DEFAULT_COMPILER_SETTINGS_MT()
    endif()

    if (NOT WCHAR_AS_DEFAULT)
        FIX_DEFAULT_COMPILER_SETTINGS_WCHAR()
    endif()

    if(USE_UNICODE)
        add_definitions(-DUNICODE -D_UNICODE)
        set(CMAKE_RC_FLAGS "${CMAKE_RC_FLAGS} -DUNICODE -D_UNICODE")
        message("-- Building with Unicode")
    else(USE_UNICODE)
        add_definitions(-D_MBCS)
        message("-- Building with MBCS")
    endif(USE_UNICODE)

    #
    # 支持xp环境
    #
    if (XP_TOOLSET) 
        if (MSVC_VERSION GREATER 1700) # 1700 is Visual Studio 2012.
            add_definitions(-D_USING_V110_SDK71_)
        endif()
    endif()
endmacro()
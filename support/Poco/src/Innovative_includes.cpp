

#if !defined(LINUX)
    #include "WindowsConsoleChannel.cpp"
    #include "EventLogChannel.cpp"
    #include "util/WinRegistryKey.cpp"
    #include "util/WinService.cpp"
    #include "util/WinRegistryConfiguration.cpp"
#else
    #include "SyslogChannel.cpp"
#endif




pkg_check_modules(PC_LIBUDEV libudev)
set (required_vars NCURSESW_LIBRARIES)

include (FindPackageHandleStandardArgs)
FIND_PACKAGE_HANDLE_STANDARD_ARGS (UDEV DEFAULT_MSG ${required_vars})

mark_as_advanced(UDEV_INCLUDE_DIR UDEV_LIBRARY)

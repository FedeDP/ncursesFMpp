pkg_check_modules (NCURSESW REQUIRED ncursesw ncurses++w menuw panelw)
set (required_vars NCURSESW_LIBRARIES)

include (FindPackageHandleStandardArgs)
FIND_PACKAGE_HANDLE_STANDARD_ARGS (NCURSESW DEFAULT_MSG ${required_vars})

mark_as_advanced (NCURSESW_LIBRARIES NCURSESW_INCLUDE_DIRS)

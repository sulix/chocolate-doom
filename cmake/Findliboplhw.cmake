# Look for libieee1284:
# See: https://github.com/twaugh/libieee1284
# and: http://cyberelk.net/tim/libieee1284/interface/

find_package(PkgConfig)
pkg_check_modules(PC_OPLHW QUIET oplhw)
set(OPLHW_DEFINITIONS ${PC_OPLHW_CFLAGS_OTHER})

find_path(OPLHW_INCLUDE_DIR oplhw.h
	HINTS ${PC_OPLHW_INCLUDEDIR} ${PC_OPLHW_INCLUDE_DIRS}
)

find_library(OPLHW_LIBRARY NAMES oplhw
	HINTS ${PC_OPLHW_LIBDIR} ${PC_OPLHW_LIBRARY_DIRS}
)

include(FindPackageHandleStandardArgs)

find_package_handle_standard_args(oplhw DEFAULT_MSG
	OPLHW_LIBRARY OPLHW_INCLUDE_DIR
)

mark_as_advanced(OPLHW_LIBRARY OPLHW_INCLUDE_DIR)

set(OPLHW_LIBRARIES ${OPLHW_LIBRARY})
set(OPLHW_INCLUDE_DIRS ${OPLHW_INCLUDE_DIR})

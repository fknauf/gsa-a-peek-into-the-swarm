AC_DEFUN([APITS_ARG_ENABLE_DEBUG],
[
  AC_ARG_ENABLE([debug],
    AS_HELP_STRING(
      [--enable-debug],
      [generate debug symbols [[default=$1]]]
    ),
    [apits_enable_debug=$enableval],
    [apits_enable_debug=$1]
  )

  if test "x$apits_enable_debug" = "xyes"; then
    CXXFLAGS+=" -g -O0 -fsanitize=undefined -fsanitize=address -fno-sanitize=vptr"
  else
    CXXFLAGS+=" -g -O3 -DNDEBUG"
  fi
])

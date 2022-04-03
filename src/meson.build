support_sources = files(
  'io.c',
  'log.c',
  'mem.c',
)

support_lib = library('support', [support_sources],
  include_directories: [support_inc],
)

libsupport_dep = declare_dependency(
  include_directories : support_inc,
  link_with: support_lib,
)

pkg = import('pkgconfig')
pkg.generate(support_lib,
  filebase: 'libsupport',
)

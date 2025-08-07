prj = meson.project_name()

sources = [
  'rlso/so-align.c',
  'rlso/so-as.c',
  'rlso/so-cmp.c',
  'rlso/so-color.c',
  'rlso/so-core.c',
  'rlso/so-count.c',
  'rlso/so-env.c',
  'rlso/so-file.c',
  'rlso/so-find.c',
  'rlso/so-fx.c',
  'rlso/so-hash.c',
  'rlso/so-heap.c',
  'rlso/so-input.c',
  'rlso/so-path.c',
  'rlso/so-print.c',
  'rlso/so-splice.c',
  'rlso/so-split.c',
  'rlso/so-trim.c',
  'rlso/so-uc.c',
  'rlso/vso.c',
  ]

headers = [
  'rlso/so-align.h',
  'rlso/so-as.h',
  'rlso/so-cmp-attr.h',
  'rlso/so-cmp.h',
  'rlso/so-color.h',
  'rlso/so-core.h',
  'rlso/so-count.h',
  'rlso/so-env.h',
  'rlso/so-file.h',
  'rlso/so-find.h',
  'rlso/so-fx.h',
  'rlso/so-hash.h',
  'rlso/so-heap.h',
  'rlso/so-input.h',
  'rlso/so-path.h',
  'rlso/so-print.h',
  'rlso/so-splice.h',
  'rlso/so-split.h',
  'rlso/so-trim.h',
  'rlso/so-uc.h',
  'rlso/vso.h',
  ]

rlc_dep = dependency('rlc',
  fallback : ['rlc', 'rlc_dep'],
  default_options: ['default_library=static']
)

install_headers(headers, subdir: 'rlso')
install_headers('rlso.h')
librlso = library('rlso',
  sources,
  dependencies: [rlc_dep],
  install: true,
  )

pkg = import('pkgconfig')
pkg.generate(
  libraries: librlso,
  version: '9999',
  name: 'rlso',
  description: 'Small String Optimized and Dynamically Allocatable String',
  )

rlso_dep = declare_dependency(link_with: librlso)


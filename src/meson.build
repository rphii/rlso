sources = [
  'so-align.c',
  'so-as.c',
  'so-cmp.c',
  'so-core.c',
  'so-count.c',
  'so-env.c',
  'so-file.c',
  'so-find.c',
  'so-fx.c',
  'so-hash.c',
  'so-heap.c',
  'so-input.c',
  'so-path.c',
  'so-print.c',
  'so-splice.c',
  'so-split.c',
  'so-trim.c',
  'so-uc.c',
  'vso.c',
  ]

headers = [
  'so-align.h',
  'so-as.h',
  'so-cmp-attr.h',
  'so-cmp.h',
  'so-core.h',
  'so-count.h',
  'so-env.h',
  'so-file.h',
  'so-find.h',
  'so-fx.h',
  'so-hash.h',
  'so-heap.h',
  'so-input.h',
  'so-path.h',
  'so-print.h',
  'so-splice.h',
  'so-split.h',
  'so-trim.h',
  'so-uc.h',
  'so.h',
  'vso.h',
  ]

dep_rlc = dependency('rlc', required: true)

install_headers(headers, subdir: 'rl')
rlso = library('rlso',
  sources,
  dependencies: [dep_rlc],
  install: true,
  )





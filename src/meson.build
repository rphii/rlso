sources = [
  'so-as.c',
  'so-cmp.c',
  'so-file.c',
  'so-find.c',
  'so-heap.c',
  'so-input.c',
  'so-print.c',
  'so-count.c',
  'so-trim.c',
  'so-uc.c',
  'so.c',
  'vso.c',
  ]

headers = [
  'so-as.h',
  'so-cmp-attr.h',
  'so-cmp.h',
  'so-file.h',
  'so-find.h',
  'so-count.h',
  'so-heap.h',
  'so-input.h',
  'so-print.h',
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





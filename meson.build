project('rlso', 'c')
subdir('src')
subdir('man')
subdir('tests')

pkg = import('pkgconfig')
pkg.generate(
  libraries: rlso,
  version: '9999',
  name: 'rlso',
  description: 'Small String Optimized and Dynamically Allocatable String',
  )



examples = [
  'len-0.c',
  'len-0.2.c',
  'len-a.c',
  'len-1000.c',
  'push-len.c',
  'uc.c',
  'uc2.c',
  'uc3.c',
  'uc4.c',
  'uc5.c',
  'uc6.c',
  'uc7.c',
  'splice.c',
  'splice.2.c',
  'env.c',
  'file.c',
  'path.c',
  'path.2.c',
  'path.3.c',
  'path.4.c',
  'vso.c',
  'as-size.c',
  'count.c',
  'split.c',
  'triml.c',
  'trimr.c',
  'trim.c',
  'cmp.c',
  'input.c',
  'find.c',
  'extend.c',
  'len-nfx.c',
  ]

tests = []

dep_rlc = dependency('rlc', required: true)

if get_option('tests').enabled()

  foreach ex : examples
    tests += executable(ex, ex, link_with: rlso, dependencies: [dep_rlc])
  endforeach

  foreach ex : tests
    test(ex.name(), ex)
  endforeach

endif


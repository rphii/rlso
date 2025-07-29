examples = [
  'len-0',
  'len-0.2',
  'len-a',
  'len-1000',
  'push-len',
  'uc',
  'uc2',
  'uc3',
  'uc4',
  'uc5',
  'uc6',
  'uc7',
  'splice',
  'splice.2',
  'env',
  'file',
  'path',
  'path.2',
  'path.3',
  'path.4',
  'vso',
  ]

tests = []

dep_rlc = dependency('rlc', required: true)

if get_option('tests').enabled()

  foreach ex : examples
    tests += executable(ex, ex + '.c', link_with: rlso, dependencies: [dep_rlc])
  endforeach

  foreach ex : tests
    test(ex.name(), ex)
  endforeach

endif


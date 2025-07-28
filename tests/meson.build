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
  'env',
  'file',
  'path',
  'path.2',
  'path.3',
  'path.4',
  ]

tests = []

foreach ex : examples
  tests += executable(ex, ex + '.c', link_with: rlso)
endforeach

foreach ex : tests
  test(ex.name(), ex)
endforeach



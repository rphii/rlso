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
  ]

tests = []

foreach ex : examples
  tests += executable(ex, ex + '.c', link_with: rlso)
endforeach

foreach ex : tests
  test(ex.name(), ex)
endforeach



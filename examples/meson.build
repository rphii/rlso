so = dependency('rphiiso', required: true)

examples = [
  'so',
  'so_l'
  ]

tests = []

foreach ex : examples
  tests += executable(ex, ex + '.c', dependencies: so)
endforeach

foreach ex : tests
  test(ex.name(), ex)
endforeach



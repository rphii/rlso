examples = [
  'so',
  'so_l',
  'so_input'
  ]

tests = []

foreach ex : examples
  tests += executable(ex, ex + '.c', link_with: rlso)
endforeach

foreach ex : tests
  test(ex.name(), ex)
endforeach



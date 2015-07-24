program fmain
  use simple
  implicit none
  integer :: a, b, c, d, val

  a = 1
  b = 2
  c = 3
  d = 4

  print *, 'Print in simple.print_sum3()'
  call print_sum3(a, b, c)

  print *, 'Print in fmain'
  val = sum3(a, b, c)
  print '(i2, " + ", i2, " + ", i2, " = ", i2)', a, b, c, val

  print *, 'Print in print_sum4()'
  call print_sum4(a, b, c, d)

  ! Can't call
  ! print *, 'Print in fmain'
  ! val = sum4(a, b, c, d)
  ! print '(i2, " + ", i2, " + ", i2, " + ", i2, " = ", i2)', a, b, c, d, val
end program fmain

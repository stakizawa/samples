integer function sum4(a, b, c, d)
  implicit none
  integer :: a, b, c, d
  sum4 = a + b + c + d
end function sum4

subroutine print_sum4(a, b, c, d)
  implicit none
  integer :: a, b, c, d, val
  val = a + b + c + d
  print '(i2, " + ", i2, " + ", i2, " + ", i2, " = ", i2)', a, b, c, d, val
end subroutine print_sum4

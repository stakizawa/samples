module simple
  implicit none
contains
  integer function sum3(a, b, c)
    integer :: a, b, c
    sum3 = a + b + c
  end function sum3

  subroutine print_sum3(a, b, c)
    integer :: a, b, c, val
    val = sum3(a, b, c)
    print '(i2, " + ", i2, " + ", i2, " = ", i2)', a, b, c, val
  end subroutine print_sum3
end module simple

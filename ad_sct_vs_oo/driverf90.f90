program driver
use OAD_active
use OAD_rev
implicit none
external toy_pde

type(active)::impliedVol(0:4999),price
double precision::vega
integer::i

do i=0,4999,1
   impliedVol(i)%d = 0.20d0
end do

price%d=1.0d0
our_rev_mode%tape=.true.

! native computation
!double precision:: impliedVol = 0.20, price

call toy_pde(impliedVol, price)

vega=0
do i=0,4999,1
   vega = vega + impliedVol(i)%d
end do

write(*,*) 'c = ', price%v, ' dprice/dvol = ', vega

end program driver

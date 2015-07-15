program driver
use OAD_active
use OAD_rev
implicit none
external toy_pde

integer, parameter:: n = 500

type(active)::impliedVol(0:n-1),price

double precision::vega,vega2,vega3,vega4,vega5
integer::i,runtest,runtestmax

write(*,*)'Enter number of computation loops: '
read(*,*),runtestmax

do runtest=0,runtestmax-1,1

 do i=0,n-1,1
    impliedVol(i)%v=0.20d0
 end do

 price%d=1.0d0
 our_rev_mode%tape=.true.

 call toy_pde(impliedVol, price)

 vega=0
 do i=0,n-1,1
    vega = vega + impliedVol(i)%d
 end do

 write(*,*) 'c = ',price%v, ' vega = ', vega

end do


end program driver

program driver
use OAD_active
implicit none
external toy_pde

integer, parameter:: n = 500

type(active)::impliedVol(0:n-1),price

double precision::vega
integer::i, testrun

do testrun=0,0,1
 do i=0,n-1,1
    impliedVol(i)%v=0.20d0
    impliedVol(i)%d=1.0
 end do

 call toy_pde(impliedVol, price)

 vega = price%d

 !write(*,*) 'c = ', price%v, ' dprice/dvol = ', vega
end do

end program driver

program driver
implicit none
external toy_pde

integer,parameter::n=500
integer::i,testrun
double precision::impliedVol(0:n-1),price

do testrun=0,49,1
 do i=0,n-1,1
   impliedVol(i) = 0.20d0
 end do

 call toy_pde(impliedVol, price)

 !write(*,*) 'c = ', price

end do

end program driver

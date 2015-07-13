program driver
implicit none
external toy_pde

double precision::impliedVol(0:4999),price

impliedVol=0.20d0
call toy_pde(impliedVol, price)

write(*,*) 'c = ', price

end program driver

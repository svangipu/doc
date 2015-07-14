subroutine toy_pde(impliedVol,price)
implicit none

integer, parameter:: n = 500

double precision:: impliedVol(0:n-1), price

double precision, parameter:: s0=4.605170185988092d0, k=4.787491742782046, t=10.0d0
double precision, parameter:: smin=1.07555172964d0, smax=8.13478864234d0
integer, parameter:: sizes = 101, sizet = 5000

double precision:: loc(0:sizes), c(0:1,0:sizes-1), exerciseValue(0:sizes-1)
double precision:: h, hq, dt, d1, d2, v
integer:: swap, i, j, ind

!$openad INDEPENDENT(impliedVol)

swap = 0

! initial values
h = (smax-smin)/dble(sizes-1)
hq = h*h
do j=0,sizeS-1,1
    loc(j) = smin + h*dble(j)
    c(swap,j) = max(dexp(loc(j))-dexp(K),0.0d0)
    exerciseValue(j) = c(swap,j)
end do

! PDE solver
dt = t / dble(sizeT)
do i=0,sizeT-1,1
    do j=0,sizeS-1,1
       ind = int(dble(n)*dble(i)/dble(sizeT))
       v = impliedVol(ind)
       if(j==0.or.j==sizeS-1) then
          d2=0
          d1=0 ! we do not really want this ...
       else
          d2=(c(swap,j+1)-2.0d0*c(swap,j)+c(swap,j-1))/hq
          d1 = (c(swap,j+1)-c(swap,j-1))/(2.0d0*h)
       endif
       ! ... but the following code does not build with OpenAD:
       ! if(j==0) d1 = (c(swap,j+1)-c(swap,j))/h
       ! if(j==sizeS-1) d1 = (c(swap,j)-c(swap,j-1))/h
       ! if(j>0.and.j<sizeS-1) d1 = (c(swap,j+1)-c(swap,j-1))/(2.0d0*h)
       c(1-swap,j)=c(swap,j) + 0.5 * dt * v*v * (d2-d1)
     end do
     do j=0,sizeS-1,1
        c(1-swap,j)=max(c(1-swap,j),exerciseValue(j))
     end do
     swap = 1 -swap
end do
  
! return solution
price = c(swap,(sizeS-1)/2)

!$openad DEPENDENT(price)

end subroutine toy_pde

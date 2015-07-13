subroutine toy_pde(impliedVol,price)
implicit none

double precision, parameter:: s0=4.605170185988092d0, k=4.787491742782046, t=10.0d0
double precision, parameter:: smin=1.07555172964d0, smax=8.13478864234d0
integer, parameter:: sizes = 101, sizet = 5000

double precision:: loc(0:sizes), c(0:1,0:sizes), exerciseValue(0:sizes)
double precision:: impliedVol(0:sizet-1)
double precision:: h, hq, dt, r, t0, v, d1, d2, price
integer:: swap, i, j

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
dt = T / dble(sizeT)
do i=0,sizeT-1,1
    do j=0,sizeS-1,1
        v = impliedVol(i)
        if(j==0.or.j==sizeS-1) then
           d2=0
        else
           d2=(c(swap,j+1)-2.0d0*c(swap,j)+c(swap,j-1))/hq
        endif
        if(j==0) then
           d1 = (c(swap,j+1)-c(swap,j))/h
        else
           if(j==sizeS-1) then
              d1 = (c(swap,j)-c(swap,j-1))/h
           else
              d1 = (c(swap,j+1)-c(swap,j-1))/(2.0d0*h)
           endif
        endif
        c(1-swap,j)=c(swap,j) + 0.5 * dt * v * v * (d2-d1)
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

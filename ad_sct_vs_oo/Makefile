ifndef F90C
F90C=gfortran
endif
ifndef CC
CC=gcc
endif
RTSUPP=w2f__types OAD_active OAD_cp OAD_tape OAD_rev
driverf90: $(addsuffix .o, $(RTSUPP)) driverf90.o testf90.pre.xb.x2w.w2f.post.o
	${F90C} -O3 -o $@ $^
testf90.pre.xb.x2w.w2f.post.f90 $(addsuffix .f90, $(RTSUPP)) iaddr.c : toolChain
toolChain : testf90.f90
	openad -c -m rj $<
%.o : %.f90
	${F90C} -g -O3 -o $@ -c $<
%.o : %.c
	${CC} -g -O3 -o $@ -c $<
clean:
	rm -f ad_template* OAD_* w2f__* iaddr*
	rm -f testf90.pre* *.B *.xaif *.o *.mod driver driverE *~
.PHONY: clean toolChain

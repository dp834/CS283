These two file differ from the original versions in ..\_csapp

csapp.h changes
line 41: #define RIO_BUFSIZE 32

csapp.c changes
lines 592, 593 of rio_read
write(2,rp->rio_buf,rp->rio_cnt);
write(2,"\n",1);


int log2ME(unsigned long int);

int main(){
	unsigned long int a = 0;
	a -= 1;//force underflow so all bits are 1
	printf("%d\n", log2ME(a));
	return 0;
}

int log2ME(unsigned long int in){//counts number of ones in long
	if(in == 0){
		return 0;
	}else{
		return 1 + log2ME(in>>1);	
	}
}

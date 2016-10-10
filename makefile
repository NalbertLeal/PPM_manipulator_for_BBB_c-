ALL:
	@echo "Compiling ..."
	@gcc main.c modificacao.c struct.h lerEscreverPPM.c -O3 -o main
	@echo "Compiled. Please execute the program as ./main"

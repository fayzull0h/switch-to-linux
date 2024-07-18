all: cmpeg mp3-dl

cmpeg:
	@echo "Compiling cmpeg..."
	@g++ cmpeg.cpp -o cmpeg
	@echo "Moving into bin folder"
	@sudo mv cmpeg /bin

mp3-dl:
	@echo "Compiling mp3-dl"
	@g++ mp3-dl.c -o mp3-dl
	@echo "Moving into bin folder"
	@sudo mv mp3-dl /bin

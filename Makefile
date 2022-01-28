FILE = Homework_1

build: $(FILE).c
	gcc $(FILE).c -o $(FILE)

run:
	./$(FILE)

.PHONY: usage build filters


usage:
	@echo "TODO"

build:
	g++ -std=c++20 -o build/ease-filter source/main.cxx

filters:
	@./build/ease-filter

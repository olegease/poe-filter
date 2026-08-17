.PHONY: usage build filters


usage:
	@echo "TODO"

build:
	g++ -std=c++17 -o build/ease-filter source/main.cxx

filters:
	@./build/ease-filter

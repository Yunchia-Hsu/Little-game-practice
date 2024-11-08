CXX = g++
CXXFLAGS = -std=c++11 -I/usr/local/opt/sfml/include
LDFLAGS = -L/usr/local/opt/sfml/lib -lsfml-graphics -lsfml-window -lsfml-system

# 源文件和頭文件
SOURCES = main.cpp
HEADERS = game_class.hpp
EXECUTABLE = game_1

# 主要目標
all: $(EXECUTABLE)

# 編譯可執行文件
$(EXECUTABLE): $(SOURCES) $(HEADERS)
	$(CXX) $(SOURCES) -o $(EXECUTABLE) $(CXXFLAGS) $(LDFLAGS)

# 清理編譯產生的文件
clean:
	rm -f $(EXECUTABLE) *.o

# 運行程序
run: $(EXECUTABLE)
	./$(EXECUTABLE)

# 防止與同名文件衝突
.PHONY: all clean run
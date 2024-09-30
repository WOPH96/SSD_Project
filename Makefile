# 컴파일러 설정
CXX = g++
CXXFLAGS = -Wall -g

# 타겟 실행 파일
OUTPUT_DIR = build/Debug

SSD_TARGET = execute/SSD
SHELL_TARGET = execute/test_shell

SSD_SRC_DIR = source/SSD
SHELL_SRC_DIR = source/Shell

HEADER_DIR = header

# 목적 파일 목록
SSD_OBJS = $(OUTPUT_DIR)/Ctrl_SSD.o $(OUTPUT_DIR)/SSD_class.o $(OUTPUT_DIR)/utils.o
SHELL_OBJS = $(OUTPUT_DIR)/shell_func.o $(OUTPUT_DIR)/shell.o 

# 기본 규칙: 타겟을 빌드하는 방법
$(SSD_TARGET): $(SSD_OBJS)
	$(CXX) $(SSD_OBJS) -o $(SSD_TARGET)

$(SHELL_TARGET): $(SHELL_OBJS)
	$(CXX) $(SHELL_OBJS) -o $(SHELL_TARGET)	

all: $(SSD_TARGET) $(SHELL_TARGET)
.PHONY: all
# 개별 파일 컴파일 규칙

$(OUTPUT_DIR)/shell_func.o: $(SHELL_SRC_DIR)/shell_func.cpp $(HEADER_DIR)/shell_func.h
	$(CXX) $(CXXFLAGS) -c $(SHELL_SRC_DIR)/shell_func.cpp -o $(OUTPUT_DIR)/shell_func.o

$(OUTPUT_DIR)/shell.o: $(SHELL_SRC_DIR)/test_shell.cpp $(HEADER_DIR)/shell_func.h
	$(CXX) $(CXXFLAGS) -c $(SHELL_SRC_DIR)/test_shell.cpp -o $(OUTPUT_DIR)/shell.o
	
$(OUTPUT_DIR)/Ctrl_SSD.o: $(SSD_SRC_DIR)/Ctrl_SSD.cpp $(HEADER_DIR)/SSD_class.h $(HEADER_DIR)/utils.h
	$(CXX) $(CXXFLAGS) -c $(SSD_SRC_DIR)/Ctrl_SSD.cpp -o $(OUTPUT_DIR)/Ctrl_SSD.o

$(OUTPUT_DIR)/SSD_class.o: $(SSD_SRC_DIR)/SSD_class.cpp $(HEADER_DIR)/SSD_class.h
	$(CXX) $(CXXFLAGS) -c $(SSD_SRC_DIR)/SSD_class.cpp -o $(OUTPUT_DIR)/SSD_class.o

$(OUTPUT_DIR)/utils.o: $(SSD_SRC_DIR)/utils.cpp $(HEADER_DIR)/utils.h
	$(CXX) $(CXXFLAGS) -c $(SSD_SRC_DIR)/utils.cpp -o $(OUTPUT_DIR)/utils.o

# clean 규칙: 빌드된 파일들을 삭제하는 방법
clean:
	rm -f $(SSD_OBJS) $(SHELL_OBJS)
# 목적 파일 삭제
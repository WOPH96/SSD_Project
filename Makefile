# 컴파일러 설정
CXX = g++
CXXFLAGS = -Wall -g

# 타겟 실행 파일
TARGET = execute/SSD
OUTPUT_DIR = build/Debug

# 목적 파일 목록
OBJS = $(OUTPUT_DIR)/Ctrl_SSD.o $(OUTPUT_DIR)/SSD_class.o $(OUTPUT_DIR)/utils.o

# 기본 규칙: 타겟을 빌드하는 방법
$(TARGET): $(OBJS)
	$(CXX) $(OBJS) -o $(TARGET)

# 개별 파일 컴파일 규칙
$(OUTPUT_DIR)/Ctrl_SSD.o: source/Ctrl_SSD.cpp header/SSD_class.h header/utils.h
	$(CXX) $(CXXFLAGS) -c source/Ctrl_SSD.cpp -o $(OUTPUT_DIR)/Ctrl_SSD.o

$(OUTPUT_DIR)/SSD_class.o: source/SSD_class.cpp header/SSD_class.h
	$(CXX) $(CXXFLAGS) -c source/SSD_class.cpp -o $(OUTPUT_DIR)/SSD_class.o

$(OUTPUT_DIR)/utils.o: source/utils.cpp header/utils.h
	$(CXX) $(CXXFLAGS) -c source/utils.cpp -o $(OUTPUT_DIR)/utils.o

# clean 규칙: 빌드된 파일들을 삭제하는 방법
clean:
	rm -f $(OUTPUT_DIR)/$(OBJS)
# 목적 파일 삭제
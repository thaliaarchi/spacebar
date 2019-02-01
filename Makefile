CXX = g++
CXXFLAGS = -std=c++17 -Wall -Werror
CXXFLAGS_DEBUG = -g $(CXXFLAGS)
CXXFLAGS_RELEASE = -O3 $(CXXFLAGS)
CXXFLAGS_VERBOSE = $(CXXFLAGS) -pedantic -Wextra -Wcast-align -Wcast-qual \
	-Wctor-dtor-privacy -Wdisabled-optimization -Wformat=2 -Winit-self \
	-Wlogical-op -Wmissing-declarations -Wmissing-include-dirs -Wnoexcept \
	-Wno-unused -Wold-style-cast -Woverloaded-virtual -Wredundant-decls \
	-Wsign-conversion -Wsign-promo -Wstrict-null-sentinel -Wstrict-overflow=5 \
	-Wswitch-default -Wundef

EXECUTABLE = spacebar
SRC := ./src
BIN := ./bin
SOURCES := $(wildcard $(SRC)/*.cpp)
HEADERS := $(wildcard $(SRC)/*.h)
OBJECTS := $(subst $(SRC), $(BIN), $(patsubst %.cpp, %.o, $(SOURCES)))

.PHONY: all debug release verbose clean
.SECONDARY:

all: $(EXECUTABLE)

debug: CXXFLAGS := $(CXXFLAGS_DEBUG)
debug: all

release: CXXFLAGS := $(CXXFLAGS_RELEASE)
release: all

verbose: CXXFLAGS := $(CXXFLAGS_VERBOSE)
verbose: all

$(EXECUTABLE): $(OBJECTS)
	$(CXX) $(CXXFLAGS) -o $@ $^

# Header changes should recompile dependents,
# so all headers are included as a workaround
$(BIN)/%.o: $(SRC)/%.cpp $(HEADERS)
	@mkdir -p $(BIN)
	$(CXX) $(CXXFLAGS) -c -o $@ $<

clean:
	rm -rf $(BIN)

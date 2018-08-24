
file(GLOB hdrs 
	"compression.h"
)

file(GLOB srcs 
	"binzip.cpp"
)

add_executable(binzip ${hdrs} ${srcs})

target_link_libraries(binzip zlib.lib)

install(TARGETS binzip DESTINATION .)
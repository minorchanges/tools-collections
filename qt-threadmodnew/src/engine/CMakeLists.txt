list(APPEND sourceFiles
	"${CMAKE_CURRENT_LIST_DIR}/engine.cpp"
)

list(APPEND includeDirs "${CMAKE_CURRENT_LIST_DIR}")

set(sourceFiles ${sourceFiles} PARENT_SCOPE)
set(includeDirs ${includeDirs} PARENT_SCOPE)

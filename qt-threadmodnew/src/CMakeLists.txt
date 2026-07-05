add_subdirectory(engine)

list(APPEND sourceFiles
	"${CMAKE_CURRENT_LIST_DIR}/main.cpp"
	"${CMAKE_CURRENT_LIST_DIR}/mainwindow.cpp"
	"${CMAKE_CURRENT_LIST_DIR}/mainwindow.ui"
)

list(APPEND includeDirs "${CMAKE_CURRENT_LIST_DIR}")

set(sourceFiles ${sourceFiles} PARENT_SCOPE)
set(includeDirs ${includeDirs} PARENT_SCOPE)

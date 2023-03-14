macro(optional_target_link_libraries NAME)
  if(TARGET ${NAME})
    target_link_libraries(${NAME} ${ARGN})
  endif(TARGET ${NAME})
endmacro(optional_target_link_libraries)
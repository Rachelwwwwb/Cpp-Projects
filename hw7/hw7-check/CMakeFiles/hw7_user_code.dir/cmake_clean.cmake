file(REMOVE_RECURSE
  "libhw7_user_code.pdb"
  "libhw7_user_code.a"
)

# Per-language clean rules from dependency scanning.
foreach(lang )
  include(CMakeFiles/hw7_user_code.dir/cmake_clean_${lang}.cmake OPTIONAL)
endforeach()

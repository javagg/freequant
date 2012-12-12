require 'mkmf'
%w{stdc++ freequant}.each do |lib| 
  $libs = append_library $libs, lib 
end

create_makefile 'freequant'  

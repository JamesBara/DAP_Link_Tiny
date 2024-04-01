add_library(stm32l412_system OBJECT
	src/stm32l412_startup.c
	src/stm32l412_system.c
	src/ffrestanding_memset.c
	src/ffrestanding_memcpy.c



 )

target_include_directories(stm32l412_system INTERFACE
	inc
	CMSIS
)

target_include_directories(stm32l412_system PRIVATE
	inc
	CMSIS
)
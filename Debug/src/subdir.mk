################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/color_resolve.c \
../src/nbclib.c 

C_DEPS += \
./src/color_resolve.d \
./src/nbclib.d 

OBJS += \
./src/color_resolve.o \
./src/nbclib.o 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.c src/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


clean: clean-src

clean-src:
	-$(RM) ./src/color_resolve.d ./src/color_resolve.o ./src/nbclib.d ./src/nbclib.o

.PHONY: clean-src


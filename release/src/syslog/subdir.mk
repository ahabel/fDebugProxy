################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/syslog/fsyslog.cpp 

OBJS += \
./src/syslog/fsyslog.o 

CPP_DEPS += \
./src/syslog/fsyslog.d 


# Each subdirectory must supply rules for building sources it contributes
src/syslog/%.o: ../src/syslog/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -I"../include" -O3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '



################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/fconfig/fconfig.cpp \
../src/fconfig/storage.fconfig.cpp 

OBJS += \
./src/fconfig/fconfig.o \
./src/fconfig/storage.fconfig.o 

CPP_DEPS += \
./src/fconfig/fconfig.d \
./src/fconfig/storage.fconfig.d 


# Each subdirectory must supply rules for building sources it contributes
src/fconfig/%.o: ../src/fconfig/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -I"/storage/webspace/fdebug-proxy/include" -O3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '



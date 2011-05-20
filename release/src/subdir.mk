################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/fdebugmessage.cpp \
../src/fdebugproxy.cpp \
../src/fdebugsocket.cpp \
../src/proxy.cpp 

OBJS += \
./src/fdebugmessage.o \
./src/fdebugproxy.o \
./src/fdebugsocket.o \
./src/proxy.o 

CPP_DEPS += \
./src/fdebugmessage.d \
./src/fdebugproxy.d \
./src/fdebugsocket.d \
./src/proxy.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -I"../include" -O3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '



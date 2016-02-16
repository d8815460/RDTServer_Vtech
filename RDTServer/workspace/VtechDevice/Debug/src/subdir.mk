################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/VtechGarageDoorDevice.cpp \
../src/VtechIPHubGatewayDevice.cpp \
../src/VtechLightBulbDevice.cpp \
../src/VtechMotionSensorDevice.cpp \
../src/VtechOpenClosedDevice.cpp \
../src/VtechVirtualGroupDevice.cpp \
../src/VtechWallSwitchDevice.cpp \
../src/main.cpp 

OBJS += \
./src/VtechGarageDoorDevice.o \
./src/VtechIPHubGatewayDevice.o \
./src/VtechLightBulbDevice.o \
./src/VtechMotionSensorDevice.o \
./src/VtechOpenClosedDevice.o \
./src/VtechVirtualGroupDevice.o \
./src/VtechWallSwitchDevice.o \
./src/main.o 

CPP_DEPS += \
./src/VtechGarageDoorDevice.d \
./src/VtechIPHubGatewayDevice.d \
./src/VtechLightBulbDevice.d \
./src/VtechMotionSensorDevice.d \
./src/VtechOpenClosedDevice.d \
./src/VtechVirtualGroupDevice.d \
./src/VtechWallSwitchDevice.d \
./src/main.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '



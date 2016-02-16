################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/BinraryRDTClientCommand.cpp \
../src/BinraryRDTClientConnect.cpp \
../src/BinraryRDTServerCommand.cpp \
../src/BinraryRDTServerConnect.cpp \
../src/Command.cpp \
../src/Connect.cpp \
../src/Device.cpp \
../src/JsonRDTClientCommand.cpp \
../src/JsonRDTCommand.cpp \
../src/JsonRDTServerCommand.cpp \
../src/UTF.cpp \
../src/Utility.cpp 

OBJS += \
./src/BinraryRDTClientCommand.o \
./src/BinraryRDTClientConnect.o \
./src/BinraryRDTServerCommand.o \
./src/BinraryRDTServerConnect.o \
./src/Command.o \
./src/Connect.o \
./src/Device.o \
./src/JsonRDTClientCommand.o \
./src/JsonRDTCommand.o \
./src/JsonRDTServerCommand.o \
./src/UTF.o \
./src/Utility.o 

CPP_DEPS += \
./src/BinraryRDTClientCommand.d \
./src/BinraryRDTClientConnect.d \
./src/BinraryRDTServerCommand.d \
./src/BinraryRDTServerConnect.d \
./src/Command.d \
./src/Connect.d \
./src/Device.d \
./src/JsonRDTClientCommand.d \
./src/JsonRDTCommand.d \
./src/JsonRDTServerCommand.d \
./src/UTF.d \
./src/Utility.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -I/media/sf_RDTServer_Vtech/TUTK_Kalay_Platform_SDK_2.1.3/Include -O0 -g3 -Wall -c -fmessage-length=0 -v -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '



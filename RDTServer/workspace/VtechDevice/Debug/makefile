################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include src/subdir.mk
-include subdir.mk
-include objects.mk
CPP_DEPS += src/stdafx.h.gch.d

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(C++_DEPS)),)
-include $(C++_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
ifneq ($(strip $(CC_DEPS)),)
-include $(CC_DEPS)
endif
ifneq ($(strip $(CPP_DEPS)),)
-include $(CPP_DEPS)
endif
ifneq ($(strip $(CXX_DEPS)),)
-include $(CXX_DEPS)
endif
ifneq ($(strip $(C_UPPER_DEPS)),)
-include $(C_UPPER_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 

# All Target
all: VtechDevice

# Tool invocations
VtechDevice: $(OBJS) $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: Cross G++ Linker'
	g++  -o "VtechDevice" $(OBJS) $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '

# Other Targets
clean:
	rm -f src/stdafx.h.gch.d ../src/stdafx.h.gch
	-$(RM) $(C++_DEPS)$(OBJS)$(C_DEPS)$(CC_DEPS)$(CPP_DEPS)$(EXECUTABLES)$(CXX_DEPS)$(C_UPPER_DEPS) VtechDevice
	-@echo ' '

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets

$(OBJS):%.o:../src/stdafx.h.gch


../src/stdafx.h.gch: ../src/stdafx.h ../.cproject ../.project
	g++ -I"/home/jakey/sf_RDTServer_Vtech/RDTServer/RDTServer/DeviceAPI" -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"src/stdafx.h.gch.d" -MT"src/stdafx.h.gch.d" -o "$@" "$<"
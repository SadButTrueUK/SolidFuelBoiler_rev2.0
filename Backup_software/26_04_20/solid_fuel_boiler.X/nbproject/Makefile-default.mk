#
# Generated Makefile - do not edit!
#
# Edit the Makefile in the project folder instead (../Makefile). Each target
# has a -pre and a -post target defined where you can add customized code.
#
# This makefile implements configuration specific macros and targets.


# Include project Makefile
ifeq "${IGNORE_LOCAL}" "TRUE"
# do not include local makefile. User is passing all local related variables already
else
include Makefile
# Include makefile containing local settings
ifeq "$(wildcard nbproject/Makefile-local-default.mk)" "nbproject/Makefile-local-default.mk"
include nbproject/Makefile-local-default.mk
endif
endif

# Environment
MKDIR=gnumkdir -p
RM=rm -f 
MV=mv 
CP=cp 

# Macros
CND_CONF=default
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
IMAGE_TYPE=debug
OUTPUT_SUFFIX=cof
DEBUGGABLE_SUFFIX=cof
FINAL_IMAGE=dist/${CND_CONF}/${IMAGE_TYPE}/solid_fuel_boiler.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
else
IMAGE_TYPE=production
OUTPUT_SUFFIX=hex
DEBUGGABLE_SUFFIX=cof
FINAL_IMAGE=dist/${CND_CONF}/${IMAGE_TYPE}/solid_fuel_boiler.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
endif

ifeq ($(COMPARE_BUILD), true)
COMPARISON_BUILD=
else
COMPARISON_BUILD=
endif

ifdef SUB_IMAGE_ADDRESS

else
SUB_IMAGE_ADDRESS_COMMAND=
endif

# Object Directory
OBJECTDIR=build/${CND_CONF}/${IMAGE_TYPE}

# Distribution Directory
DISTDIR=dist/${CND_CONF}/${IMAGE_TYPE}

# Source Files Quoted if spaced
SOURCEFILES_QUOTED_IF_SPACED=../src/Interrupts/interrupts.c ../src/Main/main.c ../src/Menu/menu.c ../src/Module_analog_inputs/module_analog_inputs.c ../src/Module_fan/module_fan.c ../src/Module_indication/module_indication.c ../src/Module_logic_inputs/module_logic_inputs.c ../src/Module_management/module_management.c ../src/Module_motor/module_motor.c ../src/Module_sound/module_sound.c ../src/OSA/osa.c ../src/Task_analog_inputs/task_analog_inputs.c ../src/Task_logic_inputs/task_logic_inputs.c ../src/Task_management/task_management.c ../src/Task_motors/task_motors.c ../src/Task_outs/task_outs.c ../src/Drivers/i2c.c ../src/EEPROMmemory/eeprom.c ../src/Drivers/spi.c ../src/DebugTools/logicAnalyzer.c ../src/EEPROMmemory/crc8.c

# Object Files Quoted if spaced
OBJECTFILES_QUOTED_IF_SPACED=${OBJECTDIR}/_ext/1695876150/interrupts.o ${OBJECTDIR}/_ext/1020072301/main.o ${OBJECTDIR}/_ext/1020068295/menu.o ${OBJECTDIR}/_ext/6916191/module_analog_inputs.o ${OBJECTDIR}/_ext/978868198/module_fan.o ${OBJECTDIR}/_ext/381719947/module_indication.o ${OBJECTDIR}/_ext/1550195517/module_logic_inputs.o ${OBJECTDIR}/_ext/1584532132/module_management.o ${OBJECTDIR}/_ext/87609412/module_motor.o ${OBJECTDIR}/_ext/82067370/module_sound.o ${OBJECTDIR}/_ext/659832547/osa.o ${OBJECTDIR}/_ext/1688643128/task_analog_inputs.o ${OBJECTDIR}/_ext/1690642378/task_logic_inputs.o ${OBJECTDIR}/_ext/1058255325/task_management.o ${OBJECTDIR}/_ext/1516331906/task_motors.o ${OBJECTDIR}/_ext/1485309755/task_outs.o ${OBJECTDIR}/_ext/990863823/i2c.o ${OBJECTDIR}/_ext/1375153083/eeprom.o ${OBJECTDIR}/_ext/990863823/spi.o ${OBJECTDIR}/_ext/1959551838/logicAnalyzer.o ${OBJECTDIR}/_ext/1375153083/crc8.o
POSSIBLE_DEPFILES=${OBJECTDIR}/_ext/1695876150/interrupts.o.d ${OBJECTDIR}/_ext/1020072301/main.o.d ${OBJECTDIR}/_ext/1020068295/menu.o.d ${OBJECTDIR}/_ext/6916191/module_analog_inputs.o.d ${OBJECTDIR}/_ext/978868198/module_fan.o.d ${OBJECTDIR}/_ext/381719947/module_indication.o.d ${OBJECTDIR}/_ext/1550195517/module_logic_inputs.o.d ${OBJECTDIR}/_ext/1584532132/module_management.o.d ${OBJECTDIR}/_ext/87609412/module_motor.o.d ${OBJECTDIR}/_ext/82067370/module_sound.o.d ${OBJECTDIR}/_ext/659832547/osa.o.d ${OBJECTDIR}/_ext/1688643128/task_analog_inputs.o.d ${OBJECTDIR}/_ext/1690642378/task_logic_inputs.o.d ${OBJECTDIR}/_ext/1058255325/task_management.o.d ${OBJECTDIR}/_ext/1516331906/task_motors.o.d ${OBJECTDIR}/_ext/1485309755/task_outs.o.d ${OBJECTDIR}/_ext/990863823/i2c.o.d ${OBJECTDIR}/_ext/1375153083/eeprom.o.d ${OBJECTDIR}/_ext/990863823/spi.o.d ${OBJECTDIR}/_ext/1959551838/logicAnalyzer.o.d ${OBJECTDIR}/_ext/1375153083/crc8.o.d

# Object Files
OBJECTFILES=${OBJECTDIR}/_ext/1695876150/interrupts.o ${OBJECTDIR}/_ext/1020072301/main.o ${OBJECTDIR}/_ext/1020068295/menu.o ${OBJECTDIR}/_ext/6916191/module_analog_inputs.o ${OBJECTDIR}/_ext/978868198/module_fan.o ${OBJECTDIR}/_ext/381719947/module_indication.o ${OBJECTDIR}/_ext/1550195517/module_logic_inputs.o ${OBJECTDIR}/_ext/1584532132/module_management.o ${OBJECTDIR}/_ext/87609412/module_motor.o ${OBJECTDIR}/_ext/82067370/module_sound.o ${OBJECTDIR}/_ext/659832547/osa.o ${OBJECTDIR}/_ext/1688643128/task_analog_inputs.o ${OBJECTDIR}/_ext/1690642378/task_logic_inputs.o ${OBJECTDIR}/_ext/1058255325/task_management.o ${OBJECTDIR}/_ext/1516331906/task_motors.o ${OBJECTDIR}/_ext/1485309755/task_outs.o ${OBJECTDIR}/_ext/990863823/i2c.o ${OBJECTDIR}/_ext/1375153083/eeprom.o ${OBJECTDIR}/_ext/990863823/spi.o ${OBJECTDIR}/_ext/1959551838/logicAnalyzer.o ${OBJECTDIR}/_ext/1375153083/crc8.o

# Source Files
SOURCEFILES=../src/Interrupts/interrupts.c ../src/Main/main.c ../src/Menu/menu.c ../src/Module_analog_inputs/module_analog_inputs.c ../src/Module_fan/module_fan.c ../src/Module_indication/module_indication.c ../src/Module_logic_inputs/module_logic_inputs.c ../src/Module_management/module_management.c ../src/Module_motor/module_motor.c ../src/Module_sound/module_sound.c ../src/OSA/osa.c ../src/Task_analog_inputs/task_analog_inputs.c ../src/Task_logic_inputs/task_logic_inputs.c ../src/Task_management/task_management.c ../src/Task_motors/task_motors.c ../src/Task_outs/task_outs.c ../src/Drivers/i2c.c ../src/EEPROMmemory/eeprom.c ../src/Drivers/spi.c ../src/DebugTools/logicAnalyzer.c ../src/EEPROMmemory/crc8.c



CFLAGS=
ASFLAGS=
LDLIBSOPTIONS=

############# Tool locations ##########################################
# If you copy a project from one host to another, the path where the  #
# compiler is installed may be different.                             #
# If you open this project with MPLAB X in the new host, this         #
# makefile will be regenerated and the paths will be corrected.       #
#######################################################################
# fixDeps replaces a bunch of sed/cat/printf statements that slow down the build
FIXDEPS=fixDeps

.build-conf:  ${BUILD_SUBPROJECTS}
ifneq ($(INFORMATION_MESSAGE), )
	@echo $(INFORMATION_MESSAGE)
endif
	${MAKE}  -f nbproject/Makefile-default.mk dist/${CND_CONF}/${IMAGE_TYPE}/solid_fuel_boiler.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}

MP_PROCESSOR_OPTION=18F87J50
MP_PROCESSOR_OPTION_LD=18f87j50
MP_LINKER_DEBUG_OPTION=  -u_DEBUGSTACK
# ------------------------------------------------------------------------------------
# Rules for buildStep: assemble
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
else
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: compile
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
${OBJECTDIR}/_ext/1695876150/interrupts.o: ../src/Interrupts/interrupts.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1695876150" 
	@${RM} ${OBJECTDIR}/_ext/1695876150/interrupts.o.d 
	@${RM} ${OBJECTDIR}/_ext/1695876150/interrupts.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -p$(MP_PROCESSOR_OPTION) -w3 -I"../src/EEPROMmemory" -I"../src/Interrupts" -I"../src/Main" -I"../src/Menu" -I"../src/Module_analog_inputs" -I"../src/Module_fan" -I"../src/Module_indication" -I"../src/Module_logic_inputs" -I"../src/Module_management" -I"../src/Module_motor" -I"../src/Module_sound" -I"../src/OSA" -I"../src/System" -I"../src/Task_analog_inputs" -I"../src/Task_logic_inputs" -I"../src/Task_management" -I"../src/Task_motors" -I"../src/Task_outs" -I"../src/osa" -I"." -I"../src/Drivers" -I"../src/DebugTools" -ms -oa-  -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/_ext/1695876150/interrupts.o   ../src/Interrupts/interrupts.c 
	@${DEP_GEN} -d ${OBJECTDIR}/_ext/1695876150/interrupts.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1695876150/interrupts.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c18 
	
${OBJECTDIR}/_ext/1020072301/main.o: ../src/Main/main.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1020072301" 
	@${RM} ${OBJECTDIR}/_ext/1020072301/main.o.d 
	@${RM} ${OBJECTDIR}/_ext/1020072301/main.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -p$(MP_PROCESSOR_OPTION) -w3 -I"../src/EEPROMmemory" -I"../src/Interrupts" -I"../src/Main" -I"../src/Menu" -I"../src/Module_analog_inputs" -I"../src/Module_fan" -I"../src/Module_indication" -I"../src/Module_logic_inputs" -I"../src/Module_management" -I"../src/Module_motor" -I"../src/Module_sound" -I"../src/OSA" -I"../src/System" -I"../src/Task_analog_inputs" -I"../src/Task_logic_inputs" -I"../src/Task_management" -I"../src/Task_motors" -I"../src/Task_outs" -I"../src/osa" -I"." -I"../src/Drivers" -I"../src/DebugTools" -ms -oa-  -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/_ext/1020072301/main.o   ../src/Main/main.c 
	@${DEP_GEN} -d ${OBJECTDIR}/_ext/1020072301/main.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1020072301/main.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c18 
	
${OBJECTDIR}/_ext/1020068295/menu.o: ../src/Menu/menu.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1020068295" 
	@${RM} ${OBJECTDIR}/_ext/1020068295/menu.o.d 
	@${RM} ${OBJECTDIR}/_ext/1020068295/menu.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -p$(MP_PROCESSOR_OPTION) -w3 -I"../src/EEPROMmemory" -I"../src/Interrupts" -I"../src/Main" -I"../src/Menu" -I"../src/Module_analog_inputs" -I"../src/Module_fan" -I"../src/Module_indication" -I"../src/Module_logic_inputs" -I"../src/Module_management" -I"../src/Module_motor" -I"../src/Module_sound" -I"../src/OSA" -I"../src/System" -I"../src/Task_analog_inputs" -I"../src/Task_logic_inputs" -I"../src/Task_management" -I"../src/Task_motors" -I"../src/Task_outs" -I"../src/osa" -I"." -I"../src/Drivers" -I"../src/DebugTools" -ms -oa-  -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/_ext/1020068295/menu.o   ../src/Menu/menu.c 
	@${DEP_GEN} -d ${OBJECTDIR}/_ext/1020068295/menu.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1020068295/menu.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c18 
	
${OBJECTDIR}/_ext/6916191/module_analog_inputs.o: ../src/Module_analog_inputs/module_analog_inputs.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/6916191" 
	@${RM} ${OBJECTDIR}/_ext/6916191/module_analog_inputs.o.d 
	@${RM} ${OBJECTDIR}/_ext/6916191/module_analog_inputs.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -p$(MP_PROCESSOR_OPTION) -w3 -I"../src/EEPROMmemory" -I"../src/Interrupts" -I"../src/Main" -I"../src/Menu" -I"../src/Module_analog_inputs" -I"../src/Module_fan" -I"../src/Module_indication" -I"../src/Module_logic_inputs" -I"../src/Module_management" -I"../src/Module_motor" -I"../src/Module_sound" -I"../src/OSA" -I"../src/System" -I"../src/Task_analog_inputs" -I"../src/Task_logic_inputs" -I"../src/Task_management" -I"../src/Task_motors" -I"../src/Task_outs" -I"../src/osa" -I"." -I"../src/Drivers" -I"../src/DebugTools" -ms -oa-  -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/_ext/6916191/module_analog_inputs.o   ../src/Module_analog_inputs/module_analog_inputs.c 
	@${DEP_GEN} -d ${OBJECTDIR}/_ext/6916191/module_analog_inputs.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/6916191/module_analog_inputs.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c18 
	
${OBJECTDIR}/_ext/978868198/module_fan.o: ../src/Module_fan/module_fan.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/978868198" 
	@${RM} ${OBJECTDIR}/_ext/978868198/module_fan.o.d 
	@${RM} ${OBJECTDIR}/_ext/978868198/module_fan.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -p$(MP_PROCESSOR_OPTION) -w3 -I"../src/EEPROMmemory" -I"../src/Interrupts" -I"../src/Main" -I"../src/Menu" -I"../src/Module_analog_inputs" -I"../src/Module_fan" -I"../src/Module_indication" -I"../src/Module_logic_inputs" -I"../src/Module_management" -I"../src/Module_motor" -I"../src/Module_sound" -I"../src/OSA" -I"../src/System" -I"../src/Task_analog_inputs" -I"../src/Task_logic_inputs" -I"../src/Task_management" -I"../src/Task_motors" -I"../src/Task_outs" -I"../src/osa" -I"." -I"../src/Drivers" -I"../src/DebugTools" -ms -oa-  -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/_ext/978868198/module_fan.o   ../src/Module_fan/module_fan.c 
	@${DEP_GEN} -d ${OBJECTDIR}/_ext/978868198/module_fan.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/978868198/module_fan.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c18 
	
${OBJECTDIR}/_ext/381719947/module_indication.o: ../src/Module_indication/module_indication.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/381719947" 
	@${RM} ${OBJECTDIR}/_ext/381719947/module_indication.o.d 
	@${RM} ${OBJECTDIR}/_ext/381719947/module_indication.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -p$(MP_PROCESSOR_OPTION) -w3 -I"../src/EEPROMmemory" -I"../src/Interrupts" -I"../src/Main" -I"../src/Menu" -I"../src/Module_analog_inputs" -I"../src/Module_fan" -I"../src/Module_indication" -I"../src/Module_logic_inputs" -I"../src/Module_management" -I"../src/Module_motor" -I"../src/Module_sound" -I"../src/OSA" -I"../src/System" -I"../src/Task_analog_inputs" -I"../src/Task_logic_inputs" -I"../src/Task_management" -I"../src/Task_motors" -I"../src/Task_outs" -I"../src/osa" -I"." -I"../src/Drivers" -I"../src/DebugTools" -ms -oa-  -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/_ext/381719947/module_indication.o   ../src/Module_indication/module_indication.c 
	@${DEP_GEN} -d ${OBJECTDIR}/_ext/381719947/module_indication.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/381719947/module_indication.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c18 
	
${OBJECTDIR}/_ext/1550195517/module_logic_inputs.o: ../src/Module_logic_inputs/module_logic_inputs.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1550195517" 
	@${RM} ${OBJECTDIR}/_ext/1550195517/module_logic_inputs.o.d 
	@${RM} ${OBJECTDIR}/_ext/1550195517/module_logic_inputs.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -p$(MP_PROCESSOR_OPTION) -w3 -I"../src/EEPROMmemory" -I"../src/Interrupts" -I"../src/Main" -I"../src/Menu" -I"../src/Module_analog_inputs" -I"../src/Module_fan" -I"../src/Module_indication" -I"../src/Module_logic_inputs" -I"../src/Module_management" -I"../src/Module_motor" -I"../src/Module_sound" -I"../src/OSA" -I"../src/System" -I"../src/Task_analog_inputs" -I"../src/Task_logic_inputs" -I"../src/Task_management" -I"../src/Task_motors" -I"../src/Task_outs" -I"../src/osa" -I"." -I"../src/Drivers" -I"../src/DebugTools" -ms -oa-  -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/_ext/1550195517/module_logic_inputs.o   ../src/Module_logic_inputs/module_logic_inputs.c 
	@${DEP_GEN} -d ${OBJECTDIR}/_ext/1550195517/module_logic_inputs.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1550195517/module_logic_inputs.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c18 
	
${OBJECTDIR}/_ext/1584532132/module_management.o: ../src/Module_management/module_management.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1584532132" 
	@${RM} ${OBJECTDIR}/_ext/1584532132/module_management.o.d 
	@${RM} ${OBJECTDIR}/_ext/1584532132/module_management.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -p$(MP_PROCESSOR_OPTION) -w3 -I"../src/EEPROMmemory" -I"../src/Interrupts" -I"../src/Main" -I"../src/Menu" -I"../src/Module_analog_inputs" -I"../src/Module_fan" -I"../src/Module_indication" -I"../src/Module_logic_inputs" -I"../src/Module_management" -I"../src/Module_motor" -I"../src/Module_sound" -I"../src/OSA" -I"../src/System" -I"../src/Task_analog_inputs" -I"../src/Task_logic_inputs" -I"../src/Task_management" -I"../src/Task_motors" -I"../src/Task_outs" -I"../src/osa" -I"." -I"../src/Drivers" -I"../src/DebugTools" -ms -oa-  -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/_ext/1584532132/module_management.o   ../src/Module_management/module_management.c 
	@${DEP_GEN} -d ${OBJECTDIR}/_ext/1584532132/module_management.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1584532132/module_management.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c18 
	
${OBJECTDIR}/_ext/87609412/module_motor.o: ../src/Module_motor/module_motor.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/87609412" 
	@${RM} ${OBJECTDIR}/_ext/87609412/module_motor.o.d 
	@${RM} ${OBJECTDIR}/_ext/87609412/module_motor.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -p$(MP_PROCESSOR_OPTION) -w3 -I"../src/EEPROMmemory" -I"../src/Interrupts" -I"../src/Main" -I"../src/Menu" -I"../src/Module_analog_inputs" -I"../src/Module_fan" -I"../src/Module_indication" -I"../src/Module_logic_inputs" -I"../src/Module_management" -I"../src/Module_motor" -I"../src/Module_sound" -I"../src/OSA" -I"../src/System" -I"../src/Task_analog_inputs" -I"../src/Task_logic_inputs" -I"../src/Task_management" -I"../src/Task_motors" -I"../src/Task_outs" -I"../src/osa" -I"." -I"../src/Drivers" -I"../src/DebugTools" -ms -oa-  -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/_ext/87609412/module_motor.o   ../src/Module_motor/module_motor.c 
	@${DEP_GEN} -d ${OBJECTDIR}/_ext/87609412/module_motor.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/87609412/module_motor.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c18 
	
${OBJECTDIR}/_ext/82067370/module_sound.o: ../src/Module_sound/module_sound.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/82067370" 
	@${RM} ${OBJECTDIR}/_ext/82067370/module_sound.o.d 
	@${RM} ${OBJECTDIR}/_ext/82067370/module_sound.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -p$(MP_PROCESSOR_OPTION) -w3 -I"../src/EEPROMmemory" -I"../src/Interrupts" -I"../src/Main" -I"../src/Menu" -I"../src/Module_analog_inputs" -I"../src/Module_fan" -I"../src/Module_indication" -I"../src/Module_logic_inputs" -I"../src/Module_management" -I"../src/Module_motor" -I"../src/Module_sound" -I"../src/OSA" -I"../src/System" -I"../src/Task_analog_inputs" -I"../src/Task_logic_inputs" -I"../src/Task_management" -I"../src/Task_motors" -I"../src/Task_outs" -I"../src/osa" -I"." -I"../src/Drivers" -I"../src/DebugTools" -ms -oa-  -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/_ext/82067370/module_sound.o   ../src/Module_sound/module_sound.c 
	@${DEP_GEN} -d ${OBJECTDIR}/_ext/82067370/module_sound.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/82067370/module_sound.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c18 
	
${OBJECTDIR}/_ext/659832547/osa.o: ../src/OSA/osa.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/659832547" 
	@${RM} ${OBJECTDIR}/_ext/659832547/osa.o.d 
	@${RM} ${OBJECTDIR}/_ext/659832547/osa.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -p$(MP_PROCESSOR_OPTION) -w3 -I"../src/EEPROMmemory" -I"../src/Interrupts" -I"../src/Main" -I"../src/Menu" -I"../src/Module_analog_inputs" -I"../src/Module_fan" -I"../src/Module_indication" -I"../src/Module_logic_inputs" -I"../src/Module_management" -I"../src/Module_motor" -I"../src/Module_sound" -I"../src/OSA" -I"../src/System" -I"../src/Task_analog_inputs" -I"../src/Task_logic_inputs" -I"../src/Task_management" -I"../src/Task_motors" -I"../src/Task_outs" -I"../src/osa" -I"." -I"../src/Drivers" -I"../src/DebugTools" -ms -oa-  -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/_ext/659832547/osa.o   ../src/OSA/osa.c 
	@${DEP_GEN} -d ${OBJECTDIR}/_ext/659832547/osa.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/659832547/osa.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c18 
	
${OBJECTDIR}/_ext/1688643128/task_analog_inputs.o: ../src/Task_analog_inputs/task_analog_inputs.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1688643128" 
	@${RM} ${OBJECTDIR}/_ext/1688643128/task_analog_inputs.o.d 
	@${RM} ${OBJECTDIR}/_ext/1688643128/task_analog_inputs.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -p$(MP_PROCESSOR_OPTION) -w3 -I"../src/EEPROMmemory" -I"../src/Interrupts" -I"../src/Main" -I"../src/Menu" -I"../src/Module_analog_inputs" -I"../src/Module_fan" -I"../src/Module_indication" -I"../src/Module_logic_inputs" -I"../src/Module_management" -I"../src/Module_motor" -I"../src/Module_sound" -I"../src/OSA" -I"../src/System" -I"../src/Task_analog_inputs" -I"../src/Task_logic_inputs" -I"../src/Task_management" -I"../src/Task_motors" -I"../src/Task_outs" -I"../src/osa" -I"." -I"../src/Drivers" -I"../src/DebugTools" -ms -oa-  -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/_ext/1688643128/task_analog_inputs.o   ../src/Task_analog_inputs/task_analog_inputs.c 
	@${DEP_GEN} -d ${OBJECTDIR}/_ext/1688643128/task_analog_inputs.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1688643128/task_analog_inputs.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c18 
	
${OBJECTDIR}/_ext/1690642378/task_logic_inputs.o: ../src/Task_logic_inputs/task_logic_inputs.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1690642378" 
	@${RM} ${OBJECTDIR}/_ext/1690642378/task_logic_inputs.o.d 
	@${RM} ${OBJECTDIR}/_ext/1690642378/task_logic_inputs.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -p$(MP_PROCESSOR_OPTION) -w3 -I"../src/EEPROMmemory" -I"../src/Interrupts" -I"../src/Main" -I"../src/Menu" -I"../src/Module_analog_inputs" -I"../src/Module_fan" -I"../src/Module_indication" -I"../src/Module_logic_inputs" -I"../src/Module_management" -I"../src/Module_motor" -I"../src/Module_sound" -I"../src/OSA" -I"../src/System" -I"../src/Task_analog_inputs" -I"../src/Task_logic_inputs" -I"../src/Task_management" -I"../src/Task_motors" -I"../src/Task_outs" -I"../src/osa" -I"." -I"../src/Drivers" -I"../src/DebugTools" -ms -oa-  -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/_ext/1690642378/task_logic_inputs.o   ../src/Task_logic_inputs/task_logic_inputs.c 
	@${DEP_GEN} -d ${OBJECTDIR}/_ext/1690642378/task_logic_inputs.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1690642378/task_logic_inputs.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c18 
	
${OBJECTDIR}/_ext/1058255325/task_management.o: ../src/Task_management/task_management.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1058255325" 
	@${RM} ${OBJECTDIR}/_ext/1058255325/task_management.o.d 
	@${RM} ${OBJECTDIR}/_ext/1058255325/task_management.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -p$(MP_PROCESSOR_OPTION) -w3 -I"../src/EEPROMmemory" -I"../src/Interrupts" -I"../src/Main" -I"../src/Menu" -I"../src/Module_analog_inputs" -I"../src/Module_fan" -I"../src/Module_indication" -I"../src/Module_logic_inputs" -I"../src/Module_management" -I"../src/Module_motor" -I"../src/Module_sound" -I"../src/OSA" -I"../src/System" -I"../src/Task_analog_inputs" -I"../src/Task_logic_inputs" -I"../src/Task_management" -I"../src/Task_motors" -I"../src/Task_outs" -I"../src/osa" -I"." -I"../src/Drivers" -I"../src/DebugTools" -ms -oa-  -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/_ext/1058255325/task_management.o   ../src/Task_management/task_management.c 
	@${DEP_GEN} -d ${OBJECTDIR}/_ext/1058255325/task_management.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1058255325/task_management.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c18 
	
${OBJECTDIR}/_ext/1516331906/task_motors.o: ../src/Task_motors/task_motors.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1516331906" 
	@${RM} ${OBJECTDIR}/_ext/1516331906/task_motors.o.d 
	@${RM} ${OBJECTDIR}/_ext/1516331906/task_motors.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -p$(MP_PROCESSOR_OPTION) -w3 -I"../src/EEPROMmemory" -I"../src/Interrupts" -I"../src/Main" -I"../src/Menu" -I"../src/Module_analog_inputs" -I"../src/Module_fan" -I"../src/Module_indication" -I"../src/Module_logic_inputs" -I"../src/Module_management" -I"../src/Module_motor" -I"../src/Module_sound" -I"../src/OSA" -I"../src/System" -I"../src/Task_analog_inputs" -I"../src/Task_logic_inputs" -I"../src/Task_management" -I"../src/Task_motors" -I"../src/Task_outs" -I"../src/osa" -I"." -I"../src/Drivers" -I"../src/DebugTools" -ms -oa-  -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/_ext/1516331906/task_motors.o   ../src/Task_motors/task_motors.c 
	@${DEP_GEN} -d ${OBJECTDIR}/_ext/1516331906/task_motors.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1516331906/task_motors.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c18 
	
${OBJECTDIR}/_ext/1485309755/task_outs.o: ../src/Task_outs/task_outs.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1485309755" 
	@${RM} ${OBJECTDIR}/_ext/1485309755/task_outs.o.d 
	@${RM} ${OBJECTDIR}/_ext/1485309755/task_outs.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -p$(MP_PROCESSOR_OPTION) -w3 -I"../src/EEPROMmemory" -I"../src/Interrupts" -I"../src/Main" -I"../src/Menu" -I"../src/Module_analog_inputs" -I"../src/Module_fan" -I"../src/Module_indication" -I"../src/Module_logic_inputs" -I"../src/Module_management" -I"../src/Module_motor" -I"../src/Module_sound" -I"../src/OSA" -I"../src/System" -I"../src/Task_analog_inputs" -I"../src/Task_logic_inputs" -I"../src/Task_management" -I"../src/Task_motors" -I"../src/Task_outs" -I"../src/osa" -I"." -I"../src/Drivers" -I"../src/DebugTools" -ms -oa-  -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/_ext/1485309755/task_outs.o   ../src/Task_outs/task_outs.c 
	@${DEP_GEN} -d ${OBJECTDIR}/_ext/1485309755/task_outs.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1485309755/task_outs.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c18 
	
${OBJECTDIR}/_ext/990863823/i2c.o: ../src/Drivers/i2c.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/990863823" 
	@${RM} ${OBJECTDIR}/_ext/990863823/i2c.o.d 
	@${RM} ${OBJECTDIR}/_ext/990863823/i2c.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -p$(MP_PROCESSOR_OPTION) -w3 -I"../src/EEPROMmemory" -I"../src/Interrupts" -I"../src/Main" -I"../src/Menu" -I"../src/Module_analog_inputs" -I"../src/Module_fan" -I"../src/Module_indication" -I"../src/Module_logic_inputs" -I"../src/Module_management" -I"../src/Module_motor" -I"../src/Module_sound" -I"../src/OSA" -I"../src/System" -I"../src/Task_analog_inputs" -I"../src/Task_logic_inputs" -I"../src/Task_management" -I"../src/Task_motors" -I"../src/Task_outs" -I"../src/osa" -I"." -I"../src/Drivers" -I"../src/DebugTools" -ms -oa-  -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/_ext/990863823/i2c.o   ../src/Drivers/i2c.c 
	@${DEP_GEN} -d ${OBJECTDIR}/_ext/990863823/i2c.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/990863823/i2c.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c18 
	
${OBJECTDIR}/_ext/1375153083/eeprom.o: ../src/EEPROMmemory/eeprom.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1375153083" 
	@${RM} ${OBJECTDIR}/_ext/1375153083/eeprom.o.d 
	@${RM} ${OBJECTDIR}/_ext/1375153083/eeprom.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -p$(MP_PROCESSOR_OPTION) -w3 -I"../src/EEPROMmemory" -I"../src/Interrupts" -I"../src/Main" -I"../src/Menu" -I"../src/Module_analog_inputs" -I"../src/Module_fan" -I"../src/Module_indication" -I"../src/Module_logic_inputs" -I"../src/Module_management" -I"../src/Module_motor" -I"../src/Module_sound" -I"../src/OSA" -I"../src/System" -I"../src/Task_analog_inputs" -I"../src/Task_logic_inputs" -I"../src/Task_management" -I"../src/Task_motors" -I"../src/Task_outs" -I"../src/osa" -I"." -I"../src/Drivers" -I"../src/DebugTools" -ms -oa-  -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/_ext/1375153083/eeprom.o   ../src/EEPROMmemory/eeprom.c 
	@${DEP_GEN} -d ${OBJECTDIR}/_ext/1375153083/eeprom.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1375153083/eeprom.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c18 
	
${OBJECTDIR}/_ext/990863823/spi.o: ../src/Drivers/spi.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/990863823" 
	@${RM} ${OBJECTDIR}/_ext/990863823/spi.o.d 
	@${RM} ${OBJECTDIR}/_ext/990863823/spi.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -p$(MP_PROCESSOR_OPTION) -w3 -I"../src/EEPROMmemory" -I"../src/Interrupts" -I"../src/Main" -I"../src/Menu" -I"../src/Module_analog_inputs" -I"../src/Module_fan" -I"../src/Module_indication" -I"../src/Module_logic_inputs" -I"../src/Module_management" -I"../src/Module_motor" -I"../src/Module_sound" -I"../src/OSA" -I"../src/System" -I"../src/Task_analog_inputs" -I"../src/Task_logic_inputs" -I"../src/Task_management" -I"../src/Task_motors" -I"../src/Task_outs" -I"../src/osa" -I"." -I"../src/Drivers" -I"../src/DebugTools" -ms -oa-  -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/_ext/990863823/spi.o   ../src/Drivers/spi.c 
	@${DEP_GEN} -d ${OBJECTDIR}/_ext/990863823/spi.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/990863823/spi.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c18 
	
${OBJECTDIR}/_ext/1959551838/logicAnalyzer.o: ../src/DebugTools/logicAnalyzer.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1959551838" 
	@${RM} ${OBJECTDIR}/_ext/1959551838/logicAnalyzer.o.d 
	@${RM} ${OBJECTDIR}/_ext/1959551838/logicAnalyzer.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -p$(MP_PROCESSOR_OPTION) -w3 -I"../src/EEPROMmemory" -I"../src/Interrupts" -I"../src/Main" -I"../src/Menu" -I"../src/Module_analog_inputs" -I"../src/Module_fan" -I"../src/Module_indication" -I"../src/Module_logic_inputs" -I"../src/Module_management" -I"../src/Module_motor" -I"../src/Module_sound" -I"../src/OSA" -I"../src/System" -I"../src/Task_analog_inputs" -I"../src/Task_logic_inputs" -I"../src/Task_management" -I"../src/Task_motors" -I"../src/Task_outs" -I"../src/osa" -I"." -I"../src/Drivers" -I"../src/DebugTools" -ms -oa-  -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/_ext/1959551838/logicAnalyzer.o   ../src/DebugTools/logicAnalyzer.c 
	@${DEP_GEN} -d ${OBJECTDIR}/_ext/1959551838/logicAnalyzer.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1959551838/logicAnalyzer.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c18 
	
${OBJECTDIR}/_ext/1375153083/crc8.o: ../src/EEPROMmemory/crc8.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1375153083" 
	@${RM} ${OBJECTDIR}/_ext/1375153083/crc8.o.d 
	@${RM} ${OBJECTDIR}/_ext/1375153083/crc8.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -p$(MP_PROCESSOR_OPTION) -w3 -I"../src/EEPROMmemory" -I"../src/Interrupts" -I"../src/Main" -I"../src/Menu" -I"../src/Module_analog_inputs" -I"../src/Module_fan" -I"../src/Module_indication" -I"../src/Module_logic_inputs" -I"../src/Module_management" -I"../src/Module_motor" -I"../src/Module_sound" -I"../src/OSA" -I"../src/System" -I"../src/Task_analog_inputs" -I"../src/Task_logic_inputs" -I"../src/Task_management" -I"../src/Task_motors" -I"../src/Task_outs" -I"../src/osa" -I"." -I"../src/Drivers" -I"../src/DebugTools" -ms -oa-  -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/_ext/1375153083/crc8.o   ../src/EEPROMmemory/crc8.c 
	@${DEP_GEN} -d ${OBJECTDIR}/_ext/1375153083/crc8.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1375153083/crc8.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c18 
	
else
${OBJECTDIR}/_ext/1695876150/interrupts.o: ../src/Interrupts/interrupts.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1695876150" 
	@${RM} ${OBJECTDIR}/_ext/1695876150/interrupts.o.d 
	@${RM} ${OBJECTDIR}/_ext/1695876150/interrupts.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -p$(MP_PROCESSOR_OPTION) -w3 -I"../src/EEPROMmemory" -I"../src/Interrupts" -I"../src/Main" -I"../src/Menu" -I"../src/Module_analog_inputs" -I"../src/Module_fan" -I"../src/Module_indication" -I"../src/Module_logic_inputs" -I"../src/Module_management" -I"../src/Module_motor" -I"../src/Module_sound" -I"../src/OSA" -I"../src/System" -I"../src/Task_analog_inputs" -I"../src/Task_logic_inputs" -I"../src/Task_management" -I"../src/Task_motors" -I"../src/Task_outs" -I"../src/osa" -I"." -I"../src/Drivers" -I"../src/DebugTools" -ms -oa-  -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/_ext/1695876150/interrupts.o   ../src/Interrupts/interrupts.c 
	@${DEP_GEN} -d ${OBJECTDIR}/_ext/1695876150/interrupts.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1695876150/interrupts.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c18 
	
${OBJECTDIR}/_ext/1020072301/main.o: ../src/Main/main.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1020072301" 
	@${RM} ${OBJECTDIR}/_ext/1020072301/main.o.d 
	@${RM} ${OBJECTDIR}/_ext/1020072301/main.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -p$(MP_PROCESSOR_OPTION) -w3 -I"../src/EEPROMmemory" -I"../src/Interrupts" -I"../src/Main" -I"../src/Menu" -I"../src/Module_analog_inputs" -I"../src/Module_fan" -I"../src/Module_indication" -I"../src/Module_logic_inputs" -I"../src/Module_management" -I"../src/Module_motor" -I"../src/Module_sound" -I"../src/OSA" -I"../src/System" -I"../src/Task_analog_inputs" -I"../src/Task_logic_inputs" -I"../src/Task_management" -I"../src/Task_motors" -I"../src/Task_outs" -I"../src/osa" -I"." -I"../src/Drivers" -I"../src/DebugTools" -ms -oa-  -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/_ext/1020072301/main.o   ../src/Main/main.c 
	@${DEP_GEN} -d ${OBJECTDIR}/_ext/1020072301/main.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1020072301/main.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c18 
	
${OBJECTDIR}/_ext/1020068295/menu.o: ../src/Menu/menu.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1020068295" 
	@${RM} ${OBJECTDIR}/_ext/1020068295/menu.o.d 
	@${RM} ${OBJECTDIR}/_ext/1020068295/menu.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -p$(MP_PROCESSOR_OPTION) -w3 -I"../src/EEPROMmemory" -I"../src/Interrupts" -I"../src/Main" -I"../src/Menu" -I"../src/Module_analog_inputs" -I"../src/Module_fan" -I"../src/Module_indication" -I"../src/Module_logic_inputs" -I"../src/Module_management" -I"../src/Module_motor" -I"../src/Module_sound" -I"../src/OSA" -I"../src/System" -I"../src/Task_analog_inputs" -I"../src/Task_logic_inputs" -I"../src/Task_management" -I"../src/Task_motors" -I"../src/Task_outs" -I"../src/osa" -I"." -I"../src/Drivers" -I"../src/DebugTools" -ms -oa-  -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/_ext/1020068295/menu.o   ../src/Menu/menu.c 
	@${DEP_GEN} -d ${OBJECTDIR}/_ext/1020068295/menu.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1020068295/menu.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c18 
	
${OBJECTDIR}/_ext/6916191/module_analog_inputs.o: ../src/Module_analog_inputs/module_analog_inputs.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/6916191" 
	@${RM} ${OBJECTDIR}/_ext/6916191/module_analog_inputs.o.d 
	@${RM} ${OBJECTDIR}/_ext/6916191/module_analog_inputs.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -p$(MP_PROCESSOR_OPTION) -w3 -I"../src/EEPROMmemory" -I"../src/Interrupts" -I"../src/Main" -I"../src/Menu" -I"../src/Module_analog_inputs" -I"../src/Module_fan" -I"../src/Module_indication" -I"../src/Module_logic_inputs" -I"../src/Module_management" -I"../src/Module_motor" -I"../src/Module_sound" -I"../src/OSA" -I"../src/System" -I"../src/Task_analog_inputs" -I"../src/Task_logic_inputs" -I"../src/Task_management" -I"../src/Task_motors" -I"../src/Task_outs" -I"../src/osa" -I"." -I"../src/Drivers" -I"../src/DebugTools" -ms -oa-  -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/_ext/6916191/module_analog_inputs.o   ../src/Module_analog_inputs/module_analog_inputs.c 
	@${DEP_GEN} -d ${OBJECTDIR}/_ext/6916191/module_analog_inputs.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/6916191/module_analog_inputs.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c18 
	
${OBJECTDIR}/_ext/978868198/module_fan.o: ../src/Module_fan/module_fan.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/978868198" 
	@${RM} ${OBJECTDIR}/_ext/978868198/module_fan.o.d 
	@${RM} ${OBJECTDIR}/_ext/978868198/module_fan.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -p$(MP_PROCESSOR_OPTION) -w3 -I"../src/EEPROMmemory" -I"../src/Interrupts" -I"../src/Main" -I"../src/Menu" -I"../src/Module_analog_inputs" -I"../src/Module_fan" -I"../src/Module_indication" -I"../src/Module_logic_inputs" -I"../src/Module_management" -I"../src/Module_motor" -I"../src/Module_sound" -I"../src/OSA" -I"../src/System" -I"../src/Task_analog_inputs" -I"../src/Task_logic_inputs" -I"../src/Task_management" -I"../src/Task_motors" -I"../src/Task_outs" -I"../src/osa" -I"." -I"../src/Drivers" -I"../src/DebugTools" -ms -oa-  -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/_ext/978868198/module_fan.o   ../src/Module_fan/module_fan.c 
	@${DEP_GEN} -d ${OBJECTDIR}/_ext/978868198/module_fan.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/978868198/module_fan.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c18 
	
${OBJECTDIR}/_ext/381719947/module_indication.o: ../src/Module_indication/module_indication.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/381719947" 
	@${RM} ${OBJECTDIR}/_ext/381719947/module_indication.o.d 
	@${RM} ${OBJECTDIR}/_ext/381719947/module_indication.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -p$(MP_PROCESSOR_OPTION) -w3 -I"../src/EEPROMmemory" -I"../src/Interrupts" -I"../src/Main" -I"../src/Menu" -I"../src/Module_analog_inputs" -I"../src/Module_fan" -I"../src/Module_indication" -I"../src/Module_logic_inputs" -I"../src/Module_management" -I"../src/Module_motor" -I"../src/Module_sound" -I"../src/OSA" -I"../src/System" -I"../src/Task_analog_inputs" -I"../src/Task_logic_inputs" -I"../src/Task_management" -I"../src/Task_motors" -I"../src/Task_outs" -I"../src/osa" -I"." -I"../src/Drivers" -I"../src/DebugTools" -ms -oa-  -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/_ext/381719947/module_indication.o   ../src/Module_indication/module_indication.c 
	@${DEP_GEN} -d ${OBJECTDIR}/_ext/381719947/module_indication.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/381719947/module_indication.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c18 
	
${OBJECTDIR}/_ext/1550195517/module_logic_inputs.o: ../src/Module_logic_inputs/module_logic_inputs.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1550195517" 
	@${RM} ${OBJECTDIR}/_ext/1550195517/module_logic_inputs.o.d 
	@${RM} ${OBJECTDIR}/_ext/1550195517/module_logic_inputs.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -p$(MP_PROCESSOR_OPTION) -w3 -I"../src/EEPROMmemory" -I"../src/Interrupts" -I"../src/Main" -I"../src/Menu" -I"../src/Module_analog_inputs" -I"../src/Module_fan" -I"../src/Module_indication" -I"../src/Module_logic_inputs" -I"../src/Module_management" -I"../src/Module_motor" -I"../src/Module_sound" -I"../src/OSA" -I"../src/System" -I"../src/Task_analog_inputs" -I"../src/Task_logic_inputs" -I"../src/Task_management" -I"../src/Task_motors" -I"../src/Task_outs" -I"../src/osa" -I"." -I"../src/Drivers" -I"../src/DebugTools" -ms -oa-  -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/_ext/1550195517/module_logic_inputs.o   ../src/Module_logic_inputs/module_logic_inputs.c 
	@${DEP_GEN} -d ${OBJECTDIR}/_ext/1550195517/module_logic_inputs.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1550195517/module_logic_inputs.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c18 
	
${OBJECTDIR}/_ext/1584532132/module_management.o: ../src/Module_management/module_management.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1584532132" 
	@${RM} ${OBJECTDIR}/_ext/1584532132/module_management.o.d 
	@${RM} ${OBJECTDIR}/_ext/1584532132/module_management.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -p$(MP_PROCESSOR_OPTION) -w3 -I"../src/EEPROMmemory" -I"../src/Interrupts" -I"../src/Main" -I"../src/Menu" -I"../src/Module_analog_inputs" -I"../src/Module_fan" -I"../src/Module_indication" -I"../src/Module_logic_inputs" -I"../src/Module_management" -I"../src/Module_motor" -I"../src/Module_sound" -I"../src/OSA" -I"../src/System" -I"../src/Task_analog_inputs" -I"../src/Task_logic_inputs" -I"../src/Task_management" -I"../src/Task_motors" -I"../src/Task_outs" -I"../src/osa" -I"." -I"../src/Drivers" -I"../src/DebugTools" -ms -oa-  -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/_ext/1584532132/module_management.o   ../src/Module_management/module_management.c 
	@${DEP_GEN} -d ${OBJECTDIR}/_ext/1584532132/module_management.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1584532132/module_management.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c18 
	
${OBJECTDIR}/_ext/87609412/module_motor.o: ../src/Module_motor/module_motor.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/87609412" 
	@${RM} ${OBJECTDIR}/_ext/87609412/module_motor.o.d 
	@${RM} ${OBJECTDIR}/_ext/87609412/module_motor.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -p$(MP_PROCESSOR_OPTION) -w3 -I"../src/EEPROMmemory" -I"../src/Interrupts" -I"../src/Main" -I"../src/Menu" -I"../src/Module_analog_inputs" -I"../src/Module_fan" -I"../src/Module_indication" -I"../src/Module_logic_inputs" -I"../src/Module_management" -I"../src/Module_motor" -I"../src/Module_sound" -I"../src/OSA" -I"../src/System" -I"../src/Task_analog_inputs" -I"../src/Task_logic_inputs" -I"../src/Task_management" -I"../src/Task_motors" -I"../src/Task_outs" -I"../src/osa" -I"." -I"../src/Drivers" -I"../src/DebugTools" -ms -oa-  -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/_ext/87609412/module_motor.o   ../src/Module_motor/module_motor.c 
	@${DEP_GEN} -d ${OBJECTDIR}/_ext/87609412/module_motor.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/87609412/module_motor.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c18 
	
${OBJECTDIR}/_ext/82067370/module_sound.o: ../src/Module_sound/module_sound.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/82067370" 
	@${RM} ${OBJECTDIR}/_ext/82067370/module_sound.o.d 
	@${RM} ${OBJECTDIR}/_ext/82067370/module_sound.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -p$(MP_PROCESSOR_OPTION) -w3 -I"../src/EEPROMmemory" -I"../src/Interrupts" -I"../src/Main" -I"../src/Menu" -I"../src/Module_analog_inputs" -I"../src/Module_fan" -I"../src/Module_indication" -I"../src/Module_logic_inputs" -I"../src/Module_management" -I"../src/Module_motor" -I"../src/Module_sound" -I"../src/OSA" -I"../src/System" -I"../src/Task_analog_inputs" -I"../src/Task_logic_inputs" -I"../src/Task_management" -I"../src/Task_motors" -I"../src/Task_outs" -I"../src/osa" -I"." -I"../src/Drivers" -I"../src/DebugTools" -ms -oa-  -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/_ext/82067370/module_sound.o   ../src/Module_sound/module_sound.c 
	@${DEP_GEN} -d ${OBJECTDIR}/_ext/82067370/module_sound.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/82067370/module_sound.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c18 
	
${OBJECTDIR}/_ext/659832547/osa.o: ../src/OSA/osa.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/659832547" 
	@${RM} ${OBJECTDIR}/_ext/659832547/osa.o.d 
	@${RM} ${OBJECTDIR}/_ext/659832547/osa.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -p$(MP_PROCESSOR_OPTION) -w3 -I"../src/EEPROMmemory" -I"../src/Interrupts" -I"../src/Main" -I"../src/Menu" -I"../src/Module_analog_inputs" -I"../src/Module_fan" -I"../src/Module_indication" -I"../src/Module_logic_inputs" -I"../src/Module_management" -I"../src/Module_motor" -I"../src/Module_sound" -I"../src/OSA" -I"../src/System" -I"../src/Task_analog_inputs" -I"../src/Task_logic_inputs" -I"../src/Task_management" -I"../src/Task_motors" -I"../src/Task_outs" -I"../src/osa" -I"." -I"../src/Drivers" -I"../src/DebugTools" -ms -oa-  -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/_ext/659832547/osa.o   ../src/OSA/osa.c 
	@${DEP_GEN} -d ${OBJECTDIR}/_ext/659832547/osa.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/659832547/osa.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c18 
	
${OBJECTDIR}/_ext/1688643128/task_analog_inputs.o: ../src/Task_analog_inputs/task_analog_inputs.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1688643128" 
	@${RM} ${OBJECTDIR}/_ext/1688643128/task_analog_inputs.o.d 
	@${RM} ${OBJECTDIR}/_ext/1688643128/task_analog_inputs.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -p$(MP_PROCESSOR_OPTION) -w3 -I"../src/EEPROMmemory" -I"../src/Interrupts" -I"../src/Main" -I"../src/Menu" -I"../src/Module_analog_inputs" -I"../src/Module_fan" -I"../src/Module_indication" -I"../src/Module_logic_inputs" -I"../src/Module_management" -I"../src/Module_motor" -I"../src/Module_sound" -I"../src/OSA" -I"../src/System" -I"../src/Task_analog_inputs" -I"../src/Task_logic_inputs" -I"../src/Task_management" -I"../src/Task_motors" -I"../src/Task_outs" -I"../src/osa" -I"." -I"../src/Drivers" -I"../src/DebugTools" -ms -oa-  -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/_ext/1688643128/task_analog_inputs.o   ../src/Task_analog_inputs/task_analog_inputs.c 
	@${DEP_GEN} -d ${OBJECTDIR}/_ext/1688643128/task_analog_inputs.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1688643128/task_analog_inputs.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c18 
	
${OBJECTDIR}/_ext/1690642378/task_logic_inputs.o: ../src/Task_logic_inputs/task_logic_inputs.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1690642378" 
	@${RM} ${OBJECTDIR}/_ext/1690642378/task_logic_inputs.o.d 
	@${RM} ${OBJECTDIR}/_ext/1690642378/task_logic_inputs.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -p$(MP_PROCESSOR_OPTION) -w3 -I"../src/EEPROMmemory" -I"../src/Interrupts" -I"../src/Main" -I"../src/Menu" -I"../src/Module_analog_inputs" -I"../src/Module_fan" -I"../src/Module_indication" -I"../src/Module_logic_inputs" -I"../src/Module_management" -I"../src/Module_motor" -I"../src/Module_sound" -I"../src/OSA" -I"../src/System" -I"../src/Task_analog_inputs" -I"../src/Task_logic_inputs" -I"../src/Task_management" -I"../src/Task_motors" -I"../src/Task_outs" -I"../src/osa" -I"." -I"../src/Drivers" -I"../src/DebugTools" -ms -oa-  -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/_ext/1690642378/task_logic_inputs.o   ../src/Task_logic_inputs/task_logic_inputs.c 
	@${DEP_GEN} -d ${OBJECTDIR}/_ext/1690642378/task_logic_inputs.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1690642378/task_logic_inputs.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c18 
	
${OBJECTDIR}/_ext/1058255325/task_management.o: ../src/Task_management/task_management.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1058255325" 
	@${RM} ${OBJECTDIR}/_ext/1058255325/task_management.o.d 
	@${RM} ${OBJECTDIR}/_ext/1058255325/task_management.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -p$(MP_PROCESSOR_OPTION) -w3 -I"../src/EEPROMmemory" -I"../src/Interrupts" -I"../src/Main" -I"../src/Menu" -I"../src/Module_analog_inputs" -I"../src/Module_fan" -I"../src/Module_indication" -I"../src/Module_logic_inputs" -I"../src/Module_management" -I"../src/Module_motor" -I"../src/Module_sound" -I"../src/OSA" -I"../src/System" -I"../src/Task_analog_inputs" -I"../src/Task_logic_inputs" -I"../src/Task_management" -I"../src/Task_motors" -I"../src/Task_outs" -I"../src/osa" -I"." -I"../src/Drivers" -I"../src/DebugTools" -ms -oa-  -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/_ext/1058255325/task_management.o   ../src/Task_management/task_management.c 
	@${DEP_GEN} -d ${OBJECTDIR}/_ext/1058255325/task_management.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1058255325/task_management.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c18 
	
${OBJECTDIR}/_ext/1516331906/task_motors.o: ../src/Task_motors/task_motors.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1516331906" 
	@${RM} ${OBJECTDIR}/_ext/1516331906/task_motors.o.d 
	@${RM} ${OBJECTDIR}/_ext/1516331906/task_motors.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -p$(MP_PROCESSOR_OPTION) -w3 -I"../src/EEPROMmemory" -I"../src/Interrupts" -I"../src/Main" -I"../src/Menu" -I"../src/Module_analog_inputs" -I"../src/Module_fan" -I"../src/Module_indication" -I"../src/Module_logic_inputs" -I"../src/Module_management" -I"../src/Module_motor" -I"../src/Module_sound" -I"../src/OSA" -I"../src/System" -I"../src/Task_analog_inputs" -I"../src/Task_logic_inputs" -I"../src/Task_management" -I"../src/Task_motors" -I"../src/Task_outs" -I"../src/osa" -I"." -I"../src/Drivers" -I"../src/DebugTools" -ms -oa-  -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/_ext/1516331906/task_motors.o   ../src/Task_motors/task_motors.c 
	@${DEP_GEN} -d ${OBJECTDIR}/_ext/1516331906/task_motors.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1516331906/task_motors.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c18 
	
${OBJECTDIR}/_ext/1485309755/task_outs.o: ../src/Task_outs/task_outs.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1485309755" 
	@${RM} ${OBJECTDIR}/_ext/1485309755/task_outs.o.d 
	@${RM} ${OBJECTDIR}/_ext/1485309755/task_outs.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -p$(MP_PROCESSOR_OPTION) -w3 -I"../src/EEPROMmemory" -I"../src/Interrupts" -I"../src/Main" -I"../src/Menu" -I"../src/Module_analog_inputs" -I"../src/Module_fan" -I"../src/Module_indication" -I"../src/Module_logic_inputs" -I"../src/Module_management" -I"../src/Module_motor" -I"../src/Module_sound" -I"../src/OSA" -I"../src/System" -I"../src/Task_analog_inputs" -I"../src/Task_logic_inputs" -I"../src/Task_management" -I"../src/Task_motors" -I"../src/Task_outs" -I"../src/osa" -I"." -I"../src/Drivers" -I"../src/DebugTools" -ms -oa-  -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/_ext/1485309755/task_outs.o   ../src/Task_outs/task_outs.c 
	@${DEP_GEN} -d ${OBJECTDIR}/_ext/1485309755/task_outs.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1485309755/task_outs.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c18 
	
${OBJECTDIR}/_ext/990863823/i2c.o: ../src/Drivers/i2c.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/990863823" 
	@${RM} ${OBJECTDIR}/_ext/990863823/i2c.o.d 
	@${RM} ${OBJECTDIR}/_ext/990863823/i2c.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -p$(MP_PROCESSOR_OPTION) -w3 -I"../src/EEPROMmemory" -I"../src/Interrupts" -I"../src/Main" -I"../src/Menu" -I"../src/Module_analog_inputs" -I"../src/Module_fan" -I"../src/Module_indication" -I"../src/Module_logic_inputs" -I"../src/Module_management" -I"../src/Module_motor" -I"../src/Module_sound" -I"../src/OSA" -I"../src/System" -I"../src/Task_analog_inputs" -I"../src/Task_logic_inputs" -I"../src/Task_management" -I"../src/Task_motors" -I"../src/Task_outs" -I"../src/osa" -I"." -I"../src/Drivers" -I"../src/DebugTools" -ms -oa-  -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/_ext/990863823/i2c.o   ../src/Drivers/i2c.c 
	@${DEP_GEN} -d ${OBJECTDIR}/_ext/990863823/i2c.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/990863823/i2c.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c18 
	
${OBJECTDIR}/_ext/1375153083/eeprom.o: ../src/EEPROMmemory/eeprom.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1375153083" 
	@${RM} ${OBJECTDIR}/_ext/1375153083/eeprom.o.d 
	@${RM} ${OBJECTDIR}/_ext/1375153083/eeprom.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -p$(MP_PROCESSOR_OPTION) -w3 -I"../src/EEPROMmemory" -I"../src/Interrupts" -I"../src/Main" -I"../src/Menu" -I"../src/Module_analog_inputs" -I"../src/Module_fan" -I"../src/Module_indication" -I"../src/Module_logic_inputs" -I"../src/Module_management" -I"../src/Module_motor" -I"../src/Module_sound" -I"../src/OSA" -I"../src/System" -I"../src/Task_analog_inputs" -I"../src/Task_logic_inputs" -I"../src/Task_management" -I"../src/Task_motors" -I"../src/Task_outs" -I"../src/osa" -I"." -I"../src/Drivers" -I"../src/DebugTools" -ms -oa-  -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/_ext/1375153083/eeprom.o   ../src/EEPROMmemory/eeprom.c 
	@${DEP_GEN} -d ${OBJECTDIR}/_ext/1375153083/eeprom.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1375153083/eeprom.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c18 
	
${OBJECTDIR}/_ext/990863823/spi.o: ../src/Drivers/spi.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/990863823" 
	@${RM} ${OBJECTDIR}/_ext/990863823/spi.o.d 
	@${RM} ${OBJECTDIR}/_ext/990863823/spi.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -p$(MP_PROCESSOR_OPTION) -w3 -I"../src/EEPROMmemory" -I"../src/Interrupts" -I"../src/Main" -I"../src/Menu" -I"../src/Module_analog_inputs" -I"../src/Module_fan" -I"../src/Module_indication" -I"../src/Module_logic_inputs" -I"../src/Module_management" -I"../src/Module_motor" -I"../src/Module_sound" -I"../src/OSA" -I"../src/System" -I"../src/Task_analog_inputs" -I"../src/Task_logic_inputs" -I"../src/Task_management" -I"../src/Task_motors" -I"../src/Task_outs" -I"../src/osa" -I"." -I"../src/Drivers" -I"../src/DebugTools" -ms -oa-  -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/_ext/990863823/spi.o   ../src/Drivers/spi.c 
	@${DEP_GEN} -d ${OBJECTDIR}/_ext/990863823/spi.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/990863823/spi.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c18 
	
${OBJECTDIR}/_ext/1959551838/logicAnalyzer.o: ../src/DebugTools/logicAnalyzer.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1959551838" 
	@${RM} ${OBJECTDIR}/_ext/1959551838/logicAnalyzer.o.d 
	@${RM} ${OBJECTDIR}/_ext/1959551838/logicAnalyzer.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -p$(MP_PROCESSOR_OPTION) -w3 -I"../src/EEPROMmemory" -I"../src/Interrupts" -I"../src/Main" -I"../src/Menu" -I"../src/Module_analog_inputs" -I"../src/Module_fan" -I"../src/Module_indication" -I"../src/Module_logic_inputs" -I"../src/Module_management" -I"../src/Module_motor" -I"../src/Module_sound" -I"../src/OSA" -I"../src/System" -I"../src/Task_analog_inputs" -I"../src/Task_logic_inputs" -I"../src/Task_management" -I"../src/Task_motors" -I"../src/Task_outs" -I"../src/osa" -I"." -I"../src/Drivers" -I"../src/DebugTools" -ms -oa-  -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/_ext/1959551838/logicAnalyzer.o   ../src/DebugTools/logicAnalyzer.c 
	@${DEP_GEN} -d ${OBJECTDIR}/_ext/1959551838/logicAnalyzer.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1959551838/logicAnalyzer.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c18 
	
${OBJECTDIR}/_ext/1375153083/crc8.o: ../src/EEPROMmemory/crc8.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1375153083" 
	@${RM} ${OBJECTDIR}/_ext/1375153083/crc8.o.d 
	@${RM} ${OBJECTDIR}/_ext/1375153083/crc8.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -p$(MP_PROCESSOR_OPTION) -w3 -I"../src/EEPROMmemory" -I"../src/Interrupts" -I"../src/Main" -I"../src/Menu" -I"../src/Module_analog_inputs" -I"../src/Module_fan" -I"../src/Module_indication" -I"../src/Module_logic_inputs" -I"../src/Module_management" -I"../src/Module_motor" -I"../src/Module_sound" -I"../src/OSA" -I"../src/System" -I"../src/Task_analog_inputs" -I"../src/Task_logic_inputs" -I"../src/Task_management" -I"../src/Task_motors" -I"../src/Task_outs" -I"../src/osa" -I"." -I"../src/Drivers" -I"../src/DebugTools" -ms -oa-  -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/_ext/1375153083/crc8.o   ../src/EEPROMmemory/crc8.c 
	@${DEP_GEN} -d ${OBJECTDIR}/_ext/1375153083/crc8.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1375153083/crc8.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c18 
	
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: link
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
dist/${CND_CONF}/${IMAGE_TYPE}/solid_fuel_boiler.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk    
	@${MKDIR} dist/${CND_CONF}/${IMAGE_TYPE} 
	${MP_LD} $(MP_EXTRA_LD_PRE)   -p$(MP_PROCESSOR_OPTION_LD)  -w -x -u_DEBUG -m"$(BINDIR_)$(TARGETBASE).map" -w -l"C:/MCC18/lib" -l"."  -z__MPLAB_BUILD=1  -u_CRUNTIME -z__MPLAB_DEBUG=1 -z__MPLAB_DEBUGGER_PK3=1 $(MP_LINKER_DEBUG_OPTION) -l ${MP_CC_DIR}\\..\\lib  -o dist/${CND_CONF}/${IMAGE_TYPE}/solid_fuel_boiler.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}  ${OBJECTFILES_QUOTED_IF_SPACED}   
else
dist/${CND_CONF}/${IMAGE_TYPE}/solid_fuel_boiler.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk   
	@${MKDIR} dist/${CND_CONF}/${IMAGE_TYPE} 
	${MP_LD} $(MP_EXTRA_LD_PRE)   -p$(MP_PROCESSOR_OPTION_LD)  -w  -m"$(BINDIR_)$(TARGETBASE).map" -w -l"C:/MCC18/lib" -l"."  -z__MPLAB_BUILD=1  -u_CRUNTIME -l ${MP_CC_DIR}\\..\\lib  -o dist/${CND_CONF}/${IMAGE_TYPE}/solid_fuel_boiler.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX}  ${OBJECTFILES_QUOTED_IF_SPACED}   
endif


# Subprojects
.build-subprojects:


# Subprojects
.clean-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r build/default
	${RM} -r dist/default

# Enable dependency checking
.dep.inc: .depcheck-impl

DEPFILES=$(shell mplabwildcard ${POSSIBLE_DEPFILES})
ifneq (${DEPFILES},)
include ${DEPFILES}
endif

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
OUTPUT_SUFFIX=elf
DEBUGGABLE_SUFFIX=elf
FINAL_IMAGE=${DISTDIR}/18f2320.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
else
IMAGE_TYPE=production
OUTPUT_SUFFIX=hex
DEBUGGABLE_SUFFIX=elf
FINAL_IMAGE=${DISTDIR}/18f2320.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
endif

ifeq ($(COMPARE_BUILD), true)
COMPARISON_BUILD=-mafrlcsj
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
SOURCEFILES_QUOTED_IF_SPACED=main.c ds18b20.c hd44780.c onewire.c eeprom.c key.c eusart.c

# Object Files Quoted if spaced
OBJECTFILES_QUOTED_IF_SPACED=${OBJECTDIR}/main.p1 ${OBJECTDIR}/ds18b20.p1 ${OBJECTDIR}/hd44780.p1 ${OBJECTDIR}/onewire.p1 ${OBJECTDIR}/eeprom.p1 ${OBJECTDIR}/key.p1 ${OBJECTDIR}/eusart.p1
POSSIBLE_DEPFILES=${OBJECTDIR}/main.p1.d ${OBJECTDIR}/ds18b20.p1.d ${OBJECTDIR}/hd44780.p1.d ${OBJECTDIR}/onewire.p1.d ${OBJECTDIR}/eeprom.p1.d ${OBJECTDIR}/key.p1.d ${OBJECTDIR}/eusart.p1.d

# Object Files
OBJECTFILES=${OBJECTDIR}/main.p1 ${OBJECTDIR}/ds18b20.p1 ${OBJECTDIR}/hd44780.p1 ${OBJECTDIR}/onewire.p1 ${OBJECTDIR}/eeprom.p1 ${OBJECTDIR}/key.p1 ${OBJECTDIR}/eusart.p1

# Source Files
SOURCEFILES=main.c ds18b20.c hd44780.c onewire.c eeprom.c key.c eusart.c



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
	${MAKE}  -f nbproject/Makefile-default.mk ${DISTDIR}/18f2320.${IMAGE_TYPE}.${OUTPUT_SUFFIX}

MP_PROCESSOR_OPTION=18F2320
# ------------------------------------------------------------------------------------
# Rules for buildStep: compile
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
${OBJECTDIR}/main.p1: main.c  nbproject/Makefile-${CND_CONF}.mk 
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/main.p1.d 
	@${RM} ${OBJECTDIR}/main.p1 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -D__DEBUG=1  -mdebugger=pickit3   -mdfp="${DFP_DIR}/xc8"  -fno-short-double -fno-short-float -memi=wordwrite -Os -fasmfile -maddrqual=ignore -xassembler-with-cpp -I"C:/Program Files (x86)/Microchip/xc8/v2.31/pic/include/proc" -mwarn=-3 -Wa,-a -DXPRJ_default=$(CND_CONF)  -msummary=-psect,-class,+mem,-hex,-file  -ginhx32 -Wl,--data-init -mno-keep-startup -mno-download -mdefault-config-bits $(COMPARISON_BUILD)  -std=c90 -gcoff -mstack=compiled:auto:auto:auto     -o ${OBJECTDIR}/main.p1 main.c 
	@-${MV} ${OBJECTDIR}/main.d ${OBJECTDIR}/main.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/main.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/ds18b20.p1: ds18b20.c  nbproject/Makefile-${CND_CONF}.mk 
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/ds18b20.p1.d 
	@${RM} ${OBJECTDIR}/ds18b20.p1 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -D__DEBUG=1  -mdebugger=pickit3   -mdfp="${DFP_DIR}/xc8"  -fno-short-double -fno-short-float -memi=wordwrite -Os -fasmfile -maddrqual=ignore -xassembler-with-cpp -I"C:/Program Files (x86)/Microchip/xc8/v2.31/pic/include/proc" -mwarn=-3 -Wa,-a -DXPRJ_default=$(CND_CONF)  -msummary=-psect,-class,+mem,-hex,-file  -ginhx32 -Wl,--data-init -mno-keep-startup -mno-download -mdefault-config-bits $(COMPARISON_BUILD)  -std=c90 -gcoff -mstack=compiled:auto:auto:auto     -o ${OBJECTDIR}/ds18b20.p1 ds18b20.c 
	@-${MV} ${OBJECTDIR}/ds18b20.d ${OBJECTDIR}/ds18b20.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/ds18b20.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/hd44780.p1: hd44780.c  nbproject/Makefile-${CND_CONF}.mk 
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/hd44780.p1.d 
	@${RM} ${OBJECTDIR}/hd44780.p1 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -D__DEBUG=1  -mdebugger=pickit3   -mdfp="${DFP_DIR}/xc8"  -fno-short-double -fno-short-float -memi=wordwrite -Os -fasmfile -maddrqual=ignore -xassembler-with-cpp -I"C:/Program Files (x86)/Microchip/xc8/v2.31/pic/include/proc" -mwarn=-3 -Wa,-a -DXPRJ_default=$(CND_CONF)  -msummary=-psect,-class,+mem,-hex,-file  -ginhx32 -Wl,--data-init -mno-keep-startup -mno-download -mdefault-config-bits $(COMPARISON_BUILD)  -std=c90 -gcoff -mstack=compiled:auto:auto:auto     -o ${OBJECTDIR}/hd44780.p1 hd44780.c 
	@-${MV} ${OBJECTDIR}/hd44780.d ${OBJECTDIR}/hd44780.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/hd44780.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/onewire.p1: onewire.c  nbproject/Makefile-${CND_CONF}.mk 
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/onewire.p1.d 
	@${RM} ${OBJECTDIR}/onewire.p1 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -D__DEBUG=1  -mdebugger=pickit3   -mdfp="${DFP_DIR}/xc8"  -fno-short-double -fno-short-float -memi=wordwrite -Os -fasmfile -maddrqual=ignore -xassembler-with-cpp -I"C:/Program Files (x86)/Microchip/xc8/v2.31/pic/include/proc" -mwarn=-3 -Wa,-a -DXPRJ_default=$(CND_CONF)  -msummary=-psect,-class,+mem,-hex,-file  -ginhx32 -Wl,--data-init -mno-keep-startup -mno-download -mdefault-config-bits $(COMPARISON_BUILD)  -std=c90 -gcoff -mstack=compiled:auto:auto:auto     -o ${OBJECTDIR}/onewire.p1 onewire.c 
	@-${MV} ${OBJECTDIR}/onewire.d ${OBJECTDIR}/onewire.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/onewire.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/eeprom.p1: eeprom.c  nbproject/Makefile-${CND_CONF}.mk 
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/eeprom.p1.d 
	@${RM} ${OBJECTDIR}/eeprom.p1 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -D__DEBUG=1  -mdebugger=pickit3   -mdfp="${DFP_DIR}/xc8"  -fno-short-double -fno-short-float -memi=wordwrite -Os -fasmfile -maddrqual=ignore -xassembler-with-cpp -I"C:/Program Files (x86)/Microchip/xc8/v2.31/pic/include/proc" -mwarn=-3 -Wa,-a -DXPRJ_default=$(CND_CONF)  -msummary=-psect,-class,+mem,-hex,-file  -ginhx32 -Wl,--data-init -mno-keep-startup -mno-download -mdefault-config-bits $(COMPARISON_BUILD)  -std=c90 -gcoff -mstack=compiled:auto:auto:auto     -o ${OBJECTDIR}/eeprom.p1 eeprom.c 
	@-${MV} ${OBJECTDIR}/eeprom.d ${OBJECTDIR}/eeprom.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/eeprom.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/key.p1: key.c  nbproject/Makefile-${CND_CONF}.mk 
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/key.p1.d 
	@${RM} ${OBJECTDIR}/key.p1 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -D__DEBUG=1  -mdebugger=pickit3   -mdfp="${DFP_DIR}/xc8"  -fno-short-double -fno-short-float -memi=wordwrite -Os -fasmfile -maddrqual=ignore -xassembler-with-cpp -I"C:/Program Files (x86)/Microchip/xc8/v2.31/pic/include/proc" -mwarn=-3 -Wa,-a -DXPRJ_default=$(CND_CONF)  -msummary=-psect,-class,+mem,-hex,-file  -ginhx32 -Wl,--data-init -mno-keep-startup -mno-download -mdefault-config-bits $(COMPARISON_BUILD)  -std=c90 -gcoff -mstack=compiled:auto:auto:auto     -o ${OBJECTDIR}/key.p1 key.c 
	@-${MV} ${OBJECTDIR}/key.d ${OBJECTDIR}/key.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/key.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/eusart.p1: eusart.c  nbproject/Makefile-${CND_CONF}.mk 
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/eusart.p1.d 
	@${RM} ${OBJECTDIR}/eusart.p1 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -D__DEBUG=1  -mdebugger=pickit3   -mdfp="${DFP_DIR}/xc8"  -fno-short-double -fno-short-float -memi=wordwrite -Os -fasmfile -maddrqual=ignore -xassembler-with-cpp -I"C:/Program Files (x86)/Microchip/xc8/v2.31/pic/include/proc" -mwarn=-3 -Wa,-a -DXPRJ_default=$(CND_CONF)  -msummary=-psect,-class,+mem,-hex,-file  -ginhx32 -Wl,--data-init -mno-keep-startup -mno-download -mdefault-config-bits $(COMPARISON_BUILD)  -std=c90 -gcoff -mstack=compiled:auto:auto:auto     -o ${OBJECTDIR}/eusart.p1 eusart.c 
	@-${MV} ${OBJECTDIR}/eusart.d ${OBJECTDIR}/eusart.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/eusart.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
else
${OBJECTDIR}/main.p1: main.c  nbproject/Makefile-${CND_CONF}.mk 
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/main.p1.d 
	@${RM} ${OBJECTDIR}/main.p1 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c   -mdfp="${DFP_DIR}/xc8"  -fno-short-double -fno-short-float -memi=wordwrite -Os -fasmfile -maddrqual=ignore -xassembler-with-cpp -I"C:/Program Files (x86)/Microchip/xc8/v2.31/pic/include/proc" -mwarn=-3 -Wa,-a -DXPRJ_default=$(CND_CONF)  -msummary=-psect,-class,+mem,-hex,-file  -ginhx32 -Wl,--data-init -mno-keep-startup -mno-download -mdefault-config-bits $(COMPARISON_BUILD)  -std=c90 -gcoff -mstack=compiled:auto:auto:auto     -o ${OBJECTDIR}/main.p1 main.c 
	@-${MV} ${OBJECTDIR}/main.d ${OBJECTDIR}/main.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/main.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/ds18b20.p1: ds18b20.c  nbproject/Makefile-${CND_CONF}.mk 
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/ds18b20.p1.d 
	@${RM} ${OBJECTDIR}/ds18b20.p1 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c   -mdfp="${DFP_DIR}/xc8"  -fno-short-double -fno-short-float -memi=wordwrite -Os -fasmfile -maddrqual=ignore -xassembler-with-cpp -I"C:/Program Files (x86)/Microchip/xc8/v2.31/pic/include/proc" -mwarn=-3 -Wa,-a -DXPRJ_default=$(CND_CONF)  -msummary=-psect,-class,+mem,-hex,-file  -ginhx32 -Wl,--data-init -mno-keep-startup -mno-download -mdefault-config-bits $(COMPARISON_BUILD)  -std=c90 -gcoff -mstack=compiled:auto:auto:auto     -o ${OBJECTDIR}/ds18b20.p1 ds18b20.c 
	@-${MV} ${OBJECTDIR}/ds18b20.d ${OBJECTDIR}/ds18b20.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/ds18b20.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/hd44780.p1: hd44780.c  nbproject/Makefile-${CND_CONF}.mk 
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/hd44780.p1.d 
	@${RM} ${OBJECTDIR}/hd44780.p1 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c   -mdfp="${DFP_DIR}/xc8"  -fno-short-double -fno-short-float -memi=wordwrite -Os -fasmfile -maddrqual=ignore -xassembler-with-cpp -I"C:/Program Files (x86)/Microchip/xc8/v2.31/pic/include/proc" -mwarn=-3 -Wa,-a -DXPRJ_default=$(CND_CONF)  -msummary=-psect,-class,+mem,-hex,-file  -ginhx32 -Wl,--data-init -mno-keep-startup -mno-download -mdefault-config-bits $(COMPARISON_BUILD)  -std=c90 -gcoff -mstack=compiled:auto:auto:auto     -o ${OBJECTDIR}/hd44780.p1 hd44780.c 
	@-${MV} ${OBJECTDIR}/hd44780.d ${OBJECTDIR}/hd44780.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/hd44780.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/onewire.p1: onewire.c  nbproject/Makefile-${CND_CONF}.mk 
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/onewire.p1.d 
	@${RM} ${OBJECTDIR}/onewire.p1 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c   -mdfp="${DFP_DIR}/xc8"  -fno-short-double -fno-short-float -memi=wordwrite -Os -fasmfile -maddrqual=ignore -xassembler-with-cpp -I"C:/Program Files (x86)/Microchip/xc8/v2.31/pic/include/proc" -mwarn=-3 -Wa,-a -DXPRJ_default=$(CND_CONF)  -msummary=-psect,-class,+mem,-hex,-file  -ginhx32 -Wl,--data-init -mno-keep-startup -mno-download -mdefault-config-bits $(COMPARISON_BUILD)  -std=c90 -gcoff -mstack=compiled:auto:auto:auto     -o ${OBJECTDIR}/onewire.p1 onewire.c 
	@-${MV} ${OBJECTDIR}/onewire.d ${OBJECTDIR}/onewire.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/onewire.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/eeprom.p1: eeprom.c  nbproject/Makefile-${CND_CONF}.mk 
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/eeprom.p1.d 
	@${RM} ${OBJECTDIR}/eeprom.p1 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c   -mdfp="${DFP_DIR}/xc8"  -fno-short-double -fno-short-float -memi=wordwrite -Os -fasmfile -maddrqual=ignore -xassembler-with-cpp -I"C:/Program Files (x86)/Microchip/xc8/v2.31/pic/include/proc" -mwarn=-3 -Wa,-a -DXPRJ_default=$(CND_CONF)  -msummary=-psect,-class,+mem,-hex,-file  -ginhx32 -Wl,--data-init -mno-keep-startup -mno-download -mdefault-config-bits $(COMPARISON_BUILD)  -std=c90 -gcoff -mstack=compiled:auto:auto:auto     -o ${OBJECTDIR}/eeprom.p1 eeprom.c 
	@-${MV} ${OBJECTDIR}/eeprom.d ${OBJECTDIR}/eeprom.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/eeprom.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/key.p1: key.c  nbproject/Makefile-${CND_CONF}.mk 
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/key.p1.d 
	@${RM} ${OBJECTDIR}/key.p1 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c   -mdfp="${DFP_DIR}/xc8"  -fno-short-double -fno-short-float -memi=wordwrite -Os -fasmfile -maddrqual=ignore -xassembler-with-cpp -I"C:/Program Files (x86)/Microchip/xc8/v2.31/pic/include/proc" -mwarn=-3 -Wa,-a -DXPRJ_default=$(CND_CONF)  -msummary=-psect,-class,+mem,-hex,-file  -ginhx32 -Wl,--data-init -mno-keep-startup -mno-download -mdefault-config-bits $(COMPARISON_BUILD)  -std=c90 -gcoff -mstack=compiled:auto:auto:auto     -o ${OBJECTDIR}/key.p1 key.c 
	@-${MV} ${OBJECTDIR}/key.d ${OBJECTDIR}/key.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/key.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/eusart.p1: eusart.c  nbproject/Makefile-${CND_CONF}.mk 
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/eusart.p1.d 
	@${RM} ${OBJECTDIR}/eusart.p1 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c   -mdfp="${DFP_DIR}/xc8"  -fno-short-double -fno-short-float -memi=wordwrite -Os -fasmfile -maddrqual=ignore -xassembler-with-cpp -I"C:/Program Files (x86)/Microchip/xc8/v2.31/pic/include/proc" -mwarn=-3 -Wa,-a -DXPRJ_default=$(CND_CONF)  -msummary=-psect,-class,+mem,-hex,-file  -ginhx32 -Wl,--data-init -mno-keep-startup -mno-download -mdefault-config-bits $(COMPARISON_BUILD)  -std=c90 -gcoff -mstack=compiled:auto:auto:auto     -o ${OBJECTDIR}/eusart.p1 eusart.c 
	@-${MV} ${OBJECTDIR}/eusart.d ${OBJECTDIR}/eusart.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/eusart.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: assemble
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
else
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: assembleWithPreprocess
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
else
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: link
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
${DISTDIR}/18f2320.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk    
	@${MKDIR} ${DISTDIR} 
	${MP_CC} $(MP_EXTRA_LD_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -Wl,-Map=${DISTDIR}/18f2320.${IMAGE_TYPE}.map  -D__DEBUG=1  -mdebugger=pickit3  -DXPRJ_default=$(CND_CONF)  -Wl,--defsym=__MPLAB_BUILD=1   -mdfp="${DFP_DIR}/xc8"  -fno-short-double -fno-short-float -memi=wordwrite -Os -fasmfile -maddrqual=ignore -xassembler-with-cpp -I"C:/Program Files (x86)/Microchip/xc8/v2.31/pic/include/proc" -mwarn=-3 -Wa,-a -msummary=-psect,-class,+mem,-hex,-file  -ginhx32 -Wl,--data-init -mno-keep-startup -mno-download -mdefault-config-bits -std=c90 -gcoff -mstack=compiled:auto:auto:auto     -mrom=default,-1dc0-1fff -mram=default,-1f4-1ff,-f9c-f9c,-fd4-fd4,-fdb-fdf,-fe3-fe7,-feb-fef,-ffd-fff  $(COMPARISON_BUILD) -Wl,--memorysummary,${DISTDIR}/memoryfile.xml -o ${DISTDIR}/18f2320.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX}  ${OBJECTFILES_QUOTED_IF_SPACED}     
	@${RM} ${DISTDIR}/18f2320.${IMAGE_TYPE}.hex 
	
else
${DISTDIR}/18f2320.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk   
	@${MKDIR} ${DISTDIR} 
	${MP_CC} $(MP_EXTRA_LD_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -Wl,-Map=${DISTDIR}/18f2320.${IMAGE_TYPE}.map  -DXPRJ_default=$(CND_CONF)  -Wl,--defsym=__MPLAB_BUILD=1   -mdfp="${DFP_DIR}/xc8"  -fno-short-double -fno-short-float -memi=wordwrite -Os -fasmfile -maddrqual=ignore -xassembler-with-cpp -I"C:/Program Files (x86)/Microchip/xc8/v2.31/pic/include/proc" -mwarn=-3 -Wa,-a -msummary=-psect,-class,+mem,-hex,-file  -ginhx32 -Wl,--data-init -mno-keep-startup -mno-download -mdefault-config-bits -std=c90 -gcoff -mstack=compiled:auto:auto:auto     $(COMPARISON_BUILD) -Wl,--memorysummary,${DISTDIR}/memoryfile.xml -o ${DISTDIR}/18f2320.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX}  ${OBJECTFILES_QUOTED_IF_SPACED}     
	
endif


# Subprojects
.build-subprojects:


# Subprojects
.clean-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${OBJECTDIR}
	${RM} -r ${DISTDIR}

# Enable dependency checking
.dep.inc: .depcheck-impl

DEPFILES=$(shell mplabwildcard ${POSSIBLE_DEPFILES})
ifneq (${DEPFILES},)
include ${DEPFILES}
endif

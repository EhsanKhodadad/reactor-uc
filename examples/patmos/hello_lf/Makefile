REACTOR_UC_PATH ?= $(CURDIR)/../../../
LF_MAIN ?= HelloLF

# The name of the LF application inside "./src" to build/run/flash etc.
SRC_GEN_PATH ?= ./src-gen/$(LF_MAIN)
# Enable reactor-uc features


# Execute the LF compiler if build target is "all"
ifeq ($(firstword $(MAKECMDGOALS)),all)
  _ :=  $(shell $(REACTOR_UC_PATH)/lfc/bin/lfc-dev src/$(LF_MAIN).lf)
endif

# ---- Patmos specific configuration ----
include ./src-gen/$(LF_MAIN)/Makefile

SRC = $(REACTOR_UC_PATH)/src/*.c
SRC += $(patsubst %, $(SRC_GEN_PATH)/%, $(LFC_GEN_SOURCES) $(LFC_GEN_MAIN)) 

all:
	patmos-clang $(SRC) -I$(REACTOR_UC_PATH)/include -I$(REACTOR_UC_PATH)/external -I$(SRC_GEN_PATH) -DPLATFORM_PATMOS -DSCHEDULER_DYNAMIC -DEVENT_QUEUE_SIZE=$(EVENT_QUEUE_SIZE) -DREACTION_QUEUE_SIZE=$(REACTION_QUEUE_SIZE) -O2 -o $(LF_MAIN) -Wno-everything


# If no BOARD is found in the environment, use this default:
BOARD ?= native

# Comment this out to disable code in RIOT that does safety checking
# which is not needed in a production environment but helps in the
# development process:
DEVELHELP ?= 1

# Change this to 0 show compiler invocation lines by default:
QUIET ?= 1


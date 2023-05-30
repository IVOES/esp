# Copyright (c) 2011-2021 Columbia University, System Level Design Group
# SPDX-License-Identifier: Apache-2.0

ifeq ("$(ESP_ROOT)","")
$(error ESP_ROOT not set)
endif

ASIC_MEMGEN = $(ESP_ROOT)/tools/asicgen/asic_memgen.py
ASIC_MEMGEN_OUT = ../$(DIRTECH_NAME)/mem_wrappers

MEMGEN = $(ESP_ROOT)/tools/asicgen/asic_plmgen.py
MEMTECH = ../$(DIRTECH_NAME)/mem_wrappers
MEMGEN_OUT = $(ESP_ROOT)/tech/$(TECHLIB)/memgen/slm_gen

mem_wrapper:
	$(ASIC_MEMGEN) $(ASIC_MEMGEN_OUT) | tee $(ASIC_MEMGEN_OUT)/asic_memgen.log

mem_slmgen: socgen/esp/slm_memgen.txt $(MEMGEN)
	@$(MEMGEN) $(MEMTECH) $< $(MEMGEN_OUT) | tee mem_slmgen.log

link_memories:
	cd $(ESP_ROOT)/rtl/sim/asic ; \
        rm verilog; \
	ln -s $(TECH_DIR_PATH)/mem_models verilog ; \
        cd - ; \
	cd $(ESP_ROOT)/rtl/techmap/asic ; \
	rm mem ; \
	ln -s $(TECH_DIR_PATH)/mem_wrappers mem ; \
	cd -

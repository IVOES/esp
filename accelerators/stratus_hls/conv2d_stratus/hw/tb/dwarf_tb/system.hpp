// Copyright (c) 2011-2019 Columbia University, System Level Design Group
// SPDX-License-Identifier: Apache-2.0

#ifndef __SYSTEM_HPP__
#define __SYSTEM_HPP__

#include "conv2d_data.hpp"
#include "fpdata.hpp"
#include "conv2d_conf_info.hpp"
#include "conv2d_debug_info.hpp"
#include "conv2d.hpp"
#include "conv2d_directives.hpp"
#include "sizes.h"
#include "esp_templates.hpp"
#include "utils.hpp"

const size_t MEM_SIZE = 75000000;

#include "core/systems/esp_system.hpp"

#ifdef CADENCE
#include "conv2d_wrap.h"
#endif


class system_t : public esp_system<DMA_WIDTH, MEM_SIZE>
{
public:

    // ACC instance
#ifdef CADENCE
    conv2d_wrapper *acc;
#else
    conv2d *acc;
#endif

    // Constructor
    SC_HAS_PROCESS(system_t);
    system_t(sc_module_name name)
        : esp_system<DMA_WIDTH, MEM_SIZE>(name)
    {
        // ACC
#ifdef CADENCE
        acc = new conv2d_wrapper("conv2d_wrapper");
#else
        acc = new conv2d("conv2d_wrapper");
#endif
        // Binding ACC
        acc->clk(clk);
        acc->rst(acc_rst);
        acc->dma_read_ctrl(dma_read_ctrl);
        acc->dma_write_ctrl(dma_write_ctrl);
        acc->dma_read_chnl(dma_read_chnl);
        acc->dma_write_chnl(dma_write_chnl);
        acc->conf_info(conf_info);
        acc->conf_done(conf_done);
        acc->acc_done(acc_done);
        acc->debug(debug);
    }

    // Processes

    // Configure accelerator
    void config_proc();

    // Load internal memory
    void load_memory();

    // Dump internal memory
    void dump_memory();

    // Validate accelerator results
    int validate();

    void run_pv(int layer, bool fully_connected);
 
    void setup_memory(int target_layer, bool fully_connected);


    // Accelerator-specific data
    /* <<--params-->> */
    int32_t channels;
    int32_t height;
    int32_t width;
    int32_t num_filters;
    int32_t kernel_h;
    int32_t kernel_w;
    int32_t pad_h;
    int32_t pad_w;
    int32_t stride_h;
    int32_t stride_w;
    int32_t dilation_h;
    int32_t dilation_w;
    int32_t do_relu;
    int32_t pool_type;
    int32_t output_h;
    int32_t output_w;
    int32_t output_pool_h;
    int32_t output_pool_w;
    int32_t batch_size;
    
    uint32_t in_words_adj;
    uint32_t weights_words_adj;
    uint32_t bias_words_adj;
    uint32_t out_words_adj;
    uint32_t in_size;
    uint32_t weights_size;
    uint32_t bias_size;
    uint32_t out_size;

    float* input;
    float* weights;
    float* bias;
    float* hw_output;
    float* sw_output;

};

#endif // __SYSTEM_HPP__

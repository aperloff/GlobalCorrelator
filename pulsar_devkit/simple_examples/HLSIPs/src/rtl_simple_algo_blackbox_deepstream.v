// This module describes SIMD Inference
// 4 adders packed into single DSP block
`timescale 100ps/100ps

(* use_dsp = "simd" *)
(* dont_touch = "1" *)
module rtl_simple_algo_blackbox_stream (input             ap_clk, ap_rst, ap_ce, ap_start, ap_continue,
                                        input [10:0]      artl, brtl,
                                        input             artl_empty_n, brtl_empty_n,
                                        input             artl_read, brtl_read,
                                        output            ap_done, ap_idle, ap_ready,
                                        output reg [10:0] z,
                                        output            z_full_n, z_write);

    wire ce = ap_ce;

    reg       dly1;
    reg [2:0] cnt;

    always @ (posedge ap_clk)
        if (ap_rst)
            begin
                z     <= 0;
                cnt   <= 0;
                dly1  <= 0;
            end
        else if (ce)
            begin
                z[10:0] <= artl[10:0] + brtl[10:0];
                dly1    <= ap_start || dly1;
                if (cnt==4)
                    cnt <= 0;
                else
                    cnt <= cnt+1;
            end

    assign ap_ready  = ap_start || dly1;//ap_ready;//ap_start && ~dly1;
    assign z_write   = dly1 && cnt!=2;
    //assign artl_read = 1'b1;
    //assign brtl_read = 1'b1;
    //These are never used later on by the HLS created code
    //A wire may be created for them, but HLS doesn't hook them up
    //assign z_full_n  = 1'b1;
    //assign artl_empty_n = 1'b1;
    //assign brtl_empty_n = 1'b1;
    assign ap_done   = dly1;
    assign ap_idle   = ~ap_ready;

endmodule // rtl_simple_algo_blackbox

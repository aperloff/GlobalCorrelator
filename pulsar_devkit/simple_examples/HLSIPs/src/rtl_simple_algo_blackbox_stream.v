// This module describes SIMD Inference
// 4 adders packed into single DSP block
`timescale 100ps/100ps

(* use_dsp = "simd" *)
(* dont_touch = "1" *)
module rtl_simple_algo_blackbox_stream (input             ap_clk, ap_rst, ap_ce, ap_start, ap_continue,
                                        input [43:0]      artl, brtl,
                                        input             artl_empty_n, brtl_empty_n,
                                        input             artl_read, brtl_read,
                                        output            ap_done, ap_idle, ap_ready,
                                        output reg [43:0] z,
                                        output            z_full_n, z_write);

    wire ce = ap_ce;

    reg [10:0] areg1, areg2, areg3, areg4;
    reg [10:0] breg1, breg2, breg3, breg4;
    reg        dly1, dly2;

    always @ (posedge ap_clk)
        if (ap_rst)
            begin
                z <= 0;
                areg1 <= 0;
                areg2 <= 0;
                areg3 <= 0;
                areg4 <= 0;
                breg1 <= 0;
                breg2 <= 0;
                breg3 <= 0;
                breg4 <= 0;
                dly1  <= 0;
                dly2  <= 0;
            end
        else if (ce)
            begin
                z[10:0]    <= areg1 + breg1;
                z[21:11]   <= areg2 + breg2;
                z[32:22]   <= areg3 + breg3;
                z[43:33]   <= areg4 + breg4;
                areg1 <= artl[10:0];
                areg2 <= artl[21:11];
                areg3 <= artl[32:22];
                areg4 <= artl[43:33];
                breg1 <= brtl[10:0];
                breg2 <= brtl[21:11];
                breg3 <= brtl[32:22];
                breg4 <= brtl[43:33];
                dly1  <= ap_start && ~dly1;
                dly2  <= dly1;
            end

    assign ap_ready  = ap_start && ~dly1;
    assign z_write   = dly2;
    //These are never used later on by the HLS created code
    //A wire may be created for them, but HLS doesn't hook them up
    assign z_full_n  = 1'b1;
    assign ap_done   = dly2;
    assign ap_idle   = (ap_start^ap_ready) || (ap_start==1'b0 && ap_ready==1'b1) || (ap_start==1'b0 && ap_ready==1'b0);

endmodule // rtl_simple_algo_blackbox

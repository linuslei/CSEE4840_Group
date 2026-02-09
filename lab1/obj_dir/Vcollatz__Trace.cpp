// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Tracing implementation internals
#include "verilated_vcd_c.h"
#include "Vcollatz__Syms.h"


//======================

void Vcollatz::traceChg(VerilatedVcd* vcdp, void* userthis, uint32_t code) {
    // Callback from vcd->dump()
    Vcollatz* t = (Vcollatz*)userthis;
    Vcollatz__Syms* __restrict vlSymsp = t->__VlSymsp;  // Setup global symbol table
    if (vlSymsp->getClearActivity()) {
        t->traceChgThis(vlSymsp, vcdp, code);
    }
}

//======================


void Vcollatz::traceChgThis(Vcollatz__Syms* __restrict vlSymsp, VerilatedVcd* vcdp, uint32_t code) {
    Vcollatz* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    int c = code;
    if (0 && vcdp && c) {}  // Prevent unused
    // Body
    {
        if (VL_UNLIKELY((2U & vlTOPp->__Vm_traceActivity))) {
            vlTOPp->traceChgThis__2(vlSymsp, vcdp, code);
        }
        vlTOPp->traceChgThis__3(vlSymsp, vcdp, code);
    }
    // Final
    vlTOPp->__Vm_traceActivity = 0U;
}

void Vcollatz::traceChgThis__2(Vcollatz__Syms* __restrict vlSymsp, VerilatedVcd* vcdp, uint32_t code) {
    Vcollatz* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    int c = code;
    if (0 && vcdp && c) {}  // Prevent unused
    // Body
    {
        vcdp->chgBit(c+1,(vlTOPp->collatz__DOT__run));
        vcdp->chgBus(c+9,(vlTOPp->collatz__DOT__unnamedblk1__DOT__next_dout),32);
    }
}

void Vcollatz::traceChgThis__3(Vcollatz__Syms* __restrict vlSymsp, VerilatedVcd* vcdp, uint32_t code) {
    Vcollatz* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    int c = code;
    if (0 && vcdp && c) {}  // Prevent unused
    // Body
    {
        vcdp->chgBit(c+17,(vlTOPp->clk));
        vcdp->chgBit(c+25,(vlTOPp->go));
        vcdp->chgBus(c+33,(vlTOPp->n),32);
        vcdp->chgBus(c+41,(vlTOPp->dout),32);
        vcdp->chgBit(c+49,(vlTOPp->done));
    }
}

// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See Vcollatz.h for the primary calling header

#include "Vcollatz.h"
#include "Vcollatz__Syms.h"

//==========

VL_CTOR_IMP(Vcollatz) {
    Vcollatz__Syms* __restrict vlSymsp = __VlSymsp = new Vcollatz__Syms(this, name());
    Vcollatz* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Reset internal values
    
    // Reset structure values
    _ctor_var_reset();
}

void Vcollatz::__Vconfigure(Vcollatz__Syms* vlSymsp, bool first) {
    if (0 && first) {}  // Prevent unused
    this->__VlSymsp = vlSymsp;
}

Vcollatz::~Vcollatz() {
    delete __VlSymsp; __VlSymsp=NULL;
}

void Vcollatz::eval() {
    VL_DEBUG_IF(VL_DBG_MSGF("+++++TOP Evaluate Vcollatz::eval\n"); );
    Vcollatz__Syms* __restrict vlSymsp = this->__VlSymsp;  // Setup global symbol table
    Vcollatz* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
#ifdef VL_DEBUG
    // Debug assertions
    _eval_debug_assertions();
#endif  // VL_DEBUG
    // Initialize
    if (VL_UNLIKELY(!vlSymsp->__Vm_didInit)) _eval_initial_loop(vlSymsp);
    // Evaluate till stable
    int __VclockLoop = 0;
    QData __Vchange = 1;
    do {
        VL_DEBUG_IF(VL_DBG_MSGF("+ Clock loop\n"););
        vlSymsp->__Vm_activity = true;
        _eval(vlSymsp);
        if (VL_UNLIKELY(++__VclockLoop > 100)) {
            // About to fail, so enable debug to see what's not settling.
            // Note you must run make with OPT=-DVL_DEBUG for debug prints.
            int __Vsaved_debug = Verilated::debug();
            Verilated::debug(1);
            __Vchange = _change_request(vlSymsp);
            Verilated::debug(__Vsaved_debug);
            VL_FATAL_MT("collatz.sv", 1, "",
                "Verilated model didn't converge\n"
                "- See DIDNOTCONVERGE in the Verilator manual");
        } else {
            __Vchange = _change_request(vlSymsp);
        }
    } while (VL_UNLIKELY(__Vchange));
}

void Vcollatz::_eval_initial_loop(Vcollatz__Syms* __restrict vlSymsp) {
    vlSymsp->__Vm_didInit = true;
    _eval_initial(vlSymsp);
    vlSymsp->__Vm_activity = true;
    // Evaluate till stable
    int __VclockLoop = 0;
    QData __Vchange = 1;
    do {
        _eval_settle(vlSymsp);
        _eval(vlSymsp);
        if (VL_UNLIKELY(++__VclockLoop > 100)) {
            // About to fail, so enable debug to see what's not settling.
            // Note you must run make with OPT=-DVL_DEBUG for debug prints.
            int __Vsaved_debug = Verilated::debug();
            Verilated::debug(1);
            __Vchange = _change_request(vlSymsp);
            Verilated::debug(__Vsaved_debug);
            VL_FATAL_MT("collatz.sv", 1, "",
                "Verilated model didn't DC converge\n"
                "- See DIDNOTCONVERGE in the Verilator manual");
        } else {
            __Vchange = _change_request(vlSymsp);
        }
    } while (VL_UNLIKELY(__Vchange));
}

VL_INLINE_OPT void Vcollatz::_sequent__TOP__1(Vcollatz__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vcollatz::_sequent__TOP__1\n"); );
    Vcollatz* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Variables
    CData/*0:0*/ __Vdly__collatz__DOT__run;
    IData/*31:0*/ __Vdly__dout;
    // Body
    __Vdly__collatz__DOT__run = vlTOPp->collatz__DOT__run;
    __Vdly__dout = vlTOPp->dout;
    if (vlTOPp->go) {
        __Vdly__dout = vlTOPp->n;
        vlTOPp->done = (1U == vlTOPp->n);
        __Vdly__collatz__DOT__run = (1U != vlTOPp->n);
    } else {
        if (vlTOPp->collatz__DOT__run) {
            vlTOPp->collatz__DOT__unnamedblk1__DOT__next_dout 
                = ((1U & vlTOPp->dout) ? ((IData)(1U) 
                                          + ((IData)(3U) 
                                             * vlTOPp->dout))
                    : (vlTOPp->dout >> 1U));
            __Vdly__dout = vlTOPp->collatz__DOT__unnamedblk1__DOT__next_dout;
            if ((1U == vlTOPp->collatz__DOT__unnamedblk1__DOT__next_dout)) {
                vlTOPp->done = 1U;
                __Vdly__collatz__DOT__run = 0U;
            }
        }
    }
    vlTOPp->dout = __Vdly__dout;
    vlTOPp->collatz__DOT__run = __Vdly__collatz__DOT__run;
}

void Vcollatz::_eval(Vcollatz__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vcollatz::_eval\n"); );
    Vcollatz* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    if (((IData)(vlTOPp->clk) & (~ (IData)(vlTOPp->__Vclklast__TOP__clk)))) {
        vlTOPp->_sequent__TOP__1(vlSymsp);
        vlTOPp->__Vm_traceActivity = (2U | vlTOPp->__Vm_traceActivity);
    }
    // Final
    vlTOPp->__Vclklast__TOP__clk = vlTOPp->clk;
}

void Vcollatz::_eval_initial(Vcollatz__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vcollatz::_eval_initial\n"); );
    Vcollatz* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->__Vclklast__TOP__clk = vlTOPp->clk;
}

void Vcollatz::final() {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vcollatz::final\n"); );
    // Variables
    Vcollatz__Syms* __restrict vlSymsp = this->__VlSymsp;
    Vcollatz* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
}

void Vcollatz::_eval_settle(Vcollatz__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vcollatz::_eval_settle\n"); );
    Vcollatz* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
}

VL_INLINE_OPT QData Vcollatz::_change_request(Vcollatz__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vcollatz::_change_request\n"); );
    Vcollatz* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    // Change detection
    QData __req = false;  // Logically a bool
    return __req;
}

#ifdef VL_DEBUG
void Vcollatz::_eval_debug_assertions() {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vcollatz::_eval_debug_assertions\n"); );
    // Body
    if (VL_UNLIKELY((clk & 0xfeU))) {
        Verilated::overWidthError("clk");}
    if (VL_UNLIKELY((go & 0xfeU))) {
        Verilated::overWidthError("go");}
}
#endif  // VL_DEBUG

void Vcollatz::_ctor_var_reset() {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vcollatz::_ctor_var_reset\n"); );
    // Body
    clk = VL_RAND_RESET_I(1);
    go = VL_RAND_RESET_I(1);
    n = VL_RAND_RESET_I(32);
    dout = VL_RAND_RESET_I(32);
    done = VL_RAND_RESET_I(1);
    collatz__DOT__run = VL_RAND_RESET_I(1);
    collatz__DOT__unnamedblk1__DOT__next_dout = VL_RAND_RESET_I(32);
    __Vm_traceActivity = 0;
}

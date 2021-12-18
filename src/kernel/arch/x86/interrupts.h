#pragma once

#include <stdbool.h>
#include <uavohottbridge.h>

struct interrupt_frame{
    uword_t ip;
    uword_t cs;
    uword_t flags;
    uword_t sp;
    uword_t ss;
};

void interrupt_handler(struct interrupt_frame *frame);
bool handle_interrupt(void);

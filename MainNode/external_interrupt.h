//external_interrupt.h
#ifndef EXINT_H
#define EXINT_H

#define EINT0_LED 16
#define EINT1_LED 17
#define EINT2_LED 18
#define EINT3_LED 19
void eint0_isr(void) __irq;
void eint1_isr(void) __irq;
void eint2_isr(void) __irq;
void eint3_isr(void) __irq;

void Enable_EINT0(void);
void Enable_EINT1(void);
void Enable_EINT2(void);
void Enable_EINT3(void);

#endif

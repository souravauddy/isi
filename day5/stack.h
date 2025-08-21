#ifndef STACK_H
#define STACK_H

#define INITIAL_STACK_SIZE 5

typedef int DATA;
/* Some other possibilities:
 * typedef char *DATA;
 * typedef char[BUF_LEN] DATA;
 * typedef struct { ... } DATA;
 */
typedef struct {
    unsigned int capacity, top;
    DATA *contents;
} STACK;


#if 0
extern STACK create_stack(); 
extern void push(STACK *s, DATA d);
extern DATA pop(STACK *s);
#else
extern STACK *create_stack(unsigned int capacity);
extern int push(STACK *s, DATA *d);
extern int pop(STACK *s, DATA *d);
#endif

extern void print_stack(STACK *s);
extern void delete_stack(STACK *s);

#endif /* STACK_H */

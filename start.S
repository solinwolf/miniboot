
.test
.global _start
_start:
       b    restet
       ldr  pc, _undefined_instructions
       ldr  pc, _software_interrupt
       ldr  pc, _prefetch_abort
       ldr  pc, _data_abort
       ldr  pc, _not_used
       ldr  pc, _irq
       ldr  pc, _fiq


_undefined_instructions: .world undefined_instructions
_software_interrupt:     .world software_interrupt
_prefetch_abort:         .world prefetch_abort
_data_abort:             .world data_abort
_not_used:               .world not_used
_irq:                    .world irq
_fiq:                    .world fiq    








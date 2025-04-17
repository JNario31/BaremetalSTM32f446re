# Understanding the Linker Script
## Memory map of the STM32F446
Linker scripts and Startup files revolve around the SRAM and the Flash memory as they are involved in program storage
![image](https://github.com/user-attachments/assets/63cdc72c-8b35-4fbb-a649-a91ad6dc5d3c)

### Flash Memory
Starts at 0x8000000, non-volatile read only memory, stores the executable code.

### SRAM
Designed for high speed and latency, this is a volatile, read and write memory. The SRAM starts at 0x200000

### Linker Script

Linker scripts: 
- Define memory layout
- Where Different sections of firmware are to be placed in memory (Code, data, uninitalized data)
  - Linker scripts do populate this data, this is done by the startup code

The assembler generates object files from the source code, containing code and data sections for the firmware. These object files have unresolved 
internal references to variables and functions. It is the linker's job to a combine these files into a cohesive output file.

#### Object file sections:
- Loadable sections: Content to be loaded into memory at runtime
- Allocated sections: Does not carry content, signal certain area of memory to be reserved, typically for data defined at runtime
- Non-loadable, non-allocated sections: Typically contains debugging info, metadata

Part of the linking process is the determination of two types of addresses of allocatable and loadable section:
- Virtual Memory Address (VMA)
  - Where the section will reside in memory during execution of the output file
  - It is the runtime address used by the system to access the section's data instructions
- Load Memory Address (LMA)
  - Where the section is physically located in the memory

### Linker Script Key Components
- Memory Layout: Specifies types of memory in MCU, flash memory, SRAM, its starting addresses and sizes
- Section Definitions:
  - ```.text``` 
    - hold executable instructions of the program
    - read only
    - placed in flash
  - ```.bss```
    - for uninitialized global and static variables
    - read-write, typically 0-initialized
  - ```.data```
    - for initialzied global and static variables
    - read-write, copied from flash memory to SRAM
    - copying of values from flash memory to SRAM done by startup code
  - ```.rodata```
    - for constant data
    - read only, stored in flash memory
  - ```.heap``` and ```.stack```
    - for dynamic memory allocation (malloc,free), and function call stacks
- Directives:
  - Memory Directive: delineates MCU memory regions, characterized by name, start address, and size
```
MEMORY
  {
    name(attributes) : ORIGIN = origin, LENGTH = length
  }
```
  - name: memory region identifier
  - attributes: access permissions for region (r/w/e)
  - ORIGIN: start address
  - LENGTH: size
```
MEMORY
{
FLASH (rx) : ORIGIN = 0x08000000, LENGTH = 2M
SRAM (rwx) : ORIGIN = 0x20000000, LENGTH = 128K
}
```
  - Entry: Specifies entry point (first piece of code to execute)
```ENTRY(Reset_Handler)```
    - Reset_Handler takes care of initalizing the system and jumping to the main program
  - Sections:
```
SECTIONS
  {
    .output_section_name address :
  {
  input_section_information
  } >memory_region [AT>load_address] [ALIGN(expression)] [:phdr_
    expression] [=fill_expression]
  }
```
   - Parameters:
     - output_section_name: name given to output section defined (.text, .data, .bss)
     - addresss: optional, specifies start address of each memory section, often left for the linker to determine
     - input_section_information: which input sections should be included in the output file
       - wildcards (*) can be used to include all text files, ```*(.text)```
     - '>memory_region': memory region defined in memory block of linker script
     - '[AT>load_address]': optional, specifies load address (specifc scenarios when execution address differs from load address
     - '[ALIGN(expression)]': optional, aligns start of section to an address that is a multiple of the value specified in the expression
     - '[:phdr_expression]': optional, associates the section with a program header,
     - '[=fill_expression]': optional, specifies byte value to fill gaps between sections 




# Stream Engine
* It preloads the memory from memory to make sure that it doesn't make the CPU wait for it
* It fetchs data inn advance so CPU works faster without waiting it
* The Streaming Engine in the TI C67x DSP processor is a hardware mechanism designed to efficiently transfer data from L2 memory (Level 2 cache or external memory) to the CPU (C67x core) with higher bandwidth and reduced latency compared to traditional load/store instructions.
* The Streaming Engine achieves efficient data transfer through the following mechanisms:
    1. DMA (Direct Memory Access):
        * The C67x processor uses dedicated DMA controllers to move large chunks of data from external memory to internal memory without CPU intervention.
        * This allows the CPU to focus on computation while data transfer happens in parallel.
    2. Circular Buffering:
        * Streaming Engines support circular buffering, allowing continuous data flow without manual intervention, useful for real-time applications.
    3. Double Buffering:
        * Two memory buffers are used to overlap data transfer with computation, ensuring a constant flow of data.
        * While the CPU processes one buffer, the Streaming Engine loads the next chunk of data.
    4. EDMA (Enhanced Direct Memory Access):
        * The TI C67x processor provides EDMA, which offers better performance by allowing multiple channels of data transfer with minimal CPU involvement.
## Advantage 
* Low latency
* High Throughput
* Reduce CPU Load
* Efficient Real time processing
* Better Cache utilization
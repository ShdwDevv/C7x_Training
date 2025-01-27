## Prerequisites
* DMA : [Click Here](../DMA/dma.md)

# Unified Data Memory Access
* It is an advancement of DMA that handle the packet based data
* Here the data is segmented and then reassembled
* By sending the data in smaller packet we can do the e=data trnansfer faster which each packet is travel in different path 
* UDMA is used for devices that need data in smaller, well-organized chunks (like Ethernet cards or audio/video devices).
* If any of the packet is lost then we can resend it 
* DMA have one or two channels so there will be one or two transfer occur at a time
* But UDMA have multiple TX and RX channel , so the data transfer happen concurrently and improve efficiency
* DMA does not focus to track the individual data transfer , its main intention to finish the transfer as soon as possible , UDMA tracks the stae of each channel and packet
* DMA eg : Transfer data from sensor to memory
* UDMA  eg : ethernet , audio/video streaming and networking
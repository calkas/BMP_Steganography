# BMP_Steganography Project

The main purpose of this project is to hide information represented as a string in *.bmp file and decode it later.

This project consists of two applications:
 - SteganoEncoder - hides string in `*Converted.bmp` file
 - SteganoDecoder - decodes data from `*Converted.bmp` file

## Working Diagram

```plantuml

@startuml
rectangle textToHide
file OriginalBmpFile 
node SteganoEncoder #pink
node SteganoDecoder #lightblue
file ConvertedBmpFile
rectangle decodedText

textToHide -> SteganoEncoder
OriginalBmpFile -down-> SteganoEncoder

SteganoEncoder -> ConvertedBmpFile


ConvertedBmpFile -> SteganoDecoder
SteganoDecoder -down-> decodedText
@enduml

```

# Links

[Steganography](https://en.wikipedia.org/wiki/Steganography)

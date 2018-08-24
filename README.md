# bin-zip
Script to compress and decompress the segmented binary file

## Instruction
There are four ways to run the script:
### run the script using config.ini
```
./binzip.exe 
```
The script will read the ./config.ini and the first line is the input folder, the second line is the output folder, the third line is zip flag, 0 for compress, 1 for decompress.
### compress by input root
```
./binzip.exe {$parent-root}/input_folder
```
The script will compress files in the input root and store the compressed data to {$parent-root}/input_folder_compressed.
### compress by input root and output root
```
./binzip.exe {$input-root} {$output-root}
```
The script will compress files in the input root and store the compressed data to the output root.
### compress/decompress by operation parameter
```
./binzip.exe [-c|-d] {$input-root} {$output-root}
```
Compress(-c) or Decompress(-d) the files in the input root to the output root